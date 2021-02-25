//================================================================================
//
// アリ処理 (ant.cpp)
// Author : 後藤慎之助(行動AI、エフェクト) / 樋宮匠(階層構造、アニメーション制御)
//
//================================================================================

//========================
// インクルードファイル
//========================
#include "ant.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "animation.h"
#include "block.h"
#include "effect3d.h"
#include "bullet.h"
#include "library.h"
#include "debug.h"
#include "score.h"
#include "game.h"
#include "modelEffect.h"
#include "player.h"
#include "bullet.h"
#include "item.h"
#include "sound.h"

//========================================
// 静的メンバ変数宣言
//========================================
LPD3DXMESH CAnt::m_pMesh[TYPE_MAX][PARTS_MAX] = {};
LPD3DXBUFFER CAnt::m_pBuffMat[TYPE_MAX][PARTS_MAX] = {};
DWORD CAnt::m_nNumMat[TYPE_MAX][PARTS_MAX] = {};

//=============================================================================
// コンストラクタ
// Author : 後藤慎之助
//=============================================================================
CAnt::CAnt() :CCharacter(OBJTYPE::OBJTYPE_ENEMY)
{
    m_type = TYPE_WHITE;
    m_move = DEFAULT_VECTOR;
    m_nScore = 0;
    m_nOrbs = 0;

    m_patrolCentralPos = DEFAULT_VECTOR;
    m_patrolDestPos = DEFAULT_VECTOR;
    m_nPatrolDistance = 0;
    m_nCntTime = 0;

    m_bWallRun = false;
    m_fSpeed = 0.0f;
    m_rotDest = DEFAULT_VECTOR;
    m_rotMin = DEFAULT_VECTOR;

    m_bWarning = false;
    m_fDiscoveryDistance = 0.0f;

    m_bAttack = false;
    m_attackAI = ATTACK_AI_WAIT;
}

//=============================================================================
// デストラクタ
// Author : 後藤慎之助
//=============================================================================
CAnt::~CAnt()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CAnt::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    // パーツ数を設定
    SetPartNum(PARTS_MAX);

    for (int nCount = 0; nCount < PARTS_MAX; nCount++)
    {
        BindMesh(CCharacter::TRIBE_ANT, nCount, m_pMesh[m_type][nCount], m_pBuffMat[m_type][nCount], m_nNumMat[m_type][nCount]);
    }

    // 座標・親子関係の読み込み
    LoadModelData("./data/ANIMATION/motion_ant.txt");

    CCharacter::Init(pos, size);

    return S_OK;
}

//=============================================================================
// 終了処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::Uninit(void)
{
    CCharacter::Uninit();
}

//=============================================================================
// 更新処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::Update(void)
{
    // 行動
    Movement();

    // アニメーションの更新
    CCharacter::Update();

    // 体力が0以下なら、スコア加算し、未使用に
    if (GetLife() <= 0)
    {
        // 位置と向きを取得
        D3DXVECTOR3 pos = DEFAULT_VECTOR;
        D3DXVECTOR3 rot = DEFAULT_VECTOR;
        pos = GetPos();
        rot = GetRot();

        // 粉砕
        DeathCrush(pos, rot);

        // ミッションクリア数に加算する
        AddMissionClear();

        // ラストヒットがプレイヤーなら
        if (GetLastHit() == LAST_HIT_PLAYER)
        {
            // オーブをバラまく
            ScatterOrbs();

            // スコア加算
            CScore *pScore = CGame::GetScore();
            pScore->AddScore(m_nScore);

            // 一定確率で、回復アイテムを落とす
            int nRandNum = GetRandNum(100, 1);
            if (nRandNum <= ANT_DROP_HEAL_ITEM)
            {
                CItem::Create(pos, DEFAULT_VECTOR, CItem::TYPE_HEAL);
            }
        }

        // 終了処理
        Uninit();
    }
}

