#ifndef _HISCORE_H_
#define _HISCORE_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//スコアクラス宣言
class CHIScore :public CScene
{
public:

	CHIScore();				//コンストラクタ
	~CHIScore();				//デストラクタ

							//メンバ関数
	static CHIScore *Create(void);
	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static void WriteFile(int nScore);
	static int ReadFile(void);
private:
	//メンバ変数
	D3DXVECTOR3				m_move;			//移動量
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	int						m_nCounterAnim;//アニメーションカウンター
	int						m_nPatternAnim;//アニメーションパターンNo.
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	static int				m_nScore;
};
#endif