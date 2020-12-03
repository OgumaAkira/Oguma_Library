#ifndef _BULLETUI_H_
#define _BULLETUI_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "game.h"

//�I�u�W�F�N�g2�N���X�錾
class CBulletUI :public CScene
{
public:
	CBulletUI(int nPriority = 8);				//�R���X�g���N�^
	~CBulletUI();				//�f�X�g���N�^

	//�����o�֐�
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��
	static CBulletUI *Create();

	HRESULT Init();			//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void SetBulletCnt(int bulletcnt);
	int GetBulletCnt(void) { return m_BulletCnt; }
	void SetbUse(void) { m_bUse = true; }
	bool GetbUse(void) { return m_bUse; }
	void Loading(void);

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���傫��
	int						m_nCounterAnim;//�A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;//�A�j���[�V�����p�^�[��No.
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��[�e�N�X�`���̐�]
	CScene2D						*m_apScene2D[5];		//�V�[��2D�̃|�C���^�z��
	int				m_BulletCnt;
	static bool				m_bUse;
};
#endif