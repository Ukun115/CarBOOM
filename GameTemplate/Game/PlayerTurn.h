///<<summary>
///プレイヤーの回転処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Player;

	class PlayerTurn : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
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
		//プレイヤーの回転処理関数
		void PlaTurn(const int plaNum);

		float m_leftStick_x[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//左スティックのx入力量
		float m_leftStick_y[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//左スティックのy入力量
		float m_rotAngle[TotalPlaNum] = { nsStdafx::FLOAT_ZERO };		//回転角度
		Quaternion m_rot[TotalPlaNum];		//プレイヤーの回転
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