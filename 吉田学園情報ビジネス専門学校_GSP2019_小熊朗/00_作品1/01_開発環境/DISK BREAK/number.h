//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CScene;

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CNumber
{
public:
	CNumber();				//�R���X�g���N�^
	~CNumber();				//�f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nTex);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(m_pos); }
	D3DXVECTOR3 GetSize(void) { return D3DXVECTOR3(m_size); }

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̏��
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���̑傫��
	D3DXVECTOR2				m_tex;			//�e�X�N�`��
	D3DXCOLOR				m_color;		//�J���[
	CScene					*m_pScene;		//�V�[���̃|�C���^
};
#endif