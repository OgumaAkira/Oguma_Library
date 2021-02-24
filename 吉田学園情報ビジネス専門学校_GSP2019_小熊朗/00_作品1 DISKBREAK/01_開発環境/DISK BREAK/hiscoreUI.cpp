//*****************************************************************************
//
// ハイスコアUI処理 [hiscore.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "hiscoreui.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CHiScoreUI::m_pTexture[2] = {};		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CHiScoreUI::CHiScoreUI(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CHiScoreUI::~CHiScoreUI()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CHiScoreUI * CHiScoreUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CHiScoreUI *pHiScoreUI = NULL;

	//ボタンのポインタが無かった場合
	if (pHiScoreUI == NULL)
	{
		pHiScoreUI = new CHiScoreUI;
		pHiScoreUI->Init(pos, size,nType);
	}
	return pHiScoreUI;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CHiScoreUI::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(ハイスコア)
	D3DXCreateTextureFromFile(pDevice,
		HISCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_HISCORE]);

	//テクスチャの読み込み(スコア)
	D3DXCreateTextureFromFile(pDevice,
		MYSCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_MYSCORE]);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
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

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CHiScoreUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	BirdTexture(m_pTexture[nType]);		//テクスチャの情報をscene2dに持ってく
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CHiScoreUI::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CHiScoreUI::Update(void)
{
	m_pos = GetPosition();	//位置を取得
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CHiScoreUI::Draw(void)
{
	CScene2D::Draw();
}