//=============================================================================
// 行動処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::Movement(void)
{
    // 位置と向きを取得
    D3DXVECTOR3 pos = DEFAULT_VECTOR;
    D3DXVECTOR3 rot = DEFAULT_VECTOR;
    pos = GetPos();
    rot = GetRot();

    // モーションをまずは待機にする
    GetAnimation()->SetAnimation(ANIM_IDLE);

    // 回転制御
    rot = RotControl(rot);

    // 1F前の位置を記憶
    SetPosOld(pos);

    // 巡回AI処理
    pos = PatrolAI(pos);

    // 警戒AI処理
    rot = WarningAI(pos, rot);

    // 攻撃AI処理
    if (CGame::GetState() == CGame::STATE_NORMAL)
    {
        pos = AttackAI(pos, rot);
    }

    // 移動量と位置を結びつける
    pos += m_move;

    // 地面より上なら
    if (pos.y > 0.0f)
    {
        // 重力
        m_move.y -= GRAVITY;
    }
    else
    {
        // 壁走りはしていない
        m_bWallRun = false;

        // 地面にいるなら、重力をかけない
        pos.y = 0.0f;
        m_move.y = 0.0f;
    }

    // ブロックへの当たり判定
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_BLOCK);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_BLOCK); nCntScene++)
    {
        // 中身があるなら
        if (pScene != NULL)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // ブロックにキャスト
            CBlock *pBlock = (CBlock*)pScene;

            // 敵が壁走りできるブロックなら
            if (pBlock->GetEnemyWallRun() == true)
            {
                // ブロックの位置と大きさを取得
                D3DXVECTOR3 blockPos = pBlock->GetPos();
                D3DXVECTOR3 blockSize = pBlock->GetCollisionSize();

                // ブロックとの当たり判定を計算
                BLOCK_HIT_INFO blockHitInfo;
                blockHitInfo.hitSurface = HIT_SURFACE_NONE;
                blockHitInfo.pos = pos;
                blockHitInfo = (BlockCollision3D(&pos, &GetPosOld(), &blockPos,
                    &GetActiveCollisionSize(), &blockSize));

                // ブロックの当たり判定で計算した位置を、結びつける
                pos = blockHitInfo.pos;

                // ヒット面よって、壁走りの仕様を変える
                //=====================================================================================
                switch (blockHitInfo.hitSurface)
                {
                case HIT_SURFACE_TOP:

                    // 壁走りはしていない
                    m_bWallRun = false;

                    // 重力を考慮しない
                    m_move.y = 0.0f;

                    break;

                case HIT_SURFACE_LEFT:

                    // 壁走り
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // 傾く
                    rot.x += ANT_TILT_SPEED;

                    // 向く方向を変える
                    m_rotDest.y = D3DXToRadian(270.0f);

                    break;

                case HIT_SURFACE_BACK:

                    // 壁走り
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // 傾く
                    rot.x += ANT_TILT_SPEED;

                    // 向く方向を変える
                    m_rotDest.y = D3DXToRadian(0.0f);

                    break;

                case HIT_SURFACE_RIGHT:

                    // 壁走り
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // 傾く
                    rot.x += ANT_TILT_SPEED;

                    // 向く方向を変える
                    m_rotDest.y = D3DXToRadian(90.0f);

                    break;

                case HIT_SURFACE_FRONT:

                    // 壁走り
                    pos.y += m_fSpeed;
                    m_bWallRun = true;
                    m_move.y = 0.0f;

                    // 傾く
                    rot.x += ANT_TILT_SPEED;

                    // 向く方向を変える
                    m_rotDest.y = D3DXToRadian(180.0f);

                    break;
                }
                //=====================================================================================
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
        else
        {
            // 中身がないなら、そこで処理を終える
            break;
        }
    }

    // マップ制限
    CGame::MAP_LIMIT mapLimit = CGame::GetMapLimit();
    if (pos.x - GetActiveCollisionSize().x < mapLimit.fWest)
    {
        pos.x = mapLimit.fWest + GetActiveCollisionSize().x;
    }
    if (pos.x + GetActiveCollisionSize().x > mapLimit.fEast)
    {
        pos.x = mapLimit.fEast - GetActiveCollisionSize().x;
    }
    if (pos.z - GetActiveCollisionSize().z < mapLimit.fSouth)
    {
        pos.z = mapLimit.fSouth + GetActiveCollisionSize().z;
    }
    if (pos.z + GetActiveCollisionSize().z > mapLimit.fNorth)
    {
        pos.z = mapLimit.fNorth - GetActiveCollisionSize().z;
    }

    // 壁走りしていないなら
    if (m_bWallRun == false)
    {
        // 傾きを直す
        rot.x -= ANT_TILT_SPEED;
    }

    // 傾き制限
    if (rot.x > ANT_TILT_LIMIT)
    {
        rot.x = ANT_TILT_LIMIT;
    }
    else if (rot.x < 0.0f)
    {
        rot.x = 0.0f;
    }

    // 位置と向きを反映
    SetPos(pos);
    SetRot(rot);

    // 当たり判定の位置を更新
    UpdateCollisionPos();

#ifdef COLLISION_TEST
    for (int nCnt = 0; nCnt < GetCntCollision(); nCnt++)
    {
        COLLISION collision = GetCollision(nCnt);
        CDebug::Create(collision.pos, collision.size, CDebug::TYPE_MOMENT);
    }
    CDebug::Create(pos, GetActiveCollisionSize(), CDebug::TYPE_MOMENT);
#endif // COLLISION_TEST
}

//=============================================================================
// 当たり判定の位置を更新
// Author : 後藤慎之助
//=============================================================================
void CAnt::UpdateCollisionPos(void)
{
    // 体の位置取得
    D3DXVECTOR3 bodyPos = D3DXVECTOR3(GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._43);

    // 腹の位置取得
    D3DXVECTOR3 stomachPos = D3DXVECTOR3(GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._43);

    // 右触角の位置取得
    D3DXVECTOR3 rightTactilePos = D3DXVECTOR3(GetParts(CAnt::PARTS_TACTILE_RIGHT)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_TACTILE_RIGHT)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_TACTILE_RIGHT)->GetWorldMtx()._43);

    // 左触角の位置取得
    D3DXVECTOR3 leftTactilePos = D3DXVECTOR3(GetParts(CAnt::PARTS_TACTILE_LEFT)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_TACTILE_LEFT)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_TACTILE_LEFT)->GetWorldMtx()._43);

    // 右牙の位置取得
    D3DXVECTOR3 rightFangPos = D3DXVECTOR3(GetParts(CAnt::PARTS_FANG_RIGHT)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_FANG_RIGHT)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_FANG_RIGHT)->GetWorldMtx()._43);

    // 左牙の位置取得
    D3DXVECTOR3 leftFangPos = D3DXVECTOR3(GetParts(CAnt::PARTS_FANG_LEFT)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_FANG_LEFT)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_FANG_LEFT)->GetWorldMtx()._43);

    // 種類ごとに、当たり判定の位置を更新
    switch (m_type)
    {
    case TYPE_WHITE:
        SetCollisionPos(0, GetPos());
        break;
    case TYPE_BLACK:
        SetCollisionPos(0, bodyPos);
        SetCollisionPos(1, stomachPos);
        SetCollisionPos(2, rightTactilePos);
        SetCollisionPos(3, leftTactilePos);
        SetCollisionPos(4, rightFangPos);
        SetCollisionPos(5, leftFangPos);
        break;
    }
}

