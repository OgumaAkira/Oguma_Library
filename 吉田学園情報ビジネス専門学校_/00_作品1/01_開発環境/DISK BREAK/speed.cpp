//インクルードファイル
#include "speed.h"
#include "sound.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9	CSpeed::m_pTexture = {};		//テクスチャの情報
int					CSpeed::m_nFrameCnt = 0;		//点滅カウント
bool				CSpeed::m_bUse = false;
														//コンストラクタ
CSpeed::CSpeed(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(1, 1, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_Cnt = 0;
}

//デストラクタ
CSpeed::~CSpeed()
{

}

//クリエイト関数
CSpeed * CSpeed::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CSpeed *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CSpeed;
		pButton->Init(pos, size);
		pButton->SetObjType(OBJTYPE_BUTTON);
	}
	return pButton;
}

//初期化関数
HRESULT CSpeed::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_Cnt = 5;
	m_bUse2 = true;
	//サウンド取得
	pSound = CManager::GetSound();
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	return S_OK;
}

//終了関数
void CSpeed::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CSpeed::Update(void)
{
	m_pos = GetPosition();
	CScene2D::Update();
	if (m_bUse == true)
	{
		if (m_bUse2 == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SPEEDUP);
			m_bUse2 = false;
		}
		m_nFrameCnt++;
		if (m_nFrameCnt <= 30)
		{
			SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		else if (m_nFrameCnt > 30)
		{
			SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
		}
		if (m_nFrameCnt == 60)
		{
			m_nFrameCnt = 0;
			m_Cnt--;
		}
		if (m_Cnt == 0)
		{
			Uninit();
			m_bUse = false;
		}
	}
}

//描画関数
void CSpeed::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CSpeed::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		SPEEDUP_TEXTURE, &m_pTexture);

	return S_OK;
}

void CSpeed::UnLoad(void)
{

		if (m_pTexture != NULL)
		{
			//テクスチャの破棄
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}