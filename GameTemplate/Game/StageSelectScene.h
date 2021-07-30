#pragma once


namespace nsCARBOOM
{
	class TitleScene;
	class GameScene;
	class Fade;


	class StageSelectScene : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		//ステージ番号
		enum enStageNum
		{
			ehehe,	//Stage1を１番にするためにeheheを入れて調整
			FlatStage,
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
		SkinModelRender* m_pla = nullptr;	//プレイヤー
		SpriteRender* m_stageName[TotalStageNum] = { nullptr };
		SpriteRender* m_stageDiscription[TotalStageNum] = { nullptr };	//説明背景画像
		SpriteRender* m_operatorDiscription[TotalStageNum] = { nullptr };	//操作説明文画像
		SpriteRender* m_stageSelectSprite = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		SpriteRender* m_Ahukidasi[TotalStageNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;


		/// <summary>
		/// フラグ
		/// </summary>
		bool m_enableUpdateFlg = true;
		bool m_canOnStageSoundPlayFlg[4] = { false };
		bool m_isOperatorFlg[TotalStageNum] = { false };
		int m_nextTitleSceneFlg = nsStdafx::INT_ZERO;

		int m_stageNum = { nsStdafx::INT_ZERO };				//どのステージを選択しているかを格納
		Vector3    m_pos;				//プレイヤーの位置
		Quaternion m_rot;				//プレイヤーの回転
		Vector3 m_moveSpeed;			//移動速度
		float m_leftStick_x = { nsStdafx::FLOAT_ZERO };			//左スティックのx入力量
		float m_leftStick_y = { nsStdafx::FLOAT_ZERO };			//左スティックのy入力量
		float m_rotAngle = { nsStdafx::FLOAT_ZERO };				//回転角度
		Vector3 m_friction;				//摩擦
		Vector3 m_diff[4];		//ステージとプレイヤーとの距離
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector3 m_stageDiscriptionLetterPos = { -370.0f,-20.0f,0.0f };

		//デバッグ用
		SkinModelRender* m_skinModelRenderArrow = nullptr;
		Vector3 m_arrowPos;
		Quaternion m_arrowRot;
		Vector3 m_arrowSize;

		char m_filePath[256];


		bool Start()override final;
		~StageSelectScene()override final;
		void Update()override final;


		//ゲーム画面遷移処理関数
		void GameSceneTransition();
		//プレイヤーの通常移動処理関数
		void PlaMove();
		//プレイヤーの移動速度に補正を入れる関数
		void PlaSpeedCorrection();
		//プレイヤーの回転処理関数
		void PlaTurn();
		//プレイヤーの位置,回転の情報を更新する関数
		void PlaDataUpdate()
		{
			//位置をセット
			m_pla->SetPosition(m_pos);
			//回転をセット
			m_pla->SetRotation(m_rot);
		}
		//ステージの上にいるときそのステージを選択できる関数
		void TouchStage();
		//プレイヤーが画面外に行かないようにする関数
		void AvoidScreenOutSide();
		//ベクトルを可視化させるデバック関数
		void PlaMooveSpeedDebug();
		//クラクションを鳴らす関数
		void CarHorn();
		//プレイヤー操作をまとめている関数
		void PlayerInformation();
		//
		Vector3 WhatStageModelPos(const int stageNum);
		//
		Vector3 WhatStageNamePos(int stageNum);
		//
		Vector3 WhatFukidasiPos(int stageNum);


	public:

		/// <summary>
		/// セッター
		/// </summary>
		//タイトルシーンで何人プレイヤーが追加されたかを持ってくる
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}