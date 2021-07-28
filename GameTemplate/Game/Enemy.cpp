///<<summary>
///�GNPC�i�p�g�J�[�j�N���X
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h
		//��2�K�w��Ƀf�B���N�g�����ړ����Ă���t�H���_�ɐ����Ă���B


//TODO: �e�𗎂Ƃ���悤�ɂ���


namespace nsEnemy
{
	const int RES_POS_NUM = 10;	//���X�|�[���ʒu�̑���
	//�G�̊e���X�|�[���ʒu
	const Vector3 ENE_RES_POS_1 = { -150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,150.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,150.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 0.0f,150.0f,0.0f };
	//�G�̊e���X�|�[����]
	const float ENE_RES_ROT_1 = 1.0f;
	const float ENE_RES_ROT_2 = 2.5f;
	const float ENE_RES_ROT_3 = 3.7f;
	const float ENE_RES_ROT_4 = 5.5f;
	const float ENE_RES_ROT_5 = 0.5f;
	const float ENE_RES_ROT_6 = 1.25f;
	const float ENE_RES_ROT_7 = 1.85f;
	const float ENE_RES_ROT_8 = 2.85f;

	const float POILIG_RANGE = 50.0f;	//�|�C���g���C�g�̉e���͈�

	const int TIME0 = 0;

	const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };

	const float DELTATIME = 1.0f;
}


