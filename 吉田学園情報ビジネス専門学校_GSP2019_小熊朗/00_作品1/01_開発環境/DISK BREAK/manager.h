//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CScene;
class CScene2D;
class CInput;
class CInputKeyboard;
class CMouse;
class CPlayer;
class CTitle;
class CResult;
class CGame;
class CFade;
class CSound;
class CScore;
class CExplosion;
class CBullet;
class CEnemy;
class CButton;
class CNumber;
class CSpeed;
//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CManager
{
public:
	//構造体
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;

	CManager();				//コンストラクタ
	~CManager();				//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }		//レンダラーの情報取得関数
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pInputKeyboard; }//キーボード入力情報取得関数
	static CMouse			*GetMouse(void)			{ return m_pMouse; }		//マウス入力情報取得関数
	static CPlayer			*GetPlayer(void)		{ return m_pPlayer; }		//プレイヤー情報取得関数
	static CEnemy			*GetEnemy(void)			{ return m_pEnemy; }		//エネミー情報取得関数
	static CSound			*GetSound(void)			{ return m_pSound; }		//サウンド情報取得関数
	static CExplosion		*GetExplosion(void)		{ return m_pExplosion; }	//爆発情報取得関数
	static CBullet			*GetBullet(void)		{ return m_pBullet; }		//バレット情報取得関数
	static CButton			*GetButton(void)		{ return m_pButton; }		//ボタン情報取得関数
	static CScore			*GetScore(void)			{ return m_pScore; }		//スコア取得関数
	static CFade			*GetFade(void)			{ return m_pFade; }			//フェード取得関数
	static MODE				GetMode(void)			{ return m_mode; }			//モード情報取得関数
	static void				SetMode(MODE mode);

private:
	//メンバ変数
	static CRenderer		*m_pRenderer;
	static CScene2D			*m_paScene[MAX_TEXTURE];
	static CInputKeyboard	*m_pInputKeyboard;
	static CMouse			*m_pMouse;
	static CPlayer			*m_pPlayer;
	static CSound			*m_pSound;
	static CExplosion		*m_pExplosion;
	static CBullet			*m_pBullet;
	static CTitle			*m_pTitle;
	static CResult			*m_pResult;
	static CGame			*m_pGame;
	static MODE				m_mode;
	static CFade			*m_pFade;
	static CEnemy			*m_pEnemy;
	static CScore				*m_pScore;
	static CButton			*m_pButton;
	static CNumber			*m_pNumber;
	static CSpeed			*m_pSpeed;
	CInput* m_pInput;
};
#endif