//=============================================================================
// 回転制御
// Author : 後藤慎之助
//=============================================================================
D3DXVECTOR3 CAnt::RotControl(D3DXVECTOR3 rot)
{
    // 返す回転量
    D3DXVECTOR3 returnRot = rot;

    // 1F前と座標が違うなら
    if (GetPosOld() != GetPos())
    {
        // 歩きにする
        GetAnimation()->SetAnimation(ANIM_WALK);

        // 1F前の位置と、現在の位置を比較し、角度を求める
        float fAngle = atan2((GetPosOld().x - GetPos().x), (GetPosOld().z - GetPos().z));

        // 1F前とX座標またはZ座標が違うなら
        if (GetPosOld().x != GetPos().x || GetPosOld().z != GetPos().z)
        {
            // 壁走りしていないなら
            if (m_bWallRun == false)
            {
                // 求めた角度を向くようにする
                m_rotDest.y = fAngle;
            }
        }

        // 回転の制限
        if (returnRot.y > D3DX_PI)
        {
            returnRot.y -= D3DX_PI * 2;
        }
        if (returnRot.y < -D3DX_PI)
        {
            returnRot.y += D3DX_PI * 2;
        }

        m_rotMin.y = m_rotDest.y - returnRot.y;

        // 目的の角度の回転を制限
        if (m_rotMin.y > D3DX_PI)
        {
            m_rotDest.y -= D3DX_PI * 2;
        }
        if (m_rotMin.y < -D3DX_PI)
        {
            m_rotDest.y += D3DX_PI * 2;
        }

        // 回転の制限
        if (returnRot.y > D3DX_PI)
        {
            returnRot.y -= D3DX_PI * 2;
        }
        if (returnRot.y < -D3DX_PI)
        {
            returnRot.y += D3DX_PI * 2;
        }

        if (fabsf(m_rotMin.y) < 0)
        {
            m_rotMin.y = m_rotDest.y;
        }
        else
        {
            returnRot.y += (m_rotDest.y - returnRot.y) * ANT_TURN_SPEED;
        }
    }

    return returnRot;
}

//=============================================================================
// 巡回AI処理
// Author : 後藤慎之助
//=============================================================================
D3DXVECTOR3 CAnt::PatrolAI(D3DXVECTOR3 pos)
{
    // 返す位置を決める
    D3DXVECTOR3 returnPos = pos;

    // 警戒中でないなら
    if (m_bWarning == false)
    {
        // 目的の位置までの距離を求める
        float fDistance = sqrtf(
            powf((m_patrolDestPos.x - pos.x), 2) +
            powf((m_patrolDestPos.z - pos.z), 2));

        // 距離が目的の位置に近いなら
        if (fDistance <= ANT_CONSIDER_CLOSE_DEST)
        {
            // カウンタを加算
            m_nCntTime++;

            // 一定カウンタで、次の目的地を決める
            if (m_nCntTime >= ANT_CHANGE_MOVE_IN_PATROL)
            {
                // カウンタをリセット
                m_nCntTime = 0;

                // 次の目的地を決める
                float fPosX = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.x;
                float fPosZ = float(rand() % m_nPatrolDistance) - float(rand() % m_nPatrolDistance) + m_patrolCentralPos.z;

                // マップ制限
                CGame::MAP_LIMIT mapLimit = CGame::GetMapLimit();
                if (fPosX - GetActiveCollisionSize().x < mapLimit.fWest)
                {
                    fPosX = mapLimit.fWest + GetActiveCollisionSize().x;
                }
                if (fPosX + GetActiveCollisionSize().x > mapLimit.fEast)
                {
                    fPosX = mapLimit.fEast - GetActiveCollisionSize().x;
                }
                if (fPosZ - GetActiveCollisionSize().z < mapLimit.fSouth)
                {
                    fPosZ = mapLimit.fSouth + GetActiveCollisionSize().z;
                }
                if (fPosZ + GetActiveCollisionSize().z > mapLimit.fNorth)
                {
                    fPosZ = mapLimit.fNorth - GetActiveCollisionSize().z;
                }

                // 次の目的地を、メンバ変数に結びつける
                m_patrolDestPos = D3DXVECTOR3(fPosX, 0.0f, fPosZ);
            }
        }
        // 距離が目的の位置より遠いなら
        else
        {
            // カウンタをリセット
            m_nCntTime = 0;

            // 現在の位置と、目的地までの角度を求める
            float fAngle = atan2((GetPos().x - m_patrolDestPos.x), (GetPos().z - m_patrolDestPos.z));

            // 移動量を決める
            D3DXVECTOR3 move = D3DXVECTOR3(-sinf(fAngle)*m_fSpeed, 0.0f, -cosf(fAngle)*m_fSpeed);

            // 位置に移動量を結びつける
            returnPos += move;
        }
    }

    return returnPos;
}