bool Enemy::Start()
{
	//�C���X�^���X��T���B
	m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
	m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
	m_light = FindGO<Light>(nsStdafx::LIGHT_NAME);
	m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);
	m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

	//�G�̃��X�|�[���ʒu�P�`�P�O
	m_ranEneResPos[ResPos1] = nsEnemy::ENE_RES_POS_1;
	m_ranEneResPos[ResPos2] = nsEnemy::ENE_RES_POS_2;
	m_ranEneResPos[ResPos3] = nsEnemy::ENE_RES_POS_3;
	m_ranEneResPos[ResPos4] = nsEnemy::ENE_RES_POS_4;
	m_ranEneResPos[ResPos5] = nsEnemy::ENE_RES_POS_5;
	m_ranEneResPos[ResPos6] = nsEnemy::ENE_RES_POS_6;
	m_ranEneResPos[ResPos7] = nsEnemy::ENE_RES_POS_7;
	m_ranEneResPos[ResPos8] = nsEnemy::ENE_RES_POS_8;
	m_ranEneResPos[ResPos9] = nsEnemy::ENE_RES_POS_9;
	if (m_stageSelectNum == nsStdafx::STAGE2)
	{
		m_ranEneResPos[ResPos10] = nsEnemy::ENE_RES_POS_10;
	}

	m_randEneResAngle[0] = nsEnemy::ENE_RES_ROT_1;
	m_randEneResAngle[1] = nsEnemy::ENE_RES_ROT_2;
	m_randEneResAngle[2] = nsEnemy::ENE_RES_ROT_3;
	m_randEneResAngle[3] = nsEnemy::ENE_RES_ROT_4;
	m_randEneResAngle[4] = nsEnemy::ENE_RES_ROT_5;
	m_randEneResAngle[5] = nsEnemy::ENE_RES_ROT_6;
	m_randEneResAngle[6] = nsEnemy::ENE_RES_ROT_7;
	m_randEneResAngle[7] = nsEnemy::ENE_RES_ROT_8;

	//�G�̍ő吔�J��Ԃ�
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		//�G���f���I�u�W�F�N�g����
		m_enemy[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0,nullptr);
		//���f���̃t�@�C���p�X��ݒ�
		m_enemy[eneNum]->Init("LowPoly_PoliceCar");	//�G���f��

		//�f�o�b�N�p�̓G�X�s�[�h�̖��\��
		//m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

		//�������W(���X�|�[�����W)�̐ݒ�B
		switch (eneNum)
		{
		case Enemy1:
			m_enePos[Enemy1] = m_ranEneResPos[Enemy1];		//�G�P�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		case Enemy2:
			m_enePos[Enemy2] = m_ranEneResPos[Enemy2];		//�G�Q�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		case Enemy3:
			m_enePos[Enemy3] = m_ranEneResPos[Enemy3];		//�G3�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		case Enemy4:
			m_enePos[Enemy4] = m_ranEneResPos[Enemy4];		//�G4�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		case Enemy5:
			m_enePos[Enemy5] = m_ranEneResPos[Enemy5];		//�G5�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		case Enemy6:
			m_enePos[Enemy6] = m_ranEneResPos[Enemy6];		//�G6�̏ꏊ
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//���
			break;
		}
		//�����蔻��̃C�j�V�����C�Y(������)
		m_charaCon[eneNum].Init(15.0f, 85.0f, m_enePos[eneNum]);
		//300�`600�͈̔͂̃����_���l�ŃX�^�[�g���̓G��DA��x�点��^�C�}�[�̒l�ɑ��
		m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120�`140�͈̔͂̃����_���l��DA���CT�^�C�}�[�̒l�ɑ��
		m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));

		//���������Ƃ��̌��ăG�t�F�N�g�̏������B
		m_shootDownEffect[eneNum].Init(u"Enemy_ShootDown");
		//�傫������
		m_shootDownEffect[eneNum].SetScale(nsEnemy::SHOOTDOWNEFFECT_SCALE);
		//�G�t�F�N�g�����|���ɂȂ��Ă���̂ł�����Œ���
		Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
		//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
		m_shootDownEffectRot.AddRotationX(-1.5708f);	//X������_�ɁA-1.5708rad(-90��)��]
		m_shootDownEffect[eneNum].SetRotation(m_shootDownEffectRot);

		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8]; //�G�̌���
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//��]���X�V
	}
	return true;
}


Enemy::~Enemy()
{
	//�S�Ă̓G���폜�B
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		DeleteGO(m_enemy[eneNum]);
	}
}


void Enemy::Update()
{
	//�|�[�Y���̂Ƃ��A�b�v�f�[�g������S�Ď~�߂�
	if (m_isPauseFlg)
	{
		return;
	}
	//�������Ԃ��O�b�ɂȂ�����A�b�v�f�[�g������S�Ď~�߂�
	if (m_gameScene->GetNowTime() == nsEnemy::TIME0)
	{
		return;
	}

	m_poiLigNum = nsStdafx::INT_ZERO;

	//�S�G�����[�v
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		//�����̍ی��ʉ���点��֐�
		FallSoundPlayBack(eneNum);

		//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
		if (!m_gameScene->GetCountDownFlg())
		{
			//�X�^�[�g�����u�ԂɓG���_�b�V�����Ă��܂��̂�������鏈��
			if (m_startDelayTimer < m_startDelay[eneNum])
			{
				//�X�^�[�g����DA��x�点��^�C�}�[�����Z
				m_startDelayTimer++;
			}
			else
			{
				//��]����
				EneTurn(eneNum);

				//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
				PlaAndEneClash(eneNum);

				//DA�U������
				EneDA(eneNum);

				//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
				EneResporn(eneNum);

				//�p�g�����v��G�̏�ɃZ�b�g����֐�
				PointLightSetting(eneNum);

				m_enePos[eneNum] += m_moveSpeed[eneNum];
			}
		}

		//�x�N�g��������������f�o�b�N�֐�
		//EneMooveSpeedDebug(eneNum);

		//�d�͂̉e����^����
		Gravity(eneNum);

		bool isHitGround;
		Vector3 hitGroundNormal;
		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_enePos[eneNum] = m_charaCon[eneNum].Execute(
			m_moveSpeed[eneNum],
			nsEnemy::DELTATIME,
			isHitGround,
			hitGroundNormal
		);

		//�G�̈ʒu�Ɖ�]�����X�V
		EneDataUpdate(eneNum);
	}
}


//�G�̈ʒu,��]�����X�V����֐�
void Enemy::EneDataUpdate(const int eneNum)const
{
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//��]���X�V
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);	//�ʒu���X�V
}


//�G����Ŋ��̃v���C���[����������֐�
void Enemy::Distance(const int eneNum)
{
	//�v���C���[�ƓG�Ƃ̋����𑪂��ԋ߂��v���C���[���Z�o����
	DistanceOfPlaToEne(eneNum);

	//��ԋ߂��v���C���[����G�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_mostShortDistanceDir[0] = m_mostShortDistance[0];
	m_mostShortDistanceDir[0].Normalize();

	//�h�[�i�c�X�e�[�W���I�΂�Ă��Ȃ�������return�ȍ~�͏������s��Ȃ�
	if (m_stageSelectNum != nsStdafx::STAGE2)
	{
		return;
	}

	m_centerKyori[eneNum] = m_center - m_enePos[eneNum];

	//�h�[�i�c�̌��̒��S�Ƃ̋�����60.0f�ȏゾ������return�ȍ~�̏������s��Ȃ�
	if (m_centerKyori[eneNum].Length() <= 60.0f)
	{
		return;
	}

	if (!m_enePos[eneNum].x == nsStdafx::INT_ZERO && !m_enePos[eneNum].z == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = (m_hankei * m_enePos[eneNum].x + m_enePos[eneNum].z * powf(m_hankei * ((powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f) - m_hankei)), 1.0f / 2.0f)) / (powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f));
		m_settenPos1[eneNum].z = (m_hankei - m_enePos[eneNum].x * m_settenPos1[eneNum].x) / m_enePos[eneNum].z;
		m_settenPos2[eneNum].x = (m_hankei * m_enePos[eneNum].x - m_enePos[eneNum].z * powf(m_hankei * ((powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f) - m_hankei)), 1.0f / 2.0f)) / (powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f));
		m_settenPos2[eneNum].z = (m_hankei - m_enePos[eneNum].x * m_settenPos2[eneNum].x) / m_enePos[eneNum].z;

	}
	else if (m_enePos[eneNum].x == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = (powf(m_hankei * (powf(m_enePos[eneNum].z, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].z);
		m_settenPos1[eneNum].z = m_hankei / m_enePos[eneNum].z;
		m_settenPos2[eneNum].x = (powf(m_hankei * (powf(m_enePos[eneNum].z, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].z) * (-1);
		m_settenPos2[eneNum].z = m_hankei / m_enePos[eneNum].z;

	}
	else if (m_enePos[eneNum].z == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = m_hankei / m_enePos[eneNum].x;
		m_settenPos1[eneNum].z = (powf(m_hankei * (powf(m_enePos[eneNum].x, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].x);
		m_settenPos2[eneNum].x = m_hankei / m_enePos[eneNum].x;
		m_settenPos2[eneNum].z = (powf(m_hankei * (powf(m_enePos[eneNum].x, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].x) * (-1);
	}

	m_EneToSetten1[eneNum] = m_settenPos1[eneNum] - m_enePos[eneNum];
	m_EneToSetten1[eneNum].y = nsStdafx::FLOAT_ZERO;
	m_EneToSetten1Dir[eneNum] = m_EneToSetten1[eneNum];
	m_EneToSetten1Dir[eneNum].Normalize();
	m_EneToSetten2[eneNum] = m_settenPos2[eneNum] - m_enePos[eneNum];
	m_EneToSetten2[eneNum].y = nsStdafx::FLOAT_ZERO;
	m_EneToSetten2Dir[eneNum] = m_EneToSetten2[eneNum];
	m_EneToSetten2Dir[eneNum].Normalize();
}


//�G��DA�����֐�
void Enemy::EneDA(const int eneNum)
{
	if (!m_canCtCountFlg[eneNum]) {
		//�����ݒ�
		Distance(eneNum);

		if (m_charaCon[eneNum].IsOnGround()) {

			//�h�[�i�c�X�e�[�W���I�����ꂽ�Ƃ�
			if (m_stageSelectNum == nsStdafx::STAGE2)
			{
				m_centerKyori[eneNum].y = nsStdafx::FLOAT_ZERO;
				m_centerKyori[eneNum].Normalize();
				m_CenterToEneAngle[eneNum] = m_centerKyori[eneNum].Dot(m_mostShortDistanceDir[0]);
				m_CenterToSettenAngle[eneNum] = m_centerKyori[eneNum].Dot(m_EneToSetten1Dir[eneNum]);

				if (m_CenterToEneAngle[eneNum] > m_CenterToSettenAngle[eneNum] && m_mostShortDistance[0].Length() > m_EneToSetten1[eneNum].Length())
				{
					m_PlayerToSetten1Angle[eneNum] = m_mostShortDistanceDir[0].Dot(m_EneToSetten1Dir[eneNum]);
					m_PlayerToSetten2Angle[eneNum] = m_mostShortDistanceDir[0].Dot(m_EneToSetten2Dir[eneNum]);
					//�ړ_�P�̕������ړ_�Q�̕����ɍs�����𔻕�
					m_moveSpeed[eneNum] = (m_PlayerToSetten1Angle[eneNum] > m_PlayerToSetten2Angle[eneNum]) ? m_EneToSetten1Dir[eneNum] : m_EneToSetten2Dir[eneNum];
					m_moveSpeed[eneNum] *= 5.0f;
				}
				else
				{
					//����������m_mostShortKyori[0]��5.0f���|���đ��x�ɂ���
					m_moveSpeed[eneNum] = m_mostShortDistanceDir[0] * 5.0f;
				}
			}
			else
			{
				//����������m_mostShortKyori[0]��5.0f���|���đ��x�ɂ���
				m_moveSpeed[eneNum] = m_mostShortDistanceDir[0] * 5.0f;
			}

		}
		//�_�b�V���T�E���h
		m_soundPlayBack->EnemySoundPlayBack(DashSound,eneNum);

		m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

		//CT���J�E���g����t���O�𗧂Ă�
		m_canCtCountFlg[eneNum] = true;
	}
	//CT�t���O�������Ă�Ƃ��A
	if (m_canCtCountFlg[eneNum]) {

		//CT���J�E���g����
		m_CTTime[eneNum]++;

		//���C�������Ă���
		EneFriction(eneNum);
	}
	//CT�̃J�E���g��120�b�`140�b�̂Ƃ��A
	if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

		//CT�t���O�����낷
		m_canCtCountFlg[eneNum] = false;

		//CT�̃J�E���g��0�ɂ���
		m_CTTime[eneNum] = nsStdafx::INT_ZERO;
	}
}


