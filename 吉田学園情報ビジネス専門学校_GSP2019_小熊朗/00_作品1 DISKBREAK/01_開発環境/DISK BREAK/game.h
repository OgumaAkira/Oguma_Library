//*****************************************************************************
//
// �Q�[����ʂ̏��� [game.h]
// Author : ���F�N
//
//*****************************************************************************
#ifndef _GAME_H_	//��d�̃C���N���[�h�h�~�̃}�N����`
#define _GAME_H_

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define _CRT_SECURE_WANINGS

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CBg;
class CEnemy;
class CFade;
class CScore;
class CBulletUI;
class CCombo;

//*****************************************************************************
//�Q�[����ʂ̃N���X�錾
//*****************************************************************************
class CGame:public CScene
{
public:
	//�\���̒�`(���)
	typedef enum
	{
		GAMESTATE_NONE = 0,		//�����Ȃ����
		GAMESTATE_SPEEDUP,		//�G���x���グ��
		GAMESTATE_NORMAL,		//�ʏ���
		GAMESTATE_ENEMYBREAK,	//�G��|������
		GAMESTATE_END,			//���U���g���
		GAMESTATE_FINISH,		//�Q�[���I�����(��ʑJ�ڊJ�n�҂���ԁj
		GAMESTATE_MAX			//�ő吔

	}GAMESTATE;

	CGame(int nPriority=2) ;												//�R���X�g���N�^
	~CGame();																//�f�X�g���N�^

	//�����o�֐�
	static CGame *Create();													//�N���G�C�g
	HRESULT Init();															//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�X�V����
	void SetEnemy(int enemy) { m_nNumEnemy = enemy; }						//�G�̏��i�[�֐�
	static void SetGameState(GAMESTATE state) {m_GameState = state;};		//�Q�[����Ԑݒ�
	static GAMESTATE GetGameState(void) { return m_GameState; }				//�Q�[����Ԏ擾
	static int GetGameSpeed(void) { return m_GameSpeed; }					//�Q�[���X�s�[�h�擾
	static int GetEnemy(void) { return m_nNumEnemy; }						//�G�̏��擾�֐�
	D3DXVECTOR3 GetRandPos(void);											//�G�̗����z�u�ʒu�擾�֐�
	D3DXVECTOR3 GetRandMove(void);											//�G�̗����z�u�����擾�֐�
private:
	//�����o�ϐ�
	static GAMESTATE			m_GameState;			//���
	int							m_WholeEnemy;			//�G�̃X�s�[�h�A�b�v�܂ł̐�
	static int					m_nNumEnemy;			//�G�̉�ʂɌ����G�̐�
	static int					m_GameSpeed;			//�G�̈ړ����x
	static CBg					*m_pBg;					//�w�i�̃|�C���^
	static CFade				*m_pFade;				//�t�F�[�h�|�C���^
	static CPlayer				*m_pPlayer;				//�v���C���[�̃|�C���^
	static CEnemy				*m_pEnemy;				//�G�̃|�C���^
	static CScore				*m_pScore;				//�X�R�A�̃|�C���^
	static CSpeed				*m_pSpeed;				//�X�s�[�h�̃|�C���^
	static CBulletUI			*m_pBulletUI;			//�c�e�̃|�C���^
	static CBullet				*m_pBullet;				//�e�̃|�C���^
	static CCombo				*m_pCombo;				//�R���{�̃|�C���^
	CSound						*pSound;				//�T�E���h�̃|�C���^
};
#endif