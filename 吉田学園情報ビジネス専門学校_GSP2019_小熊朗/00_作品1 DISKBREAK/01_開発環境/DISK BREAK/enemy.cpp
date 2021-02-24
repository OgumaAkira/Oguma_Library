//*****************************************************************************
//
// �G�̏��� [enemy.cpp]
// Author : ���F �N
//
//*****************************************************************************

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "enemy.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CEnemy::m_apTexture[MAX_ENEMY] = {};		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_nHP = 0;								//���C�t
	m_pScore = 0;							//�X�R�A
	m_state = ENEMYSTATE_NORMAL;			//���
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEnemy::~CEnemy()
{

}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CEnemy *pEnemy = NULL;
	//�G�̃|�C���^�������Ȃ������ꍇ
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(pos, size, nType);
		pEnemy->SetObjType(OBJTYPE_ENEMY);			//�I�u�W�F�N�g�w��
		pEnemy->m_move = move;
	}
	return pEnemy;
}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CEnemy::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE2, &m_apTexture[ENEMYTYPE_NORMAL]);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			//�e�N�X�`���̔j��
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}
//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);		//�ʒu
	SetPosition(m_pos);							//�ʒu�i�[
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);							//�傫���i�[
	m_nHP = 1;									//���C�t
	m_state = ENEMYSTATE_NORMAL;				//���
	BirdTexture(m_apTexture[nType]);			//�e�N�X�`���̏���scene2d�Ɏ����Ă�

	return S_OK;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CEnemy::Update(void)
{
	m_pos = GetPosition();						//�X�V�ʒu���擾
	CSound *pSound = CManager::GetSound();		//�T�E���h�擾
	CScene2D::Update();
	int nCountEnemy = 1;						//�G�̐�

	//�G�̏��
	switch (m_state)
	{
	//�ʏ�
	case ENEMYSTATE_NORMAL:
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));				//�F�̐ݒ�
		break;

	case ENEMYRSTATE_DEATH:
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);		//�T�E���h
		CExplosion::Create(m_pos, m_size);
		Uninit();
		CGame::SetGameState(CGame::GAMESTATE_ENEMYBREAK);			//�Q�[���̏��
		break;

	default:
		break;
	}

	m_pos += m_move;//�G�̈ړ����x

	//�G�̗����z�u
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if ((rand() % (nCountEnemy * 25)) == 0)
		{
			//�e�̐���
			CBullet *pBullet = CManager::GetBullet();
		}
	}

	//��ʊO�֍s���ꍇ��ʓ��ɔ��˂�����B
	if (m_pos.x - (m_size.x / 2) < 0)
	{
		//��
		m_move.x *= -1;
	}
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH )
	{
		//�E
		m_move.x *= -1;
	}
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT)
	{
		//��
		m_move.y *= -1;
	}
	if (m_pos.y - (m_size.y / 2) < 0)
	{
		//��
		m_move.y *= -1;
	}

	//�v���C���[�̈ʒu�X�V
	SetPosition(m_pos);
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//*****************************************************************************
//�_���[�W�֐�
//*****************************************************************************
void CEnemy::HitDamege(int nDamege)
{
	m_nHP -= nDamege;					//�_���[�W�v�Z
	
	//���C�t��0�ɂȂ����ꍇ
	if (m_nHP <= 0)
	{
		m_state = ENEMYRSTATE_DEATH;	//�G�̎��S���
	}
}