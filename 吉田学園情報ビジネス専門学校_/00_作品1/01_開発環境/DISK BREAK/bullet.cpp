//インクルードファイル
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "bulletUI.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9	CBullet::m_pTexture = NULL;		//テクスチャの情報
CBulletUI			*CBullet::m_pBulletUI = NULL;	//残弾のポインタ

//コンストラクタ
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//位置
	m_size = D3DXVECTOR3(0, 0, 0);			//大きさ
	m_move = D3DXVECTOR3(0, 0, 0);			//移動量
	m_nHP = 0;
}
//デストラクタ
CBullet::~CBullet()
{
}
//クリエイト
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos,size, move,type);
	pBullet->SetObjType(OBJTYPE_BULLET);
	return pBullet;
}
//初期化
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CScene2D::Init();
	//弾の初期設定
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	m_size = D3DXVECTOR3(size.x, size.y, 0);//大きさ　
	m_move = move;//移動量
	m_nHP = 1;	//ヒットポイント
	m_type = type;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_BULLET);
	SetPosition(m_pos);
	SetSize(m_size);
	return S_OK;
}
//終了
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//更新
void CBullet::Update(void)
{
	CSound *pSound = CManager::GetSound();
	m_pos = GetPosition();
	m_pos.y -= m_move.y;
	SetPosition(m_pos);
	CScene2D::Update();
	m_nHP--;	//弾のライフ

	//当たり判定
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		bool bHitEnemy = false;

		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if ((objType == OBJTYPE_ENEMY) && (m_type == BULLET_TYPE_PLAYER))
				{
					CPlayer *pPlayer = CManager::GetPlayer();
					CScene2D *pScene2d = (CScene2D*)pScene;	//キャスト
					D3DXVECTOR3 pos = pScene2d->GetPosition();//posを持ってくる
					D3DXVECTOR3 size = pScene2d->GetSize();
					//敵の当たり判定
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CEnemy *pEnemy = (CEnemy*)pScene;	//キャスト;
						pEnemy->HitDamege(1);
						m_nHP = 0;
						bHitEnemy = true;
						break;
					}
				}
				else if ((objType == OBJTYPE_BUTTON) && (m_type == BULLET_TYPE_CURSOR))
				{
					CButton *pButton = CManager::GetButton();
					CScene2D *pScene2d = (CScene2D*)pScene;
					D3DXVECTOR3 pos = pScene2d->GetPosition();
					D3DXVECTOR3 size = pScene2d->GetSize();
					//プレイヤーの当たり判定
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CButton *pButton = (CButton*)pScene;	//キャスト;
						pButton->SetButton();
						m_nHP = 0;
					}
				}
			}
		}

		if (bHitEnemy == true)
		{ 
			break;
		}
	}
	if (m_pos.x - m_size.x / 2 < 0)
	{
		m_nHP = 0;
	}
	else if (m_pos.x + m_size.x / 2 > SCREEN_WIDTH)
	{
		m_nHP = 0;
	}
	else if (m_pos.y - m_size.y / 2 < 0)
	{
		m_nHP = 0;
	}
	else if (m_pos.y + m_size.y / 2 > SCREEN_HEIGHT)
	{
		m_nHP = 0;
	}
	if (m_nHP <= 0)
	{
		//爆発生成
		if (m_type == BULLET_TYPE_PLAYER)
		{
			CExplosion::Create(m_pos, m_size);
			m_pBulletUI->SetbUse();
		}
		Uninit();
	}
}
//描画
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//読み込み
HRESULT CBullet::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png", &m_pTexture);

	return S_OK;
}
//テクスチャの破棄
void CBullet::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}