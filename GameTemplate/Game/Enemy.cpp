#include "stdafx.h"
#include "Enemy.h"

namespace
{
	const int ENEMY1 = 0;
	const int ENEMY2 = 0;
	const int ENEMY3 = 0;
	const int ENEMY4 = 0;
	const int ENEMY5 = 0;
	const int ENEMY6 = 0;
	const int ENEMYNUM = 6;		//�G�̑���
	const Vector3 ENEMY1_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY2_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY3_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY4_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY5_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY6_RESPOS={ 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
}

bool Enemy::Start()
{
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//�p�g�J�[(�G)�����[�h
		m_enemy[i] = NewGO<SkinModelRender>(0);
		//���f���̃t�@�C���p�X��ݒ�
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//�p�g�J�[
		//�������W(���X�|�[�����W)�̐ݒ�B
		if (i == ENEMY1)
		{
			m_enemy[i]->SetPosition(ENEMY1_RESPOS);		//�ꏊ
		}
		else if(i == ENEMY2)
		{
			m_enemy[i]->SetPosition(ENEMY2_RESPOS);		//�ꏊ
		}
		else if (i == ENEMY3)
		{
			m_enemy[i]->SetPosition(ENEMY3_RESPOS);		//�ꏊ
		}
		else if (i == ENEMY4)
		{
			m_enemy[i]->SetPosition(ENEMY4_RESPOS);		//�ꏊ
		}
		else if (i == ENEMY5)
		{
			m_enemy[i]->SetPosition(ENEMY5_RESPOS);		//�ꏊ
		}
		else if (i == ENEMY6)
		{
			m_enemy[i]->SetPosition(ENEMY6_RESPOS);		//�ꏊ
		}
	}

	//Start�֐���return��
	return true;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}