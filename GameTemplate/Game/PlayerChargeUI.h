///<<summary>
///�v���C���[�̃`���[�W�U��UI����
///</summary>


#pragma once


namespace nsCARBOOM
{
	class Player;


	class PlayerChargeUI :public	IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		enum enChargeUI
		{
			ChargeUI_1_1,
			ChargeUI_1_2,
			ChargeUI_2_1,
			ChargeUI_2_1_1,
			ChargeUI_2_2,
			TotalChargeUINum
		};

		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
			Player2,		//2P�̔z��ł̔ԍ�
			Player3,		//3P�̔z��ł̔ԍ�
			Player4,		//4P�̔z��ł̔ԍ�
			TotalPlayerNum	//�v���C���[�̍ő吔
		};


		bool Start()override final;
		~PlayerChargeUI()override final;
		void Update()override final;

		SpriteRender* m_chargeUI[TotalChargeUINum][TotalPlayerNum] = { nullptr };		//�`���[�W�摜
		SoundPlayBack* m_soundPlayBack = nullptr;

		//�`���[�WUI�摜�̂��ꂼ��̗D��x����
		int ChargeUIPriorityDecide(const int chargeUINum);


		char m_filePath[256];
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector2 plaScreenPos[TotalPlayerNum];
		Vector3 m_plaChargeUIPos[TotalPlayerNum];
		Quaternion m_charge1_1Rot[TotalPlayerNum];		//�v���C���[�̉�]
		float m_chargeRotValue1[TotalPlayerNum] = { nsStdafx::FLOAT_ZERO };
		Quaternion m_charge1_2Rot[TotalPlayerNum];		//�v���C���[�̉�]
		float m_chargeRotValue2[TotalPlayerNum] = { nsStdafx::FLOAT_ZERO };

	public:

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }


		void ChargeUIDeactive(const int plaNum);


		void ChargeUIScreenPos(const int plaNum, const Vector2 plaScreenPos);


		void ChargeRotValueInit(const int plaNum);


		//
		void Charge1Move(const int plaNum);


		//
		void Charge2Move(const int plaNum);


		//
		void ChargeUIActive(const int plaNum);


		//
		void SetChargeUI1(const int plaNum);


		//
		void SetChargeUI2(const int plaNum);
	};
}