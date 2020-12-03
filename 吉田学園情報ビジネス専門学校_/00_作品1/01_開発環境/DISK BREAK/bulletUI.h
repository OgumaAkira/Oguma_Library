#ifndef _BULLETUI_H_
#define _BULLETUI_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//オブジェクト2クラス宣言
class CBulletUI :public CScene
{
public:
	CBulletUI(int nPriority = 8);				//コンストラクタ
	~CBulletUI();				//デストラクタ

	//メンバ関数
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄
	static CBulletUI *Create();

	HRESULT Init();			//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetBulletCnt(int bulletcnt);
	int GetBulletCnt(void) { return m_BulletCnt; }
	void SetbUse(void) { m_bUse = true; }
	bool GetbUse(void) { return m_bUse; }
	void Loading(void);

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	int						m_nCounterAnim;//アニメーションカウンター
	int						m_nPatternAnim;//アニメーションパターンNo.
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報[テクスチャの数]
	CScene2D						*m_apScene2D[5];		//シーン2Dのポインタ配列
	int				m_BulletCnt;
	static bool				m_bUse;
};
#endif