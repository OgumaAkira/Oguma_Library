//*****************************************************************************
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "manager.h"
#include "game.h"
#include "bg.h"
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "number.h"
#include "speed.h"
#include "bulletUI.h"
#include "fade.h"
#include "combo.h"
#include <time.h>

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
CPlayer				*CGame::m_pPlayer = NULL;		//�v���C���[�̃|�C���^
CBg					*CGame::m_pBg = NULL;			//�w�i�̃|�C���^
CEnemy				*CGame::m_pEnemy = NULL;		//�G�l�~�[�̃|�C���^
CFade				*CGame::m_pFade = NULL;			//�t�F�[�h�̃|�C���^
CScore				*CGame::m_pScore = NULL;		//�X�R�A�̃|�C���^
CSpeed				*CGame::m_pSpeed = NULL;		//�X�s�[�h�A�b�v�̃|�C���^
CBulletUI			*CGame::m_pBulletUI = NULL;		//�c�e�̃|�C���^
CCombo				*CGame::m_pCombo = NULL;		//�R���{�̃|�C���^
CGame::GAMESTATE	CGame::m_GameState = {};		//�Q�[�����
int					CGame::m_nNumEnemy = 0;			//�G�̐�
int					CGame::m_GameSpeed = 0;			//�Q�[���X�s�[�h

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_nNumEnemy = 0;			//�G�̉�ʏ�̐�
	m_WholeEnemy = 0;			//�X�s�[�h�A�b�v�܂ł̓G�̐�
	m_GameSpeed = 5;			//�G�̃X�s�[�h
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CGame * CGame::Create()
{
	CGame *pGame = NULL;
	if (pGame == NULL)
	{
		pGame = new CGame;
		pGame->Init();
	}
	return pGame;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CGame::Init()
{
	
	srand((unsigned int)time(NULL));					//�����̏�����
	pSound = CManager::GetSound();						//�T�E���h�̏����擾
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);		//�Q�[��BGM�𗬂�
	m_GameState = GAMESTATE_NORMAL;						//�Q�[����ʂ̏�Ԃ͒ʏ���
	m_nNumEnemy = 0;									//��ʂɌ����G�̃J�E���g
	m_WholeEnemy = 0;									//�X�s�[�h�A�b�v�܂ł̓G�̃J�E���g
	POINT posPoint;										//�}�E�X�����擾
	GetCursorPos(&posPoint);							// �}�E�X���W���擾����
	m_pBg = CBg::Create();								//�w�i�̐���
	m_pBulletUI = CBulletUI::Create();					//�c�e�̐���
	m_pScore = CScore::Create();						//�X�R�A�̐���	
	m_pFade = CFade::Create();							//�t�F�[�h�̐���
	m_pCombo = CCombo::Create();						//�R���{�̐���

	//�G�̐���
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),	
							D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0),
							CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),
							D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
							CEnemy::ENEMYTYPE_NORMAL);
	
	//�^�[�Q�b�g�}�[�J�[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f),
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0),	
								OBJTYPE_PLAYER);
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CGame::Uninit(void)
{
	Release();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CGame::Update(void)
{

	m_pBg->Update();					//�w�i�̍X�V
	m_pFade->Update();					//�t�F�[�h�̍X�V
	m_pCombo->ComboAction();			//�R���{�A�N�V����

	//�Q�[����ʂ̏��
	switch (m_GameState)
	{
	//�ʏ��Ԃ̏ꍇ
	case GAMESTATE_NORMAL:
		//��ʏ�̓G���|����Čv10�̓|����Ă��Ȃ��ꍇ
		if (m_nNumEnemy >= 2 && m_WholeEnemy != 10)
		{
			m_nNumEnemy = 0;						//��ʏ�̓G�̐������Z�b�g
			//�G�l�~�[�̐���
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);

			m_pBulletUI->Loading();					//�c�e�̐���
		}
		//10�̂܂ł������ꍇ
		else if (m_WholeEnemy == 10)
		{
			m_GameState = GAMESTATE_SPEEDUP;		//�Q�[����ʂ̏�Ԃ��X�s�[�h�A�b�v�ɂ���
			m_pScore->AddScore(2500);				//2500�_�̃X�R�A�{�[�i�X�����_����
			//�X�s�[�h�A�b�v��UI��\��
			m_pSpeed = CSpeed::Create(D3DXVECTOR3(SPEEDUP_POS_X, SPEEDUP_POS_Y, 0), 
									D3DXVECTOR3(SPEEDUP_SIZE_X, SPEEDUP_SIZE_Y, 0));
			m_pSpeed->CSpeed::SetbUse(true);		//�X�s�[�h�A�b�v�̓_�ŕ\��
		}

		break;

	//�X�s�[�h�A�b�v�̏�Ԃ̏ꍇ
	case GAMESTATE_SPEEDUP:
		//�X�s�[�h�A�b�v��UI�_�ŃI��
		if (m_pSpeed->GetbUse() == true)
		{
				m_pSpeed->CSpeed::Update();
		}
		//�X�s�[�h�A�b�v��UI�_�ŃI�t
		else if (m_pSpeed->GetbUse() == false)
		{
			m_GameState = GAMESTATE_NORMAL;			//�ʏ��Ԃɂ���
			m_GameSpeed += 5;						//�G�̃X�s�[�h�A�b�v
			m_WholeEnemy = 0;						//�X�s�[�h�A�b�v�܂ł̓G�̐�
		}
		break;

	//�G��|�����Ƃ��̏��
	case GAMESTATE_ENEMYBREAK:
		m_nNumEnemy++;								//�G���J�E���g
		m_WholeEnemy++;								//�X�s�[�h�A�b�v�܂ł̓G���J�E���g
		m_pScore->AddScore(250);					//�G��|�����Ƃ��̃X�R�A
		m_GameState = GAMESTATE_NORMAL;				//�Q�[���̏�Ԃ�ʏ�ɂ���
		break;

	//�Q�[���̏�Ԃ��I�����ɂ���
	case GAMESTATE_END:
		//�t�F�[�h�̏�Ԃ�MAX�ɂ���
		if (CFade::GetFade() == (CFade::FADESTATE_MAX))
		{
			m_pFade->CFade::SetFade(CFade::FADESTATE_IN);			//�t�F�[�h�̏�Ԃ��t�F�[�h�C���ɂ���
		}
		//�t�F�[�h�̏�Ԃ�NONE�ɂ���
		if (CFade::GetFade() == (CFade::FADESTATE_NONE))
		{
			pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);			//�T�E���h���~�߂�
			CManager::SetMode(CManager::MODE_RESULT);				//�Q�[����ʂ��烊�U���g��ʂɑJ�ڂ���
		}
		break;

	default:
		break;
	}

}


