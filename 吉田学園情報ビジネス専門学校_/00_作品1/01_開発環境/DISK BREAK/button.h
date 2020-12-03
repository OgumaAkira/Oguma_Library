#ifndef _BUTTON_H_
#define _BUTTON_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"

//�}�N����`
#define MAX_BUTTON (2)

//�I�u�W�F�N�g2�N���X�錾
class CButton :public CScene2D
{
public:

	//�\���̒�`
	typedef enum
	{
		BUTTONSTATE_NORMAL = 0,
		BUTTONSTATE_TITLE,
		BUTTONSTATE_RESULT,
		BUTTONSTATE_MAX,
	}BUTTONSTATE;

	//�\���̒�`
	typedef enum
	{
		BUTTONTYPE_NORMAL = 0,
		BUTTONTYPE_TITLE,
		BUTTONTYPE_RESULT,
		BUTTONTYPE_MAX,
	}BUTTONTYPE;

	CButton(int nPriority = 6);				//�R���X�g���N�^
	~CButton();				//�f�X�g���N�^

	//�����o�֐�
	static CButton *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, BUTTONTYPE type);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void SetButton(void);	//���͏���
	BUTTONSTATE GetButton(void) { return m_state; }
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_move;			// �|���S���̈ړ���
	D3DXVECTOR3				m_size;			// �|���S���傫��
	BUTTONSTATE				m_state;		//���
	int						m_nCountState;	//�X�e�[�g�J�E���^�[
	bool					m_bUse;			//�g�p���Ă邩�ǂ���
	CInput* m_pInput;						//�f�o�b�O����p
	CFade					*m_pFade;
	static LPDIRECT3DTEXTURE9		m_apTexture[2];		//�e�N�X�`���̏��
};
#endif 