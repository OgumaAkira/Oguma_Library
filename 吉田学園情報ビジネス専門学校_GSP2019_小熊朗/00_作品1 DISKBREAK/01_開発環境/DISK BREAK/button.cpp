//*****************************************************************************
//
// �{�^������ [button.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "button.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CButton::m_apTexture[2] = {};		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CButton::CButton(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �{�^���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_bUse = false;
	m_state = BUTTONSTATE_NORMAL;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CButton::~CButton()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CButton * CButton::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CButton *pButton = NULL;
	//�{�^���̃|�C���^���������������ꍇ
	if (pButton == NULL)
	{
		pButton = new CButton;
		pButton->Init(pos, size, type);
		pButton->SetObjType(OBJTYPE_BUTTON);	//�{�^���̃I�u�W�F�N�g�w��
	}
	return pButton;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
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

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
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

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CButton::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);		//�ʒu�擾
	SetPosition(m_pos);							//�ʒu�i�[
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫���擾
	SetSize(m_size);							//�傫���i�[
	m_bUse = true;								//�{�^���̏��
	m_state = BUTTONSTATE_NORMAL;				//�������
	BirdTexture(m_apTexture[type]);				//�e�N�X�`���̏���scene2d�֊i�[
	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CButton::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CButton::Update(void)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h���擾
	m_pFade = CManager::GetFade();			//�t�F�[�h���擾
	CScene2D::Update();

	//�{�^���̏��
	switch (m_state)
	{
	//�^�C�g����ʂ̃{�^��
	case BUTTONSTATE_TITLE:
		if (m_bUse == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
			//�F�̕ύX
			SetColor(D3DCOLOR_RGBA(0, 0, 255, 255));//��
			m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	//���U���g��ʂ̃{�^��
	case BUTTONSTATE_RESULT:
		if (m_bUse == true)
		{
			//SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_BUTTON);
			m_bUse = false;
		}
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));//��
		m_pFade->SetFade(CFade::FADESTATE_IN);
		break;

	//�{�^���̏����ݒ�
	case BUTTONSTATE_NORMAL:
		//�����F
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;

	default:
		break;
	}
	
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CButton::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//�{�^����Ԏ擾�֐�
//*****************************************************************************
void CButton::SetButton(void)
{
	//�{�^�����ʏ��Ԃ̏ꍇ
	if (m_state == BUTTONSTATE_NORMAL)
	{
		//���[�h�̏��
		switch (CManager::GetMode())
		{
		//�^�C�g����ʂ������ꍇ
		case CManager::MODE_TITLE:
			m_state = BUTTONSTATE_TITLE;	//�^�C�g���{�^����
			break;

		//���U���g��ʂ������ꍇ
		case CManager::MODE_RESULT:
			m_state = BUTTONSTATE_RESULT;	//���U���g�{�^����
			break;

		default:
			break;
		}
	}
}