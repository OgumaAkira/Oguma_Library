//*****************************************************************************
//
// ゲーム画面の処理 [game.h]
// Author : 小熊朗
//
//*****************************************************************************
#ifndef _GAME_H_	//二重のインクルード防止のマクロ定義
#define _GAME_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define _CRT_SECURE_WANINGS

//*****************************************************************************
//前方宣言
//*****************************************************************************
class CBg;
class CEnemy;
class CFade;
class CScore;
class CBulletUI;

//*****************************************************************************
//ゲーム画面のクラス宣言
//*****************************************************************************
class CGame:public CScene
{
public:
	//構造体定義(状態)
	typedef enum
	{
		GAMESTATE_NONE = 0,		//何もない状態
		GAMESTATE_SPEEDUP,		//敵速度を上げる
		GAMESTATE_NORMAL,		//通常状態
		GAMESTATE_ENEMYBREAK,	//敵を倒した状況
		GAMESTATE_END,			//リザルト画面
		GAMESTATE_FINISH,		//ゲーム終了状態(画面遷移開始待ち状態）
		GAMESTATE_MAX			//最大数

	}GAMESTATE;

	CGame(int nPriority=2) ;												//コンストラクタ
	~CGame();																//デストラクタ

	//メンバ関数
	static CGame *Create();													//クリエイト
	HRESULT Init();															//初期化処理
	void Uninit(void);														//終了処理
	void Update(void);														//更新処理
	void Draw(void);														//更新処理
	void SetEnemy(int enemy) { m_nNumEnemy = enemy; }						//敵の情報格納関数
	static void SetGameState(GAMESTATE state) {m_GameState = state;};		//ゲーム状態設定
	static GAMESTATE GetGameState(void) { return m_GameState; }				//ゲーム状態取得
	static int GetGameSpeed(void) { return m_GameSpeed; }					//ゲームスピード取得
	D3DXVECTOR3 GetRandPos(void);											//敵の乱数配置位置取得関数
	D3DXVECTOR3 GetRandMove(void);											//敵の乱数配置慣性取得関数
	static int GetEnemy(void) { return m_nNumEnemy; }						//敵の情報取得関数
private:
	//メンバ変数
	static GAMESTATE			m_GameState;			//状態
	int							m_WholeEnemy;			//敵のスピードアップまでの数
	static int					m_nNumEnemy;			//敵の画面に現れる敵の数
	static int					m_GameSpeed;			//敵の移動速度
	static CBg					*m_pBg;					//背景のポインタ
	static CFade				*m_pFade;				//フェードポインタ
	static CPlayer				*m_pPlayer;				//プレイヤーのポインタ
	static CEnemy				*m_pEnemy;				//敵のポインタ
	static CScore				*m_pScore;				//スコアのポインタ
	static CSpeed				*m_pSpeed;				//スピードのポインタ
	static CBulletUI			*m_pBulletUI;			//残弾のポインタ
	static CBullet				*m_pBullet;				//弾のポインタ
	CSound						*pSound;				//サウンドのポインタ
};
#endif