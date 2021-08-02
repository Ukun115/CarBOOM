///<<summary>
///サウンドデータ再生クラス
///</summary>


#pragma once


namespace nsCARBOOM
{
	class SoundPlayBack :public IGameObject	//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		enum enTitleSceneSoundNum
		{
			TitleSceneGingle,	//タイトルジングル
			TitleSceneBGM,		//タイトルシーンのBGM
			TitleSceneDecideSound,		//決定音
			EngineSound,		//エンジンサウンド
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
			GameStartGingle,	//ゲームスタートジングル
			CountDownSound,		//カウントダウンサウンド
			GameSceneGameBGM,			//ゲーム内BGM
			WhistleSound,		//ホイッスルサウンド
			PauseSound,			//ポーズサウンド
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

		//音再生関数
		void TitleSceneSoundPlayBack(const int soundNum);
		void StageSelectSceneSoundPlayBack(const int soundNum);
		void GameSceneSoundPlayBack(const int soundNum);
		void PlayerSoundPlayBack(const int soundNum, const int plaNum);
		void EnemySoundPlayBack(const int soundNum, const int eneNum);
		void ResultSceneSoundPlayBack(const int soundNum);
		//削除関数
		void TitleSceneDeleteGO()const;
		void StageSelectSceneDeleteGO()const;
		void GameSceneDeleteGO()const;
		void PlayerDeleteGO()const;
		void EnemyDeleteGO()const;
		void ResultSceneDeleteGO()const;
	};
}