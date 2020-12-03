#ifndef _GAME_H_	//��d�̃C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

#define _CRT_SECURE_WANINGS

//�O���錾
class CBg;
class CEnemy;
class CFade;
class CScore;
class CBulletUI;

//�I�u�W�F�N�g2�N���X�錾
class CGame:public CScene
{
public:
	//�\���̒�`
	typedef enum
	{
		GAMESTATE_NONE = 0,		//�����Ȃ����
		GAMESTATE_SPEEDUP,		//�G���x���グ��
		GAMESTATE_NORMAL,		//�ʏ���
		GAMESTATE_ENEMYBREAK,	//�G��|������
		GAMESTATE_END,			//���U���g���
		GAMESTATE_FINISH,		//�Q�[���I�����(��ʑJ�ڊJ�n�҂���ԁj
		GAMESTATE_MAX

	}GAMESTATE;

	CGame(int nPriority=2) ;				//�R���X�g���N�^
	~CGame();				//�f�X�g���N�^
	static CGame *Create();	//�N���G�C�g

	//�v���g�^�C�v�錾
	HRESULT Init();		//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�X�V����
	void SetEnemy(int enemy) { m_nNumEnemy = enemy; }
	static void SetGameState(GAMESTATE state) {m_GameState = state;};//�Q�[����Ԑݒ�
	static GAMESTATE GetGameState(void) { return m_GameState; }	//�Q�[����Ԏ擾
	static int GetGameSpeed(void) { return m_GameSpeed; }//�Q�[���X�s�[�h�擾
	D3DXVECTOR3 GetRandPos(void);
	D3DXVECTOR3 GetRandMove(void);
	static int GetEnemy(void) { return m_nNumEnemy; }
private:
	//�����o�ϐ�
	static GAMESTATE			m_GameState;
	int							m_CounterGameState;
	int							m_WholeEnemy;
	static int					m_nNumEnemy;
	static int					m_GameSpeed;
	static CBg					*m_pBg;
	static CFade				*m_pFade;
	static CPlayer				*m_pPlayer;
	static CEnemy				*m_pEnemy;
	static CScore				*m_pScore;
	static CSpeed				*m_pSpeed;
	static CBulletUI			*m_pBulletUI;
	static CBullet				*m_pBullet;
	CSound *pSound;

};
#endif