///<<summary>
///プレイヤーのチャージ攻撃UI処理
///</summary>


#pragma once


namespace nsCARBOOM
{
	class Player;


	class PlayerChargeUI :public	IGameObject		//TODO:コピー禁止ポリシーを継承する。
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
			Player1,		//1Pの配列での番号
			Player2,		//2Pの配列での番号
			Player3,		//3Pの配列での番号
			Player4,		//4Pの配列での番号
			TotalPlayerNum	//プレイヤーの最大数
		};


		bool Start()override final;
		~PlayerChargeUI()override final;
		void Update()override final;

		SpriteRender* m_chargeUI[TotalChargeUINum][TotalPlayerNum] = { nullptr };		//チャージ画像
		SoundPlayBack* m_soundPlayBack = nullptr;

		//チャージUI画像のそれぞれの優先度決め
		int ChargeUIPriorityDecide(const int chargeUINum);


		char m_filePath[256];
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector2 plaScreenPos[TotalPlayerNum];
		Vector3 m_plaChargeUIPos[TotalPlayerNum];
		Quaternion m_charge1_1Rot[TotalPlayerNum];		//プレイヤーの回転
		float m_chargeRotValue1[TotalPlayerNum] = { nsStdafx::FLOAT_ZERO };
		Quaternion m_charge1_2Rot[TotalPlayerNum];		//プレイヤーの回転
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