///<<summary>
///�T�E���h�f�[�^�Đ��N���X
///</summary>


#pragma once


namespace nsCARBOOM
{
	class SoundPlayBack :public IGameObject	//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		enum enTitleSceneSoundNum
		{
			TitleSceneGingle,	//�^�C�g���W���O��
			TitleSceneBGM,		//�^�C�g���V�[����BGM
			TitleSceneDecideSound,		//���艹
			EngineSound,		//�G���W���T�E���h
			TotalTitleSceneSoundNum
		};

		enum enStageSelectSceneSoundNum
		{
			StageSelectSceneTitleSceneBGM,
			StageSelectSceneDecideSound,
			OnStageSound,
			StageSelectSceneCarHornSound,
			TotalStageSelectSceneSoundNum
		};

		enum enGameSceneSoundNum
		{
			GameStartGingle,	//�Q�[���X�^�[�g�W���O��
			CountDownSound,		//�J�E���g�_�E���T�E���h
			GameSceneGameBGM,			//�Q�[����BGM
			WhistleSound,		//�z�C�b�X���T�E���h
			PauseSound,			//�|�[�Y�T�E���h
			GameSceneDecideSound,
			TotalGameSceneSoundNum
		};

		enum enPlayerSoundNum
		{
			PlaShootDownSound,
			CarHornSound,
			PlaFallSound,
			ChargeSound,
			Dash1Sound,
			Dash2Sound,
			PlaAndPlaClashSound,
			PlaPlaAndEneClashSound,
			ChargeEnd,
			TotalPlayerSoundNum
		};

		enum enEnemySoundNum
		{
			EneShootDownSound,
			EneFallSound,
			DashSound,
			EnePlaAndEneClashSound,
			TotalEnemySoundNum
		};

		enum enResultSceneSoundNum
		{
			ResultGingle,
			ResultSceneGameBGM,
			ResultSceneDecideSound,
			TotalResultSceneSoundNum
		};

		enum enPlayer
		{
			Player1,
			TotalPlayerNum = 4
		};

		enum enEnemy
		{
			Enemy1,
			TotalEnemyNum = 6
		};


		SoundSource* m_enemySound[6][TotalEnemySoundNum] = { nullptr };
		SoundSource* m_titleSceneSound[TotalTitleSceneSoundNum] = { nullptr };
		SoundSource* m_stageSelectSceneSound[TotalStageSelectSceneSoundNum] = { nullptr };
		SoundSource* m_resultSceneSceneSound[TotalResultSceneSoundNum] = { nullptr };


		bool Start()override final;
		~SoundPlayBack()override final;
		void Update()override final;


		unsigned int m_randomDashSoundNum = 0;


	public:
		SoundSource* m_gameSceneSound[TotalGameSceneSoundNum] = { nullptr };
		SoundSource* m_playerSound[4][TotalPlayerSoundNum] = { nullptr };

		//���Đ��֐�
		void TitleSceneSoundPlayBack(const int soundNum);
		void StageSelectSceneSoundPlayBack(const int soundNum);
		void GameSceneSoundPlayBack(const int soundNum);
		void PlayerSoundPlayBack(const int soundNum, const int plaNum);
		void EnemySoundPlayBack(const int soundNum, const int eneNum);
		void ResultSceneSoundPlayBack(const int soundNum);
		//�폜�֐�
		void TitleSceneDeleteGO()const;
		void StageSelectSceneDeleteGO()const;
		void GameSceneDeleteGO()const;
		void PlayerDeleteGO()const;
		void EnemyDeleteGO()const;
		void ResultSceneDeleteGO()const;
	};
}