//=============================================================================
// 警戒AI処理
// Author : 後藤慎之助
//=============================================================================
D3DXVECTOR3 CAnt::WarningAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // 返す向き
    D3DXVECTOR3 returnRot = rot;

    // プレイヤーの位置を取得
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

    // 攻撃していないかつ、壁走りしていないなら
    if (m_bAttack == false && m_bWallRun == false)
    {
        // 警戒していないなら
        if (m_bWarning == false)
        {
            // プレイヤーとの距離を測る
            float fDistance = sqrtf(
                powf((playerPos.x - pos.x), 2) +
                powf((playerPos.z - pos.z), 2));

            // プレイヤー発見距離に達したら
            if (fDistance <= m_fDiscoveryDistance)
            {
                // 警戒中に(他に警戒中になるパターンは、攻撃をくらう、近くの仲間が攻撃をくらうがある)
                m_bWarning = true;
            }
        }
        // 警戒中なら
        else
        {
            // プレイヤーの位置と、自身の位置を比較し、角度を求める
            float fAngle = atan2((GetPos().x - playerPos.x), (GetPos().z - playerPos.z));

            // 求めた角度を向くようにする
            m_rotDest.y = fAngle;

            // 回転の制限
            if (returnRot.y > D3DX_PI)
            {
                returnRot.y -= D3DX_PI * 2;
            }
            if (returnRot.y < -D3DX_PI)
            {
                returnRot.y += D3DX_PI * 2;
            }

            m_rotMin.y = m_rotDest.y - returnRot.y;

            // 目的の角度の回転を制限
            if (m_rotMin.y > D3DX_PI)
            {
                m_rotDest.y -= D3DX_PI * 2;
            }
            if (m_rotMin.y < -D3DX_PI)
            {
                m_rotDest.y += D3DX_PI * 2;
            }

            // 回転の制限
            if (returnRot.y > D3DX_PI)
            {
                returnRot.y -= D3DX_PI * 2;
            }
            if (returnRot.y < -D3DX_PI)
            {
                returnRot.y += D3DX_PI * 2;
            }

            if (fabsf(m_rotMin.y) < 0)
            {
                m_rotMin.y = m_rotDest.y;
            }
            else
            {
                returnRot.y += (m_rotDest.y - returnRot.y) * ANT_TURN_SPEED;
            }

            // プレイヤーとの距離を測る
            float fDistance = sqrtf(
                powf((playerPos.x - pos.x), 2) +
                powf((playerPos.z - pos.z), 2));

            // 遠距離を超えたら
            if (fDistance >= ANT_CONSIDER_AS_LONG)
            {
                // 警戒中を解除
                m_bWarning = false;
            }
        }
    }

    return returnRot;
}

