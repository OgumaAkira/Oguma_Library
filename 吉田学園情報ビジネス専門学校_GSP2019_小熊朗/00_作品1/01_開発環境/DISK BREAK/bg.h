//*****************************************************************************
//
// �w�i�̏��� [bg.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//*****************************************************************************
//�w�i�N���X�錾
//*****************************************************************************
class CBg :public CScene
{
public:

	CBg(int nPriority = 1);									//�R���X�g���N�^
	~CBg();													//�f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);								//���[�h�֐�
	static void UnLoad(void);								//�e�N�X�`���̔j��
	static CBg *Create();

	HRESULT Init();											//����������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	void Draw(void);										//�`�揈��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;							//�ړ���
	D3DXVECTOR3				m_pos;							// �|���S���̈ʒu
	D3DXVECTOR3				m_size;							// �|���S���傫��
	int						m_nCounterAnim;					//�A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;					//�A�j���[�V�����p�^�[��No.

	static LPDIRECT3DTEXTURE9		m_pTexture[3];			//�e�N�X�`���̏��[�e�N�X�`���̐�]
	CScene2D						*m_apScene2D[3];		//�V�[��2D�̃|�C���^�z��

};
#endif