//�C���N���[�h�t�@�C��
#include "enemy.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9	CEnemy::m_apTexture[MAX_ENEMY] = {};		//�e�N�X�`���̏��

//�R���X�g���N�^
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
	m_bLand = false;
	m_bContact = false;
	m_nHP = 0;
	m_pScore = 0;
	m_state = ENEMYSTATE_NORMAL;
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}

//�N���G�C�g�֐�
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		pEnemy->Init(pos, size, nType);
		pEnemy->SetObjType(OBJTYPE_ENEMY);
		pEnemy->m_move = move;
	}
		return pEnemy;
}

//�������֐�
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, ENEMYTYPE nType)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x, pos.y, 0);	//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	m_bContact = false;
	m_nHP = 1;
	m_state = ENEMYSTATE_NORMAL;
	//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	BirdTexture(m_apTexture[nType]);
	return S_OK;
}

//�I���֐�
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V�֐�
void CEnemy::Update(void)
{
	m_pos = GetPosition();
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	CScene2D::Update();
	int nCountEnemy = 1;

	//�G�̏��
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:
		SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
		break;

	case ENEMYSTATE_DAMAGE:
		//�F�̕ύX
		SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
		//�ʏ��Ԃɖ߂�
		m_state = ENEMYSTATE_NORMAL;

		break;

	case ENEMYRSTATE_DEATH:
		//�T�E���h
		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
		CExplosion::Create(m_pos, m_size);
		Uninit();
		CGame::SetGameState(CGame::GAMESTATE_ENEMYBREAK);
		break;

	default:
		break;
	}
	m_pos += m_move;
	//m_pos.x += m_move.x * (10.0f + 0.5f*CGame::GetGameSpeed());
	//m_pos.y += m_move.y * (10.0f + 0.5f*CGame::GetGameSpeed());
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if ((rand() % (nCountEnemy * 50)) == 0)
		{
			//�e�̐���
			CBullet *pBullet = CManager::GetBullet();

			//CBullet::Create(m_pos, D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), D3DXVECTOR3(0, -10, 0), CBullet::BULLET_TYPE_ENEMY);
			//�T�E���h
			//pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
	}
	//�����蔻�茋��
	m_posold = m_pos;
	if (Collision(&m_pos, &m_posold, &m_move,&m_size) == true)
	{
		m_bContact = false;
	}

	//��ʊO�֍s���ꍇ��ʓ��ɔ��˂�����B
	if (m_pos.x - (m_size.x / 2) < 0)
	{
		//��
		m_move.x *= -1;
		//m_pos.x += m_size.x / 2 + m_move.x;
	}
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH )
	{
		//�E
		m_move.x *= -1;
		//m_pos.x = (SCREEN_WIDTH - m_size.x / 2) + m_move.x;

	}
	if (m_pos.y - (m_size.y / 2) < 0)
	{
		//��
		m_move.y *= -1;
		//m_pos.y = m_size.y / 2 + m_move.y;

	}
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT )
	{
		//��
		m_move.y *= -1;
		//m_pos.y = (SCREEN_HEIGHT - m_size.y / 2) + m_move.y;
	}
	//�v���C���[�̈ʒu�X�V
	SetPosition(m_pos);
}

//�`��֐�
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

void CEnemy::HitDamege(int nDamege)
{
	m_nHP -= nDamege;

	if (m_nHP <= 0)
	{
		m_state = ENEMYRSTATE_DEATH;
	}
	if (m_nHP > 0)
	{
		m_state = ENEMYSTATE_DAMAGE;
	}
}

bool CEnemy::Collision(D3DXVECTOR3 * Pos, D3DXVECTOR3 * PosOld, D3DXVECTOR3 * Move, D3DXVECTOR3 * Size)
{
	m_bLand = false;
	//�G���m�̓����蔻��
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
		{
			CScene *pScene = GetScene(nCountPriority, nCntScene);
			if (pScene != NULL)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				if (this != pScene)
				{
					if ((objType == OBJTYPE_ENEMY))
					{
						D3DXVECTOR3 pos = ((CScene2D*)pScene)->GetPosition();//pos�������Ă���
						D3DXVECTOR3 size = ((CScene2D*)pScene)->GetSize();

						//�G�̓����蔻��(�㉺)
						if (Pos->x - (ENEMY_SIZEX / 2) - (ENEMY_SIZEX / 2) <= m_pos.x &&
							Pos->x + (ENEMY_SIZEX / 2) + (ENEMY_SIZEX / 2) >= m_pos.x &&
							Pos->y - (ENEMY_SIZEY / 2) - (ENEMY_SIZEY / 2) <= m_pos.y &&
							Pos->y + (ENEMY_SIZEY / 2) + (ENEMY_SIZEY / 2) >= m_pos.y)
						{
							////�v���C���[�̍������u���b�N�̉E���ɂӂꂽ�Ƃ�
							//if (Pos->x + (Size->x / 2) <= m_pos.x - (ENEMY_SIZEX / 2) &&
							//	PosOld->x + (Size->x / 2) <= m_pos.x - (ENEMY_SIZEX / 2))
							//{
							//	m_move.x *= -1;
							//	Pos->x = (m_size.x / 2) + m_move.x;
							//	m_bLand = true;

							//}
							////�v���C���[�̉E�����u���b�N�̍����ɂӂꂽ
							//if (Pos->x + (Size->x / 2) >= m_pos.x + (ENEMY_SIZEX / 2) &&
							//	PosOld->x + (Size->x / 2) <= m_pos.x + (ENEMY_SIZEX / 2))
							//{
							//	Move->x *= -1;
							//	//Pos->x = (m_size.x / 2) + m_move.x;
							//	m_bLand = true;
							//}
							////�v���C���[�̏㑤���u���b�N�̉����ɂӂꂽ
							//if (Pos->y + (Size->y / 2) >= m_pos.y - (ENEMY_SIZEY / 2) &&
							//	PosOld->y + (Size->y / 2) <= m_pos.y - (ENEMY_SIZEY / 2))
							//{
							//	Move->y *= -1;
							//	//Pos->y = (m_size.y / 2) - m_size.y / 2 + m_move.y;
							//	m_bLand = true;
							//}

							////�v���C���[�̉������u���b�N�̏㑤�ɂӂꂽ
							//if (Pos->y - (Size->y / 2) <= m_pos.y + (ENEMY_SIZEY / 2) &&
							//	PosOld->y - (Size->y / 2) >= m_pos.y + (ENEMY_SIZEY / 2))
							//{
							//	Move->y *= -1;
							//	//Pos->y = (m_size.y / 2) + m_move.y;
							//	m_bLand = true;
							//}
						}
					}
				}
			}
		}
	}
	return m_bLand;
}
//���[�h�֐�
HRESULT CEnemy::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE2, &m_apTexture[ENEMYTYPE_NORMAL]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		ENEMY_TEXTURE, &m_apTexture[ENEMYTYPE_NORMAL1]);

	return S_OK;
}

//�A�����[�h�֐�
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