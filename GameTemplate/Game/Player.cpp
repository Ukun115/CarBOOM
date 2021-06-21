#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Enemy.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0
	const int PRIORITY_1 = 1;	//�D��x1

	const Vector3 PlAYER_SCA = { 1.4f,1.4f,1.4f };			//�v���C���[�̊g�嗦
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//���X�|�[�����W(�E��)
}


bool Player::Start()
{
	//�C���X�^���X��T���B
	m_titleScene = FindGO<TitleScene>("titlescene");
	m_gameScene = FindGO<GameScene>("gamescene");
	m_enemy = FindGO<Enemy>("enemy");

	//�e�v���C���[�̂Q�i�K���ߍU���̉���
	for (int i = 0; i < 4; i++)
	{
		//���߂P�i�K�ڂ́u�P�v�摜�I�u�W�F�N�g����
		m_DASpr1[i] = NewGO<SpriteRender>(PRIORITY_1,nullptr);
		m_DASpr1[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr1[i]->Deactivate();
		//���߂P�i�K�ڂ́u�Q�v�摜�I�u�W�F�N�g����
		m_DASpr2[i] = NewGO<SpriteRender>(PRIORITY_1,nullptr);
		m_DASpr2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		//��\��
		m_DASpr2[i]->Deactivate();
	}
	m_DASpr1[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_DASpr1[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_DASpr1[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_DASpr1[3]->SetPosition({ 550.0f,-200.0f,0.0f });
	m_DASpr2[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_DASpr2[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_DASpr2[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_DASpr2[3]->SetPosition({ 550.0f,-200.0f,0.0f });

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�o�^����Ă�������s
		if (m_titleScene->GetPlaFlg(i) == true)
		{
			//�v���C���[���f���I�u�W�F�N�g����
			m_player[i] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);

			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			//�ǉ����ꂽ�v���C���[�̖��O�摜�̕\���ƈʒu����
			//�PP
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�
			}
			//�傫�������B���̃��f�����������������߁A���f���̑傫����1.5�{�B
			m_player[i]->SetScale(PlAYER_SCA);
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResPos(i);

			m_charaCon[i].Init(15.0f, 85.0f, m_pos[i]);

			//�v���C���[����+1
			m_plaNum++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		m_pushPlayer[i] = 4;	//�����l�͎��Ŕ����4�B
	}

	//Start�֐���return��
	return true;
}


Player::~Player()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < m_plaNum; i++)
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
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() != 0) {

			//�d�͂̉e����^����
			Gravity(i);

			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (m_gameScene->GetCountDownFlg() == false)
			{
				//�v���C���[��DA���ߏ��
				PlaDAState(i);

				//�v���C���[�̏��
				PlaNowState(i);

				PlaSpeedCorrection(i);

				//��]����
				PlaTurn(i);

				//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
				PlaAndEneClash(i);
				//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏���
				PlaAndPlaClash(i);

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

				//�v���C���[�̃��X�|�[������
				PlaResporn(i);
			}
			else
			{
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
void Player::PlaResporn(int x)
{
	if (m_pos[x].y < -1000.0f)
	{
		//�v���C���[�̍��W�����X�|�[�����W�ɃZ�b�g
		PlaResPos(x);

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[x].SetPosition(m_pos[x]);

		//�X�s�[�h��������
		m_moveSpeed[x] = { Vector3::Zero };

		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_pos[x] = m_charaCon[x].Execute(m_moveSpeed[x], 1.0f);

		//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����G�̃i���o�[
		m_gameScene->GetPlayerAddScore(m_pushPlayer[x], x);
		//�S�ŏ��������A�S�̂܂ܗ�����ƁA
		//���łƂ݂Ȃ����g�̃|�C���g������悤�ɃZ�b�g���Ă���
		m_pushPlayer[x] = 4;
	}
}


//�������v���C���[�̏����ʒu���Z�b�g������֐�
void Player::PlaResPos(int x)
{
	switch (x)
	{
		//1P
	 case PLAYER1:
			m_pos[x] = PLAYER1_RESPOS;		//���X�|�[�����W(����)

			//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
			//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
			m_rotAngle[x] = 2.5f;
			break;
		//2P
	 case PLAYER2:
			m_pos[x] = PLAYER2_RESPOS;		//���X�|�[�����W(�E��)

			//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
			//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
			m_rotAngle[x] = 3.7f;
			break;
		//3P
	 case PLAYER3:
			m_pos[x] = PLAYER3_RESPOS;		//���X�|�[�����W(����)

			//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
			//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
			m_rotAngle[x] = 1.0f;
			break;
		//4P
	 case PLAYER4:
			m_pos[x] = PLAYER4_RESPOS;		//���X�|�[�����W(�E��)

			//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
			//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
			m_rotAngle[x] = 5.5f;
			break;
	}

	//��]�����Z�b�g����
	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

	//�v���C���[�̈ʒu,��]�̏����X�V����
	PlaDataUpdate(x);
}


//�v���C���[�̈ʒu,��]�̏����X�V����֐�
void Player::PlaDataUpdate(int x)
{
	//�ʒu���Z�b�g
	m_player[x]->SetPosition(m_pos[x]);
	//��]���Z�b�g
	m_player[x]->SetRotation(m_rot[x]);
}


//�v���C���[�̌��݂̏�Ԃ�`����֐�
void Player::PlaNowState(int x)
{
	if (m_pressTimer[x] == 0 && m_releaseTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		m_isBPushFlg[x] = false;
		m_isAtack0Flg[x] = false;
		m_isAtack1Flg[x] = false;
		m_isAtack2Flg[x] = false;
		m_atackTime[x] = 0;

	}
	if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
	{
		//�U����������
		PlaAttackBefore(x);
	}

	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && m_isAtack0Flg[x] == true)
	{
		//�������Ƃ��̃^�C�}�[������
		m_pressTimer[x] = 0;

		//�������Ƃ��̃^�C�}�[������
		m_releaseTimer[x] = 0;
		m_isBPushFlg[x] = false;
		m_isAtack0Flg[x] = false;
		m_isAtack1Flg[x] = false;
		m_isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && m_isAtack1Flg[x] == true)
	{
		//�`���[�W�U��1�̏���
		m_moveSpeed[x] = m_plaDir[x] * 10.0f;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && m_isAtack2Flg[x] == true)
	{
		//�`���[�W�U��2����
		m_moveSpeed[x] = m_plaDir[x] * 20.0f;

		m_isTyazi2Flg = true;
	}

	if (m_releaseTimer[x] == 20 && m_pressTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		m_isBPushFlg[x] = false;
		m_isAtack0Flg[x] = false;
		m_isAtack1Flg[x] = false;
		m_isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
}


//�v���C���[�̒ʏ�ړ������֐�
void Player::PlaMove(int x)
{
	//���X�e�B�b�N�̓��͗ʂ����Z����
	m_moveSpeed[x].x += m_leftStick_x[x] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -2.0f;

	//���C�͂����Z����
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}


//�v���C���[�̈ړ����x�ɕ␳������֐�
void Player::PlaSpeedCorrection(int x)
{
	//�X�s�[�h�̕␳
	if (m_moveSpeed[x].x > 5.0f) {
		m_moveSpeed[x].x = 5.0f;	//�E�����̍ő呬�x
	}
	if (m_moveSpeed[x].x < -5.0f) {
		m_moveSpeed[x].x = -5.0f;	//�������̍ő呬�x
	}
	if (m_moveSpeed[x].z > 5.0f) {
		m_moveSpeed[x].z = 5.0f;	//������̍ő呬�x
	}
	if (m_moveSpeed[x].z < -5.0f) {
		m_moveSpeed[x].z = -5.0f;	//�������̍ő呬�x
	}
}


//�v���C���[�̉�]�����֐�
void Player::PlaTurn(int x)
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x[x] = g_pad[x]->GetLStickXF();
	m_leftStick_y[x] = g_pad[x]->GetLStickYF();

	//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}


//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
void Player::PlaAttackBefore(int x)
{
	m_moveSpeed[x].x += m_leftStick_x[x] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -2.0f;

	//���C�͂����Z����
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
	m_atackTime[x]++;
	if (m_atackTime[x] > 0 && m_atackTime[x] < 30)
	{
		m_isAtack0Flg[x] = true;
		m_isAtack1Flg[x] = false;
		m_isAtack2Flg[x] = false;


	}
	if (m_atackTime[x] >= 30 && m_atackTime[x] < 90)
	{
		m_isAtack0Flg[x] = false;
		m_isAtack1Flg[x] = true;
		m_isAtack2Flg[x] = false;
		//�u1�v�\��
		if (m_atackTime[x] == 30) {
			m_DASpr2[x]->Deactivate();
			m_DASpr1[x]->Activate();
		}
	}
	if (m_atackTime[x] > 90)
	{
		m_isAtack0Flg[x] = false;
		m_isAtack1Flg[x] = false;
		m_isAtack2Flg[x] = true;
		if (m_atackTime[x] == 91) {
			//�u2�v�\��
			m_DASpr1[x]->Deactivate();
			m_DASpr2[x]->Activate();

		}
	}
	m_plaDir[x] = m_moveSpeed[x];
	m_plaDir->Normalize();
}


//�v���C���[��DA�̗��ߏ�Ԃ̔��ʏ����֐�
void Player::PlaDAState(int x)
{
	//B�{�^���������Ă���Ƃ��A
	if (g_pad[x]->IsPress(enButtonB) && m_isBPushFlg[x] == false)
	{
		//�����Ă���Ƃ��̃^�C�}�[�����Z
		m_pressTimer[x]++;

		//�������Ƃ��̃^�C�}�[������
		m_releaseTimer[x] = 0;

		m_isBPushFlg[x] = true;
	}
	//B�{�^���𗣂����Ƃ��A
	if (!g_pad[x]->IsPress(enButtonB) && m_isBPushFlg[x] == true)
	{
		//�������Ƃ��̃^�C�}�[�����Z
		m_releaseTimer[x]++;

		//�������Ƃ��̃^�C�}�[������
		m_pressTimer[x] = 0;

		m_DASpr1[x]->Deactivate();
		m_DASpr2[x]->Deactivate();
	}
}


//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
void Player::PlaAndEneClash(int x)
{
	for (int u = 0; u < 6; u++)
	{
		//�v���C���[�ƓG�Ƃ̋������v�Z
		m_diff = m_enemy->GetEnemyPos(u) - m_pos[x];
		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 30.0f)
		{
			m_enePushSpeed = m_enemy->GetEnemySpeed(u);
			//���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
			m_enePushSpeed.x /= 5;
			m_enePushSpeed.y /= 5;
			m_enePushSpeed.z /= 5;

			//�v���C���[�ɉe��
			m_moveSpeed[x] += m_enePushSpeed;
		}
	}
}


//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
void Player::PlaAndPlaClash(int x)
{
	//�ق��v���C���[(u)�Ǝ���(i)���Ԃ������Ƃ��A�ق��v���C���[�ɉ�����鏈��
	for (int u = PLAYER1; u < m_plaNum; u++) {
		if (u == x)
		{
			//u��i�̒l�������̂Ƃ��͉��̏����͍s�킸�X�L�b�v����
			continue;
		}
		//�v���C���[���m�̋������v�Z
		m_diff = m_pos[u] - m_pos[x];
		//�����̒�����30.0f��菬����������A
		if (m_diff.Length() < 40.0f)
		{
			//�Ԃ����Ă����v���C���[�̗͂�ۑ�
			m_enePushSpeed = m_moveSpeed[u];

			//�Ԃ����Ă����v���C���[�͂��̂܂܃X�e�[�W�O�ɗ����Ȃ��悤�Ɍ���������
			m_moveSpeed[u] /= 2.0;

			if (m_isTyazi2Flg == true)
			{
				m_enePushSpeed *= 5.0f;
				//�`���[�W�Q���󂯂��Ƃ�����Q���������ł͂��̂܂ܗ������Ⴄ�̂�
				//�~�܂�悤�ɂ���
				m_moveSpeed[u] = { 0.0f,0.0f,0.0f };
			}

			//�v���C���[�ɉe��
			m_moveSpeed[x] += m_enePushSpeed;

			//�N�������Ă�������ۑ�
			m_pushPlayer[x] = u;

			//�t���O��false�ɁB�B�B
			m_isTyazi2Flg = false;
		}
	}
}


//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
void Player::Gravity(int x)
{
	//�d�͂̉e����^����
	m_moveSpeed[x].y -= 0.2f;
}