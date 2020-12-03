#ifndef _HISCOREUI_H_
#define _HISCOREUI_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"

//オブジェクト2クラス宣言
class CHiScoreUI :public CScene2D
{
public:

	//構造体定義
	typedef enum
	{
		HISCORETYPE_HISCORE = 0,
		HISCORETYPE_MYSCORE,
		HISCORETYPE_MAX
	}HISCORETYPE;

	CHiScoreUI(int nPriority = 8);				//コンストラクタ
	~CHiScoreUI();				//デストラクタ

	//メンバ関数
	static CHiScoreUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	D3DXCOLOR				m_col;			//カラー
	static int				m_nFrameCnt;	//フラッシュカウント
	int						m_Cnt;			//カウント
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		//テクスチャの情報
};
#endif 