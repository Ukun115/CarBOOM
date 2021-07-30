#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Player;


	class Enemy : public IGameObject	//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		enum enEnemy
		{
			Enemy1,		 //敵１の配列での番号
			Enemy2,		 //敵２の配列での番号
			Enemy3,		 //敵３の配列での番号
			Enemy4,		 //敵４の配列での番号
			Enemy5,		 //敵５の配列での番号
			Enemy6,		 //敵６の配列での番号
			TotalEnemyNum	 //敵の総数
		};
		enum enPlayer
		{
			Player1,		//1Pの配列での番号
			Player2,		//2Pの配列での番号
			Player3,		//3Pの配列での番号
			Player4,		//4Pの配列での番号
			TotalPlayerNum	//プレイヤーの最大数
		};
		//敵のランダムリスポーン位置
		enum enRanEneResPos
		{
			ResPos1,	//１つ目
			ResPos2,	//２つ目
			ResPos3,	//３つ目
			ResPos4,	//４つ目
			ResPos5,	//５つ目
			ResPos6,	//６つ目
			ResPos7,	//７つ目
			ResPos8,	//８つ目
			ResPos9,	//９つ目
			ResPos10,	//１０つ目
			TotalResPos
		};

		enum enSoundNum
		{
			ShootDownSound,
			FallSound,
			DashSound,
			PlaAndEneClashSound,
			TotalSoundNum
		};


		/// <summary>
		/// クラスのポインタ
		/// </summary>
		Light* m_light = nullptr;
		GameScene* m_gameScene = nullptr;
		SkinModelRender* m_enemy[TotalEnemyNum] = { nullptr };
		Stage* m_stage = nullptr;
		Player* m_player = nullptr;
		SoundPlayBack* m_soundPlayBack = nullptr;


		CharacterController m_charaCon[TotalEnemyNum];		//敵６体分のキャラクタコントローラークラスを作成
		Effect m_shootDownEffect[TotalEnemyNum];		//落下したときの撃墜エフェクト


		/// <summary>
		/// フラグ
		/// </summary>
		bool m_canCtCountFlg[TotalEnemyNum] = { false };		//敵６体分のCTのフラグ
		bool m_canFallSoundPlayFlg[TotalEnemyNum] = { false };			//落下音を落下中何回もならないようにするフラグ
		bool m_canPlaAndEneClashSoundPlayFlg[TotalEnemyNum] = { false };
		bool m_isPauseFlg = false;

		/// <summary>
		/// タイマー
		/// </summary>
		unsigned int m_startDelayTimer = nsStdafx::INT_ZERO;		//スタートを遅らせるタイマー
		unsigned int m_startDelay[TotalEnemyNum] = { nsStdafx::INT_ZERO };			//敵６体分のスタート遅延時間
		unsigned int m_CTTime[TotalEnemyNum] = { nsStdafx::INT_ZERO };					//敵６体分の攻撃CTタイマー
		unsigned int m_eneCTCount[TotalEnemyNum] = { nsStdafx::INT_ZERO };			//敵６体分のCT時間


		//敵情報
		Vector3    m_enePos[TotalEnemyNum];			//敵６体分の敵の位置
		Quaternion m_rot[TotalEnemyNum];			//敵６体分の敵の回転
		float m_rotAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };			//敵６体分の回転角度
		Vector3 m_moveSpeed[TotalEnemyNum];			//敵６体分の移動速度
		Vector3 m_samDir[TotalEnemyNum];			//敵とプレイヤーの向き
		Vector3 m_friction[TotalEnemyNum];			//敵６体分の摩擦
		Vector3    m_plaPos[TotalPlayerNum];			//プレイヤー4体分のプレイヤーの位置
		Vector3    m_mostShortDistance[TotalPlayerNum];	//プレイヤー4体分と敵の距離
		//↓特に途中で変更しない値なので、const使いたい。
		Vector3 m_ranEneResPos[TotalResPos];		//敵のリスポーン位置計10か所

		float m_randEneResAngle[8] = { nsStdafx::FLOAT_ZERO };		//敵のリスポーン回転角度4か所
		Vector3 m_eneDir[TotalPlayerNum];			//向き
		Vector3 m_diff;				//プレイヤーと敵との距離
		unsigned int m_pushPlayer[TotalEnemyNum] = { nsStdafx::INT_ZERO };
		unsigned int m_randomDashSoundNum = nsStdafx::INT_ZERO;
		Vector3 m_mostShortDistanceDir[TotalPlayerNum]; //プレイヤー4体分から敵の向き
		Vector3 m_settenPos1[TotalEnemyNum];		 //敵と円の接点1の座標
		Vector3 m_settenPos2[TotalEnemyNum];		 //敵と円の接点2の座標
		Vector3 m_EneToSetten1[TotalEnemyNum];		 //敵から接点1の距離
		Vector3 m_EneToSetten2[TotalEnemyNum];		 //敵から接点2の距離
		Vector3 m_EneToSetten1Dir[TotalEnemyNum];    //敵から接点1の向き
		Vector3 m_EneToSetten2Dir[TotalEnemyNum];	 //敵から接点2の向き
		Vector3 m_centerKyori[TotalEnemyNum];		 //敵から中心の距離
		float m_CenterToEneAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };		//中心から敵のcos
		float m_CenterToSettenAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };		//中心から接点のcos
		float m_PlayerToSetten1Angle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };	//プレイヤーから接点1のcos
		float m_PlayerToSetten2Angle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };	//プレイヤーから接点2のcos
		int m_hankei = 3600;       //穴の半径の2乗
		Vector3 m_center;  //中心の座標
		Vector3 m_enePoiLigPos;
		int	m_poiLigNum = nsStdafx::INT_ZERO;
		int m_windDirection = nsStdafx::INT_ZERO;	//現在の風
		int m_totalPlaNum = nsStdafx::INT_ZERO;
		int m_stageSelectNum = nsStdafx::INT_ZERO;


		//デバッグ用矢印
		SkinModelRender* m_skinModelRenderArrow[TotalEnemyNum] = { nullptr };
		Vector3 m_arrowPos[TotalEnemyNum];
		Quaternion m_arrowRot[TotalEnemyNum];
		Vector3 m_arrowSize;


		bool Start()override final;
		~Enemy()override final;
		void Update()override final;


		//敵の位置,回転を更新する関数
		void EneDataUpdate(const int eneNum) const;
		//敵のDA処理関数
		void EneDA(const int eneNum);
		//敵の回転処理関数
		void EneTurn(const int eneNum);
		//敵から最寄りのプレイヤーを検索する関数
		void Distance(const int eneNum);
		//敵のリスポーン処理関数
		void EneResporn(const int eneNum);
		//敵の摩擦処理関数
		void EneFriction(const int eneNum);
		//プレイヤーと敵がぶつかったときの処理関数
		void PlaAndEneClash(const int eneNum);
		//敵にかかる重力を設定する関数
		void Gravity(const int eneNum)
		{
			m_moveSpeed[eneNum].y -= nsStdafx::GRAVITY;
		}
		//敵のスピードベクトルを可視化させるデバック関数
		void EneMooveSpeedDebug(const int eneNum);
		//プレイヤーと敵との距離を測り一番近いプレイヤーを算出する関数
		void DistanceOfPlaToEne(const int eneNum);
		//落下時サウンドを鳴らす関数
		void FallSoundPlayBack(const int eneNum);
		//パトランプをパトカーの上にセットする関数
		void PointLightSetting(const int eneNum);
		//
		int WhatEneRandomResRot(const int eneNum);
		//
		Vector3 WhatEneRandomResPos(const int eneNum);

	public:

		/// <summary>
		/// ゲッター
		/// </summary>
		//敵の位置を取得する関数
		Vector3 GetEnemyPos(const int eneNum)const { return m_enePos[eneNum]; }
		//敵の速度を取得する関数
		Vector3 GetEnemySpeed(const int eneNum)const { return m_moveSpeed[eneNum]; }
		/// <summary>
		/// セッター
		/// </summary>
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetStageSelectNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }

		void AddWindPowerX(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].x += windSpeed; }
		void AddWindPowerZ(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].z += windSpeed; }
	};
}