///<<summary>
///敵の移動処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Enemy;
	class Player;
	class EnemyTurn;

	class EnemyMoveSpeed : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enEnemyNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		Enemy* m_enemy = nullptr;
		Player* m_player = nullptr;
		EnemyTurn* m_enemyTurn = nullptr;

		bool Start()override final;
		~EnemyMoveSpeed()override final;
		void Update()override final;

		Vector3 m_moveSpeed[TotalEneNum];			//敵６体分の移動速度
		Vector3 m_samDir[TotalEneNum];			//敵とプレイヤーの向き
		Vector3 m_friction[TotalEneNum];			//敵６体分の摩擦

	public:
		//敵にかかる重力を設定する関数
		void Gravity(const int eneNum)
		{
			m_moveSpeed[eneNum].y -= nsStdafx::GRAVITY;
		}
		//敵の摩擦処理関数
		void EneFriction(const int eneNum);
		void EneMoveSpeedZero(const int eneNum);
		void EneNormalMove(const int eneNum);
		void EneSettenMove(const int eneNum);
		void EneCharge1Move(const int eneNum);
		void EneCharge2Move(const int eneNum);

		Vector3& GetEneMoveSpeed(const int eneNum) { return m_moveSpeed[eneNum]; }

		void AddWindPowerX(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].x += windSpeed; }
		void AddWindPowerZ(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].z += windSpeed; }
	};
}