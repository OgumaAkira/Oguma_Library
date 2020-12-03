#ifndef _SCORE_H_
#define _SCORE_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "number.h"
#include "hiscore.h"

//�X�R�A�N���X�錾
class CScore :public CScene
{
public:

	CScore(int nPriority = 7);				//�R���X�g���N�^
	~CScore();				//�f�X�g���N�^

	//�����o�֐�
	static CScore *Create(void);
	HRESULT Init(void);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void SetScore(int nScore);//�X�R�A�l�i�[����
	void AddScore(int nScore);//���Z�X�R�A����
	int ReadFile(void);
	void WriteFile(void);
	static int GetScore(void) { return m_nScore; }
private:
	//�����o�ϐ�
	D3DXVECTOR3				m_move;			//�ړ���
	D3DXVECTOR3				m_pos;			// �|���S���̈ʒu
	D3DXVECTOR3				m_size;			// �|���S���傫��
	int						m_nCounterAnim;//�A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;//�A�j���[�V�����p�^�[��No.
	CNumber					*m_apNumber[MAX_SCORE_NUMBER];		//�V�[��2D�̃|�C���^�z��
	static int						m_nScore;
};
#endif