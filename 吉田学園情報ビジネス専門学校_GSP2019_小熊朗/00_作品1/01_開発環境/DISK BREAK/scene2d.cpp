//*****************************************************************************
//
// �V�[��2D�̏��� [scene2D.cpp]
// Author : ���F�N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene2d.h"
#include "input.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pTexture = NULL;								//�e�N�X�`���̏��
	m_pVtxBuff = NULL;								//���_�o�b�t�@�̏��
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̑傫��
	m_tex = D3DXVECTOR2(0.0f, 0.0f);				//�e�X�N�`��
	m_color = D3DXCOLOR(255, 255, 255, 255);		//�J���[
	m_fMoverot = 0.0f;								//��]���x
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CScene2D::~CScene2D()
{

}

//*****************************************************************************
// �N���G�C�g�֐�
//*****************************************************************************
CScene2D * CScene2D::Create()
{
	CScene2D *pScene2D = NULL;

	//�V�[��2D�̃|�C���^���������������ꍇ
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
		pScene2D->Init();
	}
	return pScene2D;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CScene2D::Init(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���_����ݒ�
	VERTEX_2D *pVtx;


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//�|���S���̒��S�ʒu

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y - m_size.y/2, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x/2, m_pos.y + m_size.y/2, 0.0f);	//�E��

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;	//����
	pVtx[1].rhw = 1.0f;	//�E��
	pVtx[2].rhw = 1.0f;	//����
	pVtx[3].rhw = 1.0f;	//�E��

						//�F�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//����
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�E��
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//����
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	//�E��

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CScene2D::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�i�E���Őݒ肷��j
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//����
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y - m_size.y / 2, 0.0f);	//�E��
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//����
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, 0.0f);	//�E��

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;	//����
	pVtx[1].rhw = 1.0f;	//�E��
	pVtx[2].rhw = 1.0f;	//����
	pVtx[3].rhw = 1.0f;	//�E��

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_color);//����
	pVtx[1].col = D3DXCOLOR(m_color);//�E��
	pVtx[2].col = D3DXCOLOR(m_color);//����
	pVtx[3].col = D3DXCOLOR(m_color);//�E��

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 0);//����
	pVtx[1].tex = D3DXVECTOR2(1, 0);//�E��
	pVtx[2].tex = D3DXVECTOR2(0, 1);//����
	pVtx[3].tex = D3DXVECTOR2(1, 1);//�E��

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
 	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);
}

//*****************************************************************************
//*****************************************************************************
void CScene2D::SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex.y + 0.0f);	//����
	pVtx[1].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex.y + 0.0f);	//�E��
	pVtx[2].tex = D3DXVECTOR2((float)tex.x + 0.0f, tex2.y + 1.0f);	//����
	pVtx[3].tex = D3DXVECTOR2((float)tex2.x + 1.0f, tex2.y + 1.0f);	//�E��
 
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//*****************************************************************************
//�e�N�X�`���̏��i�[�֐�
//*****************************************************************************
void CScene2D::BirdTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//*****************************************************************************
//�ʒu�擾�֐�
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return D3DXVECTOR3(m_pos);
}

//*****************************************************************************
//�傫���擾�֐�
//*****************************************************************************
D3DXVECTOR3 CScene2D::GetSize(void)
{
	return D3DXVECTOR3(m_size);
}

//*****************************************************************************
//�e�N�X�`���̎擾�֐�
//*****************************************************************************
D3DXVECTOR2 CScene2D::GetTex()
{
	return D3DXVECTOR2(m_tex);
}

//*****************************************************************************
//�F�擾�֐�
//*****************************************************************************
D3DXCOLOR CScene2D::GetColor()
{
	return D3DXCOLOR(m_color);
}










