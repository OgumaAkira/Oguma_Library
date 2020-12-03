//�C���N���[�h�t�@�C��
#include "tutorial.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CTutorial::m_pTexture = {};		//�e�N�X�`���̏��
int					CTutorial::m_nFrameCnt = 0;		//�_�ŃJ�E���g
														//�R���X�g���N�^
CTutorial::CTutorial(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(1, 1, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_Cnt = 0;
}

//�f�X�g���N�^
CTutorial::~CTutorial()
{

}

//�N���G�C�g�֐�
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTutorial *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CTutorial;
		pButton->Init(pos, size);
	}
	return pButton;
}

//�������֐�
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_Cnt = 5;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture);
	return S_OK;
}

//�I���֐�
void CTutorial::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V�֐�
void CTutorial::Update(void)
{
	m_pos = GetPosition();
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//�`��֐�
void CTutorial::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CTutorial::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TUTORIAL_TEXTURE, &m_pTexture);

	return S_OK;
}

void CTutorial::UnLoad(void)
{

	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}