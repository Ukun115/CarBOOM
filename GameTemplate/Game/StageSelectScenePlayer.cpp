///<<summary>
///�X�e�[�W�Z���N�g��ʂ̃v���C���[���[�u����
///</summary>

#include "stdafx.h"
#include "StageSelectScenePlayer.h"

namespace nsCARBOOM
{
	namespace nsStageSelectScenePlayer
	{
		const int PLAYER1 = 0;		//�v���C���[�P
		const float MAX_MOOVESPEED = 5.0f;
		const float VERTICAL_WIDTH = 230.0f;
		const float BESIDE_WIDTH = 420.0f;
		const float FRICTION_POWER = -2.0f;
	}

	bool StageSelectScenePlayer::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//�v���C���[���f���I�u�W�F�N�g����
		//�����摜�̏�ɏ��悤�Ƀv���C�I���e�B�[�͂P�����摜������������
		m_player = NewGO<SkinModelRender>(nsStdafx::PRIORITY_2, nullptr);
		m_player->Init("LowPoly_PlayerCar_0");	//�v���C���[�P�̎ԃ��f��
		//�����ʒu�ݒ�
		m_player->SetPosition(Vector3::Zero);

		return true;
	}

	StageSelectScenePlayer::~StageSelectScenePlayer()
	{
		//�v���C���[���폜�B
		DeleteGO(m_player);
	}

	void StageSelectScenePlayer::Update()
	{
		//�x�N�g��������������f�o�b�N�֐�
		//PlaMooveSpeedDebug();
		//�N���N�V������炷�֐�
		CarHorn();
		//�v���C���[�̉�]����
		PlaTurn();
		//�v���C���[�̒ʏ�ړ�����
		PlaMove();
		//�v���C���[�̈ړ����x�ɕ␳������
		PlaSpeedCorrection();
		//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���
		AvoidScreenOutSide();
		//�v���C���[�̈ʒu,��]�̏����X�V����
		PlaDataUpdate();
	}

	//�v���C���[�̒ʏ�ړ������֐�
	void StageSelectScenePlayer::PlaMove()
	{
		//���X�e�B�b�N�̓��͗ʂ����Z����
		m_moveSpeed.x += m_leftStick_x * 10.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_leftStick_y * 10.0f * g_gameTime->GetFrameDeltaTime();
		//���C�͂�ݒ肷��
		m_friction = m_moveSpeed;
		m_friction *= nsStageSelectScenePlayer::FRICTION_POWER;
		//���C�͂����Z����
		m_moveSpeed.x += m_friction.x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_friction.z * g_gameTime->GetFrameDeltaTime();

		m_pos += m_moveSpeed;
	}

	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void StageSelectScenePlayer::PlaSpeedCorrection()
	{
		//�X�s�[�h�̕␳
		m_moveSpeed.x = min(m_moveSpeed.x, nsStageSelectScenePlayer::MAX_MOOVESPEED);//�E�����̍ő呬�x
		m_moveSpeed.x = max(m_moveSpeed.x, -nsStageSelectScenePlayer::MAX_MOOVESPEED);//�������̍ő呬�x

		m_moveSpeed.z = min(m_moveSpeed.z, nsStageSelectScenePlayer::MAX_MOOVESPEED);//������̍ő呬�x
		m_moveSpeed.z = max(m_moveSpeed.z, -nsStageSelectScenePlayer::MAX_MOOVESPEED);//�������̍ő呬�x
	}

	//�v���C���[�̉�]�����֐�
	void StageSelectScenePlayer::PlaTurn()
	{
		//���X�e�B�b�N�̓��͗ʂ��󂯎��
		m_leftStick_x = g_pad[nsStageSelectScenePlayer::PLAYER1]->GetLStickXF();
		m_leftStick_y = g_pad[nsStageSelectScenePlayer::PLAYER1]->GetLStickYF();
		//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
		if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
			return;
		}
		//��]�p�x
		m_rotAngle = atan2(m_moveSpeed.x, m_moveSpeed.z);

		m_rot.SetRotation(Vector3::AxisY, m_rotAngle);
	}

	//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���֐�
	void StageSelectScenePlayer::AvoidScreenOutSide()
	{
		//�E���̕␳
		m_pos.x = min(m_pos.x, nsStageSelectScenePlayer::BESIDE_WIDTH);
		//�����̕␳
		m_pos.x = max(m_pos.x, -nsStageSelectScenePlayer::BESIDE_WIDTH);
		//�㑤�̕␳
		m_pos.z = min(m_pos.z, nsStageSelectScenePlayer::VERTICAL_WIDTH);
		//�����̕␳
		m_pos.z = max(m_pos.z, -nsStageSelectScenePlayer::VERTICAL_WIDTH);
	}

	//�N���N�V������炷�֐�
	void StageSelectScenePlayer::CarHorn()
	{
		//X�{�^���������ꂽ�Ƃ��Đ�
		if (!g_pad[nsStageSelectScenePlayer::PLAYER1]->IsTrigger(enButtonX))
		{
			return;
		}
		//�N���N�V�����T�E���h
		m_soundPlayBack->StageSelectSceneSoundPlayBack(CarHornSound);
	}
}