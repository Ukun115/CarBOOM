///<<summary>
///敵の移動ベクトルを可視化処理(デバック用)
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Enemy;
	class EnemyMoveSpeed;

	class EnemyMoveSpeedArrow : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enEneNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		Enemy* m_enemy = nullptr;
		EnemyMoveSpeed* m_enemyMoveSpeed = nullptr;
		SkinModelRender* m_skinModelRenderArrow[TotalEneNum] = { nullptr };

		Vector3 m_arrowPos[TotalEneNum];
		Quaternion m_arrowRot[TotalEneNum];
		Vector3 m_arrowSize[TotalEneNum];

		bool Start()override final;
		void Update()override final;
		~EnemyMoveSpeedArrow()override final;

	public:

	};
}