//*****************************************************************************
//
// �v���C���[�̏��� [player.cpp]
// Author : �|���S���̕\���i�����\���j
//
//*****************************************************************************
//�C���N���[�h�t�@�C��
#include "player.h"

//*****************************************************************************
//�ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CPlayer::m_pTexture = NULL;		//�e�N�X�`���̏��

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPlayer::CPlayer(int nPriority) :CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0, 0, 0);			// �|���S���傫��
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CPlayer::~CPlayer()
{

}

//*****************************************************************************
//�ǂݍ��݊֐�
//*****************************************************************************
HRESULT CPlayer::Load(void)
{
	//�����_�����O�̏����擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PLAYER_TEXTURE, &m_pTexture);

	return S_OK;
}

//*****************************************************************************
//�A�����[�h�֐�
//*****************************************************************************
void CPlayer::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//*****************************************************************************
//�N���G�C�g�֐�
//*****************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	CPlayer *pPlayer = NULL;
	//�v���C���[�̃|�C���^���������������ꍇ
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		pPlayer->Init(pos, size,objtype);
	}
		return pPlayer;
}

//*****************************************************************************
//�������֐�
//*****************************************************************************
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size,OBJTYPE objtype)
{
	CScene2D::Init();
	m_pos = D3DXVECTOR3(pos.x,pos.y , 0);		//�ʒu
	SetPosition(m_pos);
	m_size = D3DXVECTOR3(size.x, size.y, 0);	//�傫��
	SetSize(m_size);
	SetObjType(objtype);						//�I�u�W�F�N�g�w��i�[
	BirdTexture(m_pTexture);					//�e�N�X�`���̏���scene2d�Ɏ����Ă�
	return S_OK;;
}

//*****************************************************************************
//�I���֐�
//*****************************************************************************
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V�֐�
//*****************************************************************************
void CPlayer::Update(void)
{
	POINT posPoint;
	GetCursorPos(&posPoint);											//�}�E�X���W���擾����
	m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//�ʒu
	m_pInput = CManager::GetMouse();									//�}�E�X�̓��͏��擾
	CSound *pSound = CManager::GetSound();								//�T�E���h���擾
	CScene2D::Update();													//�I�u�W�F�N�g�̍X�V�����̎擾

	//-Y��
	if (m_pos.y - (m_size.y / 2) < 10)
	{
		m_pos.y -= m_size.y / 2;
	}
	//+Y��
	if (m_pos.y + (m_size.y / 2) > SCREEN_HEIGHT - 10)
	{
		m_pos.y += m_size.y / 2;
	}
	//-X��
	if (m_pos.x - (m_size.x / 2) < 10)
	{
		m_pos.x -= m_size.x / 2;
	}
	//+X��
	if (m_pos.x + (m_size.x / 2) > SCREEN_WIDTH - 10)
	{
		m_pos.x += m_size.x / 2;
	}
	m_pInput = CManager::GetMouse();
	if (((CMouse*)m_pInput)->GetMousePrees(1) == true)
	{
		posPoint.x = SCREEN_WIDTH / 2;
		posPoint.y = SCREEN_HEIGHT / 2;
		m_pos = D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0.0f);	//�ʒu
	}

	else if (((CMouse*)m_pInput)->GetMouseTrigger(0) == true )
	{
		if (CManager::GetMode() == CManager::MODE_GAME&&
			GetObjType()==OBJTYPE_PLAYER&&
			CFade::GetFade() == CFade::FADESTATE_MAX)
		{
			//�e�̐���
			CBullet::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0), 
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_PLAYER);

			//�T�E���h
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		else if(CManager::GetMode() != CManager::MODE_GAME&&
				GetObjType() == OBJTYPE_CURSOR&&
				CFade::GetFade()==CFade::FADESTATE_MAX)
		{
			//�e�̐���
			CBullet::Create(D3DXVECTOR3((float)posPoint.x, (float)posPoint.y, 0), 
							D3DXVECTOR3(BULLET_SIZEX, BULLET_SIZEY, 0), 
							D3DXVECTOR3(0, 0, 0), CBullet::BULLET_TYPE_CURSOR);
		}
	}

	//�v���C���[�̈ʒu�s�i
	SetPosition(m_pos);
}

//*****************************************************************************
//�`��֐�
//*****************************************************************************
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}


