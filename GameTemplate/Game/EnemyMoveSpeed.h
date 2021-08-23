///<<summary>
///“G‚ÌˆÚ“®ˆ—
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Enemy;
	class Player;
	class EnemyTurn;

	class EnemyMoveSpeed : public IGameObject		//TODO:ƒRƒs[‹Ö~ƒ|ƒŠƒV[‚ğŒp³‚·‚éB
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

		Vector3 m_moveSpeed[TotalEneNum];			//“G‚U‘Ì•ª‚ÌˆÚ“®‘¬“x
		Vector3 m_samDir[TotalEneNum];			//“G‚ÆƒvƒŒƒCƒ„[‚ÌŒü‚«
		Vector3 m_friction[TotalEneNum];			//“G‚U‘Ì•ª‚Ì–€C

		int m_stageSelectNum = nsStdafx::INT_ZERO;

	public:
		//“G‚É‚©‚©‚éd—Í‚ğİ’è‚·‚éŠÖ”
		void Gravity(const int eneNum)
		{
			m_moveSpeed[eneNum].y -= nsStdafx::GRAVITY;
		}
		//“G‚Ì–€Cˆ—ŠÖ”
		void EneFriction(const int eneNum);
		void EneMoveSpeedZero(const int eneNum);
		void EneNormalMove(const int eneNum);
		void EneSettenMove(const int eneNum);
		void EneCharge1Move(const int eneNum);
		void EneCharge2Move(const int eneNum);

		Vector3 GetEneMoveSpeed(const int eneNum) { return m_moveSpeed[eneNum]; }
	};
}