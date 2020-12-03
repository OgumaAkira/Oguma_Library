#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"

//�C���v�b�g�N���X�錾
class CInput
{
public:
	CInput();				//�R���X�g���N�^

	//�������z�֐�
	virtual ~CInput();				//�f�X�g���N�^
	//�����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual void Draw(void);		//�`�揈��

	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
private:
};

//�L�[�{�[�h���͂̃N���X
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	bool GetKeyPrees(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateOld[NUM_KEY_MAX];
	BYTE m_aKeyStatePress[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

class CMouse:public CInput
{
public:
	CMouse();
	~CMouse();

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	bool GetMousePrees(int nKey);
	bool GetMouseTrigger(int nKey);
	bool GetMouseRelease(int nKey);

private:
	DIMOUSESTATE m_CurrentMouseState;		//!< �}�E�X�̌��݂̓��͏��
	DIMOUSESTATE m_PrevMouseState;			//!< �}�E�X�̈�t���[���O�̓��͏��

	BYTE m_aMouseState[NUM_MOUSE_MAX];
	BYTE m_aMouseStateOld[NUM_MOUSE_MAX];
	BYTE m_aMouseStatePress[NUM_MOUSE_MAX];// �}�E�X�̃v���X���
	BYTE m_aMouseStateTrigger[NUM_MOUSE_MAX];// �}�E�X�̃g���K�[
	BYTE m_aMouseStateRelease[NUM_MOUSE_MAX];
};


#endif
