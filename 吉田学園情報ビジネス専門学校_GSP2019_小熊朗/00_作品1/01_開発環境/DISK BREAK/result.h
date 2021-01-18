//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************************************************************
//*****************************************************************************
class CBg;
class CPlayer;
class CFade;
class CButton;
class CScore;
class CSound;
class CHIScore;
class CHiScoreUI;

//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CResult :public CScene
{
public:

	CResult(int nPriority=1);				//�R���X�g���N�^
	~CResult();				//�f�X�g���N�^

	static CResult *Create();

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
	static CScore			*m_pScore;
	static CHIScore			*m_pHiScore;
	static CHiScoreUI		*m_pHiScoreUI;

	CInput* m_pInput;
	bool					m_bUse;
};
#endif