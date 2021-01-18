//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//*****************************************************************************
class CBg;
class CPlayer;
class CFade;
class CButton;
class CScore;
class CSound;
class CHIScore;
class CHiScoreUI;

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CResult :public CScene
{
public:

	CResult(int nPriority=1);				//コンストラクタ
	~CResult();				//デストラクタ

	static CResult *Create();

	//プロトタイプ宣言
	HRESULT Init();		//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	//メンバ変数
	static CBg				*m_pBg;
	static CFade			*m_pFade;
	static CPlayer			*m_pPlayer;
	static CButton			*m_pButton;
	static CScore			*m_pScore;
	static CHIScore			*m_pHiScore;
	static CHiScoreUI		*m_pHiScoreUI;

	CInput* m_pInput;
	bool					m_bUse;
};
#endif