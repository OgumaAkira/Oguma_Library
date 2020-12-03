//マクロ定義
#define _CRT_SECURE_NO_WARNINGS
//インクルードファイル
#include <stdio.h>
#include "score.h"

//静的メンバ変数
int		CScore::m_nScore = 0;

//コンストラクタ
CScore::CScore(int nPriority) :CScene(nPriority)
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
CScore::~CScore()
{
}

//クリエイト関数
CScore * CScore::Create()
{
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		pScore->Init();
	}
	return pScore;
}

HRESULT CScore::Init()
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
			case CManager::MODE_GAME:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3((float)(0 + (SCORE_SIZE_X / 2) + (SCORE_SIZE_X *nCntInit)), SCORE_POS_Y, 0),
					D3DXVECTOR3(SCORE_SIZE_X, SCORE_SIZE_Y, 0), 0);
				break;
			case CManager::MODE_RESULT:
				m_apNumber[nCntInit] = CNumber::Create(D3DXVECTOR3((float)(SCREEN_WIDTH / 2 + (SCORE_SIZE_X / 2)*2 + (SCORE_SIZE_X *nCntInit)*2), SCREEN_HEIGHT/2, 0),
					D3DXVECTOR3(SCORE_SIZE_X*2, SCORE_SIZE_Y*2, 0), 0);
				break;
			default:
				break;
			}
		}
	}
	return S_OK;
}

void CScore::Uninit(void)
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

void CScore::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_GAME:
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
		WriteFile();
		if (CGame::GetGameState()==CGame::GAMESTATE_END)
		{
			int Scoreold = CHIScore::ReadFile();
			if (Scoreold < m_nScore)
			{
				CHIScore::WriteFile(m_nScore);
			}
			Uninit();
		}
		break;

	case CManager::MODE_RESULT:
		for (int nCntUpdate = 0; nCntUpdate < MAX_SCORE_NUMBER; nCntUpdate++)
		{
			if (m_apNumber[nCntUpdate] != NULL)
			{
				int nScore = ReadFile()
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

void CScore::Draw(void)
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

void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

void CScore::AddScore(int nScore)
{
	m_nScore += nScore;
}

//読み込み関数
int CScore::ReadFile(void)
{
	int ReadScore = 0;
	//ファイルポインタ
	FILE *pFile;
	//読み込みモード(r)でファイルオープン
	pFile = fopen("RankingServer", "r");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &ReadScore);
	
		//ファイルを閉じる
		fclose(pFile);
	}
	return ReadScore;
}

//書き込み関数
void CScore::WriteFile(void)
{
	//ファイルポインタ
	FILE *pFile;
	//書き込みモード(ｗ)でファイルオープン
	pFile = fopen("RankingServer", "w");

	//ファイルの中身を確認
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
		//ファイルを閉じる
		fclose(pFile);
	}
}
