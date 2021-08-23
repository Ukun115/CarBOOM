///<<summary>
///ステージセレクト画面のプレイヤームーブ処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class StageSelectScenePlayer : public IGameObject	//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enSoundNum
		{
			TitleSceneBGM,
			DecideSound,
			OnStageSound,
			CarHornSound,
			TotalSoundNum
		};

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

		SoundPlayBack* m_soundPlayBack = nullptr;
		SkinModelRender* m_player = nullptr;	//プレイヤー
		Vector3    m_pos;				//プレイヤーの位置
		Quaternion m_rot;				//プレイヤーの回転
		Vector3 m_moveSpeed;			//移動速度
		float m_leftStick_x = { nsStdafx::FLOAT_ZERO };			//左スティックのx入力量
		float m_leftStick_y = { nsStdafx::FLOAT_ZERO };			//左スティックのy入力量
		float m_rotAngle = { nsStdafx::FLOAT_ZERO };				//回転角度
		Vector3 m_friction;				//摩擦

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
			m_player->SetPosition(m_pos);
			//回転をセット
			m_player->SetRotation(m_rot);
		}
		//プレイヤーが画面外に行かないようにする関数
		void AvoidScreenOutSide();
		//クラクションを鳴らす関数
		void CarHorn();

		bool Start()override final;
		~StageSelectScenePlayer()override final;
		void Update()override final;

	public:
		//プレイヤーの位置を取得する関数
		Vector3 GetPlayerPos()const { return m_pos; }
	};
}