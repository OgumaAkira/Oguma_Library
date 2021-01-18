//*****************************************************************************
//
// ���C������ [main.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "manager.h"
//*****************************************************************************
//�I�u�W�F�N�g2�N���X�錾
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// TITLEBGM
		SOUND_LABEL_GAMEBGM,		// GAMEBGM
		SOUND_LABEL_RESULTBGM,		// RESULTBGM
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_BUTTON,		// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_SPEEDUP,	// �X�s�[�h�A�b�v
		SOUND_LABEL_MAX,
	}SOUND_LABEL;

	CSound();				//�R���X�g���N�^
	~CSound();				//�f�X�g���N�^
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	//�����o�ϐ�
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 ;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	static	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};
#endif 