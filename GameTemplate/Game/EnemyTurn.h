///<<summary>
///“G‚Ì‰ñ“]ˆ—
///</summary>

#pragma once

namespace nsCARBOOM
{
	class EnemyMoveSpeed;

	class EnemyTurn : public IGameObject		//TODO:ƒRƒs[‹Ö~ƒ|ƒŠƒV[‚ğŒp³‚·‚éB
	{
	private:
		enum enEnemyNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		//“G‚ÌƒŠƒXƒ|[ƒ“‚Ìƒ‰ƒ“ƒ_ƒ€Œü‚«
		enum enRandomEneRespornRot
		{
			ResRot1,
			ResRot2,
			ResRot3,
			ResRot4,
			ResRot5,
			ResRot6,
			ResRot7,
			ResRot8,
			TotalResRot
		};

		EnemyMoveSpeed* m_enemyMoveSpeed = nullptr;

		bool Start()override final;
		void Update()override final;
		~EnemyTurn()override final;

		//
		float WhatEneRandomResRot(const int eneNum);

		Quaternion m_rot[TotalEneNum];			//“G‚U‘Ì•ª‚Ì“G‚Ì‰ñ“]
		float m_rotAngle[TotalEneNum] = { nsStdafx::FLOAT_ZERO };			//“G‚U‘Ì•ª‚Ì‰ñ“]Šp“x
		Vector3 m_eneDir[TotalEneNum];			//Œü‚«
		float m_randEneResAngle[TotalResRot] = { nsStdafx::FLOAT_ZERO };		//“G‚ÌƒŠƒXƒ|[ƒ“‰ñ“]Šp“x4‚©Š

	public:
		//“G‚Ì‰ñ“]ˆ—ŠÖ”
		void EneTurn(const int eneNum);
		//ƒŠƒXƒ|[ƒ“‚ÌŒü‚«‚ğƒ‰ƒ“ƒ_ƒ€‚É‚·‚éˆ—
		void EneRespornAngleDecide(const int eneNum);
		Quaternion GetEneRot(const int eneNum)const { return m_rot[eneNum]; }
		Vector3 GetEneDir(const int eneNum)const { return m_eneDir[eneNum]; }
	};
}