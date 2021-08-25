///<<summary>
///敵のパトランプ処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Light;
	class Enemy;

	class EnemyPatoLump : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enEnemy
		{
			Enemy1,
			TotalEneNum = 6
		};

		Light* m_light = nullptr;
		Enemy* m_enemy = nullptr;

		Vector3 m_enePoiLigPos;
		int	m_poiLigNum = nsStdafx::INT_ZERO;
		bool m_isPauseFlg = false;

		bool Start()override final;
		~EnemyPatoLump()override final;
		void Update()override final;
	public:
		void PoiLigNumInit();
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }
	};
}