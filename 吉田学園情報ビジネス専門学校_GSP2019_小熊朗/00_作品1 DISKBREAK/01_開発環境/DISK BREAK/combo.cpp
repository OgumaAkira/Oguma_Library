//*****************************************************************************
//
// コンボ処理 [combo.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include <stdio.h>
#include "combo.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CCombo::CCombo(int nPriority) :CScene(nPriority)
{
	m_move = D3DXVECTOR3(0, 0, 0);			//移動量
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nCombo = 0;							//コンボ数
	m_bCombo = true;						//コンボ
	m_nComboScore = 0;						//コンボスコア値
	m_nComboCountFrame = 0;					//コンボのカウントフレーム
	for (int nCount = 0; nCount < MAX_COMBO_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//ナンバーのポインタ配列
	}
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CCombo::~CCombo()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CCombo * CCombo::Create()
{
	CCombo *pCombo = NULL;
	if (pCombo == NULL)
	{
		pCombo = new CCombo;
		pCombo->Init();
	}
	return pCombo;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CCombo::Init()
{
	m_nCombo = 0;							//コンボ数
	m_bCombo = true;						//コンボ
	m_nComboScore = 0;						//コンボスコア値
	m_nComboCountFrame = 0;					//コンボのカウントフレーム

	//スコアの生成
	for (int nCntInit = 0; nCntInit < MAX_COMBO_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = CNumber::Create(
			D3DXVECTOR3((float)(0 + (COMBO_SIZE_X / 2) + (COMBO_POS_X *nCntInit)), COMBO_POS_Y, 0),
			D3DXVECTOR3(COMBO_SIZE_X, COMBO_SIZE_Y, 0), 0);
	}
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CCombo::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_COMBO_NUMBER; nCntUninit++)
	{
		if (m_apNumber[nCntUninit] != NULL)
		{
			m_apNumber[nCntUninit]->Uninit();
			delete m_apNumber[nCntUninit];
			m_apNumber[nCntUninit] = NULL;
		}
	}
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CCombo::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_GAME:

		for (int nCntUpdate = 0; nCntUpdate < MAX_COMBO_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nCombo = m_nCombo / (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_COMBO_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_COMBO_NUMBER - 1) - nCntUpdate]->SetNumber(nCombo);
			}
		}

		break;

	default:
		break;
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CCombo::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < MAX_COMBO_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//乱数取得位置関数
//*****************************************************************************
void CCombo::ComboAction(void)
{
	if (m_bCombo == true && CGame::GetGameState()==CGame::GAMESTATE_ENEMYBREAK)
	{
		m_nCombo += 1;
		m_nComboCountFrame = 0;
	}
	else
	{
		m_bCombo = true;
	}
	//コンボ中で無ければ処理をしない
	if (m_bCombo == false)
	{
		return;
	}

	//経過カウントフレーム
	if (CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
	{
		m_nComboCountFrame++;
	}

	//一定フレーム以上経過したら
	if (m_nComboCountFrame>250)
	{
		m_bCombo = false;					//コンボを止める
		m_nComboScore = m_nCombo * 200;		//コンボ数×200をコンボスコアに格納
		CManager::GetScore() -> AddScore(m_nComboScore);	//加算スコア
		m_nComboCountFrame = 0;				//カウントフレームを0にする
		m_nCombo = 0;
	}
}