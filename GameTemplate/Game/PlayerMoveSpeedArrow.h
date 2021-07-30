#pragma once

namespace nsCARBOOM
{
	class Player;


	class PlayerMoveSpeedArrow : public IGameObject
	{
	private:

		Player* m_player = nullptr;
		SkinModelRender* m_skinModelRenderArrow[4] = { nullptr };


		Vector3 m_arrowPos[4];
		Quaternion m_arrowRot[4];
		Vector3 m_arrowSize[4];
		int m_totalPlaNum = 0;

	public:
		bool Start()override final;
		~PlayerMoveSpeedArrow()override final;
		void Update()override final;

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}