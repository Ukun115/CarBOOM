///<<summary>
///プレイヤーのメイン処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Stage;
	class Enemy;
	class PlayerMoveSpeedArrow;
	class PlayerTurn;
	class PlayerChargeUI;
	class PlayerEffect;

	class Player : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
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
			TotalPlayerNum	//プレイヤーの最大数
		};

		enum enEnemy
		{
			Enemy1,
			TotalEnemyNum = 6
		};

		enum enSoundNum
		{
			ShootDownSound,
			CarHornSound,
			FallSound,
			ChargeSound,
			Dash1Sound,
			Dash2Sound,
			PlaAndPlaClashSound,
			PlaAndEneClashSound,
			ChargeEnd,
			TotalSoundNum
		};

		/// <summary>
		/// クラスのポインタ
		/// </summary>
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Stage* m_stage = nullptr;
		Enemy* m_enemy = nullptr;
		SkinModelRender* m_player[TotalPlayerNum] = { nullptr };		//プレイヤー4人分
		SpriteRender* m_crown = nullptr;		//プレイヤーの上に置く王冠画像
		SoundPlayBack* m_soundPlayBack = nullptr;
		PlayerMoveSpeedArrow* m_playerMoveSpeedArrow = nullptr;
		PlayerTurn* m_playerTurn = nullptr;
		PlayerChargeUI* m_playerChargeUI = nullptr;
		PlayerEffect* m_playerEffect = nullptr;

		CharacterController m_charaCon[TotalPlayerNum];		//プレイヤー4人分のキャラクタコントローラークラスを作成

		/// <summary>
		/// フラグ
		/// </summary>
		bool m_isCharge1Flg[TotalPlayerNum] = { false };
		bool m_isCharge2Flg[TotalPlayerNum] = { false };
		bool m_isCharge1HanteiFlg[TotalPlayerNum] = { false };
		bool m_isCharge2HanteiFlg[TotalPlayerNum] = { false };
		bool m_isBPushFlg[TotalPlayerNum] = { false };		//Bボタンが押されたときのフラグ
		bool m_isAttack0Flg[TotalPlayerNum] = { false };		//Bボタンが押されたときのフラグ
		bool m_isAttack1Flg[TotalPlayerNum] = { false };		//Bボタンが押されたときのフラグ
		bool m_isAttack2Flg[TotalPlayerNum] = { false };		//Bボタンが押されたときのフラグ
		bool m_isAttack1HanteiFlg[TotalPlayerNum] = { false };		//攻撃1の判定フラグ
		bool m_isAttack2HanteiFlg[TotalPlayerNum] = { false };		//攻撃2の判定フラグ
		bool m_isCharge1EffectSoundFlg[TotalPlayerNum] = { false };
		bool m_isCharge2EffectSoundFlg[TotalPlayerNum] = { false };
		bool m_isFallSoundFlg[TotalPlayerNum] = { false };			//落下音を落下中何回もならないようにするフラグ

		bool m_plaTourokuFlg[TotalPlayerNum] = { false };
		bool m_isPauseFlg = false;

		/// <summary>
		/// タイマー
		/// </summary>
		unsigned int m_chargeTimer[TotalPlayerNum] = { 0 };		//押したときのタイマー
		unsigned int m_releaseTimer[TotalPlayerNum] = { 0 };		//離したときのタイマー
		unsigned int m_attackTimer[TotalPlayerNum] = { 0 };			//攻撃のタイマー
		unsigned int m_attackHanteiTimer[TotalPlayerNum] = { 0 };			//攻撃判定のタイマー

		Vector3    m_fallSpeed[TotalPlayerNum];	//プレイヤーの落下速度。
		Vector3    m_pos[TotalPlayerNum];		//プレイヤーの位置
		Vector3 m_moveSpeed[TotalPlayerNum];		//移動速度
		Vector3 m_enePushSpeed;		//敵から与えられるプッシュパワー
		Vector3 m_plaDir[TotalPlayerNum];		//向き
		Vector3 m_friction[TotalPlayerNum];		//摩擦
		Vector3 m_diff;				//プレイヤーと敵との距離
		unsigned int m_pushPlayer[5] = { 0 };
		Quaternion m_shootDownEffectRot;
		Vector2 m_plaScreenPos[TotalPlayerNum];
		Vector3 m_crownPos;

		char m_filePath[256];

		int m_totalPlaNum = 0;
		int m_stageSelectNum = 0;

		bool Start() override final;
		~Player() override final;
		void Update() override final;

		//プレイヤーのリスポーン処理関数
		void PlaResporn(const int plaNum);
		//落ちたプレイヤーの初期位置をセットさせる関数
		void PlaResPos(const int plaNum);
		//プレイヤーの位置,回転の情報を更新する関数
		void PlaDataUpdate(const int plaNum);
		//プレイヤーの通常移動処理関数
		void PlaMove(const int plaNum);
		//プレイヤーの移動速度に補正を入れる関数
		void PlaSpeedCorrection(const int plaNum);
		//プレイヤーのDA(ダッシュアタック)処理関数
		void PlaAttackBefore(const int plaNum);
		//プレイヤーの現在の状態を伝える関数
		void PlaNowState(const int plaNum);
		//プレイヤーと敵がぶつかったときの処理関数
		void PlaAndEneClash(const int plaNum);
		//プレイヤーとプレイヤーがぶつかったときの処理関数
		void PlaAndPlaClash(const int plaNum);
		//プレイヤーにかかる重力を設定する関数
		void Gravity(const int plaNum)
		{
			m_moveSpeed[plaNum].y -= nsStdafx::GRAVITY;
		}
		//落下時サウンドを鳴らす関数
		void FallSoundPlayBack(const int plaNum);

		//摩擦
		void Friction(const int plaNum);

	public:
		//プレイヤーの人数を取得する関数
		int GetPlaNum()const { return m_totalPlaNum; }

		Vector2 GetPlaScreenPos(const int plaNum)const { return m_plaScreenPos[plaNum]; }

		//プレイヤーの位置を取得する関数
		const Vector3& GetPlaPos(const int plaNum)const { return  m_pos[plaNum]; }

		/// @brief
		/// @param plaNum
		/// @return
		const Vector3& GetPlaSpeed(const int plaNum)const { return m_moveSpeed[plaNum]; }
		const float& GetPlaSpeedX(const int plaNum)const { return m_moveSpeed[plaNum].x; }
		const float& GetPlaSpeedZ(const int plaNum)const { return m_moveSpeed[plaNum].z; }
		//プレイヤーの向きを取得する関数
		Vector3 GetPlaDir(const int plaNum)const { return m_plaDir[plaNum]; }
		//プレイヤーのチャージを取得する関数
		bool GetPlaisTyazi1HanteiFlg(const int plaNum)const { return m_isCharge1HanteiFlg[plaNum]; }
		bool GetPlaisTyazi2HanteiFlg(const int plaNum)const { return m_isCharge2HanteiFlg[plaNum]; }

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetStageSelectNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }

		void AddWindPowerX(const int plaNum, const float windSpeed) { m_moveSpeed[plaNum].x += windSpeed; }
		void AddWindPowerZ(const int plaNum, const float windSpeed) { m_moveSpeed[plaNum].z += windSpeed; }
	};
}