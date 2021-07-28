///<<summary>
///�v���C���[�����삷��Ԃ̏����܂Ƃ߂Ă���N���X
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Enemy.h"
#include "Player.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h


//TODO: �e�𗎂Ƃ���悤�ɂ���


namespace player
{
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//���X�|�[�����W(�E��)

	const int TIME0 = 0;	//�������Ԃ�0�b

	const float MAX_MOOVESPEED = 5.0f;
}


bool Player::Start()
{
	//�C���X�^���X��T���B
	m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
	m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
	m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);
	m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);

	//�P�ʂ̃v���C���[�̏�ɒu�������摜
	m_crown = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
	m_crown->Init("crowngold", 30.0f, 30.0f);
	m_crown->Deactivate();

	//�e�v���C���[�̂Q�i�K���ߍU����UI
	for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
	{
		for (int i = 0; i < 5; i++)
		{
			switch (i)
			{
			case 0:
				m_chargeUIPriority = 2;
				break;
			case 1:
				m_chargeUIPriority = 3;
				break;
			case 2:
				m_chargeUIPriority = 1;
				break;
			case 3:
				m_chargeUIPriority = 4;
				break;
			case 4:
				m_chargeUIPriority = 2;
				break;
			}
			m_chargeUI[i][plaNum] = NewGO<SpriteRender>(m_chargeUIPriority, nullptr);
			sprintf(m_filePath, "ChargeUI_%d", i+1);
			m_chargeUI[i][plaNum]->Init(m_filePath, 50.0f, 50.0f);
			m_chargeUI[i][plaNum]->Deactivate();
			m_chargeUI[i][plaNum]->SetRotation(Quaternion::Identity);
		}
	}

	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		//�v���C���[���f���I�u�W�F�N�g����
		m_player[plaNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);

		//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
		//m_skinModelRenderArrow[plaNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);


		sprintf(m_filePath, "LowPoly_PlayerCar_%d", plaNum);
		m_player[plaNum]->Init(m_filePath);
		sprintf(m_filePath, "ShootDown%d", plaNum);
		m_shootDownEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�
		sprintf(m_filePath, "Jet%d", plaNum);
		m_jetEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�
		sprintf(m_filePath, "Landing%d", plaNum);
		m_landingEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�

		//�v���C���[�������ʒu�Ɏ����Ă����B
		PlaResPos(plaNum);

		m_charaCon[plaNum].Init(15.0f, 85.0f, m_pos[plaNum]);

		//�G�t�F�N�g�̑傫������
		m_shootDownEffect[plaNum].SetScale({ 70.0f,70.0f,70.0f });
		//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
		Quaternion m_shootDownEffectRot = m_shootDownEffect[plaNum].GetRotation();
		//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
		m_shootDownEffectRot.AddRotationX(-1.5708f);	//X������_�ɁA-1.5708rad(-90��)��]
		m_shootDownEffect[plaNum].SetRotation(m_shootDownEffectRot);

		//�G�t�F�N�g�̑傫������
		m_jetEffect[plaNum].SetScale({ 3.0f,3.0f,3.0f });
		//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
		m_shootDownEffectRot = m_jetEffect[plaNum].GetRotation();
		//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
		m_shootDownEffectRot.AddRotationX(-1.5708f);	//X������_�ɁA-1.5708rad(-90��)��]
		m_jetEffect[plaNum].SetRotation(m_shootDownEffectRot);

		//���n�G�t�F�N�g�̑傫������
		m_landingEffect[plaNum].SetScale({ 20.0f,20.0f,20.0f });

		//�v���C���[����+1
		m_plaNum++;
	}
	for (int plaNum = Player1; plaNum < 5; plaNum++)
	{
		m_pushPlayer[plaNum] = 4;	//�����l�͒N�ɂ��|�C���g������Ȃ�4�B
	}

	return true;
}


Player::~Player()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		//�v���C���[���폜
		DeleteGO(m_player[plaNum]);
		//�`���[�W�U���̍ۂ̒i�K�����\���̍폜�B
		for (int i = 0; i < 5; i++)
		{
			DeleteGO(m_chargeUI[i][plaNum]);
		}
	}
	DeleteGO(m_crown);
}


void Player::Update()
{
	//�|�[�Y��
	if (m_isPauseFlg)
	{
		return;
	}
	//�������Ԃ�0�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
	if (m_gameScene->GetNowTime() == player::TIME0)
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
			PlaTurn(plaNum);

			//�v���C���[�̏��
			PlaNowState(plaNum);

			//�x�N�g��������������f�o�b�N�֐�
			//PlaMooveSpeedDebug(i);

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
						m_jetEffect[plaNum].Play();

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
			//�x�N�g��������������f�o�b�N�֐�
			//PlaMooveSpeedDebug(i);

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
}


