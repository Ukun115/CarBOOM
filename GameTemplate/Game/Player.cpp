///<<summary>
///プレイヤーのメイン処理
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Enemy.h"
#include "Player.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード
#include "PlayerMoveSpeedArrow.h"
#include "PlayerTurn.h"
#include "PlayerChargeUI.h"
#include "PlayerEffect.h"
#include "EnemyMoveSpeed.h"

//TODO: 影を落とせるようにする

namespace nsCARBOOM
{
	namespace nsPlayer
	{
		const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//リスポーン座標(左上)
		const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//リスポーン座標(右上)
		const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//リスポーン座標(左下)
		const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//リスポーン座標(右下)
		const int TIME0 = 0;	//制限時間が0秒
		const float MAX_MOOVESPEED = 5.0f;
		const float MAX_FALL_POSITION = -1000.0f;
	}

	bool Player::Start()
	{
		//インスタンスを探す。
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		m_enemyMoveSpeed = FindGO<EnemyMoveSpeed>(nsStdafx::ENEMYMOVESPEED_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);
		m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);

		m_playerEffect = NewGO<PlayerEffect>(nsStdafx::PRIORITY_0,nullptr);
		m_playerEffect->SetTotalPlaNum(m_totalPlaNum);

		//１位のプレイヤーの上に置く王冠画像
		m_crown = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_crown->Init("crowngold", 30.0f, 30.0f);
		m_crown->Deactivate();

		//プレイヤーの回転処理クラス
		m_playerTurn = NewGO<PlayerTurn>(nsStdafx::PRIORITY_0, nsStdafx::PLAYERTURN_NAME);
		m_playerTurn->SetTotalPlaNum(m_totalPlaNum);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//プレイヤーモデルオブジェクト生成
			m_player[plaNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);

			sprintf(m_filePath, "LowPoly_PlayerCar_%d", plaNum);
			m_player[plaNum]->Init(m_filePath);

			//プレイヤーを初期位置に持っていく。
			PlaResPos(plaNum);

