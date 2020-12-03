//�C���N���[�h�t�@�C��
#include "button.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CButton::m_apTexture[2] = {};		//�e�N�X�`���̏��

//�R���X�g���N�^
CButton::CButton(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(1, 1, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_bUse = false;
	m_state = BUTTONSTATE_NORMAL;
}

//�f�X�g���N�^
CButton::~CButton()
{

}

//�N���G�C�g�֐�
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

//�������֐�
HRESULT CButton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_bUse = true;
	m_state = BUTTONSTATE_NORMAL;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_apTexture[type]);
	return S_OK;
}

//�I���֐�
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V�֐�
void CButton::Update(void)
{
	m_pos = GetPosition();
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	m_pFade = CManager::GetFade();
	CScene2D::Update();
	int nCountEnemy = 1;

	//�{�^���̏��
	switch (m_state)
	{
	case BUTTONSTATE_TITLE:
		if (m_bUse == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
			//�F�̕ύX
			SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));//��
			m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	case BUTTONSTATE_RESULT:
		if (m_bUse == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//��
		m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	case BUTTONSTATE_NORMAL:
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

		break;

	default:
		break;
	}
	
}

//�`��֐�
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
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITELBUTTON_TEXTURE, &m_apTexture[BUTTONTYPE_TITLE]);

	//�e�N�X�`���̓ǂݍ���
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
			//�e�N�X�`���̔j��
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}