//�v���C���[�̃��X�|�[�������֐�
void Player::PlaResporn(const int plaNum)
{
	if (m_pos[plaNum].y >= -1000.0f)
	{
		return;
	}
	//���ăT�E���h
	m_soundPlayBack->PlayerSoundPlayBack(ShootDownSound,plaNum);

	//���ăG�t�F�N�g�Đ��J�n�B
	m_shootDownEffect[plaNum].Play();
	//���ăG�t�F�N�g�̈ʒu���v���C���[���������ʒu�ɐݒ�
	m_shootDownEffect[plaNum].SetPosition(m_pos[plaNum]);
	//�X�V
	m_shootDownEffect[plaNum].Update();

	//�v���C���[�̍��W�����X�|�[�����W�ɃZ�b�g
	PlaResPos(plaNum);

	//�L�����R���̍��W�Ƀv���C���[�̍��W�������
	m_charaCon[plaNum].SetPosition(m_pos[plaNum]);
	//���n�G�t�F�N�g���o���邩�ǂ����̃t���O�𗧂Ă�
	m_isLandingOKFlg[plaNum] = true;

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

	for (int i = 0; i < 5; i++)
	{
		m_chargeUI[i][plaNum]->Deactivate();
		m_chargeUI[i][plaNum]->SetRotation(Quaternion::Identity);
	}

	m_chargeRotValue1[plaNum] = nsStdafx::FLOAT_ZERO;
	m_chargeRotValue2[plaNum] = nsStdafx::FLOAT_ZERO;

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
	LandingEffectPlay(plaNum);
}


//�������v���C���[�̏����ʒu���Z�b�g������֐�
void Player::PlaResPos(const int plaNum)
{
	switch (plaNum)
	{
		//1P
	case Player1:
		m_pos[plaNum] = player::PLAYER1_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 2.5f;
		break;
		//2P
	case Player2:
		m_pos[plaNum] = player::PLAYER2_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 3.7f;
		break;
		//3P
	case Player3:
		m_pos[plaNum] = player::PLAYER3_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 1.0f;
		break;
		//4P
	case Player4:
		m_pos[plaNum] = player::PLAYER4_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 5.5f;
		break;
	}

	m_isFallSoundFlg[plaNum] = true;

	//��]�����Z�b�g����
	m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);

	//�v���C���[�̈ʒu,��]�̏����X�V����
	PlaDataUpdate(plaNum);
}


