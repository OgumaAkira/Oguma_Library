//�C���N���[�h�t�@�C��
#include "fade.h"
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CFade::m_pTexture = NULL;		//�e�N�X�`���̏��
CFade::FADESTATE	CFade::m_FadeState = {};		//�g�p���Ă邩�ǂ���
int					CFade::m_color = 0;
//�R���X�g���N�^
CFade::CFade(int nPriority) :CScene(nPriority)
{
	m_move = D3DXVECTOR3(0, 0, 0);			//�ړ���
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_pScene2D = NULL;		//�V�[��2D�̃|�C���^�z��
	m_bUse = true;
}

//�f�X�g���N�^
CFade::~CFade()
{

}

//���[�h�֐�
HRESULT CFade::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���(�F��1)
	D3DXCreateTextureFromFile(pDevice,
		NULL, &m_pTexture);


	return S_OK;
}

//�A�����[�h�֐�
void CFade::UnLoad(void)
{
		if (m_pTexture != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//�N���G�C�g�֐�
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

//�������֐�
HRESULT CFade::Init()
{
	//�w�i�̐���
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

//�I���֐�
void CFade::Uninit(void)
{
	//�w�i�̔j��
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Uninit();
			delete m_pScene2D;
			m_pScene2D = NULL;
		}
	Release();
}

//�X�V�֐�
void CFade::Update(void)
{
	//�w�i�̃e�N�X�`�����W�ݒ�
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

//�`��֐�
void CFade::Draw(void)
{
	//�w�i�̕`��
		if (m_pScene2D != NULL)
		{
			m_pScene2D->Draw();
		}
}
