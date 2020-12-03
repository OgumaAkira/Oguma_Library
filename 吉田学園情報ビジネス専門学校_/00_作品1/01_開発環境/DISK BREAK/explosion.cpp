//�C���N���[�h�t�@�C��
#include "explosion.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CExplosion::m_pTexture = NULL;		//�e�N�X�`���̏��

CExplosion::CExplosion()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//�ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			//�傫��
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;//�A�j���[�V�����p�^�[��No.
}

CExplosion::~CExplosion()
{

}

CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion;
	pExplosion->Init(pos, size);
	pExplosion->SetObjType(OBJTYPE_EXPLOSION);
	return pExplosion;
}

HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init();
	//�e�̏����ݒ�
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);//�傫���@
	SetSize(m_size);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture);

	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

void CExplosion::Update(void)
{
	m_pos = GetPosition();
	CScene2D::Update();

	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if (objType == OBJTYPE_EXPLOSION)
				{
					m_nCounterAnim++;
					if (m_nCounterAnim == 1)
					{
						m_nCounterAnim = 0;
						SetTex(D3DXVECTOR2(m_nPatternAnim * 0.125f + 0.125f, 0),
							D3DXVECTOR2(m_nPatternAnim * 0.125f - 1.0f, 0));
						m_nPatternAnim++;
					}
					if (m_nPatternAnim >= 16)
					{
						Uninit();
					}
				}
			}
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CExplosion::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png", &m_pTexture);

	return S_OK;
}

void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
