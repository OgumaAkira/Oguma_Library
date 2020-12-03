#ifndef _ENEMY_H_
#define _ENEMY_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"

//�}�N����`
#define MAX_ENEMY (2)

//�I�u�W�F�N�g2�N���X�錾
class CEnemy :public CScene2D
{
public:

	//�\���̒�`
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYRSTATE_DEATH,
		ENEMYS_MAX,
	}ENEMYSTATE;

	//�\���̒�`
	typedef enum
	{
		ENEMYTYPE_NORMAL = 0,
		ENEMYTYPE_NORMAL1,
		ENEMYTYPE_NORMAL2,
		ENEMYTYPE_MAX
	}ENEMYTYPE;

	CEnemy(int nPriority = 5);				//�R���X�g���N�^
	~CEnemy();				//�f�X�g���N�^

							//�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void CEnemy::HitDamege(int nDamege);
	bool Collision(D3DXVECTOR3*Pos, D3DXVECTOR3*PosOld, D3DXVECTOR3*Move, D3DXVECTOR3 * Size);
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3				m_pos;			// �|���S���̌��݈ʒu
	D3DXVECTOR3				m_posold;		// �|���S���̉ߋ��ʒu
	D3DXVECTOR3				m_move;			// �|���S���̈ړ���
	D3DXVECTOR3				m_size;			// �|���S���傫��
	ENEMYSTATE				m_state;		//���
	int						m_nCountState;	//�X�e�[�g�J�E���^�[
	int						m_nHP;			//�q�b�g�|�C���g
	bool					m_bLand;		//�����蔻��
	bool					m_bContact;		//�����蔻��2
	CInput* m_pInput;						//�f�o�b�O����p
	CScore* m_pScore;
	static LPDIRECT3DTEXTURE9		m_apTexture[2];		//�e�N�X�`���̏��
};
#endif 