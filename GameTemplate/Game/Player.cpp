///<<summary>
///�v���C���[�̃��C������
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Enemy.h"
#include "Player.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h
#include "PlayerMoveSpeedArrow.h"
#include "PlayerTurn.h"
#include "PlayerChargeUI.h"
#include "PlayerEffect.h"
#include "EnemyMoveSpeed.h"

//TODO: �e�𗎂Ƃ���悤�ɂ���

namespace nsCARBOOM
{
	namespace nsPlayer
	{
		const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//���X�|�[�����W(����)
		const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//���X�|�[�����W(�E��)
		const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//���X�|�[�����W(����)
		const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//���X�|�[�����W(�E��)
		const int TIME0 = 0;	//�������Ԃ�0�b
		const float MAX_MOOVESPEED = 5.0f;
		const float MAX_FALL_POSITION = -1000.0f;
	}

	bool Player::Start()
	{
		//�C���X�^���X��T���B
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		m_enemyMoveSpeed = FindGO<EnemyMoveSpeed>(nsStdafx::ENEMYMOVESPEED_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);
		m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);

		m_playerEffect = NewGO<PlayerEffect>(nsStdafx::PRIORITY_0,nullptr);
		m_playerEffect->SetTotalPlaNum(m_totalPlaNum);

		//�P�ʂ̃v���C���[�̏�ɒu�������摜
		m_crown = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_crown->Init("crowngold", 30.0f, 30.0f);
		m_crown->Deactivate();

		//�v���C���[�̉�]�����N���X
		m_playerTurn = NewGO<PlayerTurn>(nsStdafx::PRIORITY_0, nsStdafx::PLAYERTURN_NAME);
		m_playerTurn->SetTotalPlaNum(m_totalPlaNum);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//�v���C���[���f���I�u�W�F�N�g����
			m_player[plaNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);

			sprintf(m_filePath, "LowPoly_PlayerCar_%d", plaNum);
			m_player[plaNum]->Init(m_filePath);

			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResPos(plaNum);