//=============================================================================
// 攻撃AI処理
// Author : 後藤慎之助
//=============================================================================
D3DXVECTOR3 CAnt::AttackAI(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // 返す位置、移動量を決める
    D3DXVECTOR3 returnPos = pos;
    D3DXVECTOR3 move = DEFAULT_VECTOR;

    // 警戒中なら
    if (m_bWarning == true)
    {
        switch (m_attackAI)
        {
        case ATTACK_AI_WAIT:

            // 攻撃していない
            m_bAttack = false;

            // カウンタアップ
            m_nCntTime++;

            // 一定カウンタで
            if (m_nCntTime >= ANT_NEXT_ATTACK_COUNT)
            {
                // カウンタリセット
                m_nCntTime = 0;

                // ランダムに数字を決める
                int nRandNum = GetRandNum(ANT_NEXT_ATTACK_PERCENT_MAX, 1);

                // 何の攻撃が採用されたか決める
                if (nRandNum >= 1 && nRandNum <= ANT_TAUNT_PERCENT)
                {
                    m_attackAI = ATTACK_AI_TAUNT;
                }
                else if (nRandNum > ANT_TAUNT_PERCENT && nRandNum <= ANT_TAUNT_PERCENT + ANT_ACID_PERCENT)
                {
                    m_attackAI = ATTACK_AI_ACID;
                }
                else if (nRandNum > ANT_TAUNT_PERCENT + ANT_ACID_PERCENT && nRandNum <= ANT_TACKLE_PERCENT + ANT_TAUNT_PERCENT + ANT_ACID_PERCENT)
                {
                    m_attackAI = ATTACK_AI_TACKLE;
                }
            }

            break;

        case ATTACK_AI_TAUNT:

            // 挑発も攻撃とみなす
            m_bAttack = true;

            // カウンタアップ
            m_nCntTime++;

            // アニメーションを挑発に
            GetAnimation()->SetAnimation(ANIM_TAUNT);

            // 一定カウンタで
            if (m_nCntTime >= ANT_TAUNT_WHOLE_FRAME)
            {
                // カウンタリセット
                m_nCntTime = 0;

                // 待機中にする
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;

        case ATTACK_AI_ACID:

            // 酸飛ばしは攻撃している
            m_bAttack = true;

            // カウンタアップ
            m_nCntTime++;

            // アニメーションを攻撃に
            GetAnimation()->SetAnimation(ANIM_ATTACK);

            // クリエイトフレーム
            if (m_nCntTime == ANT_ACID_CREATE_FRAME)
            {
                SetAcidAttack(pos, rot);
            }

            // 一定カウンタで
            if (m_nCntTime >= ANT_ACID_WHOLE_FRAME)
            {
                // カウンタリセット
                m_nCntTime = 0;

                // 待機中にする
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;

        case ATTACK_AI_TACKLE:

            // タックルは攻撃している
            m_bAttack = true;

            // カウンタアップ
            m_nCntTime++;

            // アニメーションを攻撃に
            GetAnimation()->SetAnimation(ANIM_WALK);

            // 向ている方向に進む
            move = D3DXVECTOR3(-sinf(rot.y) * m_fSpeed * ANT_TACKLE_SPEED_RATE, 0.0f, -cosf(rot.y) * m_fSpeed * ANT_TACKLE_SPEED_RATE);
            returnPos += move;

            // 巡回の中心位置を変える
            m_patrolCentralPos = returnPos;

            // 一定カウンタで
            if (m_nCntTime >= ANT_TACKLE_WHOLE_FRAME)
            {
                // カウンタリセット
                m_nCntTime = 0;

                // 待機中にする
                m_attackAI = ATTACK_AI_WAIT;
            }

            break;
        }
    }

    return returnPos;
}

//=============================================================================
// 酸飛ばし攻撃
// Author : 後藤慎之助
//=============================================================================
void CAnt::SetAcidAttack(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // プレイヤーの位置を取得
    D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

    // プレイヤーとの距離を測る
    float fDistance = sqrtf(
        powf((playerPos.x - pos.x), 2) +
        powf((playerPos.z - pos.z), 2));
    float fAngleY = 0.0f;

    // 飛ばす角度や数を、種類によって変える
    D3DXVECTOR3 moveAngle = DEFAULT_VECTOR;
    float fHorizontalAngle = 0.0f;
    switch (m_type)
    {
    case TYPE_WHITE:

        // 距離に応じて、ランダムに上に飛ばす
        // 近距離
        if (fDistance <= ANT_CONSIDER_AS_SHORT)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_SHORT_MAX_ANGLE_Y, ANT_ACID_SHORT_MIN_ANGLE_Y)) / 100.0f);
        }
        // 中距離
        else if (fDistance > ANT_CONSIDER_AS_SHORT && fDistance <= ANT_CONSIDER_AS_MEDIUM)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_MEDIUM_MAX_ANGLE_Y, ANT_ACID_MEDIUM_MIN_ANGLE_Y)) / 100.0f);
        }
        // 遠距離
        else if (fDistance > ANT_CONSIDER_AS_MEDIUM)
        {
            fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_LONG_MAX_ANGLE_Y, ANT_ACID_LONG_MIN_ANGLE_Y)) / 100.0f);
        }

        // 移動角度を決める
        moveAngle = D3DXVECTOR3(-sinf(rot.y), fAngleY, -cosf(rot.y));

        // 弾をクリエイト
        CBullet::Create(pos + ANT_ACID_ADD_SET_POS_Y, BULLET_ACID_COLLISION_SIZE, moveAngle, CBullet::TYPE_ACID, CBullet::TRIBE_ENEMY);

        break;

    case TYPE_BLACK:

        // 複数個飛ばす
        for (int nCnt = 0; nCnt < ANT_BLACK_ACID_NUMBER_ONCE; nCnt++)
        {
            // 距離に応じて、ランダムに上に飛ばす
            // 近距離
            if (fDistance <= ANT_CONSIDER_AS_SHORT)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_SHORT_MAX_ANGLE_Y, ANT_ACID_SHORT_MIN_ANGLE_Y)) / 100.0f);
            }
            // 中距離
            else if (fDistance > ANT_CONSIDER_AS_SHORT && fDistance <= ANT_CONSIDER_AS_MEDIUM)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_MEDIUM_MAX_ANGLE_Y, ANT_ACID_MEDIUM_MIN_ANGLE_Y)) / 100.0f);
            }
            // 遠距離
            else if (fDistance > ANT_CONSIDER_AS_MEDIUM)
            {
                fAngleY = D3DXToRadian(float(GetRandNum(ANT_ACID_LONG_MAX_ANGLE_Y, ANT_ACID_LONG_MIN_ANGLE_Y)) / 100.0f);
            }

            // 横に拡散させる
            if (nCnt == 0)
            {
                fHorizontalAngle = D3DXToRadian(float(GetRandNum(ANT_ACID_MAX_ANGLE_TO_SHIFT_FROM_CENTER, 0)) / 100.0f);
            }
            else if (nCnt == 1)
            {
                fHorizontalAngle = -D3DXToRadian(float(GetRandNum(ANT_ACID_MAX_ANGLE_TO_SHIFT_FROM_CENTER, 0)) / 100.0f);
            }

            // 移動角度を決める
            moveAngle = D3DXVECTOR3(-sinf(rot.y + fHorizontalAngle), fAngleY, -cosf(rot.y + fHorizontalAngle));

            // 弾をクリエイト
            CBullet::Create(pos + ANT_ACID_ADD_SET_POS_Y, BULLET_ACID_COLLISION_SIZE, moveAngle, CBullet::TYPE_ACID, CBullet::TRIBE_ENEMY);
        }

        break;
    }
}

//=============================================================================
// 描画処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::Draw(void)
{
    CCharacter::Draw();
}

