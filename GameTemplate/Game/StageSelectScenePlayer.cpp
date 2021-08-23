///<<summary>
///ステージセレクト画面のプレイヤームーブ処理
///</summary>

#include "stdafx.h"
#include "StageSelectScenePlayer.h"

namespace nsCARBOOM
{
	namespace nsStageSelectScenePlayer
	{
		const int PLAYER1 = 0;		//プレイヤー１
		const float MAX_MOOVESPEED = 5.0f;
		const float VERTICAL_WIDTH = 230.0f;
		const float BESIDE_WIDTH = 420.0f;
		const float FRICTION_POWER = -2.0f;
	}

	bool StageSelectScenePlayer::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//プレイヤーモデルオブジェクト生成
		//文字画像の上に乗るようにプライオリティーは１つ文字画像よりも高くする
		m_player = NewGO<SkinModelRender>(nsStdafx::PRIORITY_2, nullptr);
		m_player->Init("LowPoly_PlayerCar_0");	//プレイヤー１の車モデル
		//初期位置設定
		m_player->SetPosition(Vector3::Zero);

		return true;
	}

	StageSelectScenePlayer::~StageSelectScenePlayer()
	{
		//プレイヤーを削除。
		DeleteGO(m_player);
	}

	void StageSelectScenePlayer::Update()
	{
		//ベクトルを可視化させるデバック関数
		//PlaMooveSpeedDebug();
		//クラクションを鳴らす関数
		CarHorn();
		//プレイヤーの回転処理
		PlaTurn();
		//プレイヤーの通常移動処理
		PlaMove();
		//プレイヤーの移動速度に補正を入れる
		PlaSpeedCorrection();
		//プレイヤーが画面外に行かないようにする
		AvoidScreenOutSide();
		//プレイヤーの位置,回転の情報を更新する
		PlaDataUpdate();
	}

	//プレイヤーの通常移動処理関数
	void StageSelectScenePlayer::PlaMove()
	{
		//左スティックの入力量を加算する
		m_moveSpeed.x += m_leftStick_x * 10.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_leftStick_y * 10.0f * g_gameTime->GetFrameDeltaTime();
		//摩擦力を設定する
		m_friction = m_moveSpeed;
		m_friction *= nsStageSelectScenePlayer::FRICTION_POWER;
		//摩擦力を加算する
		m_moveSpeed.x += m_friction.x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_friction.z * g_gameTime->GetFrameDeltaTime();

		m_pos += m_moveSpeed;
	}

	//プレイヤーの移動速度に補正を入れる関数
	void StageSelectScenePlayer::PlaSpeedCorrection()
	{
		//スピードの補正
		m_moveSpeed.x = min(m_moveSpeed.x, nsStageSelectScenePlayer::MAX_MOOVESPEED);//右方向の最大速度
		m_moveSpeed.x = max(m_moveSpeed.x, -nsStageSelectScenePlayer::MAX_MOOVESPEED);//左方向の最大速度

		m_moveSpeed.z = min(m_moveSpeed.z, nsStageSelectScenePlayer::MAX_MOOVESPEED);//上方向の最大速度
		m_moveSpeed.z = max(m_moveSpeed.z, -nsStageSelectScenePlayer::MAX_MOOVESPEED);//下方向の最大速度
	}

	//プレイヤーの回転処理関数
	void StageSelectScenePlayer::PlaTurn()
	{
		//左スティックの入力量を受け取る
		m_leftStick_x = g_pad[nsStageSelectScenePlayer::PLAYER1]->GetLStickXF();
		m_leftStick_y = g_pad[nsStageSelectScenePlayer::PLAYER1]->GetLStickYF();
		//移動してないときは回転しない
		if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
			return;
		}
		//回転角度
		m_rotAngle = atan2(m_moveSpeed.x, m_moveSpeed.z);

		m_rot.SetRotation(Vector3::AxisY, m_rotAngle);
	}

	//プレイヤーが画面外に行かないようにする関数
	void StageSelectScenePlayer::AvoidScreenOutSide()
	{
		//右側の補正
		m_pos.x = min(m_pos.x, nsStageSelectScenePlayer::BESIDE_WIDTH);
		//左側の補正
		m_pos.x = max(m_pos.x, -nsStageSelectScenePlayer::BESIDE_WIDTH);
		//上側の補正
		m_pos.z = min(m_pos.z, nsStageSelectScenePlayer::VERTICAL_WIDTH);
		//下側の補正
		m_pos.z = max(m_pos.z, -nsStageSelectScenePlayer::VERTICAL_WIDTH);
	}

	//クラクションを鳴らす関数
	void StageSelectScenePlayer::CarHorn()
	{
		//Xボタンが押されたとき再生
		if (!g_pad[nsStageSelectScenePlayer::PLAYER1]->IsTrigger(enButtonX))
		{
			return;
		}
		//クラクションサウンド
		m_soundPlayBack->StageSelectSceneSoundPlayBack(CarHornSound);
	}
}