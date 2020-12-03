#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"
//オブジェクト2クラス宣言
class CPlayer:public CScene2D
{
public:
	//構造体定義
	typedef enum
	{
		PLAYERSTATE_APPEAR = 0,
		PLAYERSTATE_NORMAL,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer(int nPriority = 11);				//コンストラクタ
	~CPlayer();				//デストラクタ

	//メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,OBJTYPE objtype);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	void HitDamege(int ndamege);	//ダメージ処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3						m_pos;			// ポリゴンの位置
	D3DXVECTOR3						m_size;			// ポリゴン大きさ
	int								m_nHP;			//ライフ
	PLAYERSTATE						m_state;		//状態
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	CFade* m_pFade;
	CInput* m_pInput;
};
#endif 