#ifndef _HISCOREUI_H_
#define _HISCOREUI_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"

//�I�u�W�F�N�g2�N���X�錾
class CHiScoreUI :public CScene2D
{
public:

	//�\���̒�`
	typedef enum
	{
		HISCORETYPE_HISCORE = 0,
		HISCORETYPE_MYSCORE,
		HISCORETYPE_MAX
	}HISCORETYPE;

	CHiScoreUI(int nPriority = 8);				//�R���X�g���N�^
	~CHiScoreUI();				//�f�X�g���N�^

	//�����o�֐�
	static CHiScoreUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, HISCORETYPE nType);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;			// �|���S���̈ړ���
	D3DXVECTOR3				m_size;			// �|���S���傫��
	D3DXCOLOR				m_col;			//�J���[
	static int				m_nFrameCnt;	//�t���b�V���J�E���g
	int						m_Cnt;			//�J�E���g
	static LPDIRECT3DTEXTURE9		m_pTexture[2];		//�e�N�X�`���̏��
};
#endif 