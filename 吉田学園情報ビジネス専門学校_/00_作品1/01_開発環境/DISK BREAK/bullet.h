#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "sound.h"

//�O���錾
class CPlayer;
class CEnemy;
class CInput;
class CButton;
class BulletUI;

//�I�u�W�F�N�g2�N���X�錾
class CBullet :public CScene2D
{
public:
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_CURSOR,
		BULLET_TYPE_PLAYER,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_MAX
	} BULLET_TYPE;
	
	CBullet();				//�R���X�g���N�^
	~CBullet();				//�f�X�g���N�^

	//�����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_move;			//�ړ���
	D3DXVECTOR3						m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3						m_size;			// �|���S���̈ʒu
	BULLET_TYPE						m_type;			//���
	int								m_nHP;			//�q�b�g�|�C���g
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	static CBulletUI				*m_pBulletUI;
};
#endif 