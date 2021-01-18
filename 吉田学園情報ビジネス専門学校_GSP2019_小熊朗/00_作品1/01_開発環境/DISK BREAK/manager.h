//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CScene;
class CScene2D;
class CInput;
class CInputKeyboard;
class CMouse;
class CPlayer;
class CTitle;
class CResult;
class CGame;
class CFade;
class CSound;
class CScore;
class CExplosion;
class CBullet;
class CEnemy;
class CButton;
class CNumber;
class CSpeed;
//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CManager
{
public:
	//�\����
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_END
	}MODE;

	CManager();				//�R���X�g���N�^
	~CManager();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bMenu);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }		//�����_���[�̏��擾�֐�
	static CInputKeyboard	*GetInputKeyboard(void) { return m_pInputKeyboard; }//�L�[�{�[�h���͏��擾�֐�
	static CMouse			*GetMouse(void)			{ return m_pMouse; }		//�}�E�X���͏��擾�֐�
	static CPlayer			*GetPlayer(void)		{ return m_pPlayer; }		//�v���C���[���擾�֐�
	static CEnemy			*GetEnemy(void)			{ return m_pEnemy; }		//�G�l�~�[���擾�֐�
	static CSound			*GetSound(void)			{ return m_pSound; }		//�T�E���h���擾�֐�
	static CExplosion		*GetExplosion(void)		{ return m_pExplosion; }	//�������擾�֐�
	static CBullet			*GetBullet(void)		{ return m_pBullet; }		//�o���b�g���擾�֐�
	static CButton			*GetButton(void)		{ return m_pButton; }		//�{�^�����擾�֐�
	static CScore			*GetScore(void)			{ return m_pScore; }		//�X�R�A�擾�֐�
	static CFade			*GetFade(void)			{ return m_pFade; }			//�t�F�[�h�擾�֐�
	static MODE				GetMode(void)			{ return m_mode; }			//���[�h���擾�֐�
	static void				SetMode(MODE mode);

private:
	//�����o�ϐ�
	static CRenderer		*m_pRenderer;
	static CScene2D			*m_paScene[MAX_TEXTURE];
	static CInputKeyboard	*m_pInputKeyboard;
	static CMouse			*m_pMouse;
	static CPlayer			*m_pPlayer;
	static CSound			*m_pSound;
	static CExplosion		*m_pExplosion;
	static CBullet			*m_pBullet;
	static CTitle			*m_pTitle;
	static CResult			*m_pResult;
	static CGame			*m_pGame;
	static MODE				m_mode;
	static CFade			*m_pFade;
	static CEnemy			*m_pEnemy;
	static CScore				*m_pScore;
	static CButton			*m_pButton;
	static CNumber			*m_pNumber;
	static CSpeed			*m_pSpeed;
	CInput* m_pInput;
};
#endif