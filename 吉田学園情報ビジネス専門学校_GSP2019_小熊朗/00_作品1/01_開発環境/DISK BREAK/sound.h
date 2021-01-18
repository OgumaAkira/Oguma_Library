//*****************************************************************************
//
// メイン処理 [main.cpp]
// Author : ポリゴンの表示（複数表示）
//
//*****************************************************************************
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
//*****************************************************************************
#include "main.h"
#include "manager.h"
//*****************************************************************************
//オブジェクト2クラス宣言
//*****************************************************************************
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// TITLEBGM
		SOUND_LABEL_GAMEBGM,		// GAMEBGM
		SOUND_LABEL_RESULTBGM,		// RESULTBGM
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_BUTTON,		// ヒット音
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_SE_SPEEDUP,	// スピードアップ
		SOUND_LABEL_MAX,
	}SOUND_LABEL;

	CSound();				//コンストラクタ
	~CSound();				//デストラクタ
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	//メンバ変数
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 ;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// 各音素材のパラメータ
	static	SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};
#endif 