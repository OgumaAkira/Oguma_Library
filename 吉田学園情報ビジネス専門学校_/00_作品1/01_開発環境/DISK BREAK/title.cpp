//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "title.h"
#include "bg.h"
#include "enemy.h"
#include "player.h"
#include "button.h"
#include "sound.h"
#include "speed.h"
#include "fade.h"
#include "tutorial.h"
#include "titlelogo.h"
#include "hiscore.h"
#include "hiscoreUI.h"
CBg				*CTitle::m_pBg = NULL;	//�w�i�̃|�C���^
CFade			*CTitle::m_pFade = NULL;		//�t�F�[�h�̃|�C���^
CPlayer			*CTitle::m_pPlayer = NULL;	//�v���C���[�̃|�C���^
CButton			*CTitle::m_pButton = NULL;	//�{�^���̃|�C���^
CTitleLogo		*CTitle::m_pTitileLogo = NULL; //�^�C�g�����S�̃|�C���^
CTutorial		*CTitle::m_pTutorial = NULL;	//�`���[�g���A��
CHIScore		*CTitle::m_pHiScore = NULL;		//�n�C�X�R�A
CHiScoreUI		*CTitle::m_pHiScoreUI = NULL;		//�n�C�X�R�AUI


CTitle::CTitle(int nPriority) :CScene(nPriority)
{

}

CTitle::~CTitle()
{
}

CTitle * CTitle::Create()
{
	CTitle *pTitle = NULL;
	if (pTitle == NULL)
	{
		pTitle = new CTitle;
		pTitle ->Init();
		pTitle->SetObjType(OBJTYPE_TITLE);
	}
	return pTitle;
}

HRESULT CTitle::Init()
{
	//�w�i�̃N���G�C�g
	m_pBg = CBg::Create();
	// �}�E�X���W���擾����
	POINT posPoint;
	GetCursorPos(&posPoint);
	//�{�^���̐���
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0), D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_TITLE);
	m_pTutorial = CTutorial::Create(D3DXVECTOR3(1600, 700, 0), D3DXVECTOR3(500, 500, 0));
	m_pTitileLogo = CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH/2.05f, SCREEN_HEIGHT/2.5, 0), D3DXVECTOR3(1000,900,0));
	m_pHiScoreUI = CHiScoreUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.5, SCORE_POS_Y + 100, 0), D3DXVECTOR3(300,70,0),CHiScoreUI::HISCORETYPE_HISCORE);
	m_pHiScore = CHIScore::Create();
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x,(float)posPoint.y, 0), D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0),OBJTYPE_CURSOR);
	m_pFade = CFade::Create();
	bUse = true;
	return S_OK;
}

void CTitle::Uninit(void)
{
	Release();
}

void CTitle::Update(void)
{	
	//�T�E���h
	pSound = CManager::GetSound();
	if (bUse==true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_TITLEBGM);
		bUse = false;
	}
	m_pFade->Update();
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
		pSound->StopSound(CSound::SOUND_LABEL_TITLEBGM);
		CManager::SetMode(CManager::MODE_GAME);
	}
}

void CTitle::Draw(void)
{
}
