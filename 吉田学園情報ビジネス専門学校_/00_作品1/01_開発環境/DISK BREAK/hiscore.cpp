//�}�N����`
#define _CRT_SECURE_NO_WARNINGS
//�C���N���[�h�t�@�C��
#include <stdio.h>
#include "hiscore.h"
int	CHIScore::m_nScore = 0;
//�R���X�g���N�^
CHIScore::CHIScore()
{
	m_move = D3DXVECTOR3(0, 0, 0);			//�ړ���
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_nScore = 0;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��No.
	for (int nCount = 0; nCount < MAX_SCORE_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
	}
}

//�f�X�g���N�^
CHIScore::~CHIScore()
{
}

//�N���G�C�g�֐�
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
	//�X�R�A�̐���
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
	//�w�i�̕`��
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
	//�t�@�C���|�C���^
	FILE *pFile;
	//�������݃��[�h(��)�Ńt�@�C���I�[�v��
	pFile = fopen("ScoreFile", "w");

	//�t�@�C���̒��g���m�F
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
		//�t�@�C�������
		fclose(pFile);
	}
}

int CHIScore::ReadFile(void)
{
	//�t�@�C���|�C���^
	FILE *pFile;
	//�ǂݍ��݃��[�h(r)�Ńt�@�C���I�[�v��
	pFile = fopen("ScoreFile", "r");

	//�t�@�C���̒��g���m�F
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nScore);

		//�t�@�C�������
		fclose(pFile);
	}
	return m_nScore;
}
