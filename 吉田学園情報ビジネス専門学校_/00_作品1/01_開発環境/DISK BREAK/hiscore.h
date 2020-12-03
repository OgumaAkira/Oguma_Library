#ifndef _HISCORE_H_
#define _HISCORE_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"

//�X�R�A�N���X�錾
class CHIScore :public CScene
{
public:

	CHIScore();				//�R���X�g���N�^
	~CHIScore();				//�f�X�g���N�^

							//�����o�֐�
	static CHIScore *Create(void);
	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	static void WriteFile(int nScore);
	static int ReadFile(void);
private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;			//�ړ���
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���傫��
	int						m_nCounterAnim;//�A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;//�A�j���[�V�����p�^�[��No.
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
	static int				m_nScore;
};
#endif