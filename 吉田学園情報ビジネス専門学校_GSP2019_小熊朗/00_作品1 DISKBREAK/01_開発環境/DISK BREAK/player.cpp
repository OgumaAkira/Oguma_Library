//*****************************************************************************
//
// プレイヤーの処理 [player.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
//インクルードファイル
#include "player.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayer::CPlayer(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);				// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);				// ポリゴン大きさ
	m_nColor = 0;								// ポリゴンの色

}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CPlayer::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CPlayer::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer = NULL;
	//プレイヤーのポインタが何も無かった場合
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init(pos, size);
	}
		return pPlayer;
}

//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x,pos.y , 0);		//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_nColor = 255;
	SetObjType(OBJTYPE_CURSOR);						//オブジェクト指定格納
	BirdTexture(m_pTexture);					//テクスチャの情報をscene2dに持ってく
	return S_OK;;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CPlayer::Update(void)
{

	POINT posPoint;
	GetCursorPos(&posPoint);											//マウス座標を取得する
	m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//位置
	Range();															//移動範囲
	m_pInput = CManager::GetMouse();									//マウスの入力情報取得
	CSound *pSound = CManager::GetSound();								//サウンド情報取得
	CScene2D::Update();													//オブジェクトの更新処理の取得
	MarkerColor();														//マーカーの色変え
	MarkerObject();														//マーカーのオブジェクト切り替え
	
	//ホイールボタンを入力した場合
	if (((CMouse*)m_pInput)->GetMousePrees(2) == true)
	{
		m_pos.x = SCREEN_WIDTH / 2;
		m_pos.y = SCREEN_HEIGHT / 2;
	}
	//右クリックを入力し、かつゲーム画面だった場合
	if (((CMouse*)m_pInput)->GetMousePrees(1) == true&&
		CManager::GetMode()==CManager::MODE_GAME)
	{
		CManager::SetMode(CManager::MODE_PAUSE);
	}
	//左クリックを入力したと場合
	else if (((CMouse*)m_pInput)->GetMouseTrigger(0) == true )
	{
		//ゲーム画面かつオブジェクトがプレイヤーかつフェード値が最大である場合
		if (CManager::GetMode() == CManager::MODE_GAME&&
			GetObjType()==OBJTYPE_PLAYER&&
			CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//弾の生成
			CBullet::Create(D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0),
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_PLAYER);

			//サウンド
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		//ゲーム画面以外でオブジェクトがカーソルかつフェード値が最大である場合
		else if(CManager::GetMode() != CManager::MODE_GAME&&
				GetObjType() == OBJTYPE_CURSOR&&
				CFade::GetFade()==CFade::FADESTATE_MAX)
		{
			//弾の生成
			CBullet::Create(D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0),
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_CURSOR);
		}
	}

	//プレイヤーの位置行進
	SetPosition(m_pos);
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//マーカーカラー関数
//*****************************************************************************
void CPlayer::MarkerColor(void)
{
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		//判定なし
		bool bHit = false;
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			//シーンの情報取得
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			//シーンに情報が入ってる場合
			if (pScene != NULL)
			{
				//オブジェクトの情報取得
				OBJTYPE objType = pScene->GetObjType();

				//敵の当たり判定
				if (objType == OBJTYPE_ENEMY
					&& CManager::GetMode() == CManager::MODE_GAME
					&& CGame::GetGameState() == CGame::GAMESTATE_NORMAL)
				{
					CEnemy *pEnemy = CManager::GetEnemy();						//敵の情報を取得
					CScene2D *pScene2d = (CScene2D*)pScene;						//キャスト
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//位置を取得
					D3DXVECTOR3 size = pScene2d->GetSize();						//大きさを取得

					//敵と照準があった時
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));				//色を赤に変化
						bHit = true;											//判定あり
					}
					else
					{
						//元の色に戻す
						SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
					}
				}
				//ボタンの当たり判定
				if (objType == OBJTYPE_BUTTON && CManager::GetMode() == CManager::MODE_PAUSE)
				{
					CButton *pButton = CManager::GetButton();					//敵の情報を取得
					CScene2D *pScene2d = (CScene2D*)pScene;						//キャスト
					D3DXVECTOR3 pos = pScene2d->GetPosition();					//位置を取得
					D3DXVECTOR3 size = pScene2d->GetSize();						//大きさを取得

					//ボタンと照準があった時
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));				//色を赤に変化
						bHit = true;											//判定あり
					}
					else
					{
						//元の色に戻す
						SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
					}
				}
			}
		}
		//敵と照準があった時
		if (bHit == true)
		{
			break;
		}
	}
}

//*****************************************************************************
//移動制限関数
//*****************************************************************************
void CPlayer::Range(void)
{
	//上の範囲
	if (m_pos.y - (m_size.y / 2) <= 0)
	{
		m_pos.y += 90;
	}
	//下の範囲
	if (m_pos.y + (m_size.y / 2) >= SCREEN_HEIGHT)
	{
		m_pos.y -= 90;
	}
	//右の範囲
	if (m_pos.x - (m_size.x ) <= 0)
	{
		m_pos.x += 90;
	}
	//左の範囲
	if (m_pos.x + (m_size.x / 2) >= SCREEN_WIDTH)
	{
		m_pos.x -= 90;
	}
}

//*****************************************************************************
//オブジェクト指定関数
//*****************************************************************************
void CPlayer::MarkerObject(void)
{
	//ゲーム画面の場合
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		SetObjType(OBJTYPE_PLAYER);		//プレイヤーを格納
	}
	//それ以外の場合
	else
	{
		SetObjType(OBJTYPE_CURSOR);		//カーソルを格納
	}
}