//�G�̉�]�����֐�
void Enemy::EneTurn(const int eneNum)
{
	//fabsf()�͕��������_�̐�Βl��Ԃ��֐�
	if (fabsf(m_moveSpeed[eneNum].x) < 0.001f && fabsf(m_moveSpeed[eneNum].z) < 0.001f)
	{
		return;
	}
	//��]�p�x
	m_rotAngle[eneNum] = atan2(m_moveSpeed[eneNum].x, m_moveSpeed[eneNum].z);

	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);

	m_eneDir[eneNum] = m_moveSpeed[eneNum];
	m_eneDir[eneNum].Normalize();
}


//�G�̃��X�|�[�������֐�
void Enemy::EneResporn(const int eneNum)
{
	//�G��Y���W�̈ʒu���ő嗎���n�_�܂ōs���ĂȂ�������return�ȍ~�̏����͍s��Ȃ�
	if (m_enePos[eneNum].y >= -1000.0f)
	{
		return;
	}

	//���ăT�E���h
	m_soundPlayBack->EnemySoundPlayBack(ShootDownSound,eneNum);

	//���ăG�t�F�N�g�Đ��J�n�B
	m_shootDownEffect[eneNum].Play();
	//���ăG�t�F�N�g�̈ʒu��G���������ʒu�ɐݒ�
	m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
	//�X�V
	m_shootDownEffect[eneNum].Update();

	//�����_���Ń��X�|�[���ʒu������
	m_enePos[eneNum] = m_ranEneResPos[rand() % nsEnemy::RES_POS_NUM];
	if (m_stageSelectNum == nsStdafx::STAGE2)
	{
		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));
		//�����_���Ń��X�|�[���ʒu������
		m_enePos[eneNum] = m_ranEneResPos[rand() % 9];
	}
	//�����_���֐���SEED�i��j��ݒ�
	//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
	srand((int)time(nullptr));
	//�����_���Ń��X�|�[����]������
	m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8];

	//�ʒu���Z�b�g
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);

	//��]�����Z�b�g����
	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);

	//�L�����R���̍��W�Ƀv���C���[�̍��W�������
	m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

	//�X�s�[�h��0�ɂ���
	m_moveSpeed[eneNum] = { Vector3::Zero };

	bool isHitGround;
	Vector3 hitGroundNormal;
	//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
	m_enePos[eneNum] = m_charaCon[eneNum].Execute(
		m_moveSpeed[eneNum],
		nsEnemy::DELTATIME,
		isHitGround,
		hitGroundNormal
	);

	m_canFallSoundPlayFlg[eneNum] = true;

	//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����
	m_gameScene->GetPlayerAddScoreNext(m_pushPlayer[eneNum]);
}


