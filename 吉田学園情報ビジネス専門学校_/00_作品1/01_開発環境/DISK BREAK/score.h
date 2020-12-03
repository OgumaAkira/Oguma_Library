#ifndef _SCORE_H_
#define _SCORE_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"
#include "hiscore.h"

//スコアクラス宣言
class CScore :public CScene
{
public:

	CScore(int nPriority = 7);				//コンストラクタ
	~CScore();				//デストラクタ

	//メンバ関数
	static CScore *Create(void);
	HRESULT Init(void);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void SetScore(int nScore);//スコア値格納処理
	void AddScore(int nScore);//加算スコア処理
	int ReadFile(void);
	void WriteFile(void);
	static int GetScore(void) { return m_nScore; }
private:
	//メンバ変数
	D3DXVECTOR3				m_move;			//移動量
	D3DXVECTOR3				m_pos;			// ポリゴンの位置
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	int						m_nCounterAnim;//アニメーションカウンター
	int						m_nPatternAnim;//アニメーションパターンNo.
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//シーン2Dのポインタ配列
	static int						m_nScore;
};
#endif