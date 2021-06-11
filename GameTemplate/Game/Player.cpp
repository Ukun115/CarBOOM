#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "TitleScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = {1.5f,1.5f,1.5f};			//�v���C���[�̏����T�C�Y
	const int PLAYER1 = 0;			//1P
	const int PLAYER2 = 1;			//2P
	const int PLAYER3 = 2;			//3P
	const int PLAYER4 = 3;			//4P
	const int MAXPLAYERNUM = 4;		//�v���C���[�̍ő�l��
	const Vector3 PLAYER1_RESPOS = { -100.0f,0.0f,100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = { 100.0f,0.0f,100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,0.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = { 100.0f,0.0f,-100.0f };		//���X�|�[�����W(�E��)
	const float PLANAME_WIDTHSIZE = 230.0f;		//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u���́v�傫��
	const float PLANAME_HEIGHTSIZE = 120.0f;		//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u�c�́v�傫��
}

bool Player::Start()
{
	m_getAddPlayerFlg = FindGO<TitleScene>("titlescene");

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�o�^����Ă�������s
		if (m_getAddPlayerFlg->GetPlaFlg(i) == true)
		{
			m_player[i] = NewGO<SkinModelRender>(0);

			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			//�ǉ����ꂽ�v���C���[�̖��O�摜�̕\���ƈʒu����
			//�PP
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�

				//�v���C���[����+1
				m_plaNum++;
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��

				//�v���C���[����+1
				m_plaNum++;
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����

				//�v���C���[����+1
				m_plaNum++;
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�

				//�v���C���[����+1
				m_plaNum++;
			}
			//�傫�������B���̃��f�����������������߁A���f���̑傫����1.5�{�B
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResporn(i);
		}
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
}

void Player::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//��]����
		PlaTurn(i);

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

		}

		//�v���C���[�̏��
		PlaNowSpeed(i);

		m_pos[i] += m_moveSpeed[i];

		m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMax�Őݒ肳��Ă���A�j���[�V�����ŃL��������]���Ă���̂ŁA�␳������
		m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
		m_player[i]->SetRotation(m_rot2[i]); //��]���X�V
		m_player[i]->SetPosition(m_pos[i]);	//�ʒu���X�V

	//�o�^����Ă���v���C���[�̏����X�V
	//PlaDataUpdate(i);
	}
}

//�I�����ꂽ�v���C���[�����X�|�[���ʒu�܂Ŗ߂��֐�
void Player::PlaResporn(int x)
{
	//1P
	if (x == PLAYER1)
	{
		m_pos[PLAYER1] = PLAYER1_RESPOS;		//���X�|�[�����W(����)
	}
	//2P
	else if (x == PLAYER2)
	{
		m_pos[PLAYER2] = PLAYER2_RESPOS;		//���X�|�[�����W(�E��)
	}
	//3P
	else if (x == PLAYER3)
	{
		m_pos[PLAYER3] = PLAYER3_RESPOS;		//���X�|�[�����W(����)
	}
	//4P
	else if (x == PLAYER4)
	{
		m_pos[PLAYER4] = PLAYER4_RESPOS;		//���X�|�[�����W(�E��)
	}
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
		}
		if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
		{
			//�U����������
			PlaAttackBefore(x);

		}
		if (m_releaseTimer[x] > 0 && m_releaseTimer[x] < 10 && m_pressTimer[x] == 0)
		{
			//�U������
			PlaAtack(x);
		}

		if (m_releaseTimer[x] == 10 && m_pressTimer[x] == 0)
		{
			//�ړ�����
			PlaMove(x);
			isBPushFlg[x] = false;
		}
}

//�ړ�����
void Player::PlaMove(int x)
{
		//���X�e�B�b�N�̓��͗ʂ����Z����
		m_moveSpeed[x].x += m_leftStick_x[x] * 5.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_leftStick_y[x] * 5.0f * g_gameTime->GetFrameDeltaTime();

		//���C�͂�ݒ肷��
		m_friction[x] = m_moveSpeed[x];
		m_friction[x] *= -1.5f;

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
		//��]�p�x
		m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

		//������ݒ肷��
		m_plaDir[x] = m_moveSpeed[x];
		m_plaDir[x].Normalize();
}

//�U����������
void Player::PlaAttackBefore(int x)
{
		m_moveSpeed[x].x += m_leftStick_x[x] * 1.5f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_leftStick_y[x] * 1.5f * g_gameTime->GetFrameDeltaTime();

		//���C�͂�ݒ肷��
		m_friction[x] = m_moveSpeed[x];
		m_friction[x] *= -5.0f;

		//���C�͂����Z����
		m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}

//�U������
void Player::PlaAtack(int x)
{
	m_moveSpeed[x] = m_plaDir[x] * 5.0f;
}