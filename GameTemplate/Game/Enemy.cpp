#include "stdafx.h"
#include "Enemy.h"
#include "PhysicsPlayer.h"

namespace
{
	const int ENEMY1 = 0;		//�G�l�~�[�P
	const int ENEMY2 = 1;		//�G�l�~�[�Q
	const int ENEMY3 = 2;		//�G�l�~�[�R
	const int ENEMY4 = 3;		//�G�l�~�[�S
	const int ENEMY5 = 4;		//�G�l�~�[�T
	const int ENEMY6 = 5;		//�G�l�~�[�U
	const int ENEMYNUM = 6;		//�G�̑���
	const Vector3 ENEMY1_RESPOS = { -50.0f,0.0f,50.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY2_RESPOS = { 50.0f,0.0f,50.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY3_RESPOS = { 0.0f,0.0f,0.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY4_RESPOS = { -50.0f,0.0f,-50.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY5_RESPOS = { 50.0f,0.0f,-50.0f };		//�������W(���X�|�[�����W)
	const Vector3 ENEMY6_RESPOS = { 0.0f,0.0f,-50.0f };		//�������W(���X�|�[�����W)
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
			m_enePos[ENEMY1] = ENEMY1_RESPOS;		//�G�l�~�[�P�̏ꏊ
		}
		else if (i == ENEMY2)
		{
			m_enePos[ENEMY2] = ENEMY2_RESPOS;		//�G�l�~�[�Q�̏ꏊ
		}
		else if (i == ENEMY3)
		{
			m_enePos[ENEMY3] = ENEMY3_RESPOS;	//�G�l�~�[�R�̏ꏊ
		}
		else if (i == ENEMY4)
		{
			m_enePos[ENEMY4] = ENEMY4_RESPOS;	//�G�l�~�[�S�̏ꏊ
		}
		else if (i == ENEMY5)
		{
			m_enePos[ENEMY5] = ENEMY5_RESPOS;	//�G�l�~�[�T�̏ꏊ
		}
		else if (i == ENEMY6)
		{
			m_enePos[ENEMY6] = ENEMY6_RESPOS;		//�G�l�~�[�U�̏ꏊ
		}
	}

	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<PhysicsPlayer>("physicsplayer");

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
	//�o�^����Ă���G�l�~�[�����[�v
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//��]����
		EneTurn(i);

		if (ctFlg[i] == false) {

			//CT���J�E���g����t���O�𗧂Ă�
			ctFlg[i] = true;

			//�����ݒ�
			Kyori(i);

			//�ړ�����
			EneMove(i);

		}

		//CT�t���O�������Ă鎞
		if (ctFlg[i] == true) {

			//CT���J�E���g����
			m_cTime[i]++;

			//���C�͂�ݒ肷��
			m_friction[i] = m_moveSpeed[i];
			m_friction[i] *= -1.5f;

			//���C�͂����Z����
			m_moveSpeed[i].x += m_friction[i].x * g_gameTime->GetFrameDeltaTime();
			m_moveSpeed[i].z += m_friction[i].z * g_gameTime->GetFrameDeltaTime();

		}

		//CT�̃J�E���g��120�b�̎�
		if (m_cTime[i] == 120) {

			//CT�t���O�����낷
			ctFlg[i] = false;

			//CT�̃J�E���g��0�ɂ���
			m_cTime[i] = 0;

		}


		m_enePos[i] += m_moveSpeed[i];
		m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������
		m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
		m_enemy[i]->SetRotation(m_rot2[i]); //��]���X�V
		m_enemy[i]->SetPosition(m_enePos[i]);	//�ʒu���X�V
	}

	//�c��30�b�ɂȂ�����|�C���g���C�g�Ńp�g�����v�����点��悤�ɂ���
}

//�����ݒ�
void Enemy::Kyori(int x)
{
	//�v���C���[�̍��W���擾����
	m_plaPos[0] = m_player->GetPlaPos();

	//�v���C���[�ƃG�l�~�[�̃x�N�g�����擾����
	m_kyori[x] = m_plaPos[0] - m_enePos[x];

	//�v���C���[����G�l�~�[�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_kyori[x].Normalize();

}

//�ړ�����
void Enemy::EneMove(int x)
{
	//����������m_kyori[x]�ɑ������|���đ��x�ɂ���
	m_moveSpeed[x] = m_kyori[x] * 7.0f;

}

//��]����
void Enemy::EneTurn(int x)
{
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

	////������ݒ肷��
	//m_eneDir[x] = m_moveSpeed[x];
	//m_eneDir[x].Normalize();

}