//インクルードファイル
#include "tutorial.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CTutorial::m_pTexture = {};		//テクスチャの情報
int					CTutorial::m_nFrameCnt = 0;		//点滅カウント
														//コンストラクタ
CTutorial::CTutorial(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(1, 1, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_Cnt = 0;
}

//デストラクタ
CTutorial::~CTutorial()
{

}

//クリエイト関数
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTutorial *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CTutorial;
		pButton->Init(pos, size);
	}
	return pButton;
}

//初期化関数
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_Cnt = 5;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);
	return S_OK;
}

//終了関数
void CTutorial::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CTutorial::Update(void)
{
	m_pos = GetPosition();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//描画関数
void CTutorial::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CTutorial::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE, &m_pTexture);

	return S_OK;
}

void CTutorial::UnLoad(void)
{

	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}