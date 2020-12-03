#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"

//前方宣言
class CPlayer;
class CEnemy;
class CInput;
class CButton;
class BulletUI;

//オブジェクト2クラス宣言
class CBullet :public CScene2D
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_CURSOR,
		BULLET_TYPE_PLAYER,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_MAX
	} BULLET_TYPE;
	
	CBullet();				//コンストラクタ
	~CBullet();				//デストラクタ

	//メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);		//初期化処理
	void Uninit(void);		//終了処理
	void Update(void);		//更新処理
	void Draw(void);		//描画処理
	static HRESULT Load(void);		//読み込み処理
	static void UnLoad(void);		//テクスチャの破棄

private:
	//メンバ変数
	D3DXVECTOR3						m_move;			//移動量
	D3DXVECTOR3						m_pos;			// ポリゴンの位置
	D3DXVECTOR3						m_size;			// ポリゴンの位置
	BULLET_TYPE						m_type;			//種類
	int								m_nHP;			//ヒットポイント
	static LPDIRECT3DTEXTURE9		m_pTexture;		//テクスチャの情報
	static CBulletUI				*m_pBulletUI;
};
#endif 