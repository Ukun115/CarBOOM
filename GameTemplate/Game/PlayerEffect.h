///<<summary>
///�G�̃G�t�F�N�g����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PlayerTurn;
	class Player;

	class PlayerEffect : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
			Player2,		//2P�̔z��ł̔ԍ�
			Player3,		//3P�̔z��ł̔ԍ�
			Player4,		//4P�̔z��ł̔ԍ�
			TotalPlayerNum	//�v���C���[�̍ő吔
		};

		PlayerTurn* m_playerTurn = nullptr;
		Player* m_player = nullptr;

		Effect m_shootDownEffect[TotalPlayerNum];		//�v���C���[4�l���̗��������Ƃ��̌��ăG�t�F�N�g
		Effect m_jetEffect[TotalPlayerNum];		//�v���C���[4�l���̃W�F�b�g�G�t�F�N�g
		Effect m_landingEffect[TotalPlayerNum];		//�v���C���[4�l���̒��n�G�t�F�N�g

		char m_filePath[256];
		int m_totalPlaNum = 0;
		unsigned int m_landingEffectDelayTimer[TotalPlayerNum] = { 0 };			//���n�G�t�F�N�g���v���C���[�����n�����Ƃ��ɍĐ������邽�߂̃^�C�}�[
		bool m_isLandingOKFlg[TotalPlayerNum] = { false };

		bool Start()override final;
		~PlayerEffect()override final;
		void Update()override final;

	public:
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }

		void JetEffectPlay(const int plaNum);
		void ShootDownEffectPlay(const int plaNum);
		void LandingEffectPlay(const int plaNum);

		void LandingEffectFlgOn(const int plaNum);
	};
}