#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Enemy.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = { 1.4f,1.4f,1.4f };			//�v���C���[�̏����T�C�Y
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f, 100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = {  100.0f,150.0f, 100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = {  100.0f,150.0f,-100.0f };		//���X�|�[�����W(�E��)
	const float PLANAME_WIDTHSIZE = 230.0f;			//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u���́v�傫��
	const float PLANAME_HEIGHTSIZE = 120.0f;		//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u�c�́v�傫��
}

bool Player::Start()
{
	//�C���X�^���X��T���B
	m_gamescene = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_enemy = FindGO<Enemy>("enemy");

	//�e�v���C���[�̂Q�i�K���ߍU���̉���
	for (int i = 0; i < 4; i++)
	{
		m_sprite1[i] = NewGO<SpriteRender>(3);
		m_sprite1[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		m_sprite1[i]->Deactivate();

		m_sprite2[i] = NewGO<SpriteRender>(3);
		m_sprite2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		m_sprite2[i]->Deactivate();
	}
	m_sprite1[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite1[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite1[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite1[3]->SetPosition({ 550.0f,-200.0f,0.0f });
	m_sprite2[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite2[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite2[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite2[3]->SetPosition({ 550.0f,-200.0f,0.0f });

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�o�^����Ă�������s
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//�v���C���[�����[�h
			m_player[i] = NewGO<SkinModelRender>(0);

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
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResporn(i);
			m_pos[i].y = 0.0f;

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
		DeleteGO(m_sprite1[i]);
		DeleteGO(m_sprite2[i]);
	}
}

void Player::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gamescene->GetNowTime() != 0) {

			//�d�͂̉e����^����
			m_moveSpeed[i].y -= 0.2f;

			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (m_gamescene->GetCountDownFlg() == false)
			{

				//�����Ă���Ƃ��A
				if (g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == false)
				{
					//���������̃^�C�}�[�����Z
					m_pressTimer[i]++;

					//���������̃^�C�}�[������
					m_releaseTimer[i] = 0;

					isBPushFlg[i] = true;
				}
				//�������Ƃ��A
				if (!g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == true)
				{
					//���������̃^�C�}�[�����Z
					m_releaseTimer[i]++;

					//���������̃^�C�}�[������
					m_pressTimer[i] = 0;

					m_sprite1[i]->Deactivate();
					m_sprite2[i]->Deactivate();
				}

				//�v���C���[�̏��
				PlaNowSpeed(i);

				//�X�s�[�h�̕␳
				if (m_moveSpeed[i].x > 5.0f) {
					m_moveSpeed[i].x = 5.0f;	//�E�����̍ő呬�x
				}
				if (m_moveSpeed[i].x < -5.0f) {
					m_moveSpeed[i].x = -5.0f;	//�������̍ő呬�x
				}
				if (m_moveSpeed[i].z > 5.0f) {
					m_moveSpeed[i].z = 5.0f;	//������̍ő呬�x
				}
				if (m_moveSpeed[i].z < -5.0f) {
					m_moveSpeed[i].z = -5.0f;	//�������̍ő呬�x
				}

				//��]����
				PlaTurn(i);

				/// <summary>
				/// �Փˏ���
				/// </summary>
				//�p�g�J�[�ƂԂ������Ƃ��p�g�J�[�ɉ�����鏈��
				for (int u = 0; u < 6; u++)
				{
					//�v���C���[�ƃp�g�J�[�Ƃ̋������v�Z
					m_diff = m_enemy->GetEnemyPos(u) - m_pos[i];
					//�����̒�����30.0f��菬����������A
					if (m_diff.Length() < 30.0f)
					{
						m_enePushSpeed = m_enemy->GetEnemySpeed(u);
						//���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
						m_enePushSpeed.x /= 20;
						m_enePushSpeed.y /= 20;
						m_enePushSpeed.z /= 20;

						//�v���C���[�ɉe��
						m_moveSpeed[i] += m_enePushSpeed;
					}
				}
				//�ق��v���C���[(u)�Ǝ���(i)���Ԃ������Ƃ��A�ق��v���C���[�ɉ�����鏈��
				for (int u = PLAYER1; u < m_plaNum; u++) {
					if (u == i)
					{
						//u��i�̒l�������̎��͂����̏����͍s�킸�X�L�b�v����
						continue;
					}
					//�v���C���[���m�̋������v�Z
					m_diff = m_pos[u] - m_pos[i];
					//�����̒�����30.0f��菬����������A
					if (m_diff.Length() < 40.0f)
					{
						//�Փ˂��Ă���ق��v���C���[�̗͂�ۑ�
						m_enePushSpeed = m_moveSpeed[u];
						////���ꂾ�ƃv�b�V���p���[���������邽�߁A�З͂���߂�
						//m_enePushSpeed.x /= 20;
						//m_enePushSpeed.y /= 20;
						//m_enePushSpeed.z /= 20;

						//�v���C���[�ɉe��
						m_moveSpeed[i] += m_enePushSpeed;

						//�N�������Ă�������ۑ�
						m_pushPlayer[i] = u;
					}
				}

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

				/// <summary>
				/// ���X�|�[������
				/// </summary>
				if (m_pos[i].y < -1000.0f)
				{
					//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
					PlaResporn(i);

					//�L�����R���̍��W�Ƀv���C���[�̍��W�������
					m_charaCon[i].SetPosition(m_pos[i]);

					//�X�s�[�h��������
					m_moveSpeed[i] = { Vector3::Zero };

					//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
					m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����G�̃i���o�[
					m_gamescene->GetPlayerAddScore(m_pushPlayer[i],i);
					//�S�ŏ��������A�S�̂܂ܗ�����ƁA
					//���łƂ݂Ȃ����g�̃|�C���g������悤�ɃZ�b�g���Ă���
					m_pushPlayer[i] = 4;
				}
				///// <summary>
				///// �����Ȃ��Ȃ����烊�X�|�[�����鏈��
				///// </summary>
				//if (m_moveSpeed[i].Length() < 2.0f)
				//{
				//	m_noMooveTimer[i]++;
				//}
				////��������^�C�}�[��������
				//else
				//{
				//	m_noMooveTimer[i] = 0;
				//}
				//if (m_noMooveTimer[i] > 240)
				//{
				//	//���X�|�[��������
				//	PlaResporn(i);

				//	//�L�����R���̍��W�Ƀv���C���[�̍��W�������
				//	m_charaCon[i].SetPosition(m_pos[i]);

				//	//�X�s�[�h��������
				//	m_moveSpeed[i] = { Vector3::Zero };

				//	//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				//	m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

				//	m_noMooveTimer[i] = 0;
				//}
			}
			//�o�^����Ă���v���C���[�̏����X�V
			PlaDataUpdate(i);
		}
	}
}
//�I�����ꂽ�v���C���[�����X�|�[���ʒu�܂Ŗ߂��֐�
void Player::PlaResporn(int x)
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

	//�ʒu���Z�b�g
	m_player[x]->SetPosition(m_pos[x]);

	//��]�����Z�b�g����
	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

	m_player[x]->SetRotation(m_rot[x]);
}

//�v���C���[�̏����X�V����֐�
void Player::PlaDataUpdate(int x)
{
	//�ʒu���Z�b�g
	m_player[x]->SetPosition(m_pos[x]);
	//��]���Z�b�g
	m_player[x]->SetRotation(m_rot[x]);
}

void Player::PlaNowSpeed(int x)
{
	if (m_pressTimer[x] == 0 && m_releaseTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;

	}
	if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
	{
		//�U����������
		PlaAttackBefore(x);
	}

	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack0Flg[x] == true)
	{
		//���������̃^�C�}�[������
		m_pressTimer[x] = 0;

		//���������̃^�C�}�[������
		m_releaseTimer[x] = 0;
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack1Flg[x] == true)
	{
		//�`���[�W�U��1�̏���
		m_moveSpeed[x] *= 2.0f;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack2Flg[x] == true)
	{
		//�`���[�W�U��2����
		m_moveSpeed[x] *= 4.0f;
	}

	if (m_releaseTimer[x] == 20 && m_pressTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
}

//�ړ�����
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

//��]����
void Player::PlaTurn(int x)
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x[x] = g_pad[x]->GetLStickXF();
	m_leftStick_y[x] = g_pad[x]->GetLStickYF();

	//�ړ����ĂȂ����͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}

//�U����������
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
			isAtack0Flg[x] = true;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = false;


		}
		if (m_atackTime[x] >= 30 && m_atackTime[x] < 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = true;
			isAtack2Flg[x] = false;
			//�u1�v�\��
			if (m_atackTime[x] == 30) {
				m_sprite2[x]->Deactivate();
				m_sprite1[x]->Activate();
			}
		}
		if (m_atackTime[x] > 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = true;
			if (m_atackTime[x] == 91) {
				//�u2�v�\��
				m_sprite1[x]->Deactivate();
				m_sprite2[x]->Activate();

			}
		}
}