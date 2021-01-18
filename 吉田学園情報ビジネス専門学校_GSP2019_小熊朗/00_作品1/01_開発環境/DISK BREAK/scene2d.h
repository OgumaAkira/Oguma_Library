//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D(int nPriority = 14);				//コンストラクタ
	~CScene2D();				//デストラクタ

	//メンバ関数
	static CScene2D *Create();
	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2); 
	void SetColor(D3DXCOLOR col) { m_color=col; }
	void BirdTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetSize();
	D3DXVECTOR2	GetTex();
	D3DXCOLOR	GetColor();
	
private:
	//メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファの情報
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴンの大きさ
	D3DXVECTOR2				m_tex;			//テスクチャ
	D3DXCOLOR				m_color;		//カラー
	float					m_fMoverot;		//回転速度

};
#endif 