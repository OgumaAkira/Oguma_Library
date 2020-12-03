#ifndef _ENEMY_H_
#define _ENEMY_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"

//マクロ定義
#define MAX_ENEMY (2)

//オブジェクト2クラス宣言
class CEnemy :public CScene2D
{
public:

	//構造体定義
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYRSTATE_DEATH,
		ENEMYS_MAX,
	}ENEMYSTATE;

	//構造体定義
	typedef enum
	{
		ENEMYTYPE_NORMAL = 0,
		ENEMYTYPE_NORMAL1,
		ENEMYTYPE_NORMAL2,
		ENEMYTYPE_MAX
	}ENEMYTYPE;

	CEnemy(int nPriority = 5);				//コンストラクタ
	~CEnemy();				//デストラクタ

							//メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void CEnemy::HitDamege(int nDamege);
	bool Collision(D3DXVECTOR3*Pos, D3DXVECTOR3*PosOld, D3DXVECTOR3*Move, D3DXVECTOR3 * Size);
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3				m_pos;			// ポリゴンの現在位置
	D3DXVECTOR3				m_posold;		// ポリゴンの過去位置
	D3DXVECTOR3				m_move;			// ポリゴンの移動量
	D3DXVECTOR3				m_size;			// ポリゴン大きさ
	ENEMYSTATE				m_state;		//状態
	int						m_nCountState;	//ステートカウンター
	int						m_nHP;			//ヒットポイント
	bool					m_bLand;		//当たり判定
	bool					m_bContact;		//当たり判定2
	CInput* m_pInput;						//デバッグ操作用
	CScore* m_pScore;
	static LPDIRECT3DTEXTURE9		m_apTexture[2];		//テクスチャの情報
};
#endif 