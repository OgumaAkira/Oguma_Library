//インクルードファイル
#include "fade.h"
//静的メンバ変数
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;		//テクスチャの情報
CFade::FADESTATE	CFade::m_FadeState = {};		//使用してるかどうか
int					CFade::m_color = 0;
//コンストラクタ
CFade::CFade(int nPriority) :CScene(nPriority)
{
	m_move = D3DXVECTOR3(0, 0, 0);			//移動量
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_pScene2D = NULL;		//シーン2Dのポインタ配列
	m_bUse = true;
}

//デストラクタ
CFade::~CFade()
{

}

//ロード関数
HRESULT CFade::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み(宇宙1)
	D3DXCreateTextureFromFile(pDevice,
		NULL, &m_pTexture);


	return S_OK;
}

//アンロード関数
void CFade::UnLoad(void)
{
		if (m_pTexture != NULL)
		{
			//テクスチャの破棄
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//クリエイト関数
CFade * CFade::Create()
{
	CFade *pFade = NULL;
	if (pFade == NULL)
	{
		pFade = new CFade;
		pFade->Init();

	}
	return pFade;
}

//初期化関数
HRESULT CFade::Init()
{
	//背景の生成
		m_pScene2D = NULL;

		if (m_pScene2D == NULL)
		{
			m_pScene2D = new CScene2D;
			m_pScene2D->Init();
			m_pScene2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
			m_pScene2D->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
			//SetObjType(OBJTYPE_FADE);
			m_FadeState = FADESTATE_OUT;
			m_pScene2D->BirdTexture(m_pTexture);
			m_bUse = true;
			m_color = 0;
		}
	return S_OK;
}

//終了関数
void CFade::Uninit(void)
{
	//背景の破棄
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
		}
	Release();
}

//更新関数
void CFade::Update(void)
{
	//背景のテクスチャ座標設定
	if (m_pScene2D != NULL)
	{
		switch (m_FadeState)
		{
		case FADESTATE_IN:
			if (m_bUse == false)
			{
				m_pScene2D->SetColor(D3DCOLOR_RGBA(m_color,m_color,m_color,m_color));
				m_color	+= 1;
			}
			if (m_color == 255)
			{
				m_color = 255;
				m_bUse = true;
				m_FadeState = FADESTATE_NONE;
			}
			break;
		case FADESTATE_OUT:
			if (m_bUse == true)
			{
				m_pScene2D->SetColor(D3DCOLOR_RGBA(255 - m_color, 255 - m_color, 255 - m_color, 255 - m_color));
				//m_pScene2D->SetColor(D3DCOLOR_RGBA(0, 0, 0, 0));
				m_color++;
			}
			if (m_color == 255)
			{
				m_color = 0;
				m_bUse = false;
				m_FadeState = FADESTATE_MAX;
			}
			break;
		case FADESTATE_NONE:
			break;
		default:
			break;
		}
	}
}

//描画関数
void CFade::Draw(void)
{
	//背景の描画
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Draw();
		}
}
