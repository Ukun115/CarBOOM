///<<summary>
///�v���C���[�����삷��Ԃ̏����܂Ƃ߂Ă���N���X
///</summary>


#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Enemy.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h


//TODO: �e�𗎂Ƃ���悤�ɂ���


namespace
{
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//���X�|�[�����W(�E��)

	const int TIME0 = 0;	//�������Ԃ�0�b

	//const float PAI = 3.141592;		//�~����
}


bool Player::Start()
{
	//�C���X�^���X��T���B
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_enemy = FindGO<Enemy>(ENEMY_NAME);
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);

	//�e�v���C���[�̂Q�i�K���ߍU���̉���
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		//���߂P�i�K�ڂ́u�P�v�摜�I�u�W�F�N�g����
		m_DASpr1[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr1[plaNum]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr1[plaNum]->Deactivate();
		//���߂P�i�K�ڂ́u�Q�v�摜�I�u�W�F�N�g����
		m_DASpr2[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr2[plaNum]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr2[plaNum]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr2[plaNum]->Deactivate();
	}
	m_DASpr1[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr1[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr1[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr1[3]->SetPosition({ 500.0f,-150.0f,0.0f });
	m_DASpr2[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr2[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr2[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr2[3]->SetPosition({ 500.0f,-150.0f,0.0f });

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++)
	{
		//�o�^����Ă�������s
		if (m_titleScene->GetPlaFlg(plaNum))
		{
			//�v���C���[���f���I�u�W�F�N�g����
			m_player[plaNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
			//m_skinModelRenderArrow[plaNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			//�ǉ����ꂽ�v���C���[�̖��O�摜�̕\���ƈʒu����
			//�PP
			if (plaNum == Player1)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player1_ShootDown.efk");
				//�W�F�b�g�G�t�F�N�g
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetRed.efk");
				//���n�G�t�F�N�g
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingRed.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//2P
			else if (plaNum == Player2)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player2_ShootDown.efk");
				//�W�F�b�g�G�t�F�N�g
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetBlue.efk");
				//���n�G�t�F�N�g
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingBlue.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//3P
			else if (plaNum == Player3)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player3_ShootDown.efk");
				//�W�F�b�g�G�t�F�N�g
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetYellow.efk");
				//���n�G�t�F�N�g
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingYellow.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//4P
			else if (plaNum == Player4)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player4_ShootDown.efk");
				//�W�F�b�g�G�t�F�N�g
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetGreen.efk");
				//���n�G�t�F�N�g
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingGreen.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResPos(plaNum);

			m_charaCon[plaNum].Init(15.0f, 85.0f, m_pos[plaNum]);

			//�G�t�F�N�g�̑傫������
			m_shootDownEffect[plaNum].SetScale({ 70.0f,70.0f,70.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			Quaternion m_shootDownEffectRot = m_shootDownEffect[plaNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X������_�ɁA-1.5708rad(-90��)��]
			m_shootDownEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//�G�t�F�N�g�̑傫������
			m_jetEffect[plaNum].SetScale({ 3.0f,3.0f,3.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			m_shootDownEffectRot = m_jetEffect[plaNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X������_�ɁA-1.5708rad(-90��)��]
			m_jetEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//���n�G�t�F�N�g�̑傫������
			m_landingEffect[plaNum].SetScale({ 20.0f,20.0f,20.0f });

			//�v���C���[����+1
			m_plaNum++;
		}
	}
	for (int plaNum = 0; plaNum < 5; plaNum++)
	{
		m_pushPlayer[plaNum] = 4;	//�����l�͒N�ɂ��|�C���g������Ȃ�4�B
	}

	//Start�֐���return��
	return true;
}


Player::~Player()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int plaNum = Player1; plaNum < m_plaNum; plaNum++)
	{
		//�v���C���[���폜
		DeleteGO(m_player[plaNum]);
	}
	//���ߍU���̍ۂ̒i�K�����\���̍폜�B
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		DeleteGO(m_DASpr1[plaNum]);
		DeleteGO(m_DASpr2[plaNum]);
	}
}


void Player::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int plaNum = Player1; plaNum < m_plaNum; plaNum++)
	{
		//�N���N�V������炷
		SoundPlayBack(CarHornSound,plaNum);
		//������Ƃ��̗������ʉ����Ȃ炷
		SoundPlayBack(FallSound,plaNum);

		//�������Ԃ�0�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() != TIME0) {

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
						if (m_attackTimer[plaNum] == 0)
						{
							//�ړ�����
							PlaMove(plaNum);
						}
						if (m_isCharge1Flg[plaNum])
						{
							if (m_isCharge1EffectSoundFlg[plaNum])
							{
								//�`���[�W�P�T�E���h
								SoundPlayBack(Dash2Sound, plaNum);

								m_isCharge1EffectSoundFlg[plaNum] = false;
							}

							//�`���[�W�U��1�̏���
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 8.0f;
						}
						if (m_isCharge2Flg[plaNum])
						{
							if (m_isCharge2EffectSoundFlg[plaNum])
							{
								//�`���[�W�Q�T�E���h
								SoundPlayBack(Dash1Sound,plaNum);

								//�W�F�b�g�G�t�F�N�g�Đ�
								m_jetEffect[plaNum].Play();

								m_isCharge2EffectSoundFlg[plaNum] = false;
							}
							//�`���[�W�U��2����
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 20.0f;
						}

					}
					if (m_isBPushFlg[plaNum])
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

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//�x�N�g��������������f�o�b�N�֐�
				//PlaMooveSpeedDebug(i);

				//�d�͂̉e����^����
				Gravity(plaNum);

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);
			}
			//�o�^����Ă���v���C���[�̏����X�V
			PlaDataUpdate(plaNum);
		}
	}
}


//�v���C���[�̃��X�|�[�������֐�
void Player::PlaResporn(int plaNum)
{
	if (m_pos[plaNum].y < -1000.0f)
	{
		//���ăT�E���h
		SoundPlayBack(ShootDownSound,plaNum);

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
		m_DASpr1[plaNum]->Deactivate();
		m_DASpr2[plaNum]->Deactivate();

		//�������Ƃ��̃^�C�}�[������
		m_chargeTimer[plaNum] = 0;
		m_attackTimer[plaNum] = 0;
		m_attackHanteiTimer[plaNum] = 0;

		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);

		//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����G�̃i���o�[
		m_gameScene->GetPlayerAddScore(m_pushPlayer[plaNum], plaNum);

		for (int plaNum = 0; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//�N�ɂ��|�C���g������Ȃ�4�ɂ���B
		}
	}

	if (m_isLandingOKFlg[plaNum])
	{
		m_landingEffectDelayTimer[plaNum]++;

		if (m_landingEffectDelayTimer[plaNum] == 40)
		{
			//���n�G�t�F�N�g�Đ�
			m_landingEffect[plaNum].Play();
			//���n�G�t�F�N�g�̈ʒu���v���C���[�����n�����ʒu�ɐݒ�
			m_landingEffect[plaNum].SetPosition(m_pos[plaNum]);
			//�X�V
			m_landingEffect[plaNum].Update();
			//�t���O������
			m_isLandingOKFlg[plaNum] = false;

			m_landingEffectDelayTimer[plaNum] = 0;
		}
	}
}


