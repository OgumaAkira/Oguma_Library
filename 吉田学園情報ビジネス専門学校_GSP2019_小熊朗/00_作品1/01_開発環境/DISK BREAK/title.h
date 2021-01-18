//*****************************************************************************
//
// �^�C�g����ʂ̏��� [title.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBg;
class CFade;
class CPlayer;
class CButton;
class CSound;
class CTitleLogo;
class CTutorial;
class CHIScore;
class CHiScoreUI;

//*****************************************************************************
//�^�C�g����ʂ̃N���X�錾
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority=1);				//�R���X�g���N�^
	~CTitle();								//�f�X�g���N�^

	//�v���g�^�C�v�錾
	static CTitle *Create();				//�N���G�C�g�֐�
	HRESULT Init();							//�������֐�
	void Uninit(void);						//�I���֐�
	void Update(void);						//�X�V�֐�
	void Draw(void);						//�`��֐�

private:
	//�����o�ϐ�
	static CBg				*m_pBg;			//�w�i�̃|�C���^
	static CFade			*m_pFade;		//�t�F�[�h�̃|�C���^
	static CPlayer			*m_pPlayer;		//�v���C���[�̃|�C���^
	static CButton			*m_pButton;		//�{�^���̃|�C���^
	static CTitleLogo		*m_pTitileLogo;	//�^�C�g�����S�̃|�C���^
	static CTutorial		*m_pTutorial;	//�`���[�g���A���̃|�C���^
	static CHIScore			*m_pHiScore;	//�n�C�X�R�A�̃|�C���^
	static CHiScoreUI		*m_pHiScoreUI;	//�n�C�X�R�AUI�̃|�C���^
	bool					bUse;			//�X�C�b�`
	CSound					*pSound;		//�T�E���h�̃|�C���^
	CInput					*m_pInput;		//���͂̃|�C���^
};
#endif