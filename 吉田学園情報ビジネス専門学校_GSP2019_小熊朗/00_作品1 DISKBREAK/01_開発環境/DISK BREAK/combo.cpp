//*****************************************************************************
//
// �R���{���� [combo.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include <stdio.h>
#include "combo.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CCombo::CCombo(int nPriority) :CScene(nPriority)
{
	m_move = D3DXVECTOR3(0, 0, 0);			//�ړ���
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_nColor = 0;							//�F���l
	m_nCombo = 0;							//�R���{��
	m_nComboScore = 0;						//�R���{�X�R�A�l
	m_nComboCountFrame = 0;					//�R���{�̃J�E���g�t���[��
	for (int nCount = 0; nCount < MAX_COMBO_NUMBER; nCount++)
	{
		m_apNumber[nCount] = NULL;		//�i���o�[�̃|�C���^�z��
	}
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CCombo::~CCombo()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
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
//�������֐�
//*****************************************************************************
HRESULT CCombo::Init()
{
	m_nColor = 255;							//�F���l
	m_nCombo = 0;							//�R���{��
	m_nComboScore = 0;						//�R���{�X�R�A�l
	m_nComboCountFrame = 0;					//�R���{�̃J�E���g�t���[��

	//�X�R�A�̐���
	for (int nCntInit = 0; nCntInit < MAX_COMBO_NUMBER; nCntInit++)
	{
		m_apNumber[nCntInit] = CNumber::Create(
			D3DXVECTOR3((float)(COMBOUI_SIZEX + 5 + (COMBO_SIZE_X / 2) + (COMBO_POS_X *nCntInit)), COMBO_POS_Y, 0),
			D3DXVECTOR3(COMBO_SIZE_X, COMBO_SIZE_Y, 0), 0);
	}
	return S_OK;
}

//*****************************************************************************
//�I���֐�
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
//�X�V�֐�
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
//�`��֐�
//*****************************************************************************
void CCombo::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < MAX_COMBO_NUMBER; nCntDraw++)
	{
		if (m_apNumber[nCntDraw] != NULL)
		{
			m_apNumber[nCntDraw]->Draw();
		}
	}
}

//*****************************************************************************
//�����擾�ʒu�֐�
//*****************************************************************************
void CCombo::ComboAction(void)
{
	if (CGame::GetGameState()==CGame::GAMESTATE_ENEMYBREAK)
	{
		m_nCombo += 1;
		m_nColor = 0;
		m_nComboCountFrame = 0;
	}

	//�o�߃J�E���g�t���[��
	else if (CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
	{
		m_nColor += 1;
		m_nComboCountFrame++;
		if (m_nColor >= 255)
		{
			m_nColor = 255;
		}
		for (int nCnt = 0; nCnt < MAX_COMBO_NUMBER; nCnt++)
		{
			m_apNumber[nCnt]->SetColor(D3DCOLOR_RGBA(255 - m_nColor,
													 255 - m_nColor,
													 255 - m_nColor,
													 255 - m_nColor));
		}
	}

	//���t���[���ȏ�o�߂������̓Q�[���I����
	 if (m_nComboCountFrame > 255 || CGame::GetGameState() == CGame::GAMESTATE_END)
	{
		m_nComboScore = m_nCombo * 250;					//�R���{�̃X�R�A�l
 		CManager::GetScore() -> AddScore(m_nComboScore);	//���Z�X�R�A
		m_nComboCountFrame = 0;
		m_nCombo = 0;
	}
}