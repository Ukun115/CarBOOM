///<<summary>
///ポーズ機能処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;
	class Player;
	class Enemy;
	class Stage;
	class SoundPlayBack;
	class EnemyPatoLump;

	class Pause : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		enum enPlayer
		{
			Player1,		//1Pの配列での番号
		};

		enum enSoundNum
		{
			GameStartGingle,	//ゲームスタートジングル
			CountDownSound,		//カウントダウンサウンド
			GameBGM,			//ゲーム内BGM
			WhistleSound,		//ホイッスルサウンド
			PauseSound,			//ポーズサウンド
			DecideSound,
			TotalSoundNum
		};

		SpriteRender* m_pauseSprite = nullptr;
		SpriteRender* m_grayBack = nullptr;
		SoundPlayBack* m_soundPlayBack = nullptr;
		EnemyPatoLump* m_enemyPatoLump = nullptr;

		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		Enemy* m_enemy = nullptr;
		Stage* m_stage = nullptr;

		bool m_isPauseFlg = false;

		bool Start() override final;
		~Pause()override final;
		void Update() override final;

	public:
		void GrayBackActive();
	};
}