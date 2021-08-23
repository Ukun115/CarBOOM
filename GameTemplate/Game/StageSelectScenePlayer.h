///<<summary>
///�X�e�[�W�Z���N�g��ʂ̃v���C���[���[�u����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class StageSelectScenePlayer : public IGameObject	//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		enum enSoundNum
		{
			TitleSceneBGM,
			DecideSound,
			OnStageSound,
			CarHornSound,
			TotalSoundNum
		};

		enum enStageNum
		{
			FlatStage = 1,
			DonutStage,
			IceStage,
			WindStage,
			TiltStage,
			RandomStage,
			TotalStageNum
		};

		SoundPlayBack* m_soundPlayBack = nullptr;
		SkinModelRender* m_player = nullptr;	//�v���C���[
		Vector3    m_pos;				//�v���C���[�̈ʒu
		Quaternion m_rot;				//�v���C���[�̉�]
		Vector3 m_moveSpeed;			//�ړ����x
		float m_leftStick_x = { nsStdafx::FLOAT_ZERO };			//���X�e�B�b�N��x���͗�
		float m_leftStick_y = { nsStdafx::FLOAT_ZERO };			//���X�e�B�b�N��y���͗�
		float m_rotAngle = { nsStdafx::FLOAT_ZERO };				//��]�p�x
		Vector3 m_friction;				//���C

		//�v���C���[�̒ʏ�ړ������֐�
		void PlaMove();
		//�v���C���[�̈ړ����x�ɕ␳������֐�
		void PlaSpeedCorrection();
		//�v���C���[�̉�]�����֐�
		void PlaTurn();
		//�v���C���[�̈ʒu,��]�̏����X�V����֐�
		void PlaDataUpdate()
		{
			//�ʒu���Z�b�g
			m_player->SetPosition(m_pos);
			//��]���Z�b�g
			m_player->SetRotation(m_rot);
		}
		//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���֐�
		void AvoidScreenOutSide();
		//�N���N�V������炷�֐�
		void CarHorn();

		bool Start()override final;
		~StageSelectScenePlayer()override final;
		void Update()override final;

	public:
		//�v���C���[�̈ʒu���擾����֐�
		Vector3 GetPlayerPos()const { return m_pos; }
	};
}