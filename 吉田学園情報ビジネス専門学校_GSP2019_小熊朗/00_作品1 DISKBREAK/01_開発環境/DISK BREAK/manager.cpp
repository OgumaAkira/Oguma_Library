//*****************************************************************************
//
// マネージャー処理 [manager.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"		//マネージャーのヘッタ
#include "input.h"			//入力のヘッター
#include "renderer.h"		//レンダラーのヘッター
#include "scene.h"			//シーンのヘッター
#include "player.h"			//プレイヤー(ターゲットマーカ)のヘッター
#include "bg.h"				//背景のヘッター
#include "button.h"			//ボタンのヘッター
#include "sound.h"			//サウンドのヘッター
#include "explosion.h"		//爆発のヘッター
#include "enemy.h"			//敵のヘッター
#include "number.h"			//数字のヘッター
#include "score.h"			//スコア値のヘッター
#include "title.h"			//タイトル画面のヘッター
#include "game.h"			//ゲーム画面のヘッター
#include "result.h"			//リザルト画面のヘッター
#include "speed.h"			//速度上昇のヘッター
#include "fade.h"			//フェードのヘッター
#include "bulletUI.h"		//残弾のヘッター
#include "titlelogo.h"		//タイトルロゴのヘッター
#include "tutorial.h"		//チュートリアルのヘッター
#include "hiscoreUI.h"		//ハイスコアのヘッター
#include "combo.h"			//コンボのヘッター
//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
CRenderer		*CManager::m_pRenderer				= NULL;	//レンダリングのポインタ
CScene2D		*CManager::m_paScene[MAX_TEXTURE]	= {};	//シーンのポインタ
CInputKeyboard	*CManager::m_pInputKeyboard			= NULL;	//キーボード入力のポインタ7
CMouse			*CManager::m_pMouse					= NULL;	//エネミーのポインタ
CPlayer			*CManager::m_pPlayer				= NULL;	//プレイヤーのポインタ
CEnemy			*CManager::m_pEnemy					= NULL;	//プレイヤーのポインタ
CSound			*CManager::m_pSound					= NULL;	//サウンドのポインタ
CExplosion		*CManager::m_pExplosion				= NULL;	//エクスプロージョンのポインタ
CBullet			*CManager::m_pBullet				= NULL;	//バレットのポインタ
CButton			*CManager::m_pButton				= NULL; //ボタンのポインタ
CTitle			*CManager::m_pTitle					= NULL;	//タイトルのポインタ
CGame			*CManager::m_pGame					= NULL;	//ゲームのポインタ
CResult			*CManager::m_pResult				= NULL;	//バレットのポインタ
CFade			*CManager::m_pFade					= NULL;	//フェードのポインタ
CNumber			*CManager::m_pNumber				= NULL;	//ナンバーのポインタ
CScore			*CManager::m_pScore					= NULL;	//スコアのポインタ
CSpeed			*CManager::m_pSpeed					= NULL;	//スピードアップのポインタ
CCombo			*CManager::m_pCombo					= NULL;	//スピードアップのポインタ
CManager::MODE	 CManager::m_mode					= CManager::MODE_TITLE;	//初期モード
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu)
{
	//レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hInstance, hWnd, TRUE);

	//キーボード入力の生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//マウス入力の生成
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);

	//サウンドの生成
	m_pSound = new CSound;
	m_pSound->InitSound(hWnd);

	//プレイヤーのテクスチャロード
	CPlayer::Load();

	//エネミーのテクスチャロード
	CEnemy::Load();

	//バレットのテクスチャロード
	CBullet::Load();

	//爆発のテクスチャロード
	CExplosion::Load();
	
	//ボタンのテクスチャロード
	CButton::Load();

	//ナンバーのロード
	CNumber::Load();

	//スピードアップのロード
	CSpeed::Load();

	//背景のテクスチャロード
	CBg::Load();

	//残弾のテクスチャロード
	CBulletUI::Load();

	//フェードのテクスチャロード
	CFade::Load();

	//フェードのテクスチャロード
	CTutorial::Load();

	//タイトルロゴのテクスチャロード
	CTitleLogo::Load();

	//タイトルロゴのテクスチャロード
	CHiScoreUI::Load();

	//モードの情報を格納する
	SetMode(m_mode);

	return S_OK;
}
//*****************************************************************************
// 終了処理
//*****************************************************************************
void CManager::Uninit(void)
{
	//シーンの破棄
	CScene::ReleaseAll();

	//プレイヤーのアンロード
	CPlayer::UnLoad();

	//エネミーのアンロード
	CEnemy::UnLoad();

	//バレットのアンロード
	CBullet::UnLoad();

	//爆発のアンロード
	CExplosion::UnLoad();

	//ボタンのテクスチャロード
	CButton::UnLoad();

	//ナンバーのロード
	CNumber::UnLoad();

	//スピードアップのロード
	CSpeed::UnLoad();

	//背景のテクスチャロード
	CBg::UnLoad();

	//残弾のテクスチャロード
	CBulletUI::UnLoad();

	//フェードのアンロード
	CFade::UnLoad();

	//タイトルロゴのアンロード
	CTitleLogo::UnLoad();

	//ハイスコアのテクスチャロード
	CHiScoreUI::UnLoad();

	//フェードのテクスチャロード
	CTutorial::UnLoad();

	//キーボード入力破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//マウス入力破棄
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}

	//レンダラー破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
	}
	
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update(void)
{
	//入力の更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	//マウスの更新処理
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}

	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//モード情報
	switch (m_mode)
	{
		//タイトル画面
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->CTitle::Update();
		}
		break;
		//ゲーム画面
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->CGame::Update();
		}
		break;
		//リザルト画面
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->CResult::Update();
		}
		break;

	default:
		break;
	}
 }

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}
//*****************************************************************************
//モード情報格納関数
//*****************************************************************************
void CManager::SetMode(MODE mode)
{
	m_mode = mode;	//モードの値を格納

	//モード遷移
	switch (m_mode)
	{
		//タイトル画面遷移
	case MODE_TITLE:
		//リザルト画面を初期化
		if (m_pResult != NULL)	
		{
			m_pResult->CResult::Uninit();
			CScene::ReleaseAll();
			m_pResult = NULL;
		}
		//タイトル画面を出す
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;
		//ゲーム画面遷移
	case MODE_GAME:
		//タイトル画面を初期化
		if (m_pTitle != NULL)
		{
			m_pTitle->CTitle::Uninit();
			CScene::ReleaseAll();
			m_pTitle = NULL;
		}
		//ゲーム画面を出す
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;
		//リザルト画面遷移
	case MODE_RESULT:
		//ゲーム画面を初期化
		if (m_pGame != NULL)
		{
			m_pGame->CGame::Uninit();
			CScene::ReleaseAll();
			m_pGame = NULL;
		}
		//リザルト画面を出す
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	default:
		break;
	}
}
