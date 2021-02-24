//*****************************************************************************
//
// ���U���g��ʂ̏��� [result.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "score.h"
#include "manager.h"
#include "result.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "button.h"
#include "fade.h"
#include "hiscore.h"
#include "hiscoreUI.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CPlayer			*CResult::m_pPlayer = NULL;	//�v���C���[�̃|�C���^
CBg				*CResult::m_pBg = NULL;	//�w�i�̃|�C���^
CFade			*CResult::m_pFade = NULL;	//�t�F�[�h�̃|�C���^
CButton			*CResult::m_pButton = NULL;	//�{�^���̃|�C���^
CScore			*CResult::m_pScore = NULL;//�X�R�A�̃|�C���^
CHIScore		*CResult::m_pHiScore = NULL;		//�n�C�X�R�A
CHiScoreUI		*CResult::m_pHiScoreUI = NULL;		//�n�C�X�R�AUI

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_bUse = true;//���U���g��ʂ̃X�C�b�`
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CResult::~CResult()
{
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CResult * CResult::Create()
{
	CResult *pResult = NULL;
	if (pResult == NULL)
	{
		pResult = new CResult;
		pResult->Init();
		pResult->SetObjType(OBJTYPE_RESULT);
	}
	return pResult;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CResult::Init()
{

	m_pBg = CBg::Create();				//�w�i�̃N���G�C�g
	POINT posPoint;						
	GetCursorPos(&posPoint);			// �}�E�X���W���擾����
	//�{�^���̐���
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0), 
								D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_RESULT);

	//�n�C�X�R�AUI�̐���
	m_pHiScoreUI = CHiScoreUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.3f, SCORE_POS_Y + 270, 0), 
									D3DXVECTOR3(600, 150, 0),CHiScoreUI::HISCORETYPE_HISCORE);
	m_pHiScoreUI = CHiScoreUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCORE_POS_Y + 270, 0),
									D3DXVECTOR3(600, 150, 0), CHiScoreUI::HISCORETYPE_MYSCORE);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f), 
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0), OBJTYPE_CURSOR);

	m_pFade = CFade::Create();			//�t�F�[�h�̃N���G�C�g
	m_bUse = true;						//���U���g��ʂ̃X�C�b�`
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CResult::Uninit(void)
{
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CResult::Update(void)
{
	//�T�E���h
	CSound *pSound = CManager::GetSound();
	m_pFade->Update();
	m_pBg->Update();
	if (m_bUse==true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);
		m_pHiScore = CHIScore::Create();
		m_pScore = CScore::Create();
		m_bUse = false;
	}
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
		pSound->StopSound(CSound::SOUND_LABEL_RESULTBGM);
		CManager::SetMode(CManager::MODE_TITLE);
	}
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CResult::Draw(void)
{
}
