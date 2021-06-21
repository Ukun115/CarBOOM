#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h
		//��2�K�w��Ƀf�B���N�g�����ړ����Ă���t�H���_������Ă���B


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0

	const int RES_POS_NUM = 10;	//���X�|�[���ʒu�̑���
	//�G�̊e���X�|�[���ʒu
	const Vector3 ENE_RES_POS_1 = { -150.0f,0.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,0.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,0.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,0.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 0.0f,0.0f,0.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,0.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 150.0f,0.0f,150.0f };

	const int STAGE3 = 3;		//�X�e�[�W�ԍ�
}


bool Enemy::Start()
{
	//�C���X�^���X��T���B
	m_titleScene = FindGO<TitleScene>("titlescene");
	m_gameScene  = FindGO<GameScene>("gamescene");
	m_player	 = FindGO<Player>("player");
	m_stageSelectScene = FindGO<StageSelectScene>("stageselectscene");

	//�G�̃��X�|�[���ʒu�P�`�P�O
	m_ranEneResPos[ResPos1]  = ENE_RES_POS_1;
	m_ranEneResPos[ResPos2]  = ENE_RES_POS_2;
	m_ranEneResPos[ResPos3]  = ENE_RES_POS_3;
	m_ranEneResPos[ResPos4]  = ENE_RES_POS_4;
	m_ranEneResPos[ResPos5]  = ENE_RES_POS_5;
	m_ranEneResPos[ResPos6]  = ENE_RES_POS_6;
	m_ranEneResPos[ResPos7]  = ENE_RES_POS_7;
	m_ranEneResPos[ResPos8]  = ENE_RES_POS_8;
	m_ranEneResPos[ResPos9]  = ENE_RES_POS_9;
	m_ranEneResPos[ResPos10] = ENE_RES_POS_10;

	//���X�|�[�����W���v���C���[1P�`4P�̍��W�Ɠ����ɂȂ�Ȃ��悤�ɂ��Ȃ��Ƃ����Ȃ��B
	//�y�v���C���[�̃��X�|�[���ʒu�z
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	m_randEneResAngle[0] = 1.0f;
	m_randEneResAngle[1] = 2.5f;
	m_randEneResAngle[2] = 3.7f;
	m_randEneResAngle[3] = 5.5f;

	//�G�̍ő吔�J��Ԃ�
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		//�G���f���I�u�W�F�N�g����
		m_enemy[i] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//���f���̃t�@�C���p�X��ݒ�
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//�G���f��
		//�������W(���X�|�[�����W)�̐ݒ�B
		if (i == Enemy1)
		{
			m_enePos[Enemy1] = m_ranEneResPos[0];		//�G�P�̏ꏊ
		}
		else if (i == Enemy2)
		{
			m_enePos[Enemy2] = m_ranEneResPos[1];		//�G�Q�̏ꏊ
		}
		else if (i == Enemy3)
		{
			m_enePos[Enemy3] = m_ranEneResPos[3];		//�G3�̏ꏊ
		}
		else if (i == Enemy4)
		{
			m_enePos[Enemy4] = m_ranEneResPos[4];		//�G4�̏ꏊ
		}
		else if (i == Enemy5)
		{
			m_enePos[Enemy5] = m_ranEneResPos[7];		//�G5�̏ꏊ
		}
		else if (i == Enemy6)
		{
			m_enePos[Enemy6] = m_ranEneResPos[9];		//�G6�̏ꏊ
		}
		//�傫������������������
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});

		//�����蔻��̃C�j�V�����C�Y(������)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);

		//300�`600�͈̔͂̃����_���l�ŃX�^�[�g���̓G��DA��x�点��^�C�}�[�̒l�ɑ��
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120�`140�͈̔͂̃����_���l��DA���CT�^�C�}�[�̒l�ɑ��
		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
	}

	//Start�֐���return��
	return true;
}


Enemy::~Enemy()
{
	//�S�Ă̓G���폜�B
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}


void Enemy::Update()
{
	//�S�G�����[�v
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() != 0) {
			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (m_gameScene->GetCountDownFlg() == false)
			{
				//�d�͂̉e����^����
				Gravity(i);

				//�X�^�[�g�����u�ԂɓG���_�b�V�����Ă��܂��̂�������鏈��
				if (m_startDelayTimer < m_startDelay[i])
				{
					//�X�^�[�g����DA��x�点��^�C�}�[�����Z
					m_startDelayTimer++;
				}
				//�����Ă��Ȃ��Ƃ��͊�{�����̏��������s�����B
				else
				{
					//��]����
					EneTurn(i);

					//DA�U������
					EneDA(i);

					//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
					EneResporn(i);

					m_enePos[i] += m_moveSpeed[i];
				}
			}

			//�G�̈ʒu�Ɖ�]�����X�V
			EneDataUpdate(i);
		}
	}
}


//�G�̈ʒu,��]�����X�V����֐�
void Enemy::EneDataUpdate(int x)
{
	m_enemy[x]->SetRotation(m_rot[x]);		//��]���X�V
	m_enemy[x]->SetPosition(m_enePos[x]);	//�ʒu���X�V
}


//�G����Ŋ��̃v���C���[����������֐�
void Enemy::Distance(int x)
{
	//�o�^����Ă���v���C���[�̕�����������
	for (int i = 0; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		//�v���C���[�̈ʒu���擾
		m_plaPos[i] = m_player->GetPlaPos(i);
		//�v���C���[�̈ʒu�ƓG�̈ʒu�̋������擾
		m_mostShortKyori[i] = m_plaPos[i] - m_enePos[x];
	}

	//��ԋ߂�����(m_mostShortKyori[0])�̂悤�ɕ��ёւ�(�\�[�g)
	for (int s = 0; s < m_titleScene->GetTotalPlaNum() - 1; s++) {
		for (int t = s + 1; t < m_titleScene->GetTotalPlaNum(); t++) {
			if (m_mostShortKyori[t].Length() < m_mostShortKyori[s].Length()) {
				//����
				Vector3 tmp = m_mostShortKyori[t];
				m_mostShortKyori[t] = m_mostShortKyori[s];
				m_mostShortKyori[s] = tmp;
			}
		}
	}

	//��ԋ߂��v���C���[����G�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_mostShortKyori[0].Normalize();
}


//�G��DA�����֐�
void Enemy::EneDA(int x)
{
	if (m_isCtFlg[x] == false) {

		//CT���J�E���g����t���O�𗧂Ă�
		m_isCtFlg[x] = true;

		//�����ݒ�
		Distance(x);

		//����������m_mostShortKyori[0]��5.0f���|���đ��x�ɂ���
		m_moveSpeed[x] = m_mostShortKyori[0] * 5.0f;
	}
	//CT�t���O�������Ă�Ƃ��A
	if (m_isCtFlg[x] == true) {

		//CT���J�E���g����
		m_CTTime[x]++;

		//���C�������Ă���
		EneFriction(x);
	}
	//CT�̃J�E���g��120�b�`140�b�̂Ƃ��A
	if (m_CTTime[x] == m_eneCTCount[x]) {

		//CT�t���O�����낷
		m_isCtFlg[x] = false;

		//CT�̃J�E���g��0�ɂ���
		m_CTTime[x] = 0;
	}
}


