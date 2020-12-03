//�C���N���[�h�t�@�C��
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "bulletUI.h"
//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CBullet::m_pTexture = NULL;		//�e�N�X�`���̏��
CBulletUI			*CBullet::m_pBulletUI = NULL;	//�c�e�̃|�C���^

//�R���X�g���N�^
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//�ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			//�傫��
	m_move = D3DXVECTOR3(0, 0, 0);			//�ړ���
	m_nHP = 0;
}
//�f�X�g���N�^
CBullet::~CBullet()
{
}
//�N���G�C�g
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CBullet *pBullet;
	pBullet = new CBullet;
	pBullet->Init(pos,size, move,type);
	pBullet->SetObjType(OBJTYPE_BULLET);
	return pBullet;
}
//������
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, BULLET_TYPE type)
{
	CScene2D::Init();
	//�e�̏����ݒ�
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	m_size = D3DXVECTOR3(size.x, size.y, 0);//�傫���@
	m_move = move;//�ړ���
	m_nHP = 1;	//�q�b�g�|�C���g
	m_type = type;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_pTexture);
	SetObjType(CScene::OBJTYPE_BULLET);
	SetPosition(m_pos);
	SetSize(m_size);
	return S_OK;
}
//�I��
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//�X�V
void CBullet::Update(void)
{
	CSound *pSound = CManager::GetSound();
	m_pos = GetPosition();
	m_pos.y -= m_move.y;
	SetPosition(m_pos);
	CScene2D::Update();
	m_nHP--;	//�e�̃��C�t

	//�����蔻��
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		bool bHitEnemy = false;

		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if ((objType == OBJTYPE_ENEMY) && (m_type == BULLET_TYPE_PLAYER))
				{
					CPlayer *pPlayer = CManager::GetPlayer();
					CScene2D *pScene2d = (CScene2D*)pScene;	//�L���X�g
					D3DXVECTOR3 pos = pScene2d->GetPosition();//pos�������Ă���
					D3DXVECTOR3 size = pScene2d->GetSize();
					//�G�̓����蔻��
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CEnemy *pEnemy = (CEnemy*)pScene;	//�L���X�g;
						pEnemy->HitDamege(1);
						m_nHP = 0;
						bHitEnemy = true;
						break;
					}
				}
				else if ((objType == OBJTYPE_BUTTON) && (m_type == BULLET_TYPE_CURSOR))
				{
					CButton *pButton = CManager::GetButton();
					CScene2D *pScene2d = (CScene2D*)pScene;
					D3DXVECTOR3 pos = pScene2d->GetPosition();
					D3DXVECTOR3 size = pScene2d->GetSize();
					//�v���C���[�̓����蔻��
					if (pos.x - size.x / 2 <= m_pos.x&&
						pos.x + size.x / 2 >= m_pos.x&&
						pos.y - size.y / 2 <= m_pos.y&&
						pos.y + size.y / 2 >= m_pos.y)
					{
						CButton *pButton = (CButton*)pScene;	//�L���X�g;
						pButton->SetButton();
						m_nHP = 0;
					}
				}
			}
		}

		if (bHitEnemy == true)
		{ 
			break;
		}
	}
	if (m_pos.x - m_size.x / 2 < 0)
	{
		m_nHP = 0;
	}
	else if (m_pos.x + m_size.x / 2 > SCREEN_WIDTH)
	{
		m_nHP = 0;
	}
	else if (m_pos.y - m_size.y / 2 < 0)
	{
		m_nHP = 0;
	}
	else if (m_pos.y + m_size.y / 2 > SCREEN_HEIGHT)
	{
		m_nHP = 0;
	}
	if (m_nHP <= 0)
	{
		//��������
		if (m_type == BULLET_TYPE_PLAYER)
		{
			CExplosion::Create(m_pos, m_size);
			m_pBulletUI->SetbUse();
		}
		Uninit();
	}
}
//�`��
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//�ǂݍ���
HRESULT CBullet::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png", &m_pTexture);

	return S_OK;
}
//�e�N�X�`���̔j��
void CBullet::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}