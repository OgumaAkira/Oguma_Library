#ifndef _BUTTON_H_
#define _BUTTON_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"

//マクロ定義
#define MAX_BUTTON (2)

//オブジェクト2クラス宣言
class CButton :public CScene2D
{
public:

	//構造体定義
	typedef enum
	{
		BUTTONSTATE_NORMAL = 0,
		BUTTONSTATE_TITLE,
		BUTTONSTATE_RESULT,
		BUTTONSTATE_MAX,
	}BUTTONSTATE;

	//構造体定義
	typedef enum
	{
		BUTTONTYPE_NORMAL = 0,
		BUTTONTYPE_TITLE,
		BUTTONTYPE_RESULT,
		BUTTONTYPE_MAX,
	}BUTTONTYPE;

	CButton(int nPriority = 6);				//コンストラクタ
	~CButton();				//デストラクタ

	//メンバ関数
	static CButton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetButton(void);	//入力処理
	BUTTONSTATE GetButton(void) { return m_state; }
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	BUTTONSTATE				m_state;		//状態
	int						m_nCountState;	//ステートカウンター
	bool					m_bUse;			//使用してるかどうか
	CInput* m_pInput;						//デバッグ操作用
	CFade					*m_pFade;
	static LPDIRECT3DTEXTURE9		m_apTexture[2];		//テクスチャの情報
};
#endif 