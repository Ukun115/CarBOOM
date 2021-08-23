///<<summary>
///タイトル画面のメイン処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class StageSelectScene;
	class Fade;
	class TitleName;
	class PressStartButton;
	class PressASpeechBalloon;
	class PlayerName;

	class TitleScene : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		enum enPlayer
		{
			Player1,		//1Pの配列での番号
			Player2,		//2Pの配列での番号
			Player3,		//3Pの配列での番号
			Player4,		//4Pの配列での番号
			TotalPlaNum	//プレイヤーの最大数
		};

		enum enSoundNum
		{
			TitleSceneGingle,	//タイトルジングル
			TitleSceneBGM,		//タイトルシーンのBGM
			DecideSound,		//決定音
			EngineSound,		//エンジンサウンド
			TotalSoundNum
		};

		enum enFadeState
		{
			StateIn,	//フェードイン
			StateOut,	//フェードアウト
			StateWait,	//待機
		};
		enum enFadeNum
		{
			FadeIn,
			FadeOut,
			TotalFadeNum
		};

		enum enNextScene
		{
			StateSelectScene,
			GameEnd
		};

		/// <summary>
		/// クラスのポインタ
		/// </summary>
		Fade* m_fade[TotalFadeNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		TitleName* m_titleName = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		PressStartButton* m_pressStartButton = nullptr;
		PressASpeechBalloon* m_pressASpeechBalloon = nullptr;
		PlayerName* m_playerName = nullptr;

		/// <summary>
		/// フラグ
		/// </summary>
		bool m_enableUpdateFlg = true;			//trueのときはゲームスタートボタンを押せる

		unsigned int m_totalPlaNum = Player2;			//プレイヤーの合計数を計測
		int m_nextScene = nsStdafx::INT_ZERO;

		bool Start()override final;
		~TitleScene()override final;
		void Update()override final;

		//プレイヤーを追加する関数
		void AddPlayer();
		//ゲーム画面に遷移する関数
		void StageSelectSceneTransition();
		//スタートボタンが押されたときの処理関数
		void PushStartButton(int plaNum);
		//ボタンが押されたときの処理関数
		void PushSelectButton(int plaNum);
		//選択された次のシーンに行く処理関数
		void NextScene();

	public:

	};
}