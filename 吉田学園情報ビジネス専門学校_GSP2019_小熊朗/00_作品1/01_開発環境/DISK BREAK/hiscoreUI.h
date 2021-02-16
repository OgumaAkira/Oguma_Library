//*****************************************************************************
//
// ハイスコアUI処理 [hiscoreUI.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _HISCOREUI_H_
#define _HISCOREUI_H_

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

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CHiScoreUI :public CScene2D
{
public:

	//構造体定義(種類)
	typedef enum
	{
		HISCORETYPE_NONE = 0,		//何もない状態
		HISCORETYPE_HISCORE,		//ハイスコア
		HISCORETYPE_MYSCORE,		//自己スコア
		HISCORETYPE_MAX				//最大数
	}HISCORETYPE;

	CHiScoreUI(int nPriority = 8);														//コンストラクタ
	~CHiScoreUI();																		//デストラクタ

	//メンバ関数
	static CHiScoreUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);	//クリエイト関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);					//初期化関数
	void Uninit(void);																	//終了関数
	void Update(void);																	//更新関数
	void Draw(void);																	//描画関数
	static HRESULT Load(void);															//ロード関数
	static void UnLoad(void);															//アンロード関数

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;						//位置
	D3DXVECTOR3						m_size;						//大きさ
	D3DXCOLOR						m_col;						//カラー
	int								m_Cnt;						//カウント
	static LPDIRECT3DTEXTURE9		m_pTexture[2];				//テクスチャの情報
};
#endif 