//�v���C���[�̈ʒu,��]�̏����X�V����֐�
void Player::PlaDataUpdate(const int plaNum)
{
	//�ʒu���Z�b�g
	m_player[plaNum]->SetPosition(m_pos[plaNum]);
	//��]���Z�b�g
	m_player[plaNum]->SetRotation(m_rot[plaNum]);

	//�u�[�X�g�G�t�F�N�g�ʒu���v���C���[�ʒu�ɐݒ�
	m_jetEffect[plaNum].SetPosition(m_pos[plaNum]);
	m_jetEffect[plaNum].SetRotation(m_rot[plaNum]);
	//�X�V
	m_jetEffect[plaNum].Update();


	//�v���C���[�̃��[���h���W���X�N���[�����W�ɕϊ�
	g_camera3D->CalcScreenPositionFromWorldPosition(plaScreenPos[plaNum],m_pos[plaNum]);


	//(Vector2��Vector3�ɕϊ�)
	m_plaChargeUIPos[plaNum].x = plaScreenPos[plaNum].x + 50.0f;
	m_plaChargeUIPos[plaNum].y = plaScreenPos[plaNum].y;
	//�`���[�W�U����UI�Ƀv���C���[�̃X�N���[�����W����
	for (int i = 0; i < 5; i++)
	{
		m_chargeUI[i][plaNum]->SetPosition(m_plaChargeUIPos[plaNum]);
	}

	//�P�ʂ̃v���C���[�̓���ɉ����摜��u��
	//(Vector2��Vector3�ɕϊ�)
	switch (m_gameScene->GetNumber1Player())
	{
	case Player1:
		m_crown->Activate();
		m_crownPos.x = plaScreenPos[Player1].x;
		m_crownPos.y = plaScreenPos[Player1].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
		break;
	case Player2:
		m_crown->Activate();
		m_crownPos.x = plaScreenPos[Player2].x;
		m_crownPos.y = plaScreenPos[Player2].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
		break;
	case Player3:
		m_crown->Activate();
		m_crownPos.x = plaScreenPos[Player3].x;
		m_crownPos.y = plaScreenPos[Player3].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
		break;
	case Player4:
		m_crown->Activate();
		m_crownPos.x = plaScreenPos[Player4].x;
		m_crownPos.y = plaScreenPos[Player4].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
		break;
	}
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
			m_soundPlayBack->PlayerSoundPlayBack(ChargeSound,plaNum);

			m_chargeUI[_2_1_1][plaNum]->Deactivate();
			m_chargeUI[_1_1][plaNum]->Activate();
			m_chargeUI[_1_2][plaNum]->Activate();
			m_chargeUI[_2_1][plaNum]->Activate();
		}

		m_isBPushFlg[plaNum] = true;

		m_isCharge1EffectSoundFlg[plaNum] = true;
		m_isCharge2EffectSoundFlg[plaNum] = true;

		//�`���[�W���Ă���Ƃ��̃^�C�}�[�����Z
		m_chargeTimer[plaNum]++;

		//�`���[�W���Ԃɂ���čU���t���O��ς���

		if (m_chargeTimer[plaNum] >= nsStdafx::INT_ZERO && m_chargeTimer[plaNum] < 30)
		{
			m_chargeRotValue1[plaNum] -= 6.0f;
			m_charge1_1Rot[plaNum].SetRotationDeg(Vector3::AxisZ, m_chargeRotValue1[plaNum]);
			m_chargeUI[_1_1][plaNum]->SetRotation(m_charge1_1Rot[plaNum]);

			m_isAttack0Flg[plaNum] = true;
		}
		if (m_chargeTimer[plaNum] >= 30 && m_chargeTimer[plaNum] < 90)
		{
			m_chargeRotValue2[plaNum] -= 3.0f;
			m_charge1_2Rot[plaNum].SetRotationDeg(Vector3::AxisZ, m_chargeRotValue2[plaNum]);
			m_chargeUI[_1_2][plaNum]->SetRotation(m_charge1_2Rot[plaNum]);

			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = true;
			m_isAttack1HanteiFlg[plaNum] = true;

			//�u1�v�\��
			if (m_chargeTimer[plaNum] == 30) {
				m_chargeUI[_1_1][plaNum]->Deactivate();
				m_chargeUI[_2_1][plaNum]->Deactivate();
				m_chargeUI[_2_1_1][plaNum]->Activate();
				m_chargeUI[_2_2][plaNum]->Activate();
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
				m_chargeUI[_1_2][plaNum]->Deactivate();

				//�`���[�W�����T�E���h�Đ�
				m_soundPlayBack->PlayerSoundPlayBack(ChargeEnd,plaNum);
			}
		}
	}
	else
	{
		m_isBPushFlg[plaNum] = false;

		//�������Ƃ��̃^�C�}�[������
		m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;

		for (int i = 0; i < 5; i++)
		{
			m_chargeUI[i][plaNum]->Deactivate();
			m_chargeUI[i][plaNum]->SetRotation(Quaternion::Identity);
		}

		m_chargeRotValue1[plaNum] = nsStdafx::FLOAT_ZERO;
		m_chargeRotValue2[plaNum] = nsStdafx::FLOAT_ZERO;

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

				for (int i = 0; i < 5; i++)
				{
					m_chargeUI[i][plaNum]->Deactivate();
					m_chargeUI[i][plaNum]->SetRotation(Quaternion::Identity);
				}

				m_chargeRotValue1[plaNum] = nsStdafx::FLOAT_ZERO;
				m_chargeRotValue2[plaNum] = nsStdafx::FLOAT_ZERO;
			}
		}
	}
}


