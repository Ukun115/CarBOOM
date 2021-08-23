///<<summary>
///敵のエフェクト処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Enemy;

	class EnemyEffect : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		enum enEnemy
		{
			Enemy1,		 //敵１の配列での番号
			Enemy2,		 //敵２の配列での番号
			Enemy3,		 //敵３の配列での番号
			Enemy4,		 //敵４の配列での番号
			Enemy5,		 //敵５の配列での番号
			Enemy6,		 //敵６の配列での番号
			TotalEnemyNum	 //敵の総数
		};

		Effect m_shootDownEffect[TotalEnemyNum];		//落下したときの撃墜エフェクト
		Vector3 m_enePos[TotalEnemyNum];

		bool Start()override final;
		~EnemyEffect()override final;
		void Update()override final;

	public:
		void ShootDownEffectPlay(int eneNum);

		void SetEnemyPos(const Vector3 enePos,const int eneNum) { m_enePos[eneNum] = enePos; }
	};
}