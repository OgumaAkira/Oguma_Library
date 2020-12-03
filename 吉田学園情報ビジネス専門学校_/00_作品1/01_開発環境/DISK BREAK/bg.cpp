//�C���N���[�h�t�@�C��
#include "bg.h"
#include "button.h"
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CBg::m_pTexture[3] = {};		//�e�N�X�`���̏��

//�R���X�g���N�^
CBg::CBg(int nPriority) :CScene(nPriority)
{
	m_move =D3DXVECTOR3(0,0,0);			//�ړ���
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��No.
	for (int nCount = 0; nCount < 3; nCount++)
	{
		m_apScene2D[nCount] = NULL;		//�V�[��2D�̃|�C���^�z��
	}
}

//�f�X�g���N�^
CBg::~CBg()
{

}

//���[�h�֐�
HRESULT CBg::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���(�F��1)
	D3DXCreateTextureFromFile(pDevice,
		BG_SKY_TEXTURE, &m_pTexture[0]);

	//�e�N�X�`���̓ǂݍ��݁i�F��2�j
	D3DXCreateTextureFromFile(pDevice,
		BG_MOUNTAIN1_TEXTURE, &m_pTexture[1]);

	//�e�N�X�`���̓ǂݍ��݁i�F��3�j
	D3DXCreateTextureFromFile(pDevice,
		BG_MOUNTAIN2_TEXTURE, &m_pTexture[2]);

	return S_OK;
}

//�A�����[�h�֐�
void CBg::UnLoad(void)
{
	for (int nCntTex = 0; nCntTex < 3; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			//�e�N�X�`���̔j��
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//�N���G�C�g�֐�
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

//�������֐�
HRESULT CBg::Init()
{
	//�w�i�̐���
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

//�I���֐�
void CBg::Uninit(void)
{
	//�w�i�̔j��
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

//�X�V�֐�
void CBg::Update(void)
{
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		break;
	
	case CManager::MODE_GAME:
	//�w�i�̃e�N�X�`�����W�ݒ�
	for (int nCntUninit = 0; nCntUninit < 3; nCntUninit++)
	{
		if (m_apScene2D[nCntUninit] != NULL)
		{
			
			m_move += D3DXVECTOR3(0.001f , 0, 0);//�ړ���
			//�w�i��m_nPatternAnim�Ő��𓮂����ăA�j���[�V��������B
			m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0),
				D3DXVECTOR2(m_move.x * (nCntUninit + 1.0f), 0));
		}
	}
	break;

	case CManager::MODE_RESULT:
		//�w�i�̃e�N�X�`�����W�ݒ�
		for (int nCntUninit = 0; nCntUninit < 3; nCntUninit++)
		{
			if (m_apScene2D[nCntUninit] != NULL)
			{

				m_move += D3DXVECTOR3(0.001f, 0, 0);//�ړ���
				//�w�i��m_nPatternAnim�Ő��𓮂����ăA�j���[�V��������B
				m_apScene2D[nCntUninit]->SetTex(D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f)), 0),
					D3DXVECTOR2((m_move.x * (nCntUninit + 1.0f) + 1.0f), 0));
			}
		}
		break;
	default:
		break;
	}
}

//�`��֐�
void CBg::Draw(void)
{
	//�w�i�̕`��
	for (int nCntDraw = 0; nCntDraw < 3; nCntDraw++)
	{
		if (m_apScene2D[nCntDraw] != NULL)
		{
			m_apScene2D[nCntDraw]->Draw();
		}
	}
}