//=============================================================================
// モデルデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
HRESULT CAnt::Load(void)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_000_body.x"),          D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_BODY], NULL, &m_nNumMat[TYPE_WHITE][PARTS_BODY], &m_pMesh[TYPE_WHITE][PARTS_BODY]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_001_head.x"),          D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_HEAD], NULL, &m_nNumMat[TYPE_WHITE][PARTS_HEAD], &m_pMesh[TYPE_WHITE][PARTS_HEAD]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_002_stomach.x"),       D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_STOMACH], NULL, &m_nNumMat[TYPE_WHITE][PARTS_STOMACH], &m_pMesh[TYPE_WHITE][PARTS_STOMACH]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_003_tactile_000.x"),   D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_TACTILE_RIGHT], NULL, &m_nNumMat[TYPE_WHITE][PARTS_TACTILE_RIGHT], &m_pMesh[TYPE_WHITE][PARTS_TACTILE_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_004_tactile_001.x"),   D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_TACTILE_LEFT], NULL, &m_nNumMat[TYPE_WHITE][PARTS_TACTILE_LEFT], &m_pMesh[TYPE_WHITE][PARTS_TACTILE_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_005_fang_000.x"),      D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_FANG_RIGHT], NULL, &m_nNumMat[TYPE_WHITE][PARTS_FANG_RIGHT], &m_pMesh[TYPE_WHITE][PARTS_FANG_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_006_fang_001.x"),      D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_FANG_LEFT], NULL, &m_nNumMat[TYPE_WHITE][PARTS_FANG_LEFT], &m_pMesh[TYPE_WHITE][PARTS_FANG_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_007_leg_right_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_RIGHT_0], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_RIGHT_0], &m_pMesh[TYPE_WHITE][PARTS_LEG_RIGHT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_008_leg_right_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_RIGHT_1], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_RIGHT_1], &m_pMesh[TYPE_WHITE][PARTS_LEG_RIGHT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_009_leg_right_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_RIGHT_2], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_RIGHT_2], &m_pMesh[TYPE_WHITE][PARTS_LEG_RIGHT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_010_leg_left_000.x"),  D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_LEFT_0], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_LEFT_0], &m_pMesh[TYPE_WHITE][PARTS_LEG_LEFT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_011_leg_left_001.x"),  D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_LEFT_1], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_LEFT_1], &m_pMesh[TYPE_WHITE][PARTS_LEG_LEFT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_012_leg_left_002.x"),  D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_WHITE][PARTS_LEG_LEFT_2], NULL, &m_nNumMat[TYPE_WHITE][PARTS_LEG_LEFT_2], &m_pMesh[TYPE_WHITE][PARTS_LEG_LEFT_2]);

    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_000_body.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_BODY], NULL, &m_nNumMat[TYPE_BLACK][PARTS_BODY], &m_pMesh[TYPE_BLACK][PARTS_BODY]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_001_head.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_HEAD], NULL, &m_nNumMat[TYPE_BLACK][PARTS_HEAD], &m_pMesh[TYPE_BLACK][PARTS_HEAD]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_002_stomach.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_STOMACH], NULL, &m_nNumMat[TYPE_BLACK][PARTS_STOMACH], &m_pMesh[TYPE_BLACK][PARTS_STOMACH]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_003_tactile_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_TACTILE_RIGHT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_TACTILE_RIGHT], &m_pMesh[TYPE_BLACK][PARTS_TACTILE_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_004_tactile_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_TACTILE_LEFT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_TACTILE_LEFT], &m_pMesh[TYPE_BLACK][PARTS_TACTILE_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_005_fang_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_FANG_RIGHT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_FANG_RIGHT], &m_pMesh[TYPE_BLACK][PARTS_FANG_RIGHT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_006_fang_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_FANG_LEFT], NULL, &m_nNumMat[TYPE_BLACK][PARTS_FANG_LEFT], &m_pMesh[TYPE_BLACK][PARTS_FANG_LEFT]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_007_leg_right_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_0], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_0], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_008_leg_right_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_1], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_1], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_009_leg_right_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_RIGHT_2], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_RIGHT_2], &m_pMesh[TYPE_BLACK][PARTS_LEG_RIGHT_2]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_010_leg_left_000.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_0], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_0], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_0]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_011_leg_left_001.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_1], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_1], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_1]);
    D3DXLoadMeshFromX(LPCSTR("./data/MODEL/ant/ant_012_leg_left_002.x"), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[TYPE_BLACK][PARTS_LEG_LEFT_2], NULL, &m_nNumMat[TYPE_BLACK][PARTS_LEG_LEFT_2], &m_pMesh[TYPE_BLACK][PARTS_LEG_LEFT_2]);

    return S_OK;
}

//=============================================================================
// モデルデータ破棄処理
// Author : 樋宮匠
//=============================================================================
void CAnt::Unload(void)
{
    for (int nCntType = 0; nCntType < TYPE_MAX; nCntType++)
    {
        for (int nCount = 0; nCount < PARTS_MAX; nCount++)
        {
            if (m_pBuffMat[nCntType][nCount] != NULL)
            {
                m_pBuffMat[nCntType][nCount] = NULL;
            }

            if (m_nNumMat[nCntType][nCount] != NULL)
            {
                m_nNumMat[nCntType][nCount] = NULL;
            }

            if (m_pMesh[nCntType][nCount] != NULL)
            {
                m_pMesh[nCntType][nCount] = NULL;
            }
        }
    }
}

