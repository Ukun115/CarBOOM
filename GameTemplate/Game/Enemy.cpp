#include "stdafx.h"
#include "Enemy.h"
#include "PhysicsPlayer.h"
#include "TitleScene.h"
#include "GameScene.h"

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

	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int MAXPLAYERNUM = 4;
}

bool Enemy::Start()
{
	//�C���X�^���X��T���B
	m_gamescene = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_player = FindGO<PhysicsPlayer>("physicsplayer");

	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		m_mostShortKyori[i] = {1000.0f,1000.0f,1000.0f};

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

		////�����蔻��

		////�R���C�_�[���������B
		////�R���C�_�[�̑傫�����������B
		//m_boxColliderSize[i] = { 18.0f,10.0f,40.0f };
		//m_boxCollider[i].Create(m_boxColliderSize[i]);
		////���ʂ�ݒ肷��B
		//rbInitData[i].mass = 3.0f;
		//rbInitData[i].collider = &m_boxCollider[i];
		//if (i == ENEMY1)
		//	rbInitData[i].pos = ENEMY1_RESPOS;
		//if (i == ENEMY2)
		//	rbInitData[i].pos = ENEMY2_RESPOS;
		//if (i == ENEMY3)
		//	rbInitData[i].pos = ENEMY3_RESPOS;
		//if (i == ENEMY4)
		//	rbInitData[i].pos = ENEMY4_RESPOS;
		//if (i == ENEMY5)
		//	rbInitData[i].pos = ENEMY5_RESPOS;
		//if (i == ENEMY6)
		//	rbInitData[i].pos = ENEMY6_RESPOS;
		////�͂��߂͂�����Əォ��
		//rbInitData[i].pos.y = 100.0f;
		//m_rigidBody[i].Init(rbInitData[i]);
		////���C�͂�ݒ肷��B0�`10
		//m_rigidBody[i].SetFriction(0.1f);
		////���`�ړ�����v�f��ݒ肷��B
		////0���w�肵�����͈ړ����Ȃ��B
		//m_rigidBody[i].SetLinearFactor(1.0f, 1.0f, 1.0f);
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
	//�o�^����Ă���G�l�~�[�����[�v
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gamescene->GetNowTime() != 0) {
			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (m_gamescene->GetCountDownFlg() == false)
			{
				//�X�^�[�g�����u�ԂɃp�g�J�[���_�b�V�����Ă��܂��̂�������鏈��
				if (m_startDelayTimer < 600)
				{
					//�^�C�}�[���Z
					m_startDelayTimer++;
				}
				else
				{
					//�X�e�[�W�̒��S()���_�ƃv���C���[�Ƃ̋������v�Z
					m_diff = m_enePos[i] - m_origin;
					//�X�e�[�W�ォ��O��Ă���Ƃ��A
					//(�x�N�g���̒������擾���A���ꂪ250.0f���傫���A500�ȉ��̒l��������A)
					if (m_diff.Length() > 250.0f && m_diff.Length() <= 500.0f)
					{
						//����������
						m_enePos[i].y -= 2.0f;
					}
					//�������班�����Ԃ��o�߂�����A
					//��{�̓X�e�[�^�X�̏������������ł��Ă��܂��B
					else if (m_diff.Length() > 500.0f)
					{
						//�p�g�J�[�������ʒu�Ɏ����Ă����B
						EneResporn(i);
						//������Ə�Ƀp�g�J�[��߂��B
						m_enePos[i].y += 50.0f;

						//�t���O�𗧂Ă�
						m_respornFallFlg[i] = true;
					}
					//�X�e�[�W��Ƀ��X�|�[�������Ƃ����t���O����������A
					else if (m_respornFallFlg[i])
					{
						//�X�e�[�W��ɗ��������鏈��
						if (m_enePos[i].y != 0.0f)
						{
							m_enePos[i].y -= 1.0f;
						}
						else
						{
							//�v���C���[�̒~�ς���Ă���X�s�[�h���������B
							m_moveSpeed[i] = { 0.0f,0.0f,0.0f };

							//�t���O��܂�
							m_respornFallFlg[i] = false;
						}
					}
					//�����Ă��Ȃ��Ƃ��͊�{�����̏��������s�����B
					else
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

						//CT�̃J�E���g��180�b�̎�
						if (m_cTime[i] == 180) {

							//CT�t���O�����낷
							ctFlg[i] = false;

							//CT�̃J�E���g��0�ɂ���
							m_cTime[i] = 0;
						}


						m_enePos[i] += m_moveSpeed[i];
						m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������
						m_rot2[i].Multiply(m_rot[i], m_rot2[i]);

						////���̂̍��W�Ɖ�]��ݒ�B
						////m_rigidBody[i].SetPositionAndRotation(m_enePos[i], m_rot[i]);
						////���̂̍��W�Ɖ�]���擾�B
						//m_rigidBody[i].GetPositionAndRotation(m_enePos[i], m_rot[i]);
						////���̂̍��W�Ɖ�]�����f���ɔ��f�B
						//m_enemy[i]->GetModel().UpdateWorldMatrix(m_enePos[i], m_rot[i], g_vec3One);
						////���̂ɗ͂�������B
						//m_rigidBody[i].AddForce(
						//	m_moveSpeed[i],		//��
						//	g_vec3Zero	//�͂������鍄�̂̑��Έʒu
						//);
					}
				}
			}
			m_enemy[i]->SetRotation(m_rot2[i]); //��]���X�V
			m_enemy[i]->SetPosition(m_enePos[i]);	//�ʒu���X�V
		}
	}

	//�c��30�b�ɂȂ�����|�C���g���C�g�Ńp�g�����v�����点��悤�ɂ���
}

