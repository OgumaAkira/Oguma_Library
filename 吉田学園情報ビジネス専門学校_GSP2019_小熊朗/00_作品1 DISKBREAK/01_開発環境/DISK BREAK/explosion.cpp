//*****************************************************************************
//
// 爆発の処理 [explosion.cpp]
// Author : 小熊 朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "explosion.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CExplosion::m_pTexture = NULL;		//テクスチャの情報

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//位置
	m_size = D3DXVECTOR3(0, 0, 0);			//大きさ
	m_nCounterAnim = 0;						//アニメーションカウント
	m_nPatternAnim = 0;						//アニメーションパターンNo.
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CExplosion::~CExplosion()
{

}

//*****************************************************************************
//クリエイト関数
//*****************************************************************************
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = NULL;
	//敵のポインタが何もなかった場合
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		pExplosion->Init(pos, size);
		pExplosion->SetObjType(OBJTYPE_EXPLOSION);		//オブジェクト指定
	}
		return pExplosion;
}

//*****************************************************************************
//読み込み関数
//*****************************************************************************
HRESULT CExplosion::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//アンロード関数
//*****************************************************************************
void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//*****************************************************************************
//初期化関数
//*****************************************************************************
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{

	CScene2D::Init();
	//弾の初期設定
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);						//位置格納
	m_size = D3DXVECTOR3(size.x, size.y, 0);//大きさ
	SetSize(m_size);						//大きさ格納	
	m_nCounterAnim = 0;						//アニメーションカウント
	m_nPatternAnim = 0;						//アニメーションパターンNo.
	BirdTexture(m_pTexture);				//テクスチャの情報をscene2dに持ってく

	return S_OK;
}

//*****************************************************************************
//終了関数
//*****************************************************************************
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新関数
//*****************************************************************************
void CExplosion::Update(void)
{
	m_pos = GetPosition();			//更新位置を取得
	CScene2D::Update();

	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			
			//シーンのポインタが何も無かった場合
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//オブジェクトタイプ指定が「爆発」だった場合
				if (objType == OBJTYPE_EXPLOSION)
				{
					//爆発のアニメーション
					m_nCounterAnim++;
					if (m_nCounterAnim == 1)
					{
						m_nCounterAnim = 0;
						SetTex(D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0),
							D3DXVECTOR2(m_nPatternAnim * 0.125f - 1.0f, 0));
						m_nPatternAnim++;
					}
					//アニメーションパターンが16まで行った場合
					if (m_nPatternAnim >= 16)
					{
						Uninit();
					}
				}
			}
		}
	}
}

//*****************************************************************************
//描画関数
//*****************************************************************************
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