			m_charaCon[plaNum].Init(15.0f, 85.0f, m_pos[plaNum]);
		}
		for (int plaNum = Player1; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//�����l�͒N�ɂ��|�C���g������Ȃ�4�B
		}
		//�f�o�b�N�p�̃v���C���[�ړ��x�N�g���̖��̏�����
		m_playerMoveSpeedArrow = NewGO<PlayerMoveSpeedArrow>(nsStdafx::PRIORITY_0, nullptr);
		m_playerMoveSpeedArrow->SetTotalPlaNum(m_totalPlaNum);

		//�v���C���[�`���[�WUI�����N���X
		m_playerChargeUI = NewGO<PlayerChargeUI>(nsStdafx::PRIORITY_0, nullptr);
		m_playerChargeUI->SetTotalPlaNum(m_totalPlaNum);

		return true;

	}

	Player::~Player()
	{
		//�o�^����Ă���v���C���[�����[�v
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			if (m_player[plaNum] != nullptr)
			{
				//�v���C���[���폜
				DeleteGO(m_player[plaNum]);

			}
		}
		if (m_crown != nullptr)
		{
			DeleteGO(m_crown);
		}
		//�v���C���[�̈ړ��x�N�g�����폜
		DeleteGO(m_playerMoveSpeedArrow);

		DeleteGO(m_playerChargeUI);
	}

	void Player::Update()
	{
		//�|�[�Y��
		if (m_isPauseFlg)
		{
			return;
		}
		//�������Ԃ�0�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() == nsPlayer::TIME0)
		{
			return;
		}

		//�o�^����Ă���v���C���[�����[�v
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//X�{�^���������ꂽ�Ƃ��Đ�
			if (g_pad[plaNum]->IsTrigger(enButtonX))
			{
				//�N���N�V������炷
				m_soundPlayBack->PlayerSoundPlayBack(CarHornSound, plaNum);
			}

			//�������T�E���h��炷�֐�
			FallSoundPlayBack(plaNum);

			//�d�͂̉e����^����
			Gravity(plaNum);

			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (!m_gameScene->GetCountDownFlg())
			{
				//��]����
				m_playerTurn->Update();
				//�v���C���[�̏��
				PlaNowState(plaNum);

				if (m_charaCon[plaNum].IsOnGround()) {

					if (!m_isBPushFlg[plaNum])
					{
						if (m_attackTimer[plaNum] == nsStdafx::INT_ZERO)
						{
							//�ړ�����
							PlaMove(plaNum);
						}
						if (m_isCharge1Flg[plaNum] && m_isCharge1EffectSoundFlg[plaNum])
						{
							//�`���[�W�P�T�E���h
							m_soundPlayBack->PlayerSoundPlayBack(Dash2Sound, plaNum);

							//�`���[�W�U��1�̏���
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 8.0f;

							m_isCharge1EffectSoundFlg[plaNum] = false;
						}
						if (m_isCharge2Flg[plaNum] && m_isCharge2EffectSoundFlg[plaNum])
						{
							//�`���[�W�Q�T�E���h
							m_soundPlayBack->PlayerSoundPlayBack(Dash1Sound, plaNum);

							//�W�F�b�g�G�t�F�N�g�Đ�
							m_playerEffect->JetEffectPlay(plaNum);

							//�`���[�W�U��2����
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 20.0f;

							m_isCharge2EffectSoundFlg[plaNum] = false;
						}

					}
					else
					{
						//�U����������
						PlaAttackBefore(plaNum);
					}
				}

				//�v���C���[�̃��X�|�[������
				PlaResporn(plaNum);

				//�v���C���[�̈ړ����x�ɕ␳������
				PlaSpeedCorrection(plaNum);

				//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
				PlaAndEneClash(plaNum);

				//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏���
				PlaAndPlaClash(plaNum);

				bool isHitGround;
				Vector3 hitGroundNormal;
				m_moveSpeed[plaNum] += m_fallSpeed[plaNum];
				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[plaNum] = m_charaCon[plaNum].Execute(
					m_moveSpeed[plaNum],
					1.0f,
					isHitGround,
					hitGroundNormal
				);

				//if (isHitGround) {
				//	//�Ԃ������n�ʂ̖@�����X���Ă����قǗ������x���グ��B
				//	Vector3 fallPower = { 0.0f,-10.0f, 0.0f };
				//	Quaternion  qRot;
				//	qRot.SetRotation(g_vec3Up, hitGroundNormal);
				//	Vector3 vFallSpeedX, vFallSpeedZ;
				//	vFallSpeedX = g_vec3AxisX;
				//	vFallSpeedZ = g_vec3AxisZ;
				//	qRot.Apply(vFallSpeedX);
				//	qRot.Apply(vFallSpeedZ);
				//	//�������x��X���Ɏˉe����
				//	float t = vFallSpeedX.Dot(fallPower);
				//	vFallSpeedX *= t;
				//	//�������x��Z���Ɏˉe����B
				//	t = vFallSpeedZ.Dot(fallPower);
				//	vFallSpeedZ *= t * 0.1f;

				//	//XZ���̈ړ����x�����܂����̂ŁA������Z�B
				//	m_fallSpeed[plaNum] = vFallSpeedX + vFallSpeedZ;
				//}
				//else {
				//	//�Ԃ����Ă��Ȃ�
				//	m_fallSpeed[plaNum] = g_vec3Zero;
				//}
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//�d�͂̉e����^����
				Gravity(plaNum);

				bool isHitGround;
				Vector3 hitGroundNormal;
				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[plaNum] = m_charaCon[plaNum].Execute(
					m_moveSpeed[plaNum],
					1.0f,
					isHitGround,
					hitGroundNormal
				);
			}
			//�o�^����Ă���v���C���[�̏����X�V
			PlaDataUpdate(plaNum);

		}
		//�v���C���[�ړ��x�N�g���̖����X�V
		m_playerMoveSpeedArrow->Update();
	}

	//�v���C���[�̃��X�|�[�������֐�
	void Player::PlaResporn(const int plaNum)
	{
		if (m_pos[plaNum].y >= nsPlayer::MAX_FALL_POSITION)
		{
			return;
		}
		//���ăT�E���h
		m_soundPlayBack->PlayerSoundPlayBack(ShootDownSound, plaNum);

		//���ăG�t�F�N�g�Đ��J�n�B
		m_playerEffect->ShootDownEffectPlay(plaNum);

		//�v���C���[�̍��W�����X�|�[�����W�ɃZ�b�g
		PlaResPos(plaNum);

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[plaNum].SetPosition(m_pos[plaNum]);
		//���n�G�t�F�N�g���o���邩�ǂ����̃t���O�𗧂Ă�
		m_playerEffect->LandingEffectFlgOn(plaNum);

		//�X�s�[�h��������
		m_moveSpeed[plaNum] = { Vector3::Zero };

		m_isBPushFlg[plaNum] = false;
		m_isCharge1Flg[plaNum] = false;
		m_isCharge2Flg[plaNum] = false;
		m_isAttack0Flg[plaNum] = false;
		m_isAttack1Flg[plaNum] = false;
		m_isAttack2Flg[plaNum] = false;
		m_isAttack1HanteiFlg[plaNum] = false;
		m_isAttack2HanteiFlg[plaNum] = false;

		m_playerChargeUI->ChargeUIDeactive(plaNum);

		m_playerChargeUI->ChargeRotValueInit(plaNum);

		//�������Ƃ��̃^�C�}�[������
		m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;
		m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
		m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;

		bool isHitGround;
		Vector3 hitGroundNormal;
		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_pos[plaNum] = m_charaCon[plaNum].Execute(
			m_moveSpeed[plaNum],
			1.0f,
			isHitGround,
			hitGroundNormal
		);

		//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����G�̃i���o�[
		m_gameScene->GetPlayerAddScore(m_pushPlayer[plaNum], plaNum);

		for (int plaNum = Player1; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//�N�ɂ��|�C���g������Ȃ�4�ɂ���B
		}
		//�v���C���[�̒��n�G�t�F�N�g���Đ�������֐�
		m_playerEffect->LandingEffectPlay(plaNum);
	}

	//�������v���C���[�̏����ʒu���Z�b�g������֐�
	void Player::PlaResPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			m_pos[plaNum] = nsPlayer::PLAYER1_RESPOS;		//���X�|�[�����W(����)
			break;
		case Player2:
			m_pos[plaNum] = nsPlayer::PLAYER2_RESPOS;		//���X�|�[�����W(�E��)
			break;
		case Player3:
			m_pos[plaNum] = nsPlayer::PLAYER3_RESPOS;		//���X�|�[�����W(����)
			break;
		case Player4:
			m_pos[plaNum] = nsPlayer::PLAYER4_RESPOS;		//���X�|�[�����W(�E��)
			break;
		}

		m_isFallSoundFlg[plaNum] = true;

		//�v���C���[�̃��X�|�[��������^�񒆂Ɍ����悤�ɒ���
		m_playerTurn->PlaResAngle(plaNum);

		//�v���C���[�̈ʒu,��]�̏����X�V����
		PlaDataUpdate(plaNum);
	}

	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void Player::PlaDataUpdate(const int plaNum)
	{
		//�ʒu���Z�b�g
		m_player[plaNum]->SetPosition(m_pos[plaNum]);
		//��]���Z�b�g
		m_player[plaNum]->SetRotation(m_playerTurn->GetPlaRot(plaNum));

		//�v���C���[�̃��[���h���W���X�N���[�����W�ɕϊ�
		g_camera3D->CalcScreenPositionFromWorldPosition(m_plaScreenPos[plaNum], m_pos[plaNum]);

		//�P�ʂ̃v���C���[�̓���ɉ����摜��u��
		m_crown->Activate();
		m_crownPos.x = m_plaScreenPos[m_gameScene->GetNumber1Player()].x;
		m_crownPos.y = m_plaScreenPos[m_gameScene->GetNumber1Player()].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
	}

	//�v���C���[�̌��݂̏�Ԃ�`����֐�
	void Player::PlaNowState(const int plaNum)
	{
		//A�{�^����������Ă�Ƃ��A
		if (g_pad[plaNum]->IsPress(enButtonA))
		{
			if (m_chargeTimer[plaNum] == nsStdafx::INT_ZERO)
			{
				//�`���[�W����炷
				m_soundPlayBack->PlayerSoundPlayBack(ChargeSound, plaNum);

				m_playerChargeUI->ChargeUIActive(plaNum);
			}

			m_isBPushFlg[plaNum] = true;

			m_isCharge1EffectSoundFlg[plaNum] = true;
			m_isCharge2EffectSoundFlg[plaNum] = true;

			//�`���[�W���Ă���Ƃ��̃^�C�}�[�����Z
			m_chargeTimer[plaNum]++;

			//�`���[�W���Ԃɂ���čU���t���O��ς���

			if (m_chargeTimer[plaNum] >= nsStdafx::INT_ZERO && m_chargeTimer[plaNum] < 30)
			{
				m_playerChargeUI->Charge1Move(plaNum);

				m_isAttack0Flg[plaNum] = true;
			}
			if (m_chargeTimer[plaNum] >= 30 && m_chargeTimer[plaNum] < 90)
			{
				m_playerChargeUI->Charge2Move(plaNum);

				m_isAttack0Flg[plaNum] = false;
				m_isAttack1Flg[plaNum] = true;
				m_isAttack1HanteiFlg[plaNum] = true;

				//�u1�v�\��
				if (m_chargeTimer[plaNum] == 30) {

					m_playerChargeUI->SetChargeUI1(plaNum);
				}
			}
			if (m_chargeTimer[plaNum] >= 90)
			{
				m_isAttack1Flg[plaNum] = false;
				m_isAttack1HanteiFlg[plaNum] = false;
				m_isAttack2Flg[plaNum] = true;
				m_isAttack2HanteiFlg[plaNum] = true;

				//�u2�v�\��
				if (m_chargeTimer[plaNum] == 90) {

					m_playerChargeUI->SetChargeUI2(plaNum);

					//�`���[�W�����T�E���h�Đ�
					m_soundPlayBack->PlayerSoundPlayBack(ChargeEnd, plaNum);
				}
			}
		}
		else
		{
			m_isBPushFlg[plaNum] = false;

			//�������Ƃ��̃^�C�}�[������
			m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;

			m_playerChargeUI->ChargeUIDeactive(plaNum);

			m_playerChargeUI->ChargeRotValueInit(plaNum);

			//�U���t���O�ɂ���čU��������ς���

			//�`���[�W���s
			if (m_isAttack0Flg[plaNum])
			{
				m_isAttack0Flg[plaNum] = false;
			}

			//�`���[�W1
			//�U���̓����̃t���O
			if (m_isAttack1Flg[plaNum])
			{
				m_attackTimer[plaNum]++;

				if (m_attackTimer[plaNum] > 0 && m_attackTimer[plaNum] < 20)
				{
					m_isCharge1Flg[plaNum] = true;
				}
				if (m_attackTimer[plaNum] == 20)
				{
					m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge1Flg[plaNum] = false;
					m_isAttack1Flg[plaNum] = false;
				}
			}

			//�`���[�W1
			//�U���̔���̃t���O
			if (m_isAttack1HanteiFlg[plaNum])
			{
				m_attackHanteiTimer[plaNum]++;

				if (m_attackHanteiTimer[plaNum] > 0 && m_attackHanteiTimer[plaNum] < 25)
				{
					m_isCharge1HanteiFlg[plaNum] = true;
				}
				if (m_attackHanteiTimer[plaNum] == 25)
				{
					m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge1HanteiFlg[plaNum] = false;
					m_isAttack1HanteiFlg[plaNum] = false;
				}
			}

			//�`���[�W2
			//�U���̓����̃t���O
			if (m_isAttack2Flg[plaNum])
			{
				m_attackTimer[plaNum]++;

				if (0 < m_attackTimer[plaNum] && m_attackTimer[plaNum] < 25)
				{
					m_isCharge2Flg[plaNum] = true;
				}
				if (m_attackTimer[plaNum] == 25)
				{
					m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge2Flg[plaNum] = false;
					m_isAttack2Flg[plaNum] = false;
				}
			}

			//�`���[�W2
			//�U���̔���̃t���O
			if (m_isAttack2HanteiFlg[plaNum])
			{
				m_attackHanteiTimer[plaNum]++;

				if (m_attackHanteiTimer[plaNum] > 0 && m_attackHanteiTimer[plaNum] < 30)
				{
					m_isCharge2HanteiFlg[plaNum] = true;
				}
				if (m_attackHanteiTimer[plaNum] == 30)
				{
					m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge2HanteiFlg[plaNum] = false;
					m_isAttack2HanteiFlg[plaNum] = false;

					m_playerChargeUI->ChargeUIDeactive(plaNum);

					m_playerChargeUI->ChargeRotValueInit(plaNum);
				}
			}
		}
	}

	//�v���C���[�̒ʏ�ړ������֐�
	void Player::PlaMove(const int plaNum)
	{
		//���X�e�B�b�N�̓��͗ʂ����Z����
		m_moveSpeed[plaNum].x += m_playerTurn->GetPlaLeftStickX(plaNum) * 10.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_playerTurn->GetPlaLeftStickY(plaNum) * 10.0f * g_gameTime->GetFrameDeltaTime();

		Friction(plaNum);
	}

	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void Player::PlaSpeedCorrection(const int plaNum)
	{
		//�X�s�[�h�̕␳
		m_moveSpeed[plaNum].x = min(m_moveSpeed[plaNum].x, nsPlayer::MAX_MOOVESPEED);//�E�����̍ő呬�x
		m_moveSpeed[plaNum].x = max(m_moveSpeed[plaNum].x, -nsPlayer::MAX_MOOVESPEED);//�������̍ő呬�x

		m_moveSpeed[plaNum].z = min(m_moveSpeed[plaNum].z, nsPlayer::MAX_MOOVESPEED);//������̍ő呬�x
		m_moveSpeed[plaNum].z = max(m_moveSpeed[plaNum].z, -nsPlayer::MAX_MOOVESPEED);//�������̍ő呬�x
	}

	//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
	void Player::PlaAttackBefore(const int plaNum)
	{
		m_moveSpeed[plaNum].x += m_playerTurn->GetPlaLeftStickX(plaNum) * 1.5f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_playerTurn->GetPlaLeftStickY(plaNum) * 1.5f * g_gameTime->GetFrameDeltaTime();

		Friction(plaNum);

		m_plaDir[plaNum] = m_moveSpeed[plaNum];
		m_plaDir->Normalize();
	}

	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void Player::PlaAndEneClash(const int plaNum)
	{
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//�v���C���[�ƓG�Ƃ̋������v�Z
			m_diff = m_enemy->GetEnemyPos(eneNum) - m_pos[plaNum];

			//�����̒�����30.0f��菬����������A
			if (m_diff.Length() >= 30.0f)
			{
				return;
			}
			if (m_isCharge1HanteiFlg[plaNum])
			{
				return;
			}
			if (m_isCharge2HanteiFlg[plaNum])
			{
				return;
			}

			m_enePushSpeed = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
			////���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
			//m_enePushSpeed /= 2;

			//�`���[�W���ɓG�ƏՓ˂�����`���[�W���L�����Z�������
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = false;
			m_isAttack2Flg[plaNum] = false;
			//�����ꂽ��`���[�W�T�E���h���~�߂�
			if (m_chargeTimer[plaNum] > 0)
			{
				m_soundPlayBack->m_playerSound[plaNum][ChargeSound]->Stop();
			}

			m_playerChargeUI->ChargeUIDeactive(plaNum);

			m_playerChargeUI->ChargeRotValueInit(plaNum);

			//�������Ƃ��̃^�C�}�[������
			m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;

			//�v���C���[�ɉe��
			m_moveSpeed[plaNum] += m_enePushSpeed;
		}
	}

	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
	void Player::PlaAndPlaClash(const int plaNum)
	{
		//�ق��v���C���[(u)�Ǝ���(i)���Ԃ������Ƃ��A�ق��v���C���[�ɉ�����鏈��
		for (int otherPlaNum = Player1; otherPlaNum < m_totalPlaNum; otherPlaNum++) {
			if (otherPlaNum == plaNum)
			{
				//u��i�̒l�������̂Ƃ��͉��̏����͍s�킸�X�L�b�v����
				continue;
			}
			//�v���C���[���m�̋������v�Z
			m_diff = m_pos[otherPlaNum] - m_pos[plaNum];
			//�����̒�����30.0f��菬����������A
			if (m_diff.Length() >= 40.0f)
			{
				continue;
			}
			//�Ԃ����Ă����v���C���[�̗͂�ۑ�
			m_enePushSpeed = m_moveSpeed[otherPlaNum];

			//�Ԃ����Ă����v���C���[�͂��̂܂܃X�e�[�W�O�ɗ����Ȃ��悤�Ɍ���������
			m_moveSpeed[otherPlaNum] /= 2.0;

			//���肪�`���[�W1�̂Ƃ�
			if (m_isCharge1HanteiFlg[otherPlaNum] == true && m_isCharge2HanteiFlg[plaNum] == false)
			{
				m_enePushSpeed *= 2.0f;
				//�`���[�W�Q���󂯂��Ƃ�����Q���������ł͂��̂܂ܗ������Ⴄ�̂�
				//�~�܂�悤�ɂ���
				m_moveSpeed[otherPlaNum] = Vector3::Zero;
				//�������`���[�W1�̂Ƃ�
				if (m_isCharge1HanteiFlg[plaNum] == true)
				{
					m_isCharge1HanteiFlg[plaNum] = false;
				}
			}

			//���肪�`���[�W2�̂Ƃ�
			if (m_isCharge2HanteiFlg[otherPlaNum] == true)
			{
				m_enePushSpeed *= 5.0f;
				//�`���[�W�Q���󂯂��Ƃ�����Q���������ł͂��̂܂ܗ������Ⴄ�̂�
				//�~�܂�悤�ɂ���
				m_moveSpeed[otherPlaNum] = Vector3::Zero;

				//�������`���[�W1�̂Ƃ�
				if (m_isCharge1HanteiFlg[plaNum] == true)
				{
					m_isCharge1HanteiFlg[plaNum] = false;
				}
				//�������`���[�W2�̂Ƃ�
				if (m_isCharge2HanteiFlg[plaNum] == true)
				{
					m_isCharge2HanteiFlg[plaNum] = false;
				}
			}

			//�Փˉ�
			m_soundPlayBack->PlayerSoundPlayBack(PlaAndPlaClashSound, plaNum);

			//�v���C���[�ɉe��
			m_moveSpeed[plaNum] += m_enePushSpeed;

			//�N�������Ă�������ۑ�
			m_pushPlayer[plaNum] = otherPlaNum;
		}
	}

	//�������T�E���h��炷�֐�
	void Player::FallSoundPlayBack(const int plaNum)
	{
		//������-10�ȉ��̂Ƃ��Đ�
		if (m_pos[plaNum].y >= -10.0f)
		{
			return;
		}
		if (!m_isFallSoundFlg[plaNum])
		{
			return;
		}
		//������Ƃ��̗������ʉ����Ȃ炷
		m_soundPlayBack->PlayerSoundPlayBack(FallSound, plaNum);
		m_isFallSoundFlg[plaNum] = false;
	}

	//���C
	void Player::Friction(const int plaNum)
	{
		//���C�͂�ݒ肷��
		m_friction[plaNum] = m_moveSpeed[plaNum];
		m_friction[plaNum] *= -2.0f;

		///����if�̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�ɏ����B
		//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
		if (m_stageSelectNum == nsStdafx::STAGE3)
		{
			//���C�����炷
			m_friction[plaNum] /= 3.0f;
		}

		//���C�͂����Z����
		m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();
	}
}