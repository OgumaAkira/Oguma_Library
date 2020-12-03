//�C���N���[�h�t�@�C��
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
#include <time.h>

//�ÓI�����o�ϐ�
CPlayer				*CGame::m_pPlayer = NULL;	//�v���C���[�̃|�C���^
CBg					*CGame::m_pBg = NULL;	//�w�i�̃|�C���^
CEnemy				*CGame::m_pEnemy = NULL;	//�G�l�~�[�̃|�C���^
CFade				*CGame::m_pFade = NULL;		//�t�F�[�h�̃|�C���^
CScore				*CGame::m_pScore = NULL;	//�X�R�A�̃|�C���^
CSpeed				*CGame::m_pSpeed = NULL;	//�X�s�[�h�A�b�v�̃|�C���^
CBulletUI			*CGame::m_pBulletUI = NULL;	//�c�e�̃|�C���^
CGame::GAMESTATE	CGame::m_GameState = {};//�Q�[�����
int					CGame::m_nNumEnemy = 0;	//�G�̐�
int					CGame::m_GameSpeed = 0;//�Q�[���X�s�[�h
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_CounterGameState = 0;
	m_nNumEnemy = 0;
	m_WholeEnemy = 0;
	m_GameSpeed = 5;
}

CGame::~CGame()
{

}

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

HRESULT CGame::Init()
{
	// �����̏�����
	srand((unsigned int)time(NULL));
	//�T�E���h
	pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);
	m_GameState = GAMESTATE_NORMAL;
	m_nNumEnemy = 0;
	m_WholeEnemy = 0;
	// �}�E�X���W���擾����
	POINT posPoint;
	GetCursorPos(&posPoint);
	//�w�i�̃N���G�C�g
	m_pBg = CBg::Create();
	//�c�e�̐���
	m_pBulletUI = CBulletUI::Create();
	//�X�R�A�̐���
	m_pScore = CScore::Create();
	m_pFade = CFade::Create();
	//�G�l�~�[�̐���
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX, ENEMY_POSY, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX - 500, ENEMY_POSY+1000, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f), D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0),OBJTYPE_PLAYER);
	return S_OK;
}

void CGame::Uninit(void)
{
	Release();
}

void CGame::Update(void)
{

	m_pBg->Update();
	m_pFade->Update();
	switch (m_GameState)
	{
	case GAMESTATE_NORMAL:
		if (m_nNumEnemy >= 2 && m_WholeEnemy != 10)
		{
			m_nNumEnemy = 0;
			//�G�l�~�[�̐���
			/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX * m_GameSpeed, ENEMY_POSY, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX, ENEMY_POSY*m_GameSpeed, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);*/
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			//�c�e�̐���
			m_pBulletUI->Loading();
		}
		else if (m_WholeEnemy == 10)
		{
			m_GameState = GAMESTATE_SPEEDUP;
			m_pScore->AddScore(2500);

			m_pSpeed = CSpeed::Create(D3DXVECTOR3(SPEEDUP_POS_X, SPEEDUP_POS_Y, 0), D3DXVECTOR3(SPEEDUP_SIZE_X, SPEEDUP_SIZE_Y, 0));
			m_pSpeed->CSpeed::SetbUse(true);
		}
		break;

	case GAMESTATE_SPEEDUP:
		if (m_pSpeed->GetbUse() == true)
		{
				m_pSpeed->CSpeed::Update();
		}
		else if (m_pSpeed->GetbUse() == false)
		{
			m_GameState = GAMESTATE_NORMAL;
			m_GameSpeed += 5;
			m_WholeEnemy = 0;
		}
		break;
	case GAMESTATE_ENEMYBREAK:
		m_nNumEnemy++;
		m_WholeEnemy++;
		m_pScore->AddScore(100);
		m_GameState = GAMESTATE_NORMAL;
		break;

	case GAMESTATE_END:
		if (CFade::GetFade() == (CFade::FADESTATE_MAX))
		{
			m_pFade->CFade::SetFade(CFade::FADESTATE_IN);
		}
		if (CFade::GetFade() == (CFade::FADESTATE_NONE))
		{
			pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);
			CManager::SetMode(CManager::MODE_RESULT);
		}
		break;

	default:
		break;
	}

}


void CGame::Draw(void)
{
}

D3DXVECTOR3 CGame::GetRandPos(void)
{
	// �ϐ��錾
	D3DXVECTOR3 returnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �Ԃ��l
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	// Random�Ȓl�𓾂�
	fPosX = (SCREEN_WIDTH / 2) + ((float)(rand() % 100000) / 100.0f - (float)(rand() % 100000) / 100.0f);
	fPosY = (SCREEN_HEIGHT / 2) + ((float)(rand() % 50000) / 100.0f - (float)(rand() % 50000) / 100.0f);

	// �Ԃ��ʒu�Ɍ��ѕt����
	returnPos = D3DXVECTOR3(fPosX, fPosY, 0.0f);

	return returnPos;
}

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
