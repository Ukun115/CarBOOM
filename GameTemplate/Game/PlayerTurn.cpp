///<<summary>
///�v���C���[�̉�]����
///</summary>

#include "stdafx.h"
#include "PlayerTurn.h"
#include "Player.h"

namespace nsCARBOOM
{
	namespace nsPlayerTurn
	{
		const float PLAYER1_RES_ANGLE = 2.5F;
		const float PLAYER2_RES_ANGLE = 3.7f;
		const float PLAYER3_RES_ANGLE = 1.0f;
		const float PLAYER4_RES_ANGLE = 5.5f;
	}

	bool PlayerTurn::Start()
	{
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);

		return true;
	}

	PlayerTurn::~PlayerTurn()
	{

	}

	void PlayerTurn::Update()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			PlaTurn(plaNum);
		}
	}

	//�v���C���[�̉�]�����֐�
	void PlayerTurn::PlaTurn(const int plaNum)
	{
		//���X�e�B�b�N�̓��͗ʂ��󂯎��
		m_leftStick_x[plaNum] = g_pad[plaNum]->GetLStickXF();
		m_leftStick_y[plaNum] = g_pad[plaNum]->GetLStickYF();

		//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
		if (fabsf(m_player->GetPlaSpeedX(plaNum)) < 0.001f && fabsf(m_player->GetPlaSpeedZ(plaNum)) < 0.001f) {
			return;
		}
		//��]�p�x
		m_rotAngle[plaNum] = atan2(m_player->GetPlaSpeedX(plaNum), m_player->GetPlaSpeedZ(plaNum));

		m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);
	}

	//
	void PlayerTurn::PlaResAngle(const int plaNum)
	{
		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		switch (plaNum)
		{
		case Player1:
			m_rotAngle[plaNum] = nsPlayerTurn::PLAYER1_RES_ANGLE;
			break;
		case Player2:
			m_rotAngle[plaNum] = nsPlayerTurn::PLAYER2_RES_ANGLE;
			break;
		case Player3:
			m_rotAngle[plaNum] = nsPlayerTurn::PLAYER3_RES_ANGLE;
			break;
		case Player4:
			m_rotAngle[plaNum] = nsPlayerTurn::PLAYER4_RES_ANGLE;
			break;
		}
		//��]�����Z�b�g����
		m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);
	}
}