//�������v���C���[�̏����ʒu���Z�b�g������֐�
void Player::PlaResPos(int plaNum)
{
	switch (plaNum)
	{
		//1P
	case Player1:
		m_pos[plaNum] = PLAYER1_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 2.5f;
		break;
		//2P
	case Player2:
		m_pos[plaNum] = PLAYER2_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 3.7f;
		break;
		//3P
	case Player3:
		m_pos[plaNum] = PLAYER3_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 1.0f;
		break;
		//4P
	case Player4:
		m_pos[plaNum] = PLAYER4_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[plaNum] = 5.5f;
		break;
	}

	//��]�����Z�b�g����
	m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);

	//�v���C���[�̈ʒu,��]�̏����X�V����
	PlaDataUpdate(plaNum);
}


//�v���C���[�̈ʒu,��]�̏����X�V����֐�
void Player::PlaDataUpdate(int plaNum)
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
}


//�v���C���[�̌��݂̏�Ԃ�`����֐�
void Player::PlaNowState(int plaNum)
{

	//A�{�^����������Ă�Ƃ��A
	if (g_pad[plaNum]->IsPress(enButtonA))
	{
		if (m_chargeTimer[plaNum] == 0)
		{
			//�`���[�W����炷
			SoundPlayBack(ChargeSound,plaNum);
		}

		m_isBPushFlg[plaNum] = true;

		m_isCharge1EffectSoundFlg[plaNum] = true;
		m_isCharge2EffectSoundFlg[plaNum] = true;

		//�`���[�W���Ă���Ƃ��̃^�C�}�[�����Z
		m_chargeTimer[plaNum]++;

		//�`���[�W���Ԃɂ���čU���t���O��ς���

		if (m_chargeTimer[plaNum] >= 0 && m_chargeTimer[plaNum] < 30)
		{
			m_isAttack0Flg[plaNum] = true;
		}
		if (m_chargeTimer[plaNum] >= 30 && m_chargeTimer[plaNum] < 90)
		{
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = true;
			m_isAttack1HanteiFlg[plaNum] = true;

			//�u1�v�\��
			if (m_chargeTimer[plaNum] == 30) {
				m_DASpr2[plaNum]->Deactivate();
				m_DASpr1[plaNum]->Activate();
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
				m_DASpr1[plaNum]->Deactivate();
				m_DASpr2[plaNum]->Activate();
			}
		}
	}

	//A�{�^����������ĂȂ��Ƃ��A
	if (!g_pad[plaNum]->IsPress(enButtonA))
	{
		m_isBPushFlg[plaNum] = false;

		//�������Ƃ��̃^�C�}�[������
		m_chargeTimer[plaNum] = 0;

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
				m_attackTimer[plaNum] = 0;
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
				m_attackHanteiTimer[plaNum] = 0;
				m_isCharge1HanteiFlg[plaNum] = false;
				m_isAttack1HanteiFlg[plaNum] = false;
				m_DASpr1[plaNum]->Deactivate();
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
				m_attackTimer[plaNum] = 0;
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
				m_attackHanteiTimer[plaNum] = 0;
				m_isCharge2HanteiFlg[plaNum] = false;
				m_isAttack2HanteiFlg[plaNum] = false;
				m_DASpr2[plaNum]->Deactivate();
			}
		}
	}
}


