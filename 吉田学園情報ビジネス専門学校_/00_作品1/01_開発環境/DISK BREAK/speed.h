#ifndef _SPEED_H_
#define _SPEED_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
class CSound;

//マクロ定義
#define	MAX_FLASHING	(30)
//オブジェクト2クラス宣言
class CSpeed :public CScene2D
{
public:

	CSpeed(int nPriority=7);				//コンストラクタ
	~CSpeed();				//デストラクタ

	//メンバ関数
	static CSpeed *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄
	static void SetbUse(bool bUse) { m_bUse = bUse; }
	static bool GetbUse(void) { return m_bUse; }

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	D3DXCOLOR				m_col;			//カラー
	static int				m_nFrameCnt;	//フラッシュカウント
	int						m_Cnt;			//カウント
	bool					m_bUse2;
	static bool				m_bUse;			//使用してるかどうか
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	CSound					*pSound;		//サウンド
};
#endif 