//�G�̉�]�����֐�
void Enemy::EneTurn(int x)
{
	//fabsf()�͕��������_�̐�Βl��Ԃ��֐�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}


//�G�̃��X�|�[�������֐�
void Enemy::EneResporn(int x)
{
	if (m_enePos[x].y < -1000.0f)
	{
		//�����_���Ń��X�|�[���ʒu������
		m_enePos[x] = m_ranEneResPos[rand() % RES_POS_NUM];

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[x].SetPosition(m_enePos[x]);

		//�X�s�[�h��0�ɂ���
		m_moveSpeed[x] = { Vector3::Zero };

		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_enePos[x] = m_charaCon[x].Execute(m_moveSpeed[x], 1.0f);
	}
}


//�G�̖��C�����֐�
void Enemy::EneFriction(int x)
{
	//���C�͂�ݒ肷��
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -1.5f;
	//���X�e�[�W���I������Ă���Ƃ��A
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//���C����؂Ȃ��ϐ����`
		Vector3 m_stage3Friction = { Vector3::Zero };
		//���C��0�ɂ���
		m_friction[x] = m_stage3Friction;
	}
	//���C�͂����Z����
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}


//�G�ɂ�����d�͂�ݒ肷��֐�
void Enemy::Gravity(int x)
{
	//�d�͂̉e����^����
	m_moveSpeed[x].y -= 0.2f;
}