//�v���C���[�̒ʏ�ړ������֐�
void Player::PlaMove(int plaNum)
{
	//���X�e�B�b�N�̓��͗ʂ����Z����
	m_moveSpeed[plaNum].x += m_leftStick_x[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_leftStick_y[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[plaNum] = m_moveSpeed[plaNum];
	m_friction[plaNum] *= -2.0f;

	///����if�̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�ɏ����B
	//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//���C�����炷
		m_friction[plaNum] /= 3.0f;
	}

	//���C�͂����Z����
	m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();
}


//�v���C���[�̈ړ����x�ɕ␳������֐�
void Player::PlaSpeedCorrection(int plaNum)
{
	//�X�s�[�h�̕␳
	m_moveSpeed[plaNum].x = min(m_moveSpeed[plaNum].x, 5.0f);//�E�����̍ő呬�x
	m_moveSpeed[plaNum].x = max(m_moveSpeed[plaNum].x, -5.0f);//�������̍ő呬�x

	m_moveSpeed[plaNum].z = min(m_moveSpeed[plaNum].z, 5.0f);//������̍ő呬�x
	m_moveSpeed[plaNum].z = max(m_moveSpeed[plaNum].z, -5.0f);//�������̍ő呬�x
}


//�v���C���[�̉�]�����֐�
void Player::PlaTurn(int plaNum)
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
void Player::PlaAttackBefore(int plaNum)
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
void Player::PlaAndEneClash(int plaNum)
{
	for (int eneNum = 0; eneNum < 6; eneNum++)
	{
		//�v���C���[�ƓG�Ƃ̋������v�Z
		m_diff = m_enemy->GetEnemyPos(eneNum) - m_pos[plaNum];

		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 30.0f && m_isCharge1HanteiFlg[plaNum] == false && m_isCharge2HanteiFlg[plaNum] == false)
		{
			m_enePushSpeed = m_enemy->GetEnemySpeed(eneNum);
			//���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
			m_enePushSpeed.x /= 5;
			m_enePushSpeed.y /= 5;
			m_enePushSpeed.z /= 5;

			//�`���[�W���ɓG�ƏՓ˂�����`���[�W���L�����Z�������
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = false;
			m_isAttack2Flg[plaNum] = false;
			//�����ꂽ��`���[�W�T�E���h���~�߂�
			if (m_chargeTimer[plaNum] > 0)
			{
				m_ChargeSound[plaNum]->Stop();
			}

			m_DASpr1[plaNum]->Deactivate();
			m_DASpr2[plaNum]->Deactivate();

			//�������Ƃ��̃^�C�}�[������
			m_chargeTimer[plaNum] = 0;

			//�v���C���[�ɉe��
			m_moveSpeed[plaNum] += m_enePushSpeed;
		}
	}
}