//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CGame::Draw(void)
{
}

//*****************************************************************************
//�����擾�ʒu�֐�
//*****************************************************************************
D3DXVECTOR3 CGame::GetRandPos(void)
{
	// �ϐ��錾
	D3DXVECTOR3 returnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ԃ��l
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	// Random�Ȓl�𓾂�
	fPosX = (SCREEN_WIDTH / 2) + ((float)(rand() % 100000) 
				/100.0f - (float)(rand() % 100000) / 100.0f);
	fPosY = (SCREEN_HEIGHT / 2) + ((float)(rand() % 50000) 
				/ 100.0f - (float)(rand() % 50000) / 100.0f);

	
	returnPos = D3DXVECTOR3(fPosX, fPosY, 0.0f);		// �Ԃ��ʒu�Ɍ��ѕt����

	return returnPos;
}

//*****************************************************************************
//�����擾�����֐�
//*****************************************************************************
D3DXVECTOR3 CGame::GetRandMove(void)
{
	// �ϐ��錾
	D3DXVECTOR3 returnMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ԃ��l
	float fAngle = 0.0f;

	// Random�Ȋp�x�𓾂�
	fAngle = (float)(rand() % 314) / 100.0f - (float)(rand() % 314) / 100.0f;

	// �Ԃ��ړ��ʂɌ��ѕt����
	returnMove = D3DXVECTOR3(sinf(fAngle)*m_GameSpeed, cosf(fAngle)*m_GameSpeed, 0.0f);

	return returnMove;
}