//=============================================================================
// インスタンス生成処理
// Author : 後藤慎之助
//=============================================================================
CAnt * CAnt::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bWarning, TYPE type)
{
    // メモリ確保
    CAnt *pAnt = NULL;
    pAnt = new CAnt;

    // 親元の情報を設定
    pAnt->SetPos(pos);
    pAnt->SetRot(rot);
    pAnt->SetTribe(CCharacter::TRIBE_ANT);

    // 読み込む種類の設定
    pAnt->m_type = type;

    // 初期化(黒アリはスケール2倍)
    D3DXVECTOR3 scale = DEFAULT_SCALE;
    if (type == TYPE_BLACK)
    {
        scale = ANT_BLACK_SCALE;
    }
    pAnt->Init(pos, scale);

    // パトロールの中心位置を記憶
    pAnt->m_patrolCentralPos = pos;

    // 目標位置を記憶
    pAnt->m_patrolDestPos = pos;

    // 警戒中かどうかを引数から結びつける
    pAnt->m_bWarning = bWarning;

    // タイプごとに、固定の値を紐づけ
    switch (type)
    {
    case TYPE_WHITE:

        pAnt->SetActiveCollisionSize(ANT_WHITE_ACTIVE_COLLISION_SIZE);
        pAnt->SetLife(ANT_WHITE_LIFE);
        pAnt->m_nScore = ANT_WHITE_SCORE;
        pAnt->m_nOrbs = ANT_WHITE_ORBS;
        pAnt->m_fSpeed = ANT_WHITE_SPEED;
        pAnt->m_nPatrolDistance = ANT_WHITE_PATROL_DISTANCE;
        pAnt->m_fDiscoveryDistance = ANT_WHITE_DISCOVERY_DISTANCE;

        pAnt->SetCntCollision(ANT_WHITE_COLLISION_MAX);
        pAnt->SetCollisionSize(0, ANT_WHITE_BODY_COLLISION_SIZE);

        break;

    case TYPE_BLACK:

        pAnt->SetActiveCollisionSize(ANT_BLACK_ACTIVE_COLLISION_SIZE);
        pAnt->SetLife(ANT_BLACK_LIFE);
        pAnt->m_nScore = ANT_BLACK_SCORE;
        pAnt->m_nOrbs = ANT_BLACK_ORBS;
        pAnt->m_fSpeed = ANT_BLACK_SPEED;
        pAnt->m_nPatrolDistance = ANT_BLACK_PATROL_DISTANCE;
        pAnt->m_fDiscoveryDistance = ANT_BLACK_DISCOVERY_DISTANCE;

        pAnt->SetCntCollision(ANT_BLACK_COLLISION_MAX);
        pAnt->SetCollisionSize(0, ANT_BLACK_BODY_COLLISION_SIZE);
        pAnt->SetCollisionSize(1, ANT_BLACK_STOMACH_COLLISION_SIZE);
        pAnt->SetCollisionSize(2, ANT_BLACK_TACTILE_COLLISION_SIZE);
        pAnt->SetCollisionSize(3, ANT_BLACK_TACTILE_COLLISION_SIZE);
        pAnt->SetCollisionSize(4, ANT_BLACK_FANG_COLLISION_SIZE);
        pAnt->SetCollisionSize(5, ANT_BLACK_FANG_COLLISION_SIZE);

        break;
    }

    // 当たり判定の位置を更新
    pAnt->UpdateCollisionPos();

    return pAnt;
}

//=============================================================================
// オーブをバラまく処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::ScatterOrbs(void)
{
    // 位置を取得
    D3DXVECTOR3 pos = GetPos();

    // オーブ飛散エフェクト
    float fSpeedX = 0.0f;   //速さX
    float fSpeedY = 0.0f;   //速さY
    float fSpeedZ = 0.0f;   //速さZ
    int nPlusMinusX = 0;    //符号X
    int nPlusMinusZ = 0;    //符号Z
    for (int nCnt = 0; nCnt < m_nOrbs; nCnt++)
    {
        // 速さと、符号をランダムに決める
        fSpeedX = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_X, 0)) / 100.0f;
        fSpeedY = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Y, EFFECT_CHARGE_SPREAD_MIN_Y)) / 100.0f;
        fSpeedZ = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Z, 0)) / 100.0f;
        nPlusMinusX = GetRandNum(2, 1);
        nPlusMinusZ = GetRandNum(2, 1);
        if (nPlusMinusX == 1)
        {
            nPlusMinusX = 1;
        }
        else
        {
            nPlusMinusX = -1;
        }

        if (nPlusMinusZ == 1)
        {
            nPlusMinusZ = 1;
        }
        else
        {
            nPlusMinusZ = -1;
        }

        // 移動量を決める
        D3DXVECTOR3 move = D3DXVECTOR3(fSpeedX*nPlusMinusX, fSpeedY, fSpeedZ*nPlusMinusZ);

        // エフェクト発生
        CEffect3D::Create(pos, EFFECT_CHARGE_SIZE, move,
            EFFECT3D_PURPLE_FIRE_FIRST_COLOR, DEFAULT_VECTOR, EFFECT3D_PURPLE_FIRE_FADE_OUT_RATE, CEffect3D::TYPE_CHARGE);
    }
}

//=============================================================================
// やられた時の粉砕処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::DeathCrush(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    // 虫撃破音
    CSound *pSound = CManager::GetSound();
    pSound->Play(CSound::LABEL_SE_BUG);

    // パーツの位置と、モデルエフェクトの種類
    D3DXVECTOR3 partsPos = DEFAULT_VECTOR;
    CModelEffect::TYPE modelEffectType = CModelEffect::TYPE_WHITE_ANT_BODY;

    //==============================
    // 体
    //==============================
    // 位置
    partsPos = D3DXVECTOR3(GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_BODY)->GetWorldMtx()._43);

    // 種類
    switch (m_type)
    {
    case TYPE_WHITE:
        modelEffectType = CModelEffect::TYPE_WHITE_ANT_BODY;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_ANT_BODY;
        break;
    }

    // エフェクトの発生
    SetDeathCrushEffect(partsPos, rot, modelEffectType);

    //==============================
    // 腹
    //==============================
    // 位置
    partsPos = D3DXVECTOR3(GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._41,
        GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._42,
        GetParts(CAnt::PARTS_STOMACH)->GetWorldMtx()._43);

    // 種類
    switch (m_type)
    {
    case TYPE_WHITE:
        modelEffectType = CModelEffect::TYPE_WHITE_ANT_STOMACH;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_ANT_STOMACH;
        break;
    }

    // エフェクトの発生
    SetDeathCrushEffect(partsPos, rot, modelEffectType);

    //==============================
    // 足
    //==============================
    // 種類
    switch (m_type)
    {
    case TYPE_WHITE:
        modelEffectType = CModelEffect::TYPE_WHITE_ANT_LEG;
        break;
    case TYPE_BLACK:
        modelEffectType = CModelEffect::TYPE_BLACK_ANT_LEG;
        break;
    }

    // 足の本数分バラまく
    for (int nCnt = 0; nCnt < ANT_MAX_LEG; nCnt++)
    {
        // エフェクトの発生(足は中心から出す)
        SetDeathCrushEffect(pos, rot, modelEffectType);
    }
}

