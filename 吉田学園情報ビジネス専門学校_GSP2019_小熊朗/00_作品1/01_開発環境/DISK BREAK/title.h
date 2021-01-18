//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
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
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CTitle :public CScene
{
public:
	CTitle(int nPriority=1);				//�R���X�g���N�^
	~CTitle();				//�f�X�g���N�^
	static CTitle *Create();

	//�v���g�^�C�v�錾
	HRESULT Init();		//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	//�����o�ϐ�
	static CBg				*m_pBg;
	static CFade			*m_pFade;
	static CPlayer			*m_pPlayer;
	static CButton			*m_pButton;
	static CTitleLogo		*m_pTitileLogo;
	static CTutorial		*m_pTutorial;
	static CHIScore			*m_pHiScore;
	static CHiScoreUI		*m_pHiScoreUI;
	bool bUse;
	CSound *pSound;
	CInput* m_pInput;
};
#endif