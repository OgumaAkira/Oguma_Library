//インクルードファイル
#include "bulletUI.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CBulletUI::m_pTexture = {};		//テクスチャの情報
bool				CBulletUI::m_bUse = false;

//コンストラクタ
CBulletUI::CBulletUI(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//アニメーションパターンNo.
	for (int nCount = 0; nCount < 5; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//シーン2Dのポインタ配列
	}
}

//デストラクタ
CBulletUI::~CBulletUI()
{

}

//ロード関数
HRESULT CBulletUI::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(宇宙1)
	D3DXCreateTextureFromFile(pDevice,
		BULLETUI_TEXTURE, &m_pTexture);

	return S_OK;
}

//アンロード関数
void CBulletUI::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (m_pTexture != NULL)
		{
			//テクスチャの破棄
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//クリエイト関数
CBulletUI * CBulletUI::Create()
{
	CBulletUI *pBulletUI = NULL;
	if (pBulletUI == NULL)
	{
		pBulletUI = new CBulletUI;
		pBulletUI->Init();

	}
	return pBulletUI;
}

//初期化関数
HRESULT CBulletUI::Init()
{
	//残弾の生成
	for (int nCntInit = 0; nCntInit < 5; nCntInit++)
	{
		m_apScene2D[nCntInit] = NULL;
		if (m_apScene2D[nCntInit] == NULL)
		{
			m_apScene2D[nCntInit] = new CScene2D;
			m_apScene2D[nCntInit]->Init();
			m_apScene2D[nCntInit]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			m_apScene2D[nCntInit]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/1.03f - 50.0f * nCntInit,100,0));
			m_apScene2D[nCntInit]->SetSize(D3DXVECTOR3(50.0f, 100, 0));
			m_apScene2D[nCntInit]->BirdTexture(m_pTexture);

		}
	}
	m_BulletCnt = 0;	//残弾数
	m_bUse = false;
	return S_OK;
}

//終了関数
void CBulletUI::Uninit(void)
{
	//残弾の破棄
	for (int nCntUninit = 0; nCntUninit < 5; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			m_apScene2D[nCntUninit]->Uninit();
			delete m_apScene2D[nCntUninit];
			m_apScene2D[nCntUninit] = NULL;
		}
	}
	Release();
}

//更新関数
void CBulletUI::Update(void)
{
		if (m_bUse == true)
		{
 			m_apScene2D[m_BulletCnt]->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0));
			m_bUse = false;
			if (CGame::GetGameState() != CGame::GAMESTATE_END && CGame::GetGameState() != (CGame::GAMESTATE_SPEEDUP))
			{
				m_BulletCnt++;
 			}

		}
		if (m_BulletCnt == 5 && CGame::GetGameState() != (CGame::GAMESTATE_ENEMYBREAK) && CGame::GetGameState() != (CGame::GAMESTATE_SPEEDUP))
		{
			CGame::SetGameState(CGame::GAMESTATE_END);
		}
}

//描画関数
void CBulletUI::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < 5; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}

void CBulletUI::SetBulletCnt(int bulletcnt)
{
	m_BulletCnt = bulletcnt;
}

void CBulletUI::Loading(void)
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		//装填
		m_apScene2D[nCnt]->SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	m_BulletCnt = 0;
}
