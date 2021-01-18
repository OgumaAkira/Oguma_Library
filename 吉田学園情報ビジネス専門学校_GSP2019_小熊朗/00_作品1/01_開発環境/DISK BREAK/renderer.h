//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//レンダリングのクラス宣言
//*****************************************************************************
class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//デバイスの取得
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	//メンバ関数
	void DrawFPS(void);

	//メンバ変数
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;			// フォントへのポインタ
};
#endif // !_RENDERER_H_

