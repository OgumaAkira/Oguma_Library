#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "fade.h"
//�I�u�W�F�N�g2�N���X�錾
class CPlayer:public CScene2D
{
public:
	//�\���̒�`
	typedef enum
	{
		PLAYERSTATE_APPEAR = 0,
		PLAYERSTATE_NORMAL,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_MAX
	}PLAYERSTATE;

	CPlayer(int nPriority = 11);				//�R���X�g���N�^
	~CPlayer();				//�f�X�g���N�^

	//�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,OBJTYPE objtype);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void HitDamege(int ndamege);	//�_���[�W����
	static HRESULT Load(void);		//�ǂݍ��ݏ���
	static void UnLoad(void);		//�e�N�X�`���̔j��

private:
	//�����o�ϐ�
	D3DXVECTOR3						m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3						m_size;			// �|���S���傫��
	int								m_nHP;			//���C�t
	PLAYERSTATE						m_state;		//���
	static LPDIRECT3DTEXTURE9		m_pTexture;		//�e�N�X�`���̏��
	CFade* m_pFade;
	CInput* m_pInput;
};
#endif 