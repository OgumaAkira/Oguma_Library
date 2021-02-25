//*****************************************************************************
//
// �V�[��2D���� [scene.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
//�V�[��2D�̃N���X�錾
//*****************************************************************************
class CScene2D :public CScene
{
public:
	CScene2D(int nPriority = 14);												//�R���X�g���N�^
	~CScene2D();																//�f�X�g���N�^

	//�����o�֐�
	static CScene2D *Create();														//�N���G�C�g�֐�
	HRESULT Init(void);																//����������
	void Uninit(void);																//�I������
	void Update(void);																//�X�V����
	void Draw(void);																//�`�揈��
	void SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2);									//�e�N�X�`���i�[�֐�
	void SetPosition(D3DXVECTOR3 pos)				{ m_pos = pos; }				//�ʒu�i�[�֐�
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; }				//�傫���i�[�֐�
	void SetColor(D3DXCOLOR col)					{ m_color = col; }				//�F�i�[�֐�
	void BirdTexture(LPDIRECT3DTEXTURE9 pTexture)	{ m_pTexture = pTexture; }		//�e�N�X�`���̏��i�[�֐�
	D3DXVECTOR3 GetPosition()						{ return D3DXVECTOR3(m_pos); }	//�ʒu�擾�֐�
	D3DXVECTOR3 GetSize()							{ return D3DXVECTOR3(m_size); }	//�傫���擾�֐�
	D3DXVECTOR2	GetTex()							{ return D3DXVECTOR2(m_tex); }	//�e�N�X�`���擾�֐�
	D3DXCOLOR	GetColor()							{ return D3DXCOLOR(m_color); }	//�F�擾�֐�
	
private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;											//�e�N�X�`���̏��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;											//���_�o�b�t�@�̏��
	D3DXVECTOR3				m_pos;												// �|���S���̈ʒu
	D3DXVECTOR3				m_size;												// �|���S���̑傫��
	D3DXVECTOR2				m_tex;												//�e�X�N�`��
	D3DXCOLOR				m_color;											//�J���[
	float					m_fMoverot;											//��]���x

};
#endif 