//=============================================================================
// やられた時の粉砕エフェクトの発生
// Author : 後藤慎之助
//=============================================================================
void CAnt::SetDeathCrushEffect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelEffect::TYPE type)
{
    // 粉砕エフェクト用の変数宣言
    float fSpeedX = 0.0f;               // 速さX
    float fSpeedY = 0.0f;               // 速さY
    float fSpeedZ = 0.0f;               // 速さZ
    float fRotSpeedX = 0.0f;            // 回転速度X
    float fRotSpeedY = 0.0f;            // 回転速度Y
    float fRotSpeedZ = 0.0f;            // 回転速度Z
    int nPlusMinusX = 0;                // 符号X
    int nPlusMinusZ = 0;                // 符号Z

    // 速さと、符号をランダムに決める
    fSpeedX = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_X, 0)) / 100.0f;
    fSpeedY = float(GetRandNum(MODEL_EFFECT_ANT_SPLATTER_FORCE_MAX, MODEL_EFFECT_ANT_SPLATTER_FORCE_MIN)) / 100.0f;
    fSpeedZ = float(GetRandNum(EFFECT_CHARGE_SPREAD_MAX_Z, 0)) / 100.0f;
    fRotSpeedX = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
    fRotSpeedY = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
    fRotSpeedZ = float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f - float(GetRandNum(MODEL_EFFECT_ROT_MAX, MODEL_EFFECT_ROT_MIN)) / 100.0f;
    nPlusMinusX = GetRandNum(2, 1);
    nPlusMinusZ = GetRandNum(2, 1);
    if (nPlusMinusX == 1)
    {
        nPlusMinusX = 1;
    }
    else
    {
        nPlusMinusX = -1;
    }

    if (nPlusMinusZ == 1)
    {
        nPlusMinusZ = 1;
    }
    else
    {
        nPlusMinusZ = -1;
    }

    // 移動量を決める
    D3DXVECTOR3 move = D3DXVECTOR3(fSpeedX*nPlusMinusX, fSpeedY, fSpeedZ*nPlusMinusZ);

    // 回転量を決める
    D3DXVECTOR3 rotMove = D3DXVECTOR3(D3DXToRadian(fRotSpeedX), D3DXToRadian(fRotSpeedY), D3DXToRadian(fRotSpeedZ));

    // エフェクト発生
    CModelEffect::Create(pos, rot, move, rotMove, type);
}

//=============================================================================
// 仲間に警告する処理
// Author : 後藤慎之助
//=============================================================================
void CAnt::WarnFellow(void)
{
    // 周囲の仲間を警戒中にする処理
    CScene *pScene = CScene::GetTopScene(CScene::OBJTYPE_ENEMY);
    for (int nCntScene = 0; nCntScene < CScene::GetNumAll(CScene::OBJTYPE_ENEMY); nCntScene++)
    {
        // 中身があるなら
        if (pScene != NULL)
        {
            // 次のシーンを記憶
            CScene*pNextScene = pScene->GetNextScene();

            // キャラクターにキャスト
            CCharacter *pEnemy = (CCharacter*)pScene;

            // 敵の種族がアリなら
            if (pEnemy->GetTribe() == CCharacter::TRIBE_ANT)
            {
                // 対象の位置
                D3DXVECTOR3 targetPos = pEnemy->GetPos();

                // 対象との距離
                float fDistance = sqrtf(
                    powf((targetPos.x - GetPos().x), 2) +
                    powf((targetPos.z - GetPos().z), 2));

                // 対象との距離が、仲間に警告するときの範囲内なら
                if (fDistance <= ANT_WARN_ANT_DISTANCE)
                {
                    // アリ型にキャスト
                    CAnt*pAnt = (CAnt*)pEnemy;

                    // 壁走りしていないなら
                    if (pAnt->GetWallRun() == false)
                    {
                        // 警戒中に
                        pAnt->SetWarning(true);
                    }
                }
            }

            // 次のシーンにする
            pScene = pNextScene;
        }
        else
        {
            // 中身がないなら、そこで処理を終える
            break;
        }
    }
}

//=============================================================================
// ミッションクリア数に加算する
// Author : 後藤慎之助
//=============================================================================
void CAnt::AddMissionClear(void)
{
    // ステージと現在のミッションに応じて、クリア数を増加
    CGame::STAGE stage = CGame::GetStage();
    CGame::CURRENT_MISSION currentMission = CGame::GetCurrentMission();
    switch (stage)
    {
    case CGame::STAGE_1:

        switch (currentMission)
        {
        case CGame::CURRENT_MISSION_1:
            CGame::SetClearNumMission1();
            break;

        case CGame::CURRENT_MISSION_2:

            break;
        }

        break;

    case CGame::STAGE_2:

        break;

    case CGame::STAGE_FINAL:

        break;
    }
}