///<<summary>
///ステージ選択画面のメイン処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class GameScene;
	class Fade;
	class StageSelectScenePlayer;

	class StageSelectScene : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		//ステージ番号
		enum enStageNum
		{
			FlatStage = 1,
			DonutStage,
			IceStage,
			WindStage,
			TiltStage,
			RandomStage,
			TotalStageNum
		};

		enum enSoundNum
		{
			TitleSceneBGM,
			DecideSound,
			OnStageSound,
			CarHornSound,
			TotalSoundNum
		};

		//列挙型
		enum enFadeState
		{
			StateIn,	//フェードイン
			StateOut,	//フェードアウト
			StateWait,	//待機
		};
		enum enFadeNum
		{
			FadeIn,
			FadeOutBadk,
			FadeOutNext,
			TotalFadeNum
		};

		Light* m_light = nullptr;
		Fade* m_fade[TotalFadeNum] = { nullptr };
		TitleScene* m_titleScene = nullptr;
		GameScene* m_gameScene = nullptr;
		SkinModelRender* m_stage[TotalStageNum] = { nullptr };
		SpriteRender* m_stageName[TotalStageNum] = { nullptr };
		SpriteRender* m_stageDiscription[TotalStageNum] = { nullptr };	//説明背景画像
		SpriteRender* m_operatorDiscription[TotalStageNum] = { nullptr };	//操作説明文画像
		SpriteRender* m_stageSelectSprite = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		SpriteRender* m_Ahukidasi[TotalStageNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;
		StageSelectScenePlayer* m_stageSelectScenePlayer = nullptr;

		/// <summary>
		/// フラグ
		/// </summary>
		bool m_enableUpdateFlg = true;
		bool m_canOnStageSoundPlayFlg[RandomStage] = { false };
		bool m_isOperatorFlg[TotalStageNum] = { false };
		int m_nextTitleSceneFlg = nsStdafx::INT_ZERO;

		int m_stageNum = { nsStdafx::INT_ZERO };				//どのステージを選択しているかを格納
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector3 m_stageDiscriptionLetterPos = { -370.0f,-20.0f,0.0f };

		Vector3 m_diff[TotalStageNum];		//ステージとプレイヤーとの距離

		char m_filePath[256];

		bool Start()override final;
		~StageSelectScene()override final;
		void Update()override final;

		//ゲーム画面遷移処理関数
		void GameSceneTransition();
		//
		Vector3 WhatStageModelPos(const int stageNum);
		//
		Vector3 WhatStageNamePos(int stageNum);
		//
		Vector3 WhatFukidasiPos(int stageNum);
		//ステージの上にいるときそのステージを選択できる関数
		void TouchStage();

	public:
		/// <summary>
		/// セッター
		/// </summary>
		//タイトルシーンで何人プレイヤーが追加されたかを持ってくる
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}