//*****************************************************************************
//
// プレイヤーの処理 [player.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
//インクルードファイル
#include "player.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayer::CPlayer(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CPlayer::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CPlayer::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	CPlayer *pPlayer = NULL;
	//プレイヤーのポインタが何も無かった場合
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init(pos, size,objtype);
	}
		return pPlayer;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,OBJTYPE objtype)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x,pos.y , 0);		//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	SetObjType(objtype);						//オブジェクト指定格納
	BirdTexture(m_pTexture);					//テクスチャの情報をscene2dに持ってく
	return S_OK;;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CPlayer::Update(void)
{
	POINT posPoint;
	GetCursorPos(&posPoint);											//マウス座標を取得する
	m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//位置
	m_pInput = CManager::GetMouse();									//マウスの入力情報取得
	CSound *pSound = CManager::GetSound();								//サウンド情報取得
	CScene2D::Update();													//オブジェクトの更新処理の取得

	//-Y軸
	if (m_pos.y - (m_size.y / 2) < 10)
	{
		m_pos.y -= m_size.y / 2;
	}
	//+Y軸
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT - 10)
	{
		m_pos.y += m_size.y / 2;
	}
	//-X軸
	if (m_pos.x - (m_size.x / 2) < 10)
	{
		m_pos.x -= m_size.x / 2;
	}
	//+X軸
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH - 10)
	{
		m_pos.x += m_size.x / 2;
	}
	m_pInput = CManager::GetMouse();
	if (((CMouse*)m_pInput)->GetMousePrees(1) == true)
	{
		posPoint.x = SCREEN_WIDTH / 2;
		posPoint.y = SCREEN_HEIGHT / 2;
		m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//位置
	}

	else if (((CMouse*)m_pInput)->GetMouseTrigger(0) == true )
	{
		if (CManager::GetMode() == CManager::MODE_GAME&&
			GetObjType()==OBJTYPE_PLAYER&&
			CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//弾の生成
			CBullet::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0), 
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_PLAYER);

			//サウンド
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		else if(CManager::GetMode() != CManager::MODE_GAME&&
				GetObjType() == OBJTYPE_CURSOR&&
				CFade::GetFade()==CFade::FADESTATE_MAX)
		{
			//弾の生成
			CBullet::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0), 
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_CURSOR);
		}
	}

	//プレイヤーの位置行進
	SetPosition(m_pos);
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}


