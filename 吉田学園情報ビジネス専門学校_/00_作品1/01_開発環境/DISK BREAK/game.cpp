//インクルードファイル
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

//静的メンバ変数
CPlayer				*CGame::m_pPlayer = NULL;	//プレイヤーのポインタ
CBg					*CGame::m_pBg = NULL;	//背景のポインタ
CEnemy				*CGame::m_pEnemy = NULL;	//エネミーのポインタ
CFade				*CGame::m_pFade = NULL;		//フェードのポインタ
CScore				*CGame::m_pScore = NULL;	//スコアのポインタ
CSpeed				*CGame::m_pSpeed = NULL;	//スピードアップのポインタ
CBulletUI			*CGame::m_pBulletUI = NULL;	//残弾のポインタ
CGame::GAMESTATE	CGame::m_GameState = {};//ゲーム状態
int					CGame::m_nNumEnemy = 0;	//敵の数
int					CGame::m_GameSpeed = 0;//ゲームスピード
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
	// 乱数の初期化
	srand((unsigned int)time(NULL));
	//サウンド
	pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);
	m_GameState = GAMESTATE_NORMAL;
	m_nNumEnemy = 0;
	m_WholeEnemy = 0;
	// マウス座標を取得する
	POINT posPoint;
	GetCursorPos(&posPoint);
	//背景のクリエイト
	m_pBg = CBg::Create();
	//残弾の生成
	m_pBulletUI = CBulletUI::Create();
	//スコアの生成
	m_pScore = CScore::Create();
	m_pFade = CFade::Create();
	//エネミーの生成
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX, ENEMY_POSY, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX - 500, ENEMY_POSY+1000, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
	//プレイヤーの生成
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
			//エネミーの生成
			/*m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX * m_GameSpeed, ENEMY_POSY, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(ENEMY_POSX, ENEMY_POSY*m_GameSpeed, 0), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);*/
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), CEnemy::ENEMYTYPE_NORMAL);
			//残弾の生成
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
	// 変数宣言
	D3DXVECTOR3 returnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 返す値
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	// Randomな値を得る
	fPosX = (SCREEN_WIDTH / 2) + ((float)(rand() % 100000) / 100.0f - (float)(rand() % 100000) / 100.0f);
	fPosY = (SCREEN_HEIGHT / 2) + ((float)(rand() % 50000) / 100.0f - (float)(rand() % 50000) / 100.0f);

	// 返す位置に結び付ける
	returnPos = D3DXVECTOR3(fPosX, fPosY, 0.0f);

	return returnPos;
}

D3DXVECTOR3 CGame::GetRandMove(void)
{
	// 変数宣言
	D3DXVECTOR3 returnMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 返す値
	float fAngle = 0.0f;

	// Randomな角度を得る
	fAngle = (float)(rand() % 314) / 100.0f - (float)(rand() % 314) / 100.0f;

	// 返す移動量に結び付ける
	returnMove = D3DXVECTOR3(sinf(fAngle)*m_GameSpeed, cosf(fAngle)*m_GameSpeed, 0.0f);

	return returnMove;
}
