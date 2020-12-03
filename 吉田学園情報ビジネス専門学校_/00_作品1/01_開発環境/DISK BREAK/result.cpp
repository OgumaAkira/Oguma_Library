//インクルードファイル
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "scene.h"
#include "score.h"
#include "manager.h"
#include "result.h"
#include "bg.h"
#include "sound.h"
#include "player.h"
#include "button.h"
#include "fade.h"
#include "hiscore.h"
#include "hiscoreUI.h"

CPlayer			*CResult::m_pPlayer = NULL;	//プレイヤーのポインタ
CBg				*CResult::m_pBg = NULL;	//背景のポインタ
CFade			*CResult::m_pFade = NULL;	//フェードのポインタ
CButton			*CResult::m_pButton = NULL;	//ボタンのポインタ
CScore			*CResult::m_pScore = NULL;//スコアのポインタ
CHIScore		*CResult::m_pHiScore = NULL;		//ハイスコア
CHiScoreUI		*CResult::m_pHiScoreUI = NULL;		//ハイスコアUI

CResult::CResult(int nPriority) : CScene(nPriority)
{
	m_bUse = true;
}

CResult::~CResult()
{
}

CResult * CResult::Create()
{
	CResult *pResult = NULL;
	if (pResult == NULL)
	{
		pResult = new CResult;
		pResult->Init();
		pResult->SetObjType(OBJTYPE_RESULT);
	}
	return pResult;
}

HRESULT CResult::Init()
{
	//背景のクリエイト
	m_pBg = CBg::Create();
	// マウス座標を取得する
	POINT posPoint;
	GetCursorPos(&posPoint);
	//ボタンの生成
	m_pButton = CButton::Create(D3DXVECTOR3(BUTTON_POSX, BUTTON_POSY, 0), D3DXVECTOR3(500.0f, 200.0f, 0.0f), CButton::BUTTONTYPE_RESULT);
	m_pHiScoreUI = CHiScoreUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 4.3f, SCORE_POS_Y + 270, 0), D3DXVECTOR3(600, 150, 0),CHiScoreUI::HISCORETYPE_HISCORE);
	m_pHiScoreUI = CHiScoreUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.5f, SCORE_POS_Y + 270, 0), D3DXVECTOR3(600, 150, 0), CHiScoreUI::HISCORETYPE_MYSCORE);
	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f), D3DXVECTOR3(PLAYER_SIZEX, PLAYER_SIZEY, 0), OBJTYPE_CURSOR);
	m_pFade = CFade::Create();
	m_bUse = true;
	return S_OK;
}

void CResult::Uninit(void)
{
	Release();
}

void CResult::Update(void)
{
	//サウンド
	CSound *pSound = CManager::GetSound();
	m_pFade->Update();
	m_pBg->Update();
	if (m_bUse==true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);
		m_pHiScore = CHIScore::Create();
		m_pScore = CScore::Create();
		m_bUse = false;
	}
	if (m_pFade->GetFade() == CFade::FADESTATE_NONE)
	{
		pSound->StopSound(CSound::SOUND_LABEL_RESULTBGM);
		CManager::SetMode(CManager::MODE_TITLE);
	}
}

void CResult::Draw(void)
{
}
