//*****************************************************************************
//
// 背景の処理 [bg.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//*****************************************************************************
//背景クラス宣言
//*****************************************************************************
class CBg :public CScene
{
public:

	CBg(int nPriority = 1);									//コンストラクタ
	~CBg();													//デストラクタ

	//メンバ関数
	static HRESULT Load(void);								//ロード関数
	static void UnLoad(void);								//テクスチャの破棄
	static CBg *Create();

	HRESULT Init();											//初期化処理
	void Uninit(void);										//終了処理
	void Update(void);										//更新処理
	void Draw(void);										//描画処理

private:
	//メンバ変数
	D3DXVECTOR3				m_move;							//移動量
	D3DXVECTOR3				m_pos;							// ポリゴンの位置
	D3DXVECTOR3				m_size;							// ポリゴン大きさ
	int						m_nCounterAnim;					//アニメーションカウンター
	int						m_nPatternAnim;					//アニメーションパターンNo.

	static LPDIRECT3DTEXTURE9		m_pTexture[3];			//テクスチャの情報[テクスチャの数]
	CScene2D						*m_apScene2D[3];		//シーン2Dのポインタ配列

};
#endif