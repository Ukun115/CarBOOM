///<<summary>
///�G�̃G�t�F�N�g����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Enemy;

	class EnemyEffect : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enEnemy
		{
			Enemy1,		 //�G�P�̔z��ł̔ԍ�
			Enemy2,		 //�G�Q�̔z��ł̔ԍ�
			Enemy3,		 //�G�R�̔z��ł̔ԍ�
			Enemy4,		 //�G�S�̔z��ł̔ԍ�
			Enemy5,		 //�G�T�̔z��ł̔ԍ�
			Enemy6,		 //�G�U�̔z��ł̔ԍ�
			TotalEnemyNum	 //�G�̑���
		};

		Effect m_shootDownEffect[TotalEnemyNum];		//���������Ƃ��̌��ăG�t�F�N�g
		Vector3 m_enePos[TotalEnemyNum];

		bool Start()override final;
		~EnemyEffect()override final;
		void Update()override final;

	public:
		void ShootDownEffectPlay(int eneNum);

		void SetEnemyPos(const Vector3 enePos,const int eneNum) { m_enePos[eneNum] = enePos; }
	};
}