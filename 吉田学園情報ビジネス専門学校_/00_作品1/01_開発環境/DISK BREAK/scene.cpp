//---------------------------------
//インクルードファイル
//---------------------------------
#include "scene.h"
#include "renderer.h"

//静的メンバ変数
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_TEXTURE] = {};
int CScene::m_nNumAll = 0;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CScene::CScene(int nPriority)
{
#if 1
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nID = nCntScene;
			m_Priority = nPriority;
			m_nNumAll++;
			break;
		}
	}
#endif
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CScene::~CScene()
{

}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CScene::UpdateAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Update();
			}
		}
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CScene::DrawAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Draw();
			}
		}
	}
}

//*****************************************************************************
// リリース処理
//*****************************************************************************
void CScene::ReleaseAll(void)
{
	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			if (m_apScene[nCountPriority][nCntScene] != NULL)
			{
				m_apScene[nCountPriority][nCntScene]->Release();
			}
		}
	}
}

//*****************************************************************************
// リリース処理
//*****************************************************************************
void CScene::Release(void)
{
	if (m_apScene[m_Priority][m_nID]!=NULL)
	{
		int nID = m_nID;
		int nPriority = m_Priority;
		delete m_apScene[nPriority][m_nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

