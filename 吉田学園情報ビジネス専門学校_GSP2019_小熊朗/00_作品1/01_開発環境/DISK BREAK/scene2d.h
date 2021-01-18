//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D(int nPriority = 14);				//�R���X�g���N�^
	~CScene2D();				//�f�X�g���N�^

	//�����o�֐�
	static CScene2D *Create();
	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex2); 
	void SetColor(D3DXCOLOR col) { m_color=col; }
	void BirdTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetSize();
	D3DXVECTOR2	GetTex();
	D3DXCOLOR	GetColor();
	
private:
	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�̏��
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���̑傫��
	D3DXVECTOR2				m_tex;			//�e�X�N�`��
	D3DXCOLOR				m_color;		//�J���[
	float					m_fMoverot;		//��]���x

};
#endif 