//インクルードファイル
#include "enemy.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CEnemy::m_apTexture[MAX_ENEMY] = {};		//テクスチャの情報

//コンストラクタ
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_bLand = false;
	m_bContact = false;
	m_nHP = 0;
	m_pScore = 0;
	m_state = ENEMYSTATE_NORMAL;
}

//デストラクタ
CEnemy::~CEnemy()
{

}

//クリエイト関数
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(pos, size, nType);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
		pEnemy->m_move = move;
	}
		return pEnemy;
}

//初期化関数
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_bContact = false;
	m_nHP = 1;
	m_state = ENEMYSTATE_NORMAL;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_apTexture[nType]);
	return S_OK;
}

//終了関数
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CEnemy::Update(void)
{
	m_pos = GetPosition();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
	int nCountEnemy = 1;

	//敵の状態
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;

	case ENEMYSTATE_DAMAGE:
		//色の変更
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		//通常状態に戻す
		m_state = ENEMYSTATE_NORMAL;

		break;

	case ENEMYRSTATE_DEATH:
		//サウンド
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		CExplosion::Create(m_pos, m_size);
		Uninit();
		CGame::SetGameState(CGame::GAMESTATE_ENEMYBREAK);
		break;

	default:
		break;
	}
	m_pos += m_move;
	//m_pos.x += m_move.x * (10.0f + 0.5f*CGame::GetGameSpeed());
	//m_pos.y += m_move.y * (10.0f + 0.5f*CGame::GetGameSpeed());
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if ((rand() % (nCountEnemy * 50)) == 0)
		{
			//弾の生成
			CBullet *pBullet = CManager::GetBullet();

			//CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), D3DXVECTOR3(0, -10, 0), CBullet::BULLET_TYPE_ENEMY);
			//サウンド
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
	}
	//当たり判定結果
	m_posold = m_pos;
	if (Collision(&m_pos, &m_posold, &m_move,&m_size) == true)
	{
		m_bContact = false;
	}

	//画面外へ行く場合画面内に反射させる。
	if (m_pos.x - (m_size.x / 2) < 0)
	{
		//左
		m_move.x *= -1;
		//m_pos.x += m_size.x / 2 + m_move.x;
	}
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH )
	{
		//右
		m_move.x *= -1;
		//m_pos.x = (SCREEN_WIDTH - m_size.x / 2) + m_move.x;

	}
	if (m_pos.y - (m_size.y / 2) < 0)
	{
		//下
		m_move.y *= -1;
		//m_pos.y = m_size.y / 2 + m_move.y;

	}
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT )
	{
		//上
		m_move.y *= -1;
		//m_pos.y = (SCREEN_HEIGHT - m_size.y / 2) + m_move.y;
	}
	//プレイヤーの位置更新
	SetPosition(m_pos);
}

//描画関数
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

void CEnemy::HitDamege(int nDamege)
{
	m_nHP -= nDamege;

	if (m_nHP <= 0)
	{
		m_state = ENEMYRSTATE_DEATH;
	}
	if (m_nHP > 0)
	{
		m_state = ENEMYSTATE_DAMAGE;
	}
}

bool CEnemy::Collision(D3DXVECTOR3 * Pos, D3DXVECTOR3 * PosOld, D3DXVECTOR3 * Move, D3DXVECTOR3 * Size)
{
	m_bLand = false;
	//敵同士の当たり判定
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if (this != pScene)
				{
					if ((objType == OBJTYPE_ENEMY))
					{
						D3DXVECTOR3 pos = ((CScene2D*)pScene)->GetPosition();//posを持ってくる
						D3DXVECTOR3 size = ((CScene2D*)pScene)->GetSize();

						//敵の当たり判定(上下)
						if (Pos->x - (ENEMY_SIZEX / 2) - (ENEMY_SIZEX / 2) <= m_pos.x &&
							Pos->x + (ENEMY_SIZEX / 2) + (ENEMY_SIZEX / 2) >= m_pos.x &&
							Pos->y - (ENEMY_SIZEY / 2) - (ENEMY_SIZEY / 2) <= m_pos.y &&
							Pos->y + (ENEMY_SIZEY / 2) + (ENEMY_SIZEY / 2) >= m_pos.y)
						{
							////プレイヤーの左側がブロックの右側にふれたとき
							//if (Pos->x + (Size->x / 2) <= m_pos.x - (ENEMY_SIZEX / 2) &&
							//	PosOld->x + (Size->x / 2) <= m_pos.x - (ENEMY_SIZEX / 2))
							//{
							//	m_move.x *= -1;
							//	Pos->x = (m_size.x / 2) + m_move.x;
							//	m_bLand = true;

							//}
							////プレイヤーの右側がブロックの左側にふれた
							//if (Pos->x + (Size->x / 2) >= m_pos.x + (ENEMY_SIZEX / 2) &&
							//	PosOld->x + (Size->x / 2) <= m_pos.x + (ENEMY_SIZEX / 2))
							//{
							//	Move->x *= -1;
							//	//Pos->x = (m_size.x / 2) + m_move.x;
							//	m_bLand = true;
							//}
							////プレイヤーの上側がブロックの下側にふれた
							//if (Pos->y + (Size->y / 2) >= m_pos.y - (ENEMY_SIZEY / 2) &&
							//	PosOld->y + (Size->y / 2) <= m_pos.y - (ENEMY_SIZEY / 2))
							//{
							//	Move->y *= -1;
							//	//Pos->y = (m_size.y / 2) - m_size.y / 2 + m_move.y;
							//	m_bLand = true;
							//}

							////プレイヤーの下側がブロックの上側にふれた
							//if (Pos->y - (Size->y / 2) <= m_pos.y + (ENEMY_SIZEY / 2) &&
							//	PosOld->y - (Size->y / 2) >= m_pos.y + (ENEMY_SIZEY / 2))
							//{
							//	Move->y *= -1;
							//	//Pos->y = (m_size.y / 2) + m_move.y;
							//	m_bLand = true;
							//}
						}
					}
				}
			}
		}
	}
	return m_bLand;
}
//ロード関数
HRESULT CEnemy::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE2, &m_apTexture[ENEMYTYPE_NORMAL]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE, &m_apTexture[ENEMYTYPE_NORMAL1]);

	return S_OK;
}

//アンロード関数
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}