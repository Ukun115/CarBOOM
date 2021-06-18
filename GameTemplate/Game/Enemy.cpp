#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{

}

bool Enemy::Start()
{
	//�C���X�^���X��T���B
	m_gamescene  = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_player	 = FindGO<Player>("player");

	m_randEneResPos[0] = { -150.0f,0.0f,150.0f };
	m_randEneResPos[1] = { 0.0f,0.0f,100.0f };
	m_randEneResPos[2] = { 100.0f,0.0f,100.0f };
	m_randEneResPos[3] = { -100.0f,0.0f,00.0f };
	m_randEneResPos[4] = { 0.0f,0.0f,0.0f };
	m_randEneResPos[5] = { 100.0f,0.0f,0.0f };
	m_randEneResPos[6] = { -100.0f,0.0f,-100.0f };
	m_randEneResPos[7] = { 0.0f,0.0f,-100.0f };
	m_randEneResPos[8] = { 100.0f,0.0f,-100.0f };
	m_randEneResPos[9] = { 150.0f,0.0f,150.0f };

	//���X�|�[�����W���v���C���[1P�`4P�̍��W�Ɠ����ɂȂ�Ȃ��悤�ɂ��Ȃ��Ƃ����Ȃ��B
	//�y�v���C���[�̃��X�|�[���ʒu�z
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//�p�g�J�[(�G)�����[�h
		m_enemy[i] = NewGO<SkinModelRender>(0);
		//���f���̃t�@�C���p�X��ݒ�
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//�p�g�J�[
		//�������W(���X�|�[�����W)�̐ݒ�B
		if (i == ENEMY1)
		{
			m_enePos[ENEMY1] = m_randEneResPos[0];		//�G�l�~�[�P�̏ꏊ
		}
		else if (i == ENEMY2)
		{
			m_enePos[ENEMY2] = m_randEneResPos[1];		//�G�l�~�[�Q�̏ꏊ
		}
		else if (i == ENEMY3)
		{
			m_enePos[ENEMY3] = m_randEneResPos[3];		//�G�l�~�[�R�̏ꏊ
		}
		else if (i == ENEMY4)
		{
			m_enePos[ENEMY4] = m_randEneResPos[4];		//�G�l�~�[�S�̏ꏊ
		}
		else if (i == ENEMY5)
		{
			m_enePos[ENEMY5] = m_randEneResPos[7];		//�G�l�~�[�T�̏ꏊ
		}
		else if (i == ENEMY6)
		{
			m_enePos[ENEMY6] = m_randEneResPos[9];		//�G�l�~�[�U�̏ꏊ
		}
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});

		//�����蔻��̃C�j�V�����C�Y(������)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);

		//300�`600�͈̔͂̃����_���̒l���擾
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));

		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
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
				//�d�͂̉e����^����
				m_moveSpeed[i].y -= 0.2f;

				//�X�^�[�g�����u�ԂɃp�g�J�[���_�b�V�����Ă��܂��̂�������鏈��
				if (m_startDelayTimer < m_startDelay[i])
				{
					//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					m_enePos[i] += m_moveSpeed[i];
					m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������
					m_rot2[i].Multiply(m_rot[i], m_rot2[i]);

					//�^�C�}�[���Z
					m_startDelayTimer++;
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
						Distance(i);

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
					if (m_cTime[i] == m_eneCTCount[i]) {

						//CT�t���O�����낷
						ctFlg[i] = false;

						//CT�̃J�E���g��0�ɂ���
						m_cTime[i] = 0;
					}

					//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					/// <summary>
					/// ���X�|�[������
					/// </summary>
					if (m_enePos[i].y < -1000.0f)
					{
						//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
						EneResporn(i);

						//�L�����R���̍��W�Ƀv���C���[�̍��W�������
						m_charaCon[i].SetPosition(m_enePos[i]);

						//�X�s�[�h��������
						m_moveSpeed[i] = { Vector3::Zero };

						//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
						m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
					}

					m_enePos[i] += m_moveSpeed[i];
					m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������
					m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
				}
			}
			m_enemy[i]->SetRotation(m_rot2[i]);		//��]���X�V
			m_enemy[i]->SetPosition(m_enePos[i]);	//�ʒu���X�V
		}
	}
}

//�����ݒ�
void Enemy::Distance(int x)
{
	//�o�^����Ă���v���C���[�̕�����������
	for (int i = 0; i < m_titlescene->GetTotalPlaNum(); i++)
	{
		//�Ԃ̈ʒu���擾
		m_plaPos[i] = m_player->GetPlaPos(i);
		//�Ԃ̈ʒu�ƃp�g�J�[�̈ʒu�̋������擾
		m_mostShortKyori[i] = m_plaPos[i] - m_enePos[x];
	}

	//m_mostShortKyori[0].Length()�̒l����ԏ������Ȃ�悤�ɕ��ёւ�(�\�[�g)
	for (int s = 0; s < m_titlescene->GetTotalPlaNum() - 1; s++) {
		for (int t = s + 1; t < m_titlescene->GetTotalPlaNum(); t++) {
			if (m_mostShortKyori[t].Length() < m_mostShortKyori[s].Length()) {
				Vector3 tmp = m_mostShortKyori[t];
				m_mostShortKyori[t] = m_mostShortKyori[s];
				m_mostShortKyori[s] = tmp;
			}
		}
	}

	//�v���C���[����G�l�~�[�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_mostShortKyori[0].Normalize();
}

//�ړ�����
void Enemy::EneMove(int x)
{
	//����������m_kyori[x]�ɑ������|���đ��x�ɂ���
	m_moveSpeed[x] = m_mostShortKyori[0] * 5.0f;
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
}

//�p�g�J�[�����X�|�[���ʒu�܂Ŗ߂��֐�
void Enemy::EneResporn(int x)
{
	//�����_���Ń��X�|�[���ʒu������
	m_enePos[x] = m_randEneResPos[rand() % 10];
}