//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
void Player::PlaAndPlaClash(int plaNum)
{
	//�ق��v���C���[(u)�Ǝ���(i)���Ԃ������Ƃ��A�ق��v���C���[�ɉ�����鏈��
	for (int otherPlaNum = Player1; otherPlaNum < m_plaNum; otherPlaNum++) {
		if (otherPlaNum == plaNum)
		{
			//u��i�̒l�������̂Ƃ��͉��̏����͍s�킸�X�L�b�v����
			continue;
		}
		//�v���C���[���m�̋������v�Z
		m_diff = m_pos[otherPlaNum] - m_pos[plaNum];
		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 40.0f)
		{
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
			SoundPlayBack(PlaAndPlaClashSound,plaNum);

			//�v���C���[�ɉe��
			m_moveSpeed[plaNum] += m_enePushSpeed;

			//�N�������Ă�������ۑ�
			m_pushPlayer[plaNum] = otherPlaNum;
		}
	}
}


//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
void Player::Gravity(int plaNum)
{
	//�d�͂̉e����^����
	m_moveSpeed[plaNum].y -= 0.2f;
}


//�x�N�g��������������f�o�b�N�֐�
void Player::PlaMooveSpeedDebug(int plaNum)
{
	Vector3 Dir = m_moveSpeed[plaNum];
	Dir.y = 0;
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


//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void Player::SoundPlayBack(int soundNum, int plaNum)
{
	switch (soundNum)
	{
	case ShootDownSound:
		//���ăT�E���h�̏�����
		m_shootDownSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_shootDownSound[plaNum]->Init(L"Assets/sound/ShootDown.wav");
		m_shootDownSound[plaNum]->SetVolume(1.0f);
		m_shootDownSound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case CarHornSound:
		//X�{�^���������ꂽ�Ƃ��Đ�
		if (g_pad[plaNum]->IsTrigger(enButtonX))
		{
			//�N���N�V�����T�E���h�̏�����
			m_carHorn[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_carHorn[plaNum]->Init(L"Assets/sound/CarHorn.wav");
			m_carHorn[plaNum]->SetVolume(0.5f);
			m_carHorn[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�
		}

		break;

	case FallSound:
		//������-10�ȉ��̂Ƃ��Đ�
		if (m_pos[plaNum].y < -10.0f && m_isFallSoundFlg[plaNum])
		{
			//�N���N�V�����T�E���h�̏�����
			m_FallSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_FallSound[plaNum]->Init(L"Assets/sound/Fall.wav");
			m_FallSound[plaNum]->SetVolume(0.1f);
			m_FallSound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			m_isFallSoundFlg[plaNum] = false;
		}
		//���X�|�[���ʒu�Ɉړ������Ƃ��Ƀt���O�𕜊�������
		if (m_pos[plaNum].y == 150.0f)
		{
			m_isFallSoundFlg[plaNum] = true;
		}

		break;

	case ChargeSound:
		//�`���[�W�T�E���h�̏�����
		m_ChargeSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_ChargeSound[plaNum]->Init(L"Assets/sound/Charge.wav");
		m_ChargeSound[plaNum]->SetVolume(0.1f);
		m_ChargeSound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case Dash1Sound:
		//�_�b�V���P�T�E���h�̏�����
		m_Dash1Sound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_Dash1Sound[plaNum]->Init(L"Assets/sound/PlaDash1.wav");
		m_Dash1Sound[plaNum]->SetVolume(0.5f);
		m_Dash1Sound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case Dash2Sound:
		//�_�b�V���Q�T�E���h�̏�����
		m_Dash2Sound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_Dash2Sound[plaNum]->Init(L"Assets/sound/PlaDash2.wav");
		m_Dash2Sound[plaNum]->SetVolume(0.5f);
		m_Dash2Sound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	case PlaAndPlaClashSound:
		//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h�̏�����
		m_PlaAndPlaClashSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_PlaAndPlaClashSound[plaNum]->Init(L"Assets/sound/Clash1.wav");
		m_PlaAndPlaClashSound[plaNum]->SetVolume(1.0f);
		m_PlaAndPlaClashSound[plaNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}