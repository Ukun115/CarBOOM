///<<summary>
///�v���C���[�̉�]����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Player;

	class PlayerTurn : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		enum enPlaNum
		{
			Player1,
			Player2,
			Player3,
			Player4,
			TotalPlaNum
		};

		Player* m_player = nullptr;

		~PlayerTurn()override final;
		//�v���C���[�̉�]�����֐�
		void PlaTurn(const int plaNum);

		float m_leftStick_x[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//���X�e�B�b�N��x���͗�
		float m_leftStick_y[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//���X�e�B�b�N��y���͗�
		float m_rotAngle[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//��]�p�x
		Quaternion m_rot[TotalPlaNum];		//�v���C���[�̉�]
		int m_totalPlaNum = nsStdafx::INT_ZERO;

	public:
		bool Start()override final;
		void Update()override final;

		//
		void PlaResAngle(const int plaNum);

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }

		Quaternion GetPlaRot(const int plaNum)const { return m_rot[plaNum]; }
		float GetPlaLeftStickX(const int plaNum)const { return m_leftStick_x[plaNum]; }
		float GetPlaLeftStickY(const int plaNum)const { return m_leftStick_y[plaNum]; }
	};
}