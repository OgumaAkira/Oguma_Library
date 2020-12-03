#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//�I�u�W�F�N�g�N���X�錾
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

	CScene(int nPriority = 3);				//�R���X�g���N�^
	virtual~CScene();				//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void) = 0;		//����������
	virtual void Uninit(void) = 0;		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��


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
	OBJTYPE m_ObjType;//�I�u�W�F�N�g�̎��
	int m_Priority;
};
#endif // !_RENDERER_H_