//�v���C���[�̒ʏ�ړ������֐�
void Player::PlaMove(const int plaNum)
{
	//���X�e�B�b�N�̓��͗ʂ����Z����
	m_moveSpeed[plaNum].x += m_leftStick_x[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_leftStick_y[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();

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


//�v���C���[�̈ړ����x�ɕ␳������֐�
void Player::PlaSpeedCorrection(const int plaNum)
{
	//�X�s�[�h�̕␳
	m_moveSpeed[plaNum].x = min(m_moveSpeed[plaNum].x, player::MAX_MOOVESPEED);//�E�����̍ő呬�x
	m_moveSpeed[plaNum].x = max(m_moveSpeed[plaNum].x, -player::MAX_MOOVESPEED);//�������̍ő呬�x

	m_moveSpeed[plaNum].z = min(m_moveSpeed[plaNum].z, player::MAX_MOOVESPEED);//������̍ő呬�x
	m_moveSpeed[plaNum].z = max(m_moveSpeed[plaNum].z, -player::MAX_MOOVESPEED);//�������̍ő呬�x
}


//�v���C���[�̉�]�����֐�
void Player::PlaTurn(const int plaNum)
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x[plaNum] = g_pad[plaNum]->GetLStickXF();
	m_leftStick_y[plaNum] = g_pad[plaNum]->GetLStickYF();

	//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
	if (fabsf(m_moveSpeed[plaNum].x) < 0.001f && fabsf(m_moveSpeed[plaNum].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[plaNum] = atan2(m_moveSpeed[plaNum].x, m_moveSpeed[plaNum].z);

	m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);
}


//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
void Player::PlaAttackBefore(const int plaNum)
{
	m_moveSpeed[plaNum].x += m_leftStick_x[plaNum] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_leftStick_y[plaNum] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[plaNum] = m_moveSpeed[plaNum];
	m_friction[plaNum] *= -2.0f;

	//���C�͂����Z����
	m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();

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

		m_enePushSpeed = m_enemy->GetEnemySpeed(eneNum);
		//���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
		m_enePushSpeed /= 5;

		//�`���[�W���ɓG�ƏՓ˂�����`���[�W���L�����Z�������
		m_isAttack0Flg[plaNum] = false;
		m_isAttack1Flg[plaNum] = false;
		m_isAttack2Flg[plaNum] = false;
		//�����ꂽ��`���[�W�T�E���h���~�߂�
		if (m_chargeTimer[plaNum] > 0)
		{
			m_soundPlayBack->m_playerSound[plaNum][ChargeSound]->Stop();
		}

		for (int i = 0; i < 5; i++)
		{
			m_chargeUI[i][plaNum]->Deactivate();
			m_chargeUI[i][plaNum]->SetRotation(Quaternion::Identity);
		}

		m_chargeRotValue1[plaNum] = nsStdafx::FLOAT_ZERO;
		m_chargeRotValue2[plaNum] = nsStdafx::FLOAT_ZERO;

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
	for (unsigned int otherPlaNum = Player1; otherPlaNum < m_plaNum; otherPlaNum++) {
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
		m_soundPlayBack->PlayerSoundPlayBack(PlaAndPlaClashSound,plaNum);

		//�v���C���[�ɉe��
		m_moveSpeed[plaNum] += m_enePushSpeed;

		//�N�������Ă�������ۑ�
		m_pushPlayer[plaNum] = otherPlaNum;
	}
}


//�x�N�g��������������f�o�b�N�֐�
void Player::PlaMooveSpeedDebug(const int plaNum)
{
	Vector3 Dir = m_moveSpeed[plaNum];
	Dir.y = nsStdafx::INT_ZERO;
	Dir.Normalize();//�傫�����ʒu�ɂ���
	float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
	Dir.z *= -1;
	float angleX = acosf(x);//�A�[�N�R�T�C��
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[plaNum].SetRotationY(angleX);//���x����Y������
	m_skinModelRenderArrow[plaNum]->SetRotation(m_arrowRot[plaNum]);//�p�x��ݒ肷��
	m_arrowPos[plaNum] = m_pos[plaNum];
	m_arrowPos[plaNum].y += 30.0f;
	m_skinModelRenderArrow[plaNum]->SetPosition(m_arrowPos[plaNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[plaNum].Length() / 5;
	m_skinModelRenderArrow[plaNum]->SetScale(m_arrowSize);
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


//�v���C���[�̒��n�G�t�F�N�g���Đ�������֐�
void Player::LandingEffectPlay(const int plaNum)
{
	if (!m_isLandingOKFlg[plaNum])
	{
		return;
	}
	m_landingEffectDelayTimer[plaNum]++;

	if (m_landingEffectDelayTimer[plaNum] != 40)
	{
		return;
	}
	//���n�G�t�F�N�g�Đ�
	m_landingEffect[plaNum].Play();
	//���n�G�t�F�N�g�̈ʒu���v���C���[�����n�����ʒu�ɐݒ�
	m_landingEffect[plaNum].SetPosition(m_pos[plaNum]);
	//�X�V
	m_landingEffect[plaNum].Update();
	//�t���O������
	m_isLandingOKFlg[plaNum] = false;

	m_landingEffectDelayTimer[plaNum] = nsStdafx::INT_ZERO;
}