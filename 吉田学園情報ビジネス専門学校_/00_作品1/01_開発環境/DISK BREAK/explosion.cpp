//インクルードファイル
#include "explosion.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CExplosion::m_pTexture = NULL;		//テクスチャの情報

CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//位置
	m_size = D3DXVECTOR3(0, 0, 0);			//大きさ
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//アニメーションパターンNo.
}

CExplosion::~CExplosion()
{

}

CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	pExplosion->Init(pos, size);
	pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	return pExplosion;
}

HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	//弾の初期設定
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);//大きさ　
	SetSize(m_size);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_pTexture);

	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

void CExplosion::Update(void)
{
	m_pos = GetPosition();
	CScene2D::Update();

	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if (objType == OBJTYPE_EXPLOSION)
				{
					m_nCounterAnim++;
					if (m_nCounterAnim == 1)
					{
						m_nCounterAnim = 0;
						SetTex(D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0),
							D3DXVECTOR2(m_nPatternAnim * 0.125f - 1.0f, 0));
						m_nPatternAnim++;
					}
					if (m_nPatternAnim >= 16)
					{
						Uninit();
					}
				}
			}
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CExplosion::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}

void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
