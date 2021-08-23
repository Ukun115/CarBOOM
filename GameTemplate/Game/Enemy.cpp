///<<summary>
///�GNPC�̃��C������
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
#include "EnemyMoveSpeedArrow.h"
#include "EnemyTurn.h"
#include "EnemyEffect.h"
#include "EnemyMoveSpeed.h"
#include "EnemyPatoLump.h"

//TODO: �e�𗎂Ƃ���悤�ɂ���

namespace nsCARBOOM
{
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
		const int TIME0 = 0;
		const float DELTATIME = 1.0f;
		const float MAX_FALL_POSITION = -1000.0f;
		const float CHARACON_RADIUS = 15.0f;
		const float CHARACON_HEIGHT = 85.0f;
		const float FRICTION_POWER = -1.5f;
		const float REDUCE_FRICTION_POWER = 2.0f;
		const int MOST_SHORT_DIR_NUM = 0;
		const float FALLSOUND_PLAYBACK_HEIGHT = -10.0f;
	}

	bool Enemy::Start()
	{
		//�C���X�^���X��T���B
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		m_enemyEffect = NewGO<EnemyEffect>(nsStdafx::PRIORITY_0, nullptr);

		m_enemyPatoLump = NewGO<EnemyPatoLump>(nsStdafx::PRIORITY_0, nullptr);

		//�G�̃��X�|�[���ʒu
		for (int resPosNum = ResPos1; resPosNum < TotalResPos; resPosNum++)
		{
			m_ranEneResPos[resPosNum] = WhatEneRandomResPos(resPosNum);
		}

		m_enemyTurn = NewGO<EnemyTurn>(nsStdafx::PRIORITY_0, nsStdafx::ENEMYTURN_NAME);

		//�G�̍ő吔�J��Ԃ�
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//�G���f���I�u�W�F�N�g����
			m_enemy[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
			//���f���̃t�@�C���p�X��ݒ�
			m_enemy[eneNum]->Init("LowPoly_PoliceCar");	//�G���f��

			//�������W(���X�|�[�����W)�̐ݒ�B
			m_enePos[eneNum] = m_ranEneResPos[eneNum];		//�G�P�̏ꏊ
			//m_skinModelRenderArrow[WhatEnemyNum(eneNum)]->Init("Arrow");	//���

			//�����蔻��̃C�j�V�����C�Y(������)
			m_charaCon[eneNum].Init(nsEnemy::CHARACON_RADIUS, nsEnemy::CHARACON_HEIGHT, m_enePos[eneNum]);
			//300�`600�͈̔͂̃����_���l�ŃX�^�[�g���̓G��DA��x�点��^�C�}�[�̒l�ɑ��
			m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
			//120�`140�͈̔͂̃����_���l��DA���CT�^�C�}�[�̒l�ɑ��
			m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));

			m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));		//��]���X�V
		}

		m_enemyMoveSpeed = NewGO<EnemyMoveSpeed>(nsStdafx::PRIORITY_0, nullptr);

		//�f�o�b�N�p�̓G�ړ��x�N�g���̖��̏�����
		m_enemyMoveSpeedArrow = NewGO<EnemyMoveSpeedArrow>(nsStdafx::PRIORITY_0, nullptr);

		return true;
	}

	Enemy::~Enemy()
	{
		//�S�Ă̓G���폜�B
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			if (m_enemy[eneNum] != nullptr)
			{
				DeleteGO(m_enemy[eneNum]);
			}
		}
		//�G�̈ړ��x�N�g�������폜
		DeleteGO(m_enemyMoveSpeedArrow);

		DeleteGO(m_enemyEffect);
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

		m_enemyPatoLump->PoiLigNumInit();

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
					m_enemyTurn->EneTurn(eneNum);

					//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
					PlaAndEneClash(eneNum);

					//DA�U������
					EneDA(eneNum);

					//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
					EneResporn(eneNum);

					m_enePos[eneNum] += m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
				}
			}

			//�d�͂̉e����^����
			m_enemyMoveSpeed->Gravity(eneNum);

			bool isHitGround;
			Vector3 hitGroundNormal;
			m_moveSpeed[eneNum] = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
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
		m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));		//��]���X�V
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
					m_CenterToEneAngle[eneNum] = m_centerKyori[eneNum].Dot(m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM]);
					m_CenterToSettenAngle[eneNum] = m_centerKyori[eneNum].Dot(m_EneToSetten1Dir[eneNum]);

					if (m_CenterToEneAngle[eneNum] > m_CenterToSettenAngle[eneNum] && m_mostShortDistance[nsEnemy::MOST_SHORT_DIR_NUM].Length() > m_EneToSetten1[eneNum].Length())
					{
						m_PlayerToSetten1Angle[eneNum] = m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM].Dot(m_EneToSetten1Dir[eneNum]);
						m_PlayerToSetten2Angle[eneNum] = m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM].Dot(m_EneToSetten2Dir[eneNum]);
						//�ړ_�P�̕������ړ_�Q�̕����ɍs�����𔻕�
						m_enemyMoveSpeed->EneSettenMove(eneNum);
					}
					else
					{
						m_enemyMoveSpeed->EneNormalMove(eneNum);
					}
				}
				else
				{
					m_enemyMoveSpeed->EneNormalMove(eneNum);
				}

			}
			//�_�b�V���T�E���h
			m_soundPlayBack->EnemySoundPlayBack(DashSound, eneNum);

			m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

			//CT���J�E���g����t���O�𗧂Ă�
			m_canCtCountFlg[eneNum] = true;
		}
		//CT�t���O�������Ă�Ƃ��A
		if (m_canCtCountFlg[eneNum]) {

			//CT���J�E���g����
			m_CTTime[eneNum]++;

			//���C�������Ă���
			m_enemyMoveSpeed->EneFriction(eneNum);
		}
		//CT�̃J�E���g��120�b�`140�b�̂Ƃ��A
		if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

			//CT�t���O�����낷
			m_canCtCountFlg[eneNum] = false;

			//CT�̃J�E���g��0�ɂ���
			m_CTTime[eneNum] = nsStdafx::INT_ZERO;
		}
	}

	//�G�̃��X�|�[�������֐�
	void Enemy::EneResporn(const int eneNum)
	{
		//�G��Y���W�̈ʒu���ő嗎���n�_�܂ōs���ĂȂ�������return�ȍ~�̏����͍s��Ȃ�
		if (m_enePos[eneNum].y >= nsEnemy::MAX_FALL_POSITION)
		{
			return;
		}

		//���ăT�E���h
		m_soundPlayBack->EnemySoundPlayBack(ShootDownSound, eneNum);

		m_enemyEffect->SetEnemyPos(m_enePos[eneNum],eneNum);
		m_enemyEffect->ShootDownEffectPlay(eneNum);

		//�����_���Ń��X�|�[���ʒu������
		m_enePos[eneNum] = m_ranEneResPos[rand() % nsEnemy::RES_POS_NUM];
		if (m_stageSelectNum == nsStdafx::STAGE2)
		{
			//�����_���֐���SEED�i��j��ݒ�
			//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
			srand((int)time(nullptr));
			//�����_���Ń��X�|�[���ʒu������
			m_enePos[eneNum] = m_ranEneResPos[rand() % TotalResPos];
		}
		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));

		m_enemyTurn->EneRespornAngleDecide(eneNum);

		//�ʒu���Z�b�g
		m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);
		//��]�����Z�b�g����
		m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

		//�X�s�[�h��0�ɂ���
		m_enemyMoveSpeed->EneMoveSpeedZero(eneNum);

		bool isHitGround;
		Vector3 hitGroundNormal;
		m_moveSpeed[eneNum] = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
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

			if (m_player->GetPlaisTyazi1HanteiFlg(plaNum))
			{
				m_enemyMoveSpeed->EneCharge1Move(eneNum);
			}
			if (m_player->GetPlaisTyazi2HanteiFlg(plaNum))
			{
				m_enemyMoveSpeed->EneCharge2Move(eneNum);
			}
			//�Ō�ɉ����Ă����v���C���[���L�^
			m_pushPlayer[eneNum] = plaNum;
		}
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

		if (m_enePos[eneNum].y > nsEnemy::FALLSOUND_PLAYBACK_HEIGHT || !m_canFallSoundPlayFlg[eneNum])
		{
			return;
		}
		//�����鎞�ɗ�������点�鏈��
		m_soundPlayBack->EnemySoundPlayBack(FallSound, eneNum);
		m_canFallSoundPlayFlg[eneNum] = false;
	}

	//
	Vector3 Enemy::WhatEneRandomResPos(const int eneResPosNum)
	{
		switch (eneResPosNum)
		{
		case ResPos1:
			return nsEnemy::ENE_RES_POS_1;
			break;
		case ResPos2:
			return nsEnemy::ENE_RES_POS_2;
			break;
		case ResPos3:
			return nsEnemy::ENE_RES_POS_3;
			break;
		case ResPos4:
			return nsEnemy::ENE_RES_POS_4;
			break;
		case ResPos5:
			return nsEnemy::ENE_RES_POS_5;
			break;
		case ResPos6:
			return nsEnemy::ENE_RES_POS_6;
			break;
		case ResPos7:
			return nsEnemy::ENE_RES_POS_7;
			break;
		case ResPos8:
			return nsEnemy::ENE_RES_POS_8;
			break;
		case ResPos9:
			return nsEnemy::ENE_RES_POS_9;
			break;
		case ResPos10:
			if (m_stageSelectNum == nsStdafx::STAGE2)
			{
				return nsEnemy::ENE_RES_POS_10;
			}
			break;
		}
	}
}