#ifndef _EXLPOSION_H_
#define _EXLPOSION_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
//オブジェクト2クラス宣言
class CExplosion :public CScene2D
{
public:
	CExplosion();				//コンストラクタ
	~CExplosion();				//デストラクタ

	//メンバ関数
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄


private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴンの位置
	int						m_nCounterAnim;//アニメーションカウンター
	int						m_nPatternAnim;//アニメーションパターンNo.

	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報


};
#endif 