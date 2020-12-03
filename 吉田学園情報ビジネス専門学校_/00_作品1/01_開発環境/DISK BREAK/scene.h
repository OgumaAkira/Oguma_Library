#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//オブジェクトクラス宣言
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_CURSOR,
		OBJTYPE_PLAYER ,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_BG,
		OBJTYPE_BUTTON,
		OBJTYPE_TITLE,
		OBJTYPE_GAME,
		OBJTYPE_RESULT,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 3);				//コンストラクタ
	virtual~CScene();				//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void) = 0;		//初期化処理
	virtual void Uninit(void) = 0;		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual void Draw(void) = 0;		//描画処理


	void SetObjType(OBJTYPE objType) { m_ObjType = objType; };
	OBJTYPE GetObjType(void) { return m_ObjType; };
	static CScene *GetScene(int Priority, int scene) { return m_apScene[Priority][scene]; }
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_TEXTURE];
	static int m_nNumAll;
	int m_nID;
	OBJTYPE m_ObjType;//オブジェクトの種類
	int m_Priority;
};
#endif // !_RENDERER_H_