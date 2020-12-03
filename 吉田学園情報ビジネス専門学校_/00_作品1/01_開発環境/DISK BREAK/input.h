#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"

//インプットクラス宣言
class CInput
{
public:
	CInput();				//コンストラクタ

	//純粋仮想関数
	virtual ~CInput();				//デストラクタ
	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual void Draw(void);		//描画処理

	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
private:
};

//キーボード入力のクラス
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	bool GetKeyPrees(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateOld[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

class CMouse:public CInput
{
public:
	CMouse();
	~CMouse();

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	bool GetMousePrees(int nKey);
	bool GetMouseTrigger(int nKey);
	bool GetMouseRelease(int nKey);

private:
	DIMOUSESTATE m_CurrentMouseState;		//!< マウスの現在の入力情報
	DIMOUSESTATE m_PrevMouseState;			//!< マウスの一フレーム前の入力情報

	BYTE m_aMouseState[NUM_MOUSE_MAX];
	BYTE m_aMouseStateOld[NUM_MOUSE_MAX];
	BYTE m_aMouseStatePress[NUM_MOUSE_MAX];// マウスのプレス情報
	BYTE m_aMouseStateTrigger[NUM_MOUSE_MAX];// マウスのトリガー
	BYTE m_aMouseStateRelease[NUM_MOUSE_MAX];
};


#endif
