#ifndef _EXLPOSION_H_
#define _EXLPOSION_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
//�I�u�W�F�N�g2�N���X�錾
class CExplosion :public CScene2D
{
public:
	CExplosion();				//�R���X�g���N�^
	~CExplosion();				//�f�X�g���N�^

	//�����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��


private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���̈ʒu
	int						m_nCounterAnim;//�A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;//�A�j���[�V�����p�^�[��No.

	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��


};
#endif 