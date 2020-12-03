//インクルードファイル
#include "bg.h"
#include "button.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9	CBg::m_pTexture[3] = {};		//テクスチャの情報

//コンストラクタ
CBg::CBg(int nPriority) :CScene(nPriority)
{
	m_move =D3DXVECTOR3(0,0,0);			//移動量
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//アニメーションパターンNo.
	for (int nCount = 0; nCount < 3; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//シーン2Dのポインタ配列
	}
}

//デストラクタ
CBg::~CBg()
{

}

//ロード関数
HRESULT CBg::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(宇宙1)
	D3DXCreateTextureFromFile(pDevice,
		BG_SKY_TEXTURE, &m_pTexture[0]);

	//テクスチャの読み込み（宇宙2）
	D3DXCreateTextureFromFile(pDevice,
		BG_MOUNTAIN1_TEXTURE, &m_pTexture[1]);

	//テクスチャの読み込み（宇宙3）
	D3DXCreateTextureFromFile(pDevice,
		BG_MOUNTAIN2_TEXTURE, &m_pTexture[2]);

	return S_OK;
}

//アンロード関数
void CBg::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			//テクスチャの破棄
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//クリエイト関数
CBg * CBg::Create()
{
	CBg *pBg=NULL;
	if (pBg == NULL)
	{
		pBg = new CBg;
		pBg->Init();
	
	}
		return pBg;
}

//初期化関数
HRESULT CBg::Init()
{
	//背景の生成
	for (int nCntInit = 0; nCntInit < 3; nCntInit++)
	{
		m_apScene2D[nCntInit] = NULL;

		if (m_apScene2D[nCntInit] == NULL)
		{
			m_apScene2D[nCntInit] = new CScene2D;
			m_apScene2D[nCntInit]->Init();
			m_apScene2D[nCntInit]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2 ,0));
			m_apScene2D[nCntInit]->SetSize(D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT , 0));
			m_apScene2D[nCntInit]->BirdTexture(m_pTexture[nCntInit]);
			m_apScene2D[nCntInit]->SetObjType(OBJTYPE_BG);
		}
	}
	return S_OK;
}

//終了関数
void CBg::Uninit(void)
{
	//背景の破棄
	for (int nCntUninit = 0; nCntUninit < 3; nCntUninit++)
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
void CBg::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		break;
	
	case CManager::MODE_GAME:
	//背景のテクスチャ座標設定
	for (int nCntUninit = 0; nCntUninit < 3; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			
			m_move += D3DXVECTOR3(0.001f , 0, 0);//移動量
			//背景をm_nPatternAnimで数を動かしてアニメーションする。
			m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0),
				D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0));
		}
	}
	break;

	case CManager::MODE_RESULT:
		//背景のテクスチャ座標設定
		for (int nCntUninit = 0; nCntUninit < 3; nCntUninit++)
		{
			if (m_apScene2D[nCntUninit] != NULL)
			{

				m_move += D3DXVECTOR3(0.001f, 0, 0);//移動量
				//背景をm_nPatternAnimで数を動かしてアニメーションする。
				m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f)), 0),
					D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f) + 1.0f), 0));
			}
		}
		break;
	default:
		break;
	}
}

//描画関数
void CBg::Draw(void)
{
	//背景の描画
	for (int nCntDraw = 0; nCntDraw < 3; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}
