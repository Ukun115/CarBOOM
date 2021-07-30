#pragma once


namespace nsCARBOOM
{
	class GameScene;
	class TitleScene;
	class StageSelectScene;
	class Player;
	class Enemy;


	class Stage : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		//ステージ番号
		enum enStageNum
		{
			ehehe,	//Stage1を１番にするためにeheheを入れて調整
			Stage1,
			Stage2,
			Stage3,
			Stage4,
			Stage5
		};

		enum enWindDirection
		{
			UpWind,		//上方向の風
			DownWind,	//下方向の風
			LeftWind,	//左方向の風
			RightWind,	//右方向の風
		};


		/// <summary>
		/// クラスのポインタ
		/// </summary>
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		Enemy* m_enemy = nullptr;
		SkinModelRender* m_stage = nullptr;


		PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクトクラスを作成
		Effect m_fallSnowEffect[2];		//アイスステージの降ってくる雪エフェクト


		bool m_isPauseFlg = false;
		bool m_eneFrictionFlg[6] = { false };
		bool m_plaFrictionFlg[4];


		/// <summary>
		/// タイマー
		/// </summary>
		int m_fallSnowTimer = nsStdafx::INT_ZERO;
		int m_windDirection = nsStdafx::INT_ZERO;	//現在の風


		Vector3 m_plaPos[4];			//プレイヤー4体分のプレイヤーの位置
		Vector3 m_LengthFromStaPivToPla[4];	//ステージの基点からプレイヤーまでの距離

		int m_stageSelectNum = nsStdafx::INT_ZERO;
		int m_nowTime = nsStdafx::INT_ZERO;
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		char m_stageModelFilePath[256];


		bool Start() override final;
		~Stage()override final;
		void Update() override final;


		//雪エフェクト処理関数
		void SnowFall();
		//風の影響を与える処理
		void WindInpact();
		//傾かせる処理
		void Tilt();

	public:
		int GetWindDirection()const { return m_windDirection; }

		void SetNowTime(const int nowTime) { m_nowTime = nowTime; }
		void SetSelectStageNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }
	};
}