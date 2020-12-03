#ifndef _GAME_H_	//二重のインクルード防止のマクロ定義
#define _GAME_H_

#define _CRT_SECURE_WANINGS

//前方宣言
class CBg;
class CEnemy;
class CFade;
class CScore;
class CBulletUI;

//オブジェクト2クラス宣言
class CGame:public CScene
{
public:
	//構造体定義
	typedef enum
	{
		GAMESTATE_NONE = 0,		//何もない状態
		GAMESTATE_SPEEDUP,		//敵速度を上げる
		GAMESTATE_NORMAL,		//通常状態
		GAMESTATE_ENEMYBREAK,	//敵を倒した状況
		GAMESTATE_END,			//リザルト画面
		GAMESTATE_FINISH,		//ゲーム終了状態(画面遷移開始待ち状態）
		GAMESTATE_MAX

	}GAMESTATE;

	CGame(int nPriority=2) ;				//コンストラクタ
	~CGame();				//デストラクタ
	static CGame *Create();	//クリエイト

	//プロトタイプ宣言
	HRESULT Init();		//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//更新処理
	void SetEnemy(int enemy) { m_nNumEnemy = enemy; }
	static void SetGameState(GAMESTATE state) {m_GameState = state;};//ゲーム状態設定
	static GAMESTATE GetGameState(void) { return m_GameState; }	//ゲーム状態取得
	static int GetGameSpeed(void) { return m_GameSpeed; }//ゲームスピード取得
	D3DXVECTOR3 GetRandPos(void);
	D3DXVECTOR3 GetRandMove(void);
	static int GetEnemy(void) { return m_nNumEnemy; }
private:
	//メンバ変数
	static GAMESTATE			m_GameState;
	int							m_CounterGameState;
	int							m_WholeEnemy;
	static int					m_nNumEnemy;
	static int					m_GameSpeed;
	static CBg					*m_pBg;
	static CFade				*m_pFade;
	static CPlayer				*m_pPlayer;
	static CEnemy				*m_pEnemy;
	static CScore				*m_pScore;
	static CSpeed				*m_pSpeed;
	static CBulletUI			*m_pBulletUI;
	static CBullet				*m_pBullet;
	CSound *pSound;

};
#endif