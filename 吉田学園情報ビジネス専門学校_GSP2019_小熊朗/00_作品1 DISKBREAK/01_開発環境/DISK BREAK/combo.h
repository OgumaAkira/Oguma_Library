//*****************************************************************************
//
// コンボの処理 [combo.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _COMBO_H_
#define _COMBO_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"
#include "hiscore.h"
#include "score.h"

//*****************************************************************************
//インクルードファイル
//*****************************************************************************

//*****************************************************************************
//スコアのクラス宣言
//*****************************************************************************
class CCombo :public CScene
{
public:

	CCombo(int nPriority = 7);							//コンストラクタ
	~CCombo();											//デストラクタ

	//メンバ関数
	static CCombo *Create(void);						//クリエイト関数
	HRESULT Init(void);									//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	void ComboAction(void);								//コンボ処理

private:
	//メンバ変数
	D3DXVECTOR3				m_move;								//移動量
	D3DXVECTOR3				m_pos;								//ポリゴンの位置
	D3DXVECTOR3				m_size;								//ポリゴン大きさ
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	CScore					*m_pScore;							//スコアのポインタ
	int						m_nColor;							//色数値
	int						m_nCombo;							//コンボ数
	int						m_nComboScore;						//コンボのスコア値
	int						m_nComboCountFrame;					//コンボ表示のフレーム数
};
#endif
