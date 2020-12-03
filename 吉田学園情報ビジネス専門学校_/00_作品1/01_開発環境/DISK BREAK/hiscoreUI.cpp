//インクルードファイル
#include "hiscoreui.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CHiScoreUI::m_pTexture[2] = {};		//テクスチャの情報
int					CHiScoreUI::m_nFrameCnt = 0;		//点滅カウント
														//コンストラクタ
CHiScoreUI::CHiScoreUI(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(1, 1, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_Cnt = 0;
}

//デストラクタ
CHiScoreUI::~CHiScoreUI()
{

}

//クリエイト関数
CHiScoreUI * CHiScoreUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CHiScoreUI *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CHiScoreUI;
		pButton->Init(pos, size,nType);
	}
	return pButton;
}

//初期化関数
HRESULT CHiScoreUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_Cnt = 5;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture[nType]);
	return S_OK;
}

//終了関数
void CHiScoreUI::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CHiScoreUI::Update(void)
{
	m_pos = GetPosition();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//描画関数
void CHiScoreUI::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CHiScoreUI::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		HISCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_HISCORE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		MYSCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_MYSCORE]);

	return S_OK;
}

void CHiScoreUI::UnLoad(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}