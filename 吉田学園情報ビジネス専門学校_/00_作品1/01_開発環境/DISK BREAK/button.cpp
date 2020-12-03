//インクルードファイル
#include "button.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9	CButton::m_apTexture[2] = {};		//テクスチャの情報

//コンストラクタ
CButton::CButton(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// ポリゴンの位置
	m_move = D3DXVECTOR3(1, 1, 0);			// ポリゴンの位置
	m_size = D3DXVECTOR3(0, 0, 0);			// ポリゴン大きさ
	m_bUse = false;
	m_state = BUTTONSTATE_NORMAL;
}

//デストラクタ
CButton::~CButton()
{

}

//クリエイト関数
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CButton *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CButton;
		pButton->Init(pos, size, type);
		pButton->SetObjType(OBJTYPE_BUTTON);
	}
	return pButton;
}

//初期化関数
HRESULT CButton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//位置
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//大きさ
	SetSize(m_size);
	m_bUse = true;
	m_state = BUTTONSTATE_NORMAL;
	//テクスチャの情報をscene2dに持ってく
	BirdTexture(m_apTexture[type]);
	return S_OK;
}

//終了関数
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}

//更新関数
void CButton::Update(void)
{
	m_pos = GetPosition();
	//サウンド取得
	CSound *pSound = CManager::GetSound();
	m_pFade = CManager::GetFade();
	CScene2D::Update();
	int nCountEnemy = 1;

	//ボタンの状態
	switch (m_state)
	{
	case BUTTONSTATE_TITLE:
		if (m_bUse == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
			//色の変更
			SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));//青
			m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	case BUTTONSTATE_RESULT:
		if (m_bUse == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
		//色の変更
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//赤
		m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	case BUTTONSTATE_NORMAL:
		//色の変更
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	default:
		break;
	}
	
}

//描画関数
void CButton::Draw(void)
{
	CScene2D::Draw();
}

void CButton::SetButton(void)
{
	if (m_state == BUTTONSTATE_NORMAL)
	{
		switch (CManager::GetMode())
		{
		case CManager::MODE_TITLE:
			m_state = BUTTONSTATE_TITLE;
			break;

		case CManager::MODE_RESULT:
			m_state = BUTTONSTATE_RESULT;
			break;

		default:
			break;
		}
	}
}

HRESULT CButton::Load(void)
{
	//レンダリングの情報を取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TITELBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_TITLE]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RESULTBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_RESULT]);

	return S_OK;
}

void CButton::UnLoad(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//テクスチャの破棄
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}