//インクルードファイル
#include "player.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;		//テクスチャの情報

//コンストラクタ
CPlayer::CPlayer(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nHP = 0;
}

//デストラクタ
CPlayer::~CPlayer()
{

}

//クリエイト関数
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init(pos, size,objtype);
	}
		return pPlayer;
}

//初期化関数
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,OBJTYPE objtype)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x,pos.y , 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	SetObjType(objtype);
	m_nHP = 10;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	return S_OK;;
}

//終了関数
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CPlayer::Update(void)
{
	// マウス座標を取得する
	POINT posPoint;
	GetCursorPos(&posPoint);
	m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);
	m_pInput = CManager::GetMouse();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	//オブジェクトの更新処理の取得
	CScene2D::Update();
	//プレイヤーの状態
	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:

		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;

	case PLAYERSTATE_DAMAGE:
		//色の変更

		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		//通常状態に戻す
		if (m_state == PLAYERSTATE_DAMAGE)
		{
			m_state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
			CGame::SetGameState(CGame::GAMESTATE_END);
	default:
		break;
	}

	if (m_pos.y - (m_size.y / 2) < 10)
	{
		m_pos.y -= m_size.y / 2;
	}
	//+Y軸
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT - 10)
	{
		//キー入力処理
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
	if (((CMouse*)m_pInput)->GetMouseTrigger(0) == true )
	{
		if (CManager::GetMode() == CManager::MODE_GAME&&GetObjType()==OBJTYPE_PLAYER&&CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//弾の生成
			CBullet::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0), 
				D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
				D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_PLAYER);

			//サウンド
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		else if(CManager::GetMode() != CManager::MODE_GAME&&GetObjType() == OBJTYPE_CURSOR&&CFade::GetFade()==CFade::FADESTATE_MAX)
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

//描画関数
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

void CPlayer::HitDamege(int nDamege)
{          
	
	m_nHP -= nDamege;
	
	if (m_nHP <= 0)
	{
		m_state = PLAYERSTATE_DEATH;
	}
	else if(m_nHP > 0&&nDamege<=1)
	{
		m_state = PLAYERSTATE_DAMAGE; 
	}
}

HRESULT CPlayer::Load(void)
{
	//テクスチャの読み込み
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE, &m_pTexture);

	return S_OK;
}

void CPlayer::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
