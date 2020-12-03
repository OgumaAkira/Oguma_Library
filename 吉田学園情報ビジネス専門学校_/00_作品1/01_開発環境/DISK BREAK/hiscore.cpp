//マクロ定義
#define _CRT_SECURE_NO_WARNINGS
//インクルードファイル
#include <stdio.h>
#include "hiscore.h"
int	CHIScore::m_nScore = 0;
//コンストラクタ
CHIScore::CHIScore()
{
	m_move = D3DXVECTOR3(0, 0, 0);			//移動量
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nScore = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//アニメーションパターンNo.
	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//ナンバーのポインタ配列
	}
}

//デストラクタ
CHIScore::~CHIScore()
{
}

//クリエイト関数
CHIScore * CHIScore::Create()
{
	CHIScore *pHiScore = NULL;
	if (pHiScore == NULL)
	{
		pHiScore = new CHIScore;
		pHiScore->Init();
	}
	return pHiScore;
}

HRESULT CHIScore::Init()
{
	m_nScore = 0;
	//スコアの生成
	for (int nCntInit = 0; nCntInit < MAX_SCORE_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = NULL;
		if (m_apNumber[nCntInit] == NULL)
		{
			switch (CManager::GetMode())
			{
			case CManager::MODE_TITLE:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2 + (SCORE_SIZE_X / 2) + (SCORE_SIZE_X *nCntInit)), SCORE_POS_Y+100, 0),
					D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), 0);
				break;

			case CManager::MODE_RESULT:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3((float)(150 + (SCORE_SIZE_X / 2) * 2 + (SCORE_SIZE_X *nCntInit) * 2), SCREEN_HEIGHT / 2, 0),
					D3DXVECTOR3(SCORE_SIZE_X * 2, SCORE_SIZE_Y * 2, 0), 0);
				break;
			default:
				break;
			}
		}
	}
	return S_OK;
}

void CHIScore::Uninit(void)
{
	for (int nCntUninit = 0; nCntUninit < MAX_SCORE_NUMBER; nCntUninit++)
	{
		if (m_apNumber[nCntUninit] != NULL)
		{
			m_apNumber[nCntUninit]->Uninit();
			delete m_apNumber[nCntUninit];
			m_apNumber[nCntUninit] = NULL;
		}
	}
}

void CHIScore::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		ReadFile();
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nScore = m_nScore
					/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			}
		}
		break;

	case CManager::MODE_RESULT:
		ReadFile();
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nScore = m_nScore
					/ (int)powf(10.0f, (float)nCntUpdate) % (int)powf(10.0f, nCntUpdate + 1.0f);
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->Update();
				m_apNumber[(MAX_SCORE_NUMBER - 1) - nCntUpdate]->SetNumber(nScore);
			}
		}
		break;
	default:
		break;
	}
}

void CHIScore::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < MAX_SCORE_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

void CHIScore::WriteFile(int nScore)
{
	m_nScore = nScore;
	//ファイルポインタ
	FILE *pFile;
	//書き込みモード(ｗ)でファイルオープン
	pFile = fopen("ScoreFile", "w");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}

int CHIScore::ReadFile(void)
{
	//ファイルポインタ
	FILE *pFile;
	//読み込みモード(r)でファイルオープン
	pFile = fopen("ScoreFile", "r");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nScore);

		//ファイルを閉じる
		fclose(pFile);
	}
	return m_nScore;
}
