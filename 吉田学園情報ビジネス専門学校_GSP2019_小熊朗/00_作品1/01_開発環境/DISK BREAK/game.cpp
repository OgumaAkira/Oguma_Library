//*****************************************************************************
//
// ゲーム画面処理 [game.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
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
//静的メンバ変数
//*****************************************************************************
CPlayer				*CGame::m_pPlayer = NULL;		//プレイヤーのポインタ
CBg					*CGame::m_pBg = NULL;			//背景のポインタ
CEnemy				*CGame::m_pEnemy = NULL;		//エネミーのポインタ
CFade				*CGame::m_pFade = NULL;			//フェードのポインタ
CScore				*CGame::m_pScore = NULL;		//スコアのポインタ
CSpeed				*CGame::m_pSpeed = NULL;		//スピードアップのポインタ
CBulletUI			*CGame::m_pBulletUI = NULL;		//残弾のポインタ
CCombo				*CGame::m_pCombo = NULL;		//コンボのポインタ
CGame::GAMESTATE	CGame::m_GameState = {};		//ゲーム状態
int					CGame::m_nNumEnemy = 0;			//敵の数
int					CGame::m_GameSpeed = 0;			//ゲームスピード

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_nNumEnemy = 0;			//敵の画面上の数
	m_WholeEnemy = 0;			//スピードアップまでの敵の数
	m_GameSpeed = 5;			//敵のスピード
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame::~CGame()
{

}

//*****************************************************************************
//クリエイト関数
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
//初期化関数
//*****************************************************************************
HRESULT CGame::Init()
{
	
	srand((unsigned int)time(NULL));					//乱数の初期化
	pSound = CManager::GetSound();						//サウンドの情報を取得
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);		//ゲームBGMを流す
	m_GameState = GAMESTATE_NORMAL;						//ゲーム画面の状態は通常状態
	m_nNumEnemy = 0;									//画面に現れる敵のカウント
	m_WholeEnemy = 0;									//スピードアップまでの敵のカウント
	POINT posPoint;										//マウス情報を取得
	GetCursorPos(&posPoint);							// マウス座標を取得する
	m_pBg = CBg::Create();								//背景の生成
	m_pBulletUI = CBulletUI::Create();					//残弾の生成
	m_pScore = CScore::Create();						//スコアの生成	
	m_pFade = CFade::Create();							//フェードの生成
	m_pCombo = CCombo::Create();						//コンボの生成

	//敵の生成
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),	
							D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0),
							CEnemy::ENEMYTYPE_NORMAL);
	m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(),
							D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
							CEnemy::ENEMYTYPE_NORMAL);
	
	//ターゲットマーカーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f),
								D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0),	
								OBJTYPE_PLAYER);
	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CGame::Uninit(void)
{
	Release();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CGame::Update(void)
{

	m_pBg->Update();					//背景の更新
	m_pFade->Update();					//フェードの更新
	m_pCombo->ComboAction();			//コンボアクション

	//ゲーム画面の状態
	switch (m_GameState)
	{
	//通常状態の場合
	case GAMESTATE_NORMAL:
		//画面上の敵が倒されて計10体倒されていない場合
		if (m_nNumEnemy >= 2 && m_WholeEnemy != 10)
		{
			m_nNumEnemy = 0;						//画面上の敵の数をリセット
			//エネミーの生成
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);
			m_pEnemy = CEnemy::Create(GetRandPos(), GetRandMove(), 
									D3DXVECTOR3(ENEMY_SIZEX, ENEMY_SIZEY, 0), 
									CEnemy::ENEMYTYPE_NORMAL);

			m_pBulletUI->Loading();					//残弾の生成
		}
		//10体までいった場合
		else if (m_WholeEnemy == 10)
		{
			m_GameState = GAMESTATE_SPEEDUP;		//ゲーム画面の状態をスピードアップにする
			m_pScore->AddScore(2500);				//2500点のスコアボーナスを加点する
			//スピードアップのUIを表示
			m_pSpeed = CSpeed::Create(D3DXVECTOR3(SPEEDUP_POS_X, SPEEDUP_POS_Y, 0), 
									D3DXVECTOR3(SPEEDUP_SIZE_X, SPEEDUP_SIZE_Y, 0));
			m_pSpeed->CSpeed::SetbUse(true);		//スピードアップの点滅表示
		}

		break;

	//スピードアップの状態の場合
	case GAMESTATE_SPEEDUP:
		//スピードアップのUI点滅オン
		if (m_pSpeed->GetbUse() == true)
		{
				m_pSpeed->CSpeed::Update();
		}
		//スピードアップのUI点滅オフ
		else if (m_pSpeed->GetbUse() == false)
		{
			m_GameState = GAMESTATE_NORMAL;			//通常状態にする
			m_GameSpeed += 5;						//敵のスピードアップ
			m_WholeEnemy = 0;						//スピードアップまでの敵の数
		}
		break;

	//敵を倒したときの状態
	case GAMESTATE_ENEMYBREAK:
		m_nNumEnemy++;								//敵をカウント
		m_WholeEnemy++;								//スピードアップまでの敵をカウント
		m_pScore->AddScore(250);					//敵を倒したときのスコア
		m_GameState = GAMESTATE_NORMAL;				//ゲームの状態を通常にする
		break;

	//ゲームの状態を終了時にする
	case GAMESTATE_END:
		//フェードの状態をMAXにする
		if (CFade::GetFade() == (CFade::FADESTATE_MAX))
		{
			m_pFade->CFade::SetFade(CFade::FADESTATE_IN);			//フェードの状態をフェードインにする
		}
		//フェードの状態をNONEにする
		if (CFade::GetFade() == (CFade::FADESTATE_NONE))
		{
			pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM);			//サウンドを止める
			CManager::SetMode(CManager::MODE_RESULT);				//ゲーム画面からリザルト画面に遷移する
		}
		break;

	default:
		break;
	}

}


//*****************************************************************************
//描画関数
//*****************************************************************************
void CGame::Draw(void)
{
}

//*****************************************************************************
//乱数取得位置関数
//*****************************************************************************
D3DXVECTOR3 CGame::GetRandPos(void)
{
	// 変数宣言
	D3DXVECTOR3 returnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 返す値
	float fPosX = 0.0f;
	float fPosY = 0.0f;

	// Randomな値を得る
	fPosX = (SCREEN_WIDTH / 2) + ((float)(rand() % 100000) 
				/100.0f - (float)(rand() % 100000) / 100.0f);
	fPosY = (SCREEN_HEIGHT / 2) + ((float)(rand() % 50000) 
				/ 100.0f - (float)(rand() % 50000) / 100.0f);

	
	returnPos = D3DXVECTOR3(fPosX, fPosY, 0.0f);		// 返す位置に結び付ける

	return returnPos;
}

//*****************************************************************************
//乱数取得慣性関数
//*****************************************************************************
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
