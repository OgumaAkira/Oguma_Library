//*****************************************************************************
//
// シーン2Dの処理 [scene2D.cpp]
// Author : 小熊朗
//
//*****************************************************************************

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "scene2d.h"
#include "input.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;								//テクスチャの情報
	m_pVtxBuff = NULL;								//頂点バッファの情報
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ポリゴンの大きさ
	m_tex = D3DXVECTOR2(0.0f, 0.0f);				//テスクチャ
	m_color = D3DXCOLOR(255, 255, 255, 255);		//カラー
	m_fMoverot = 0.0f;								//回転速度
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
// クリエイト関数
//*****************************************************************************
CScene2D * CScene2D::Create()
{
	CScene2D *pScene2D = NULL;

	//シーン2Dのポインタが何も無かった場合
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CScene2D::Init(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 頂点情報を設定
	VERTEX_2D *pVtx;


	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//ポリゴンの中心位置

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（右回りで設定する）
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//左上
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//右上
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//左下
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//右下

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//左上
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//右上
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//左下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//右下

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CScene2D::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene2D::Update(void)
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

	//rhwの設定
	pVtx[0].rhw = 1.0f;	//左上
	pVtx[1].rhw = 1.0f;	//右上
	pVtx[2].rhw = 1.0f;	//左下
	pVtx[3].rhw = 1.0f;	//右下

	//色の設定
	pVtx[0].col = D3DXCOLOR(m_color);//左上
	pVtx[1].col = D3DXCOLOR(m_color);//右上
	pVtx[2].col = D3DXCOLOR(m_color);//左下
	pVtx[3].col = D3DXCOLOR(m_color);//右下

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0, 0);//左上
	pVtx[1].tex = D3DXVECTOR2(1, 0);//右上
	pVtx[2].tex = D3DXVECTOR2(0, 1);//左下
	pVtx[3].tex = D3DXVECTOR2(1, 1);//右下

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene2D::Draw(void)
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

//*****************************************************************************
//*****************************************************************************
void CScene2D::SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex.y + 0.0f);	//左上
	pVtx[1].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex.y + 0.0f);	//右上
	pVtx[2].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex2.y + 1.0f);	//左下
	pVtx[3].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex2.y + 1.0f);	//右下
 
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//テクスチャの情報格納関数
//*****************************************************************************
void CScene2D::BirdTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//*****************************************************************************
//位置取得関数
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return D3DXVECTOR3(m_pos);
}

//*****************************************************************************
//大きさ取得関数
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return D3DXVECTOR3(m_size);
}

//*****************************************************************************
//テクスチャの取得関数
//*****************************************************************************
D3DXVECTOR2 CScene2D::GetTex()
{
	return D3DXVECTOR2(m_tex);
}

//*****************************************************************************
//色取得関数
//*****************************************************************************
D3DXCOLOR CScene2D::GetColor()
{
	return D3DXCOLOR(m_color);
}










