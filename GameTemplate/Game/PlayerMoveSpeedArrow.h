///<<summary>
///プレイヤーの移動ベクトルを可視化処理(デバック用)
///</summary>


#pragma once

namespace nsCARBOOM
{
	class Player;


	class PlayerMoveSpeedArrow : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		enum enPlaNum
		{
			Player1,
			TotalPlaNum = 4
		};

		Player* m_player = nullptr;
		SkinModelRender* m_skinModelRenderArrow[TotalPlaNum] = { nullptr };


		Vector3 m_arrowPos[TotalPlaNum];
		Quaternion m_arrowRot[TotalPlaNum];
		Vector3 m_arrowSize[TotalPlaNum];
		int m_totalPlaNum = 0;

	public:
		bool Start()override final;
		~PlayerMoveSpeedArrow()override final;
		void Update()override final;

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}