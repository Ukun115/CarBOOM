///<<summary>
///�G�̈ړ��x�N�g������������(�f�o�b�N�p)
///</summary>


#pragma once


namespace nsCARBOOM
{
	class Enemy;

	class EnemyMoveSpeedArrow : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		enum enEneNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		Enemy* m_enemy = nullptr;
		SkinModelRender* m_skinModelRenderArrow[TotalEneNum] = { nullptr };


		Vector3 m_arrowPos[TotalEneNum];
		Quaternion m_arrowRot[TotalEneNum];
		Vector3 m_arrowSize[TotalEneNum];

		~EnemyMoveSpeedArrow()override final;

	public:
		bool Start()override final;
		void Update()override final;
	};
}

