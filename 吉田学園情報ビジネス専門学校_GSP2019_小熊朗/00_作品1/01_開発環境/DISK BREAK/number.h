//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CScene;

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CNumber
{
public:
	CNumber();				//コンストラクタ
	~CNumber();				//デストラクタ

	//メンバ関数
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_pos); }
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(m_size); }

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファの情報
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴンの大きさ
	D3DXVECTOR2				m_tex;			//テスクチャ
	D3DXCOLOR				m_color;		//カラー
	CScene					*m_pScene;		//シーンのポインタ
};
#endif