			m_charaCon[plaNum].Init(15.0f, 85.0f, m_pos[plaNum]);
		}
		for (int plaNum = Player1; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//初期値は誰にもポイントが入らない4。
		}
		//デバック用のプレイヤー移動ベクトルの矢印の初期化
		m_playerMoveSpeedArrow = NewGO<PlayerMoveSpeedArrow>(nsStdafx::PRIORITY_0, nullptr);
		m_playerMoveSpeedArrow->SetTotalPlaNum(m_totalPlaNum);

		//プレイヤーチャージUI処理クラス
		m_playerChargeUI = NewGO<PlayerChargeUI>(nsStdafx::PRIORITY_0, nullptr);
		m_playerChargeUI->SetTotalPlaNum(m_totalPlaNum);

		return true;

	}

	Player::~Player()
	{
		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			if (m_player[plaNum] != nullptr)
			{
				//プレイヤーを削除
				DeleteGO(m_player[plaNum]);

			}
		}
		if (m_crown != nullptr)
		{
			DeleteGO(m_crown);
		}
		//プレイヤーの移動ベクトルを削除
		DeleteGO(m_playerMoveSpeedArrow);

		DeleteGO(m_playerChargeUI);
	}

	void Player::Update()
	{
		//ポーズ中
		if (m_isPauseFlg)
		{
			return;
		}
		//制限時間が0秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() == nsPlayer::TIME0)
		{
			return;
		}

		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//Xボタンが押されたとき再生
			if (g_pad[plaNum]->IsTrigger(enButtonX))
			{
				//クラクションを鳴らす
				m_soundPlayBack->PlayerSoundPlayBack(CarHornSound, plaNum);
			}

			//落下時サウンドを鳴らす関数
			FallSoundPlayBack(plaNum);

			//重力の影響を与える
			Gravity(plaNum);

			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (!m_gameScene->GetCountDownFlg())
			{
				//回転処理
				m_playerTurn->Update();
				//プレイヤーの状態
				PlaNowState(plaNum);

				if (m_charaCon[plaNum].IsOnGround()) {

					if (!m_isBPushFlg[plaNum])
					{
						if (m_attackTimer[plaNum] == nsStdafx::INT_ZERO)
						{
							//移動処理
							PlaMove(plaNum);
						}
						if (m_isCharge1Flg[plaNum] && m_isCharge1EffectSoundFlg[plaNum])
						{
							//チャージ１サウンド
							m_soundPlayBack->PlayerSoundPlayBack(Dash2Sound, plaNum);

							//チャージ攻撃1の処理
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 8.0f;

							m_isCharge1EffectSoundFlg[plaNum] = false;
						}
						if (m_isCharge2Flg[plaNum] && m_isCharge2EffectSoundFlg[plaNum])
						{
							//チャージ２サウンド
							m_soundPlayBack->PlayerSoundPlayBack(Dash1Sound, plaNum);

							//ジェットエフェクト再生
							m_playerEffect->JetEffectPlay(plaNum);

							//チャージ攻撃2処理
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 20.0f;

							m_isCharge2EffectSoundFlg[plaNum] = false;
						}

					}
					else
					{
						//攻撃準備処理
						PlaAttackBefore(plaNum);
					}
				}

				//プレイヤーのリスポーン処理
				PlaResporn(plaNum);

				//プレイヤーの移動速度に補正を入れる
				PlaSpeedCorrection(plaNum);

				//プレイヤーが敵とぶつかったとき敵に押される処理
				PlaAndEneClash(plaNum);

				//プレイヤーとプレイヤーがぶつかったときの処理
				PlaAndPlaClash(plaNum);

				bool isHitGround;
				Vector3 hitGroundNormal;
				m_moveSpeed[plaNum] += m_fallSpeed[plaNum];
				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[plaNum] = m_charaCon[plaNum].Execute(
					m_moveSpeed[plaNum],
					1.0f,
					isHitGround,
					hitGroundNormal
				);

				//if (isHitGround) {
				//	//ぶつかった地面の法線が傾いていくほど落下速度を上げる。
				//	Vector3 fallPower = { 0.0f,-10.0f, 0.0f };
				//	Quaternion  qRot;
				//	qRot.SetRotation(g_vec3Up, hitGroundNormal);
				//	Vector3 vFallSpeedX, vFallSpeedZ;
				//	vFallSpeedX = g_vec3AxisX;
				//	vFallSpeedZ = g_vec3AxisZ;
				//	qRot.Apply(vFallSpeedX);
				//	qRot.Apply(vFallSpeedZ);
				//	//落下速度をX軸に射影する
				//	float t = vFallSpeedX.Dot(fallPower);
				//	vFallSpeedX *= t;
				//	//落下速度をZ軸に射影する。
				//	t = vFallSpeedZ.Dot(fallPower);
				//	vFallSpeedZ *= t * 0.1f;

				//	//XZ軸の移動速度が求まったので、二つを合算。
				//	m_fallSpeed[plaNum] = vFallSpeedX + vFallSpeedZ;
				//}
				//else {
				//	//ぶつかっていない
				//	m_fallSpeed[plaNum] = g_vec3Zero;
				//}
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//重力の影響を与える
				Gravity(plaNum);

				bool isHitGround;
				Vector3 hitGroundNormal;
				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[plaNum] = m_charaCon[plaNum].Execute(
					m_moveSpeed[plaNum],
					1.0f,
					isHitGround,
					hitGroundNormal
				);
			}
			//登録されているプレイヤーの情報を更新
			PlaDataUpdate(plaNum);

		}
		//プレイヤー移動ベクトルの矢印を更新
		m_playerMoveSpeedArrow->Update();
	}

	//プレイヤーのリスポーン処理関数
	void Player::PlaResporn(const int plaNum)
	{
		if (m_pos[plaNum].y >= nsPlayer::MAX_FALL_POSITION)
		{
			return;
		}
		//撃墜サウンド
		m_soundPlayBack->PlayerSoundPlayBack(ShootDownSound, plaNum);

		//撃墜エフェクト再生開始。
		m_playerEffect->ShootDownEffectPlay(plaNum);

		//プレイヤーの座標をリスポーン座標にセット
		PlaResPos(plaNum);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[plaNum].SetPosition(m_pos[plaNum]);
		//着地エフェクトを出せるかどうかのフラグを立てる
		m_playerEffect->LandingEffectFlgOn(plaNum);

		//スピードを初期化
		m_moveSpeed[plaNum] = { Vector3::Zero };

		m_isBPushFlg[plaNum] = false;
		m_isCharge1Flg[plaNum] = false;
		m_isCharge2Flg[plaNum] = false;
		m_isAttack0Flg[plaNum] = false;
		m_isAttack1Flg[plaNum] = false;
		m_isAttack2Flg[plaNum] = false;
		m_isAttack1HanteiFlg[plaNum] = false;
		m_isAttack2HanteiFlg[plaNum] = false;

		m_playerChargeUI->ChargeUIDeactive(plaNum);

		m_playerChargeUI->ChargeRotValueInit(plaNum);

		//押したときのタイマー初期化
		m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;
		m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
		m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;

		bool isHitGround;
		Vector3 hitGroundNormal;
		//キャラクターコントローラーを使った移動処理に変更。
		m_pos[plaNum] = m_charaCon[plaNum].Execute(
			m_moveSpeed[plaNum],
			1.0f,
			isHitGround,
			hitGroundNormal
		);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきた敵のナンバー
		m_gameScene->GetPlayerAddScore(m_pushPlayer[plaNum], plaNum);

		for (int plaNum = Player1; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//誰にもポイントが入らない4にする。
		}
		//プレイヤーの着地エフェクトを再生させる関数
		m_playerEffect->LandingEffectPlay(plaNum);
	}

	//落ちたプレイヤーの初期位置をセットさせる関数
	void Player::PlaResPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			m_pos[plaNum] = nsPlayer::PLAYER1_RESPOS;		//リスポーン座標(左上)
			break;
		case Player2:
			m_pos[plaNum] = nsPlayer::PLAYER2_RESPOS;		//リスポーン座標(右上)
			break;
		case Player3:
			m_pos[plaNum] = nsPlayer::PLAYER3_RESPOS;		//リスポーン座標(左下)
			break;
		case Player4:
			m_pos[plaNum] = nsPlayer::PLAYER4_RESPOS;		//リスポーン座標(右下)
			break;
		}

		m_isFallSoundFlg[plaNum] = true;

		//プレイヤーのリスポーン向きを真ん中に向くように調整
		m_playerTurn->PlaResAngle(plaNum);

		//プレイヤーの位置,回転の情報を更新する
		PlaDataUpdate(plaNum);
	}

	//プレイヤーの位置,回転の情報を更新する関数
	void Player::PlaDataUpdate(const int plaNum)
	{
		//位置をセット
		m_player[plaNum]->SetPosition(m_pos[plaNum]);
		//回転をセット
		m_player[plaNum]->SetRotation(m_playerTurn->GetPlaRot(plaNum));

		//プレイヤーのワールド座標をスクリーン座標に変換
		g_camera3D->CalcScreenPositionFromWorldPosition(m_plaScreenPos[plaNum], m_pos[plaNum]);

		//１位のプレイヤーの頭上に王冠画像を置く
		m_crown->Activate();
		m_crownPos.x = m_plaScreenPos[m_gameScene->GetNumber1Player()].x;
		m_crownPos.y = m_plaScreenPos[m_gameScene->GetNumber1Player()].y + 40.0f;
		m_crown->SetPosition(m_crownPos);
	}

	//プレイヤーの現在の状態を伝える関数
	void Player::PlaNowState(const int plaNum)
	{
		//Aボタンが押されてるとき、
		if (g_pad[plaNum]->IsPress(enButtonA))
		{
			if (m_chargeTimer[plaNum] == nsStdafx::INT_ZERO)
			{
				//チャージ音を鳴らす
				m_soundPlayBack->PlayerSoundPlayBack(ChargeSound, plaNum);

				m_playerChargeUI->ChargeUIActive(plaNum);
			}

			m_isBPushFlg[plaNum] = true;

			m_isCharge1EffectSoundFlg[plaNum] = true;
			m_isCharge2EffectSoundFlg[plaNum] = true;

			//チャージしているときのタイマーを加算
			m_chargeTimer[plaNum]++;

			//チャージ時間によって攻撃フラグを変える

			if (m_chargeTimer[plaNum] >= nsStdafx::INT_ZERO && m_chargeTimer[plaNum] < 30)
			{
				m_playerChargeUI->Charge1Move(plaNum);

				m_isAttack0Flg[plaNum] = true;
			}
			if (m_chargeTimer[plaNum] >= 30 && m_chargeTimer[plaNum] < 90)
			{
				m_playerChargeUI->Charge2Move(plaNum);

				m_isAttack0Flg[plaNum] = false;
				m_isAttack1Flg[plaNum] = true;
				m_isAttack1HanteiFlg[plaNum] = true;

				//「1」表示
				if (m_chargeTimer[plaNum] == 30) {

					m_playerChargeUI->SetChargeUI1(plaNum);
				}
			}
			if (m_chargeTimer[plaNum] >= 90)
			{
				m_isAttack1Flg[plaNum] = false;
				m_isAttack1HanteiFlg[plaNum] = false;
				m_isAttack2Flg[plaNum] = true;
				m_isAttack2HanteiFlg[plaNum] = true;

				//「2」表示
				if (m_chargeTimer[plaNum] == 90) {

					m_playerChargeUI->SetChargeUI2(plaNum);

					//チャージ完了サウンド再生
					m_soundPlayBack->PlayerSoundPlayBack(ChargeEnd, plaNum);
				}
			}
		}
		else
		{
			m_isBPushFlg[plaNum] = false;

			//押したときのタイマー初期化
			m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;

			m_playerChargeUI->ChargeUIDeactive(plaNum);

			m_playerChargeUI->ChargeRotValueInit(plaNum);

			//攻撃フラグによって攻撃処理を変える

			//チャージ失敗
			if (m_isAttack0Flg[plaNum])
			{
				m_isAttack0Flg[plaNum] = false;
			}

			//チャージ1
			//攻撃の動きのフラグ
			if (m_isAttack1Flg[plaNum])
			{
				m_attackTimer[plaNum]++;

				if (m_attackTimer[plaNum] > 0 && m_attackTimer[plaNum] < 20)
				{
					m_isCharge1Flg[plaNum] = true;
				}
				if (m_attackTimer[plaNum] == 20)
				{
					m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge1Flg[plaNum] = false;
					m_isAttack1Flg[plaNum] = false;
				}
			}

			//チャージ1
			//攻撃の判定のフラグ
			if (m_isAttack1HanteiFlg[plaNum])
			{
				m_attackHanteiTimer[plaNum]++;

				if (m_attackHanteiTimer[plaNum] > 0 && m_attackHanteiTimer[plaNum] < 25)
				{
					m_isCharge1HanteiFlg[plaNum] = true;
				}
				if (m_attackHanteiTimer[plaNum] == 25)
				{
					m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge1HanteiFlg[plaNum] = false;
					m_isAttack1HanteiFlg[plaNum] = false;
				}
			}

			//チャージ2
			//攻撃の動きのフラグ
			if (m_isAttack2Flg[plaNum])
			{
				m_attackTimer[plaNum]++;

				if (0 < m_attackTimer[plaNum] && m_attackTimer[plaNum] < 25)
				{
					m_isCharge2Flg[plaNum] = true;
				}
				if (m_attackTimer[plaNum] == 25)
				{
					m_attackTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge2Flg[plaNum] = false;
					m_isAttack2Flg[plaNum] = false;
				}
			}

			//チャージ2
			//攻撃の判定のフラグ
			if (m_isAttack2HanteiFlg[plaNum])
			{
				m_attackHanteiTimer[plaNum]++;

				if (m_attackHanteiTimer[plaNum] > 0 && m_attackHanteiTimer[plaNum] < 30)
				{
					m_isCharge2HanteiFlg[plaNum] = true;
				}
				if (m_attackHanteiTimer[plaNum] == 30)
				{
					m_attackHanteiTimer[plaNum] = nsStdafx::INT_ZERO;
					m_isCharge2HanteiFlg[plaNum] = false;
					m_isAttack2HanteiFlg[plaNum] = false;

					m_playerChargeUI->ChargeUIDeactive(plaNum);

					m_playerChargeUI->ChargeRotValueInit(plaNum);
				}
			}
		}
	}

	//プレイヤーの通常移動処理関数
	void Player::PlaMove(const int plaNum)
	{
		//左スティックの入力量を加算する
		m_moveSpeed[plaNum].x += m_playerTurn->GetPlaLeftStickX(plaNum) * 10.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_playerTurn->GetPlaLeftStickY(plaNum) * 10.0f * g_gameTime->GetFrameDeltaTime();

		Friction(plaNum);
	}

	//プレイヤーの移動速度に補正を入れる関数
	void Player::PlaSpeedCorrection(const int plaNum)
	{
		//スピードの補正
		m_moveSpeed[plaNum].x = min(m_moveSpeed[plaNum].x, nsPlayer::MAX_MOOVESPEED);//右方向の最大速度
		m_moveSpeed[plaNum].x = max(m_moveSpeed[plaNum].x, -nsPlayer::MAX_MOOVESPEED);//左方向の最大速度

		m_moveSpeed[plaNum].z = min(m_moveSpeed[plaNum].z, nsPlayer::MAX_MOOVESPEED);//上方向の最大速度
		m_moveSpeed[plaNum].z = max(m_moveSpeed[plaNum].z, -nsPlayer::MAX_MOOVESPEED);//下方向の最大速度
	}

	//プレイヤーのDA(ダッシュアタック)処理関数
	void Player::PlaAttackBefore(const int plaNum)
	{
		m_moveSpeed[plaNum].x += m_playerTurn->GetPlaLeftStickX(plaNum) * 1.5f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_playerTurn->GetPlaLeftStickY(plaNum) * 1.5f * g_gameTime->GetFrameDeltaTime();

		Friction(plaNum);

		m_plaDir[plaNum] = m_moveSpeed[plaNum];
		m_plaDir->Normalize();
	}

	//プレイヤーと敵がぶつかったときの処理関数
	void Player::PlaAndEneClash(const int plaNum)
	{
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//プレイヤーと敵との距離を計算
			m_diff = m_enemy->GetEnemyPos(eneNum) - m_pos[plaNum];

			//距離の長さが30.0fより小さかったら、
			if (m_diff.Length() >= 30.0f)
			{
				return;
			}
			if (m_isCharge1HanteiFlg[plaNum])
			{
				return;
			}
			if (m_isCharge2HanteiFlg[plaNum])
			{
				return;
			}

			m_enePushSpeed = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
			////これだとプッシュパワーが強すぎるため、威力を弱める
			//m_enePushSpeed /= 2;

			//チャージ中に敵と衝突したらチャージがキャンセルされる
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = false;
			m_isAttack2Flg[plaNum] = false;
			//押されたらチャージサウンドを止める
			if (m_chargeTimer[plaNum] > 0)
			{
				m_soundPlayBack->m_playerSound[plaNum][ChargeSound]->Stop();
			}

			m_playerChargeUI->ChargeUIDeactive(plaNum);

			m_playerChargeUI->ChargeRotValueInit(plaNum);

			//押したときのタイマー初期化
			m_chargeTimer[plaNum] = nsStdafx::INT_ZERO;

			//プレイヤーに影響
			m_moveSpeed[plaNum] += m_enePushSpeed;
		}
	}

	//プレイヤーとプレイヤーがぶつかったときの処理関数
	void Player::PlaAndPlaClash(const int plaNum)
	{
		//ほかプレイヤー(u)と自分(i)がぶつかったとき、ほかプレイヤーに押される処理
		for (int otherPlaNum = Player1; otherPlaNum < m_totalPlaNum; otherPlaNum++) {
			if (otherPlaNum == plaNum)
			{
				//uとiの値が同じのときは下の処理は行わずスキップする
				continue;
			}
			//プレイヤー同士の距離を計算
			m_diff = m_pos[otherPlaNum] - m_pos[plaNum];
			//距離の長さが30.0fより小さかったら、
			if (m_diff.Length() >= 40.0f)
			{
				continue;
			}
			//ぶつかってきたプレイヤーの力を保存
			m_enePushSpeed = m_moveSpeed[otherPlaNum];

			//ぶつかってきたプレイヤーはそのままステージ外に落ちないように減速させる
			m_moveSpeed[otherPlaNum] /= 2.0;

			//相手がチャージ1のとき
			if (m_isCharge1HanteiFlg[otherPlaNum] == true && m_isCharge2HanteiFlg[plaNum] == false)
			{
				m_enePushSpeed *= 2.0f;
				//チャージ２を受けたとき割る２しただけではそのまま落ちちゃうので
				//止まるようにする
				m_moveSpeed[otherPlaNum] = Vector3::Zero;
				//自分がチャージ1のとき
				if (m_isCharge1HanteiFlg[plaNum] == true)
				{
					m_isCharge1HanteiFlg[plaNum] = false;
				}
			}

			//相手がチャージ2のとき
			if (m_isCharge2HanteiFlg[otherPlaNum] == true)
			{
				m_enePushSpeed *= 5.0f;
				//チャージ２を受けたとき割る２しただけではそのまま落ちちゃうので
				//止まるようにする
				m_moveSpeed[otherPlaNum] = Vector3::Zero;

				//自分がチャージ1のとき
				if (m_isCharge1HanteiFlg[plaNum] == true)
				{
					m_isCharge1HanteiFlg[plaNum] = false;
				}
				//自分がチャージ2のとき
				if (m_isCharge2HanteiFlg[plaNum] == true)
				{
					m_isCharge2HanteiFlg[plaNum] = false;
				}
			}

			//衝突音
			m_soundPlayBack->PlayerSoundPlayBack(PlaAndPlaClashSound, plaNum);

			//プレイヤーに影響
			m_moveSpeed[plaNum] += m_enePushSpeed;

			//誰が押してきたかを保存
			m_pushPlayer[plaNum] = otherPlaNum;
		}
	}

	//落下時サウンドを鳴らす関数
	void Player::FallSoundPlayBack(const int plaNum)
	{
		//高さが-10以下のとき再生
		if (m_pos[plaNum].y >= -10.0f)
		{
			return;
		}
		if (!m_isFallSoundFlg[plaNum])
		{
			return;
		}
		//落ちるときの落下効果音をならす
		m_soundPlayBack->PlayerSoundPlayBack(FallSound, plaNum);
		m_isFallSoundFlg[plaNum] = false;
	}

	//摩擦
	void Player::Friction(const int plaNum)
	{
		//摩擦力を設定する
		m_friction[plaNum] = m_moveSpeed[plaNum];
		m_friction[plaNum] *= -2.0f;

		///下のifはステージの処理なのでステージクラスに書く。
		//アイスステージが選択されているとき、
		if (m_stageSelectNum == nsStdafx::STAGE3)
		{
			//摩擦を減らす
			m_friction[plaNum] /= 3.0f;
		}

		//摩擦力を加算する
		m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();
	}
}