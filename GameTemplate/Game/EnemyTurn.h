///<<summary>
///敵の回転処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class EnemyMoveSpeed;

	class EnemyTurn : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enEnemyNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		//敵のリスポーン時のランダム向き
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

		Quaternion m_rot[TotalEneNum];			//敵６体分の敵の回転
		float m_rotAngle[TotalEneNum] = { nsStdafx::FLOAT_ZERO };			//敵６体分の回転角度
		Vector3 m_eneDir[TotalEneNum];			//向き
		float m_randEneResAngle[TotalResRot] = { nsStdafx::FLOAT_ZERO };		//敵のリスポーン回転角度4か所

	public:
		//敵の回転処理関数
		void EneTurn(const int eneNum);
		//リスポーン時の向きをランダムにする処理
		void EneRespornAngleDecide(const int eneNum);
		Quaternion GetEneRot(const int eneNum)const { return m_rot[eneNum]; }
		Vector3 GetEneDir(const int eneNum)const { return m_eneDir[eneNum]; }
	};
}