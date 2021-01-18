//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
//*****************************************************************************
class CBg;
class CFade;
class CPlayer;
class CButton;
class CSound;
class CTitleLogo;
class CTutorial;
class CHIScore;
class CHiScoreUI;

//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority=1);				//コンストラクタ
	~CTitle();				//デストラクタ
	static CTitle *Create();

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
	static CTitleLogo		*m_pTitileLogo;
	static CTutorial		*m_pTutorial;
	static CHIScore			*m_pHiScore;
	static CHiScoreUI		*m_pHiScoreUI;
	bool bUse;
	CSound *pSound;
	CInput* m_pInput;
};
#endif