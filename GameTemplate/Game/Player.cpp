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
	for (int i = 0; i < 4; i++)
	{
		//���߂P�i�K�ڂ́u�P�v�摜�I�u�W�F�N�g����
		m_DASpr1[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr1[i]->Deactivate();
		//���߂P�i�K�ڂ́u�Q�v�摜�I�u�W�F�N�g����
		m_DASpr2[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr2[i]->Deactivate();
	}
	m_DASpr1[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr1[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr1[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr1[3]->SetPosition({ 500.0f,-150.0f,0.0f });
	m_DASpr2[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr2[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr2[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr2[3]->SetPosition({ 500.0f,-150.0f,0.0f });

	for (int i = Player1; i < MaxPlayerNum; i++)
	{
		//�o�^����Ă�������s
		if (m_titleScene->GetPlaFlg(i))
		{
			//�v���C���[���f���I�u�W�F�N�g����
			m_player[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
			m_skinModelRenderArrow[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			//�ǉ����ꂽ�v���C���[�̖��O�摜�̕\���ƈʒu����
			//�PP
			if (i == Player1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player1_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetRed.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//2P
			else if (i == Player2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player2_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetBlue.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//3P
			else if (i == Player3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player3_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetYellow.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//4P
			else if (i == Player4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�
				//���������Ƃ��̌��ăG�t�F�N�g�̏������B
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player4_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetGreen.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//���
			}
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResPos(i);

			m_charaCon[i].Init(15.0f, 85.0f, m_pos[i]);

			//�G�t�F�N�g�̑傫������
			m_shootDownEffect[i].SetScale({ 70.0f,70.0f,70.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			Quaternion m_shootDownEffectRot = m_shootDownEffect[i].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X������_�ɁA-1.5708rad(-90��)��]
			m_shootDownEffect[i].SetRotation(m_shootDownEffectRot);

			//�G�t�F�N�g�̑傫������
			m_jetEffect[i].SetScale({ 3.0f,3.0f,3.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			m_shootDownEffectRot = m_jetEffect[i].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X������_�ɁA-1.5708rad(-90��)��]
			m_jetEffect[i].SetRotation(m_shootDownEffectRot);

			//�v���C���[����+1
			m_plaNum++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		m_pushPlayer[i] = 4;	//�����l�͒N�ɂ��|�C���g������Ȃ�4�B
	}

	//Start�֐���return��
	return true;
}


Player::~Player()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = Player1; i < m_plaNum; i++)
	{
		//�v���C���[���폜
		DeleteGO(m_player[i]);
	}
	//���ߍU���̍ۂ̒i�K�����\���̍폜�B
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_DASpr1[i]);
		DeleteGO(m_DASpr2[i]);
	}
}


void Player::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = Player1; i < m_plaNum; i++)
	{
		//�N���N�V������炷
		SoundPlayBack(CarHornSound,i);
		//������Ƃ��̗������ʉ����Ȃ炷
		SoundPlayBack(FallSound,i);

		//�������Ԃ�0�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() != TIME0) {

			//�d�͂̉e����^����
			Gravity(i);

			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (!m_gameScene->GetCountDownFlg())
			{
				//��]����
				PlaTurn(i);

				//�v���C���[�̏��
				PlaNowState(i);

				//�x�N�g��������������f�o�b�N�֐�
				PlaMooveSpeedDebug(i);

				if (m_charaCon[i].IsOnGround()) {

					if (!m_isBPushFlg[i])
					{
						if (m_atackTimer[i] == 0)
						{
							//�ړ�����
							PlaMove(i);
						}
						if (m_isTyazi1Flg[i])
						{
							if (m_isCharge1EffectSoundFlg[i])
							{
								//�`���[�W�P�T�E���h
								SoundPlayBack(Dash2Sound, i);

								m_isCharge1EffectSoundFlg[i] = false;
							}

							//�`���[�W�U��1�̏���
							m_moveSpeed[i] = m_plaDir[i] * 8.0f;
						}
						if (m_isTyazi2Flg[i])
						{
							if (m_isCharge2EffectSoundFlg[i])
							{
								//�`���[�W�Q�T�E���h
								SoundPlayBack(Dash1Sound,i);

								//�W�F�b�g�G�t�F�N�g�Đ�
								m_jetEffect[i].Play();

								m_isCharge2EffectSoundFlg[i] = false;
							}
							//�`���[�W�U��2����
							m_moveSpeed[i] = m_plaDir[i] * 20.0f;
						}

					}
					if (m_isBPushFlg[i])
					{
						//�U����������
						PlaAttackBefore(i);

					}
				}

				//�v���C���[�̃��X�|�[������
				PlaResporn(i);
				//�v���C���[�̈ړ����x�ɕ␳������
				PlaSpeedCorrection(i);

				//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
				PlaAndEneClash(i);

				//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏���
				PlaAndPlaClash(i);

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//�x�N�g��������������f�o�b�N�֐�
				PlaMooveSpeedDebug(i);

				//�d�͂̉e����^����
				Gravity(i);

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}
			//�o�^����Ă���v���C���[�̏����X�V
			PlaDataUpdate(i);
		}
	}
}


//�v���C���[�̃��X�|�[�������֐�
void Player::PlaResporn(int planum)
{
	if (m_pos[planum].y < -1000.0f)
	{
		//���ăT�E���h
		SoundPlayBack(ShootDownSound,planum);

		//���ăG�t�F�N�g�Đ��J�n�B
		m_shootDownEffect[planum].Play();
		//���ăG�t�F�N�g�̈ʒu���v���C���[���������ʒu�ɐݒ�
		m_shootDownEffect[planum].SetPosition(m_pos[planum]);
		//�X�V
		m_shootDownEffect[planum].Update();

		//�v���C���[�̍��W�����X�|�[�����W�ɃZ�b�g
		PlaResPos(planum);

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[planum].SetPosition(m_pos[planum]);

		//�X�s�[�h��������
		m_moveSpeed[planum] = { Vector3::Zero };

		m_isBPushFlg[planum] = false;
		m_isTyazi1Flg[planum] = false;
		m_isTyazi2Flg[planum] = false;
		m_isAtack0Flg[planum] = false;
		m_isAtack1Flg[planum] = false;
		m_isAtack2Flg[planum] = false;
		m_DASpr1[planum]->Deactivate();
		m_DASpr2[planum]->Deactivate();

		//�������Ƃ��̃^�C�}�[������
		m_tyaziTimer[planum] = 0;
		m_atackTimer[planum] = 0;

		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_pos[planum] = m_charaCon[planum].Execute(m_moveSpeed[planum], 1.0f);

		//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����G�̃i���o�[
		m_gameScene->GetPlayerAddScore(m_pushPlayer[planum], planum);

		for (int i = 0; i < 5; i++)
		{
			m_pushPlayer[i] = 4;	//�N�ɂ��|�C���g������Ȃ�4�ɂ���B
		}
	}
}


//�������v���C���[�̏����ʒu���Z�b�g������֐�
void Player::PlaResPos(int planum)
{
	switch (planum)
	{
		//1P
	case Player1:
		m_pos[planum] = PLAYER1_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[planum] = 2.5f;
		break;
		//2P
	case Player2:
		m_pos[planum] = PLAYER2_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[planum] = 3.7f;
		break;
		//3P
	case Player3:
		m_pos[planum] = PLAYER3_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[planum] = 1.0f;
		break;
		//4P
	case Player4:
		m_pos[planum] = PLAYER4_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[planum] = 5.5f;
		break;
	}

	//��]�����Z�b�g����
	m_rot[planum].SetRotation(Vector3::AxisY, m_rotAngle[planum]);

	//�v���C���[�̈ʒu,��]�̏����X�V����
	PlaDataUpdate(planum);
}


//�v���C���[�̈ʒu,��]�̏����X�V����֐�
void Player::PlaDataUpdate(int planum)
{
	//�ʒu���Z�b�g
	m_player[planum]->SetPosition(m_pos[planum]);
	//��]���Z�b�g
	m_player[planum]->SetRotation(m_rot[planum]);

	//�u�[�X�g�G�t�F�N�g�ʒu���v���C���[�ʒu�ɐݒ�
	m_jetEffect[planum].SetPosition(m_pos[planum]);
	m_jetEffect[planum].SetRotation(m_rot[planum]);
	//�X�V
	m_jetEffect[planum].Update();
}


//�v���C���[�̌��݂̏�Ԃ�`����֐�
void Player::PlaNowState(int planum)
{

	//A�{�^����������Ă�Ƃ��A
	if (g_pad[planum]->IsPress(enButtonA))
	{
		if (m_tyaziTimer[planum] == 0)
		{
			//�`���[�W����炷
			SoundPlayBack(ChargeSound,planum);
		}

		m_isBPushFlg[planum] = true;

		m_isCharge1EffectSoundFlg[planum] = true;
		m_isCharge2EffectSoundFlg[planum] = true;

		//�`���[�W���Ă���Ƃ��̃^�C�}�[�����Z
		m_tyaziTimer[planum]++;

		//�`���[�W���Ԃɂ���čU���t���O��ς���

		if (m_tyaziTimer[planum] >= 0 && m_tyaziTimer[planum] < 30)
		{
			m_isAtack0Flg[planum] = true;
		}
		if (m_tyaziTimer[planum] >= 30 && m_tyaziTimer[planum] < 90)
		{
			m_isAtack0Flg[planum] = false;
			m_isAtack1Flg[planum] = true;

			//�u1�v�\��
			if (m_tyaziTimer[planum] == 30) {
				m_DASpr2[planum]->Deactivate();
				m_DASpr1[planum]->Activate();
			}
		}
		if (m_tyaziTimer[planum] >= 90)
		{
			m_isAtack1Flg[planum] = false;
			m_isAtack2Flg[planum] = true;

			//�u2�v�\��
			if (m_tyaziTimer[planum] == 90) {
				m_DASpr1[planum]->Deactivate();
				m_DASpr2[planum]->Activate();
			}
		}
	}

	//A�{�^����������ĂȂ��Ƃ��A
	if (!g_pad[planum]->IsPress(enButtonA))
	{
		m_isBPushFlg[planum] = false;

		m_DASpr1[planum]->Deactivate();
		m_DASpr2[planum]->Deactivate();

		//�������Ƃ��̃^�C�}�[������
		m_tyaziTimer[planum] = 0;

		//�U���t���O�ɂ���čU��������ς���

		//�`���[�W���s
		if (m_isAtack0Flg[planum])
		{
			m_isAtack0Flg[planum] = false;
		}

		//�`���[�W1
		if (m_isAtack1Flg[planum])
		{
			m_atackTimer[planum]++;
			m_atackHanteiTimer[planum]++;

			if (m_atackTimer[planum] > 0 && m_atackTimer[planum] < 20)
			{
				m_isTyazi1Flg[planum] = true;
			}
			if (m_atackTimer[planum] == 20)
			{
				m_atackTimer[planum] = 0;
				m_isAtack1Flg[planum] = false;
				m_isTyazi1Flg[planum] = false;
				////�������Ƃ��̃^�C�}�[������
				//m_tyaziTimer[x] = 0;
			}


		}

		//�`���[�W2
		if (m_isAtack2Flg[planum])
		{
			m_atackTimer[planum]++;
			if (0 < m_atackTimer[planum] && m_atackTimer[planum] < 20)
			{
				m_isTyazi2Flg[planum] = true;
			}
			if (m_atackTimer[planum] == 20)
			{
				m_atackTimer[planum] = 0;
				m_isAtack2Flg[planum] = false;
				m_isTyazi2Flg[planum] = false;
				////�������Ƃ��̃^�C�}�[������
				//m_tyaziTimer[x] = 0;
			}
		}
	}
}


//�v���C���[�̒ʏ�ړ������֐�
void Player::PlaMove(int planum)
{
	//���X�e�B�b�N�̓��͗ʂ����Z����
	m_moveSpeed[planum].x += m_leftStick_x[planum] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_leftStick_y[planum] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[planum] = m_moveSpeed[planum];
	m_friction[planum] *= -2.0f;

	///����if�̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�ɏ����B
	//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//���C�����炷
		m_friction[planum] /= 3.0f;
	}

	//���C�͂����Z����
	m_moveSpeed[planum].x += m_friction[planum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_friction[planum].z * g_gameTime->GetFrameDeltaTime();
}


//�v���C���[�̈ړ����x�ɕ␳������֐�
void Player::PlaSpeedCorrection(int planum)
{
	//�X�s�[�h�̕␳
	m_moveSpeed[planum].x = min(m_moveSpeed[planum].x, 5.0f);//�E�����̍ő呬�x
	m_moveSpeed[planum].x = max(m_moveSpeed[planum].x, -5.0f);//�������̍ő呬�x

	m_moveSpeed[planum].z = min(m_moveSpeed[planum].z, 5.0f);//������̍ő呬�x
	m_moveSpeed[planum].z = max(m_moveSpeed[planum].z, -5.0f);//�������̍ő呬�x
}


//�v���C���[�̉�]�����֐�
void Player::PlaTurn(int planum)
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x[planum] = g_pad[planum]->GetLStickXF();
	m_leftStick_y[planum] = g_pad[planum]->GetLStickYF();

	//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
	if (fabsf(m_moveSpeed[planum].x) < 0.001f && fabsf(m_moveSpeed[planum].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[planum] = atan2(m_moveSpeed[planum].x, m_moveSpeed[planum].z);

	m_rot[planum].SetRotation(Vector3::AxisY, m_rotAngle[planum]);
}


//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
void Player::PlaAttackBefore(int planum)
{
	m_moveSpeed[planum].x += m_leftStick_x[planum] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_leftStick_y[planum] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[planum] = m_moveSpeed[planum];
	m_friction[planum] *= -2.0f;

	//���C�͂����Z����
	m_moveSpeed[planum].x += m_friction[planum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_friction[planum].z * g_gameTime->GetFrameDeltaTime();

	m_plaDir[planum] = m_moveSpeed[planum];
	m_plaDir->Normalize();
}


//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
void Player::PlaAndEneClash(int planum)
{
	for (int u = 0; u < 6; u++)
	{
		//�v���C���[�ƓG�Ƃ̋������v�Z
		m_diff = m_enemy->GetEnemyPos(u) - m_pos[planum];

		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 30.0f && !m_isTyazi1Flg[planum] && !m_isTyazi2Flg[planum])
		{
			m_enePushSpeed = m_enemy->GetEnemySpeed(u);
			//���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
			m_enePushSpeed.x /= 5;
			m_enePushSpeed.y /= 5;
			m_enePushSpeed.z /= 5;

			//�`���[�W���ɓG�ƏՓ˂�����`���[�W���L�����Z�������
			m_isAtack0Flg[planum] = false;
			m_isAtack1Flg[planum] = false;
			m_isAtack2Flg[planum] = false;
			//�����ꂽ��`���[�W�T�E���h���~�߂�
			if (m_tyaziTimer[planum] > 0)
			{
				m_ChargeSound[planum]->Stop();
			}

			m_DASpr1[planum]->Deactivate();
			m_DASpr2[planum]->Deactivate();

			//�������Ƃ��̃^�C�}�[������
			m_tyaziTimer[planum] = 0;

			//�v���C���[�ɉe��
			m_moveSpeed[planum] += m_enePushSpeed;
		}
	}
}


//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
void Player::PlaAndPlaClash(int planum)
{
	//�ق��v���C���[(u)�Ǝ���(i)���Ԃ������Ƃ��A�ق��v���C���[�ɉ�����鏈��
	for (int u = Player1; u < m_plaNum; u++) {
		if (u == planum)
		{
			//u��i�̒l�������̂Ƃ��͉��̏����͍s�킸�X�L�b�v����
			continue;
		}
		//�v���C���[���m�̋������v�Z
		m_diff = m_pos[u] - m_pos[planum];
		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 40.0f)
		{
			//�Ԃ����Ă����v���C���[�̗͂�ۑ�
			m_enePushSpeed = m_moveSpeed[u];

			//�Ԃ����Ă����v���C���[�͂��̂܂܃X�e�[�W�O�ɗ����Ȃ��悤�Ɍ���������
			m_moveSpeed[u] /= 2.0;

			if (m_isTyazi2Flg[planum])
			{
				m_enePushSpeed *= 5.0f;
				//�`���[�W�Q���󂯂��Ƃ�����Q���������ł͂��̂܂ܗ������Ⴄ�̂�
				//�~�܂�悤�ɂ���
				m_moveSpeed[u] = { 0.0f,0.0f,0.0f };
			}

			//�Փˉ�
			SoundPlayBack(PlaAndPlaClashSound,planum);

			//�v���C���[�ɉe��
			m_moveSpeed[planum] += m_enePushSpeed;

			//�N�������Ă�������ۑ�
			m_pushPlayer[planum] = u;
		}
	}
}


//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
void Player::Gravity(int planum)
{
	//�d�͂̉e����^����
	m_moveSpeed[planum].y -= 0.2f;
}


//�x�N�g��������������f�o�b�N�֐�
void Player::PlaMooveSpeedDebug(int planum)
{
	Vector3 Dir = m_moveSpeed[planum];
	Dir.y = 0;
	Dir.Normalize();//�傫�����ʒu�ɂ���
	float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
	Dir.z *= -1;
	float angleX = acosf(x);//�A�[�N�R�T�C��
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[planum].SetRotationY(angleX);//���x����Y������
	m_skinModelRenderArrow[planum]->SetRotation(m_arrowRot[planum]);//�p�x��ݒ肷��
	m_arrowPos[planum] = m_pos[planum];
	m_arrowPos[planum].y += 30.0f;
	m_skinModelRenderArrow[planum]->SetPosition(m_arrowPos[planum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[planum].Length() / 5;
	m_skinModelRenderArrow[planum]->SetScale(m_arrowSize);
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