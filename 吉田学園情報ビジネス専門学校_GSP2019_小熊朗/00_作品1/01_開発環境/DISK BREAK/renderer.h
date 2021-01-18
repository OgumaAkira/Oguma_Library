//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�����_�����O�̃N���X�錾
//*****************************************************************************
class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	//�����o�֐�
	void DrawFPS(void);

	//�����o�ϐ�
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
};
#endif // !_RENDERER_H_