//�G�̖��C�����֐�
void Enemy::EneFriction(const int eneNum)
{
	//���C�͂�ݒ肷��
	m_friction[eneNum] = m_moveSpeed[eneNum];
	m_friction[eneNum] *= -1.5f;

	///����if���̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�Ɉڂ������B
	//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
	if (m_stageSelectNum == nsStdafx::STAGE3)
	{
		//���C�����炷
		m_friction[eneNum] /= 2.0f;
	}

	//���C�͂����Z����
	m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
}


//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
void Enemy::PlaAndEneClash(const int eneNum)
{
	for (int plaNum = nsStdafx::INT_ZERO; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//�v���C���[�ƓG�Ƃ̋������v�Z
		m_diff = m_player->GetPlaPos(plaNum) - m_enePos[eneNum];

		//�����̒�����40.0f���傫�������珈�����s��Ȃ�
		if (m_diff.Length() >= 40.0f)
		{
			return;
		}

		if (m_canPlaAndEneClashSoundPlayFlg[eneNum])
		{
			//�Փˉ�4
			m_soundPlayBack->EnemySoundPlayBack(PlaAndEneClashSound, eneNum);

			m_canPlaAndEneClashSoundPlayFlg[eneNum] = false;
		}

		if (m_player->GetPlaisTyazi1HanteiFlg(plaNum)) {
			m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 20.0f;
		}
		if (m_player->GetPlaisTyazi2HanteiFlg(plaNum)) {

			m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 30.0f;

		}
		//�Ō�ɉ����Ă����v���C���[���L�^
		m_pushPlayer[eneNum] = plaNum;
	}
}


