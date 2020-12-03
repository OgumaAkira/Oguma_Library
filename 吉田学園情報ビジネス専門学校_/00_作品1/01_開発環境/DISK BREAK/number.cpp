//---------------------------------
//インクルードファイル
//---------------------------------
#include "number.h"
#include "scene.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CNumber::m_pTexture = NULL;		//テクスチャの情報

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CNumber::CNumber()
{
	m_pVtxBuff = NULL;								//頂点バッファの情報
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ポリゴンの大きさ
	m_tex = D3DXVECTOR2(0.0f, 0.0f);				//テスクチャ
	m_color = D3DXCOLOR(255, 255, 255, 255);		//カラー
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CNumber::~CNumber()
{
}

//*****************************************************************************
// ロード関数
//*****************************************************************************
HRESULT CNumber::Load(void)
{
	//テクスチャの読み込み
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		NUMBER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
// アンロード関数
//*****************************************************************************
void CNumber::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
// クリエイト関数
//*****************************************************************************
CNumber * CNumber::Create(D3DXVECTOR3 pos ,D3DXVECTOR3 size, int nTex)
{
	CNumber *pNumber = NULL;
	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		pNumber->Init(pos, size, nTex);
	}
	return pNumber;
}

HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点情報を設定
	VERTEX_2D *pVtx;


	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX*MAX_SCORE_NUMBER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//ポリゴンの中心位置
	m_pos = pos;
	m_size = size;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//右下

	//rhwの設定
	pVtx[0].rhw = 1.0f;	//左上
	pVtx[1].rhw = 1.0f;	//右上
	pVtx[2].rhw = 1.0f;	//左下
	pVtx[3].rhw = 1.0f;	//右下

						//色の設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//左上
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//右上
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//左下
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//右下

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

void CNumber::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void CNumber::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//右下

	//色の設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//左上
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//右上
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//左下
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//右下

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);
	pVtx[1].tex = D3DXVECTOR2(1, 0);
	pVtx[2].tex = D3DXVECTOR2(0, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 1);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

void CNumber::SetNumber(int nNumber)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((float)nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber * 0.1f), 1.0f);
	
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
