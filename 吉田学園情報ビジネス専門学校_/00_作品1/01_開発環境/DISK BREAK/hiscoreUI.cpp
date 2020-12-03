//�C���N���[�h�t�@�C��
#include "hiscoreui.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CHiScoreUI::m_pTexture[2] = {};		//�e�N�X�`���̏��
int					CHiScoreUI::m_nFrameCnt = 0;		//�_�ŃJ�E���g
														//�R���X�g���N�^
CHiScoreUI::CHiScoreUI(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(1, 1, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_Cnt = 0;
}

//�f�X�g���N�^
CHiScoreUI::~CHiScoreUI()
{

}

//�N���G�C�g�֐�
CHiScoreUI * CHiScoreUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CHiScoreUI *pButton = NULL;
	if (pButton == NULL)
	{
		pButton = new CHiScoreUI;
		pButton->Init(pos, size,nType);
	}
	return pButton;
}

//�������֐�
HRESULT CHiScoreUI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_Cnt = 5;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture[nType]);
	return S_OK;
}

//�I���֐�
void CHiScoreUI::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V�֐�
void CHiScoreUI::Update(void)
{
	m_pos = GetPosition();
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
}

//�`��֐�
void CHiScoreUI::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CHiScoreUI::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		HISCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_HISCORE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		MYSCOREUI_TEXTURE, &m_pTexture[HISCORETYPE_MYSCORE]);

	return S_OK;
}

void CHiScoreUI::UnLoad(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}