//�x�N�g��������������f�o�b�N�֐�
void Enemy::EneMooveSpeedDebug(const int eneNum)
{
	Vector3 Dir = m_moveSpeed[eneNum];
	Dir.y = nsStdafx::INT_ZERO;
	Dir.Normalize();//�傫�����ʒu�ɂ���
	float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
	Dir.z *= -1;
	float angleX = acosf(x);//�A�[�N�R�T�C��
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[eneNum].SetRotationY(angleX);//���x����Y������
	m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//�p�x��ݒ肷��
	m_arrowPos[eneNum] = m_enePos[eneNum];
	m_arrowPos[eneNum].y += 50.0f;
	m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[eneNum].Length() / 10;
	m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize);
}


//�v���C���[�ƓG�Ƃ̋����𑪂��ԋ߂��v���C���[���Z�o����֐�
void Enemy::DistanceOfPlaToEne(const int eneNum)
{
	//�o�^����Ă���v���C���[�̕�����������
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		//�v���C���[�̈ʒu���擾
		m_plaPos[plaNum] = m_player->GetPlaPos(plaNum);
		//�v���C���[�̈ʒu�ƓG�̈ʒu�̋������擾
		m_mostShortDistance[plaNum] = m_plaPos[plaNum] - m_enePos[eneNum];
		m_mostShortDistance[plaNum].y = nsStdafx::FLOAT_ZERO;
	}
	//��ԋ߂�����(m_mostShortDistance[0])�̂悤�ɕ��ёւ�(�\�[�g)
	for (int plaNum = Player1; plaNum < m_totalPlaNum - 1; plaNum++) {
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_totalPlaNum; nextPlaNum++) {
			if (m_mostShortDistance[nextPlaNum].Length() < m_mostShortDistance[plaNum].Length()) {
				//����
				Vector3 tmp = m_mostShortDistance[nextPlaNum];
				m_mostShortDistance[nextPlaNum] = m_mostShortDistance[plaNum];
				m_mostShortDistance[plaNum] = tmp;
			}
		}
	}
}


//�������T�E���h��炷�֐�
void Enemy::FallSoundPlayBack(const int eneNum)
{
	//������-10�ȉ��̂Ƃ��Đ�

	if (m_enePos[eneNum].y > -10.0f || !m_canFallSoundPlayFlg[eneNum])
	{
		return;
	}
	//�����鎞�ɗ�������点�鏈��
	m_soundPlayBack->EnemySoundPlayBack(FallSound, eneNum);
	m_canFallSoundPlayFlg[eneNum] = false;
}


//�p�g�����v���p�g�J�[�̏�ɃZ�b�g����֐�
void Enemy::PointLightSetting(const int eneNum)
{
	//�ԃ|�C���g���C�g��ݒ�
	m_enePoiLigPos = m_enePos[eneNum];
	m_enePoiLigPos.x -= 10.0f;
	m_enePoiLigPos.y += 10.0f;
	m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::RED, nsEnemy::POILIG_RANGE, m_poiLigNum);
	m_poiLigNum++;
	//�|�C���g���C�g��ݒ�
	m_enePoiLigPos = m_enePos[eneNum];
	m_enePoiLigPos.x += 10.0f;
	m_enePoiLigPos.y += 10.0f;
	m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::BLUE, nsEnemy::POILIG_RANGE, m_poiLigNum);
	m_poiLigNum++;
}