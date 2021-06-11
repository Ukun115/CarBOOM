#include "stdafx.h"
#include "Enemy.h"

namespace
{
	const int ENEMY1 = 0;		//�G�l�~�[�P
	const int ENEMY2 = 1;		//�G�l�~�[�Q
	const int ENEMY3 = 2;		//�G�l�~�[�R
	const int ENEMY4 = 3;		//�G�l�~�[�S
	const int ENEMY5 = 4;		//�G�l�~�[�T
	const int ENEMY6 = 5;		//�G�l�~�[�U
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
			m_enemy[i]->SetPosition(ENEMY1_RESPOS);		//�G�l�~�[�P�̏ꏊ
		}
		else if(i == ENEMY2)
		{
			m_enemy[i]->SetPosition(ENEMY2_RESPOS);		//�G�l�~�[�Q�̏ꏊ
		}
		else if (i == ENEMY3)
		{
			m_enemy[i]->SetPosition(ENEMY3_RESPOS);		//�G�l�~�[�R�̏ꏊ
		}
		else if (i == ENEMY4)
		{
			m_enemy[i]->SetPosition(ENEMY4_RESPOS);		//�G�l�~�[�S�̏ꏊ
		}
		else if (i == ENEMY5)
		{
			m_enemy[i]->SetPosition(ENEMY5_RESPOS);		//�G�l�~�[�T�̏ꏊ
		}
		else if (i == ENEMY6)
		{
			m_enemy[i]->SetPosition(ENEMY6_RESPOS);		//�G�l�~�[�U�̏ꏊ
		}
	}

	//Start�֐���return��
	return true;
}

Enemy::~Enemy()
{
	//�S�G�l�~�[���폜�B
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}

void Enemy::Update()
{
	//�c��30�b�ɂȂ�����|�C���g���C�g�Ńp�g�����v�����点��悤�ɂ���
}