//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _BUTTON_H_
#define _BUTTON_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_BUTTON (2)	//ボタンの最大数

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CButton :public CScene2D
{
public:

	//構造体定義(状態)
	typedef enum
	{
		BUTTONSTATE_NORMAL = 0,		//通常
		BUTTONSTATE_TITLE,			//タイトル
		BUTTONSTATE_RESULT,			//リザルト
		BUTTONSTATE_MAX,			//最大数
	}BUTTONSTATE;

	//構造体定義(種類)
	typedef enum
	{
		BUTTONTYPE_NORMAL = 0,		//通常
		BUTTONTYPE_TITLE,			//タイトル
		BUTTONTYPE_RESULT,			//リザルト
		BUTTONTYPE_MAX,				//最大数
	}BUTTONTYPE;

	CButton(int nPriority = 6);				//コンストラクタ
	~CButton();								//デストラクタ

	//メンバ関数
	static CButton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);			//初期化関数
	void Uninit(void);															//終了関数
	void Update(void);															//更新関数
	void Draw(void);															//描画関数
	void SetButton(void);														//ボタン状態格納関数
	BUTTONSTATE GetButton(void) { return m_state; }								//ボタン状態取得関数
	static HRESULT Load(void);													//ロード関数
	static void UnLoad(void);													//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;						// ポリゴンの位置
	D3DXVECTOR3						m_move;						// ポリゴンの移動量
	D3DXVECTOR3						m_size;						// ポリゴン大きさ
	BUTTONSTATE						m_state;					//状態
	int								m_nCountState;				//ステートカウンター
	bool							m_bUse;						//使用してるかどうか
	CInput							*m_pInput;					//デバッグ操作用
	CFade							*m_pFade;					//フェードのポインタ
	static LPDIRECT3DTEXTURE9		m_apTexture[2];				//テクスチャの情報
};
#endif 