//�����ݒ�
void Enemy::Kyori(int x)
{
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�o�^����Ă�������s
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//�n�ʂɒ��n���Ă���v���C���[�̋��������v�Z�B
			//�n�ʂɂ��Ȃ��v���C���[�̋������v�Z����ƃp�g�J�[���󒆂ɔ��ōs�����肷�邽�߁B
			if (m_player->GetIsPlaLanding(i) == true)
			{
				m_plaPos[i] = m_player->GetPlaPos(i);
				m_newKyori[x] = m_plaPos[i] - m_enePos[x];

				//�������r���āA���݂̍ŒZ�������V�����擾����
				//�v���C���[�Ƃ̋����̂ق����߂�������A
				if (m_mostShortKyori[x].Length() > m_newKyori[x].Length())
				{
					//�ŒZ�������㏑������
					m_mostShortKyori[x] = m_newKyori[x];
				}
			}
		}
	}
	//�v���C���[����G�l�~�[�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_mostShortKyori[x].Normalize();
}

//�ړ�����
void Enemy::EneMove(int x)
{
	//����������m_kyori[x]�ɑ������|���đ��x�ɂ���
	m_moveSpeed[x] = m_mostShortKyori[x] * 5.0f;

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

//�p�g�J�[�����X�|�[���ʒu�܂Ŗ߂��֐�
void Enemy::EneResporn(int x)
{
	//1
	if (x == ENEMY1)
	{
		m_enePos[x] = ENEMY1_RESPOS;
	}
	//2
	else if (x == ENEMY2)
	{
		m_enePos[x] = ENEMY2_RESPOS;
	}
	//3
	else if (x == ENEMY3)
	{
		m_enePos[x] = ENEMY3_RESPOS;
	}
	//4
	else if (x == ENEMY4)
	{
		m_enePos[x] = ENEMY4_RESPOS;
	}
	//5
	else if (x == ENEMY5)
	{
		m_enePos[x] = ENEMY5_RESPOS;
	}
	//6
	else if (x == ENEMY6)
	{
		m_enePos[x] = ENEMY6_RESPOS;
	}
}