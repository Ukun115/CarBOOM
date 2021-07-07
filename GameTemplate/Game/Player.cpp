///<<summary>
///プレイヤーが操作する車の情報をまとめているクラス
///</summary>


#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Enemy.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード


//TODO: 影を落とせるようにする


namespace
{
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f,100.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = { 100.0f,150.0f, 100.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = { 100.0f,150.0f,-100.0f };		//リスポーン座標(右下)

	const int TIME0 = 0;	//制限時間が0秒

	//const float PAI = 3.141592;		//円周率
}


bool Player::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_enemy = FindGO<Enemy>(ENEMY_NAME);
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);

	//各プレイヤーの２段階溜め攻撃の可視化
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		//溜め１段階目の「１」画像オブジェクト生成
		m_DASpr1[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr1[plaNum]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		//非表示
		m_DASpr1[plaNum]->Deactivate();
		//溜め１段階目の「２」画像オブジェクト生成
		m_DASpr2[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr2[plaNum]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr2[plaNum]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		//非表示
		m_DASpr2[plaNum]->Deactivate();
	}
	m_DASpr1[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr1[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr1[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr1[3]->SetPosition({ 500.0f,-150.0f,0.0f });
	m_DASpr2[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr2[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr2[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr2[3]->SetPosition({ 500.0f,-150.0f,0.0f });

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++)
	{
		//登録されていたら実行
		if (m_titleScene->GetPlaFlg(plaNum))
		{
			//プレイヤーモデルオブジェクト生成
			m_player[plaNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//デバック用のプレイヤースピードの矢印表示
			//m_skinModelRenderArrow[plaNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			//追加されたプレイヤーの名前画像の表示と位置決め
			//１P
			if (plaNum == Player1)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player1_ShootDown.efk");
				//ジェットエフェクト
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetRed.efk");
				//着地エフェクト
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingRed.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//2P
			else if (plaNum == Player2)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player2_ShootDown.efk");
				//ジェットエフェクト
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetBlue.efk");
				//着地エフェクト
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingBlue.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//3P
			else if (plaNum == Player3)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player3_ShootDown.efk");
				//ジェットエフェクト
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetYellow.efk");
				//着地エフェクト
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingYellow.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//4P
			else if (plaNum == Player4)
			{
				m_player[plaNum]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/Player4_ShootDown.efk");
				//ジェットエフェクト
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/JetGreen.efk");
				//着地エフェクト
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/LandingGreen.efk");

				//m_skinModelRenderArrow[plaNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//プレイヤーを初期位置に持っていく。
			PlaResPos(plaNum);

			m_charaCon[plaNum].Init(15.0f, 85.0f, m_pos[plaNum]);

			//エフェクトの大きさ調整
			m_shootDownEffect[plaNum].SetScale({ 70.0f,70.0f,70.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			Quaternion m_shootDownEffectRot = m_shootDownEffect[plaNum].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
			m_shootDownEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//エフェクトの大きさ調整
			m_jetEffect[plaNum].SetScale({ 3.0f,3.0f,3.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			m_shootDownEffectRot = m_jetEffect[plaNum].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
			m_jetEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//着地エフェクトの大きさ調整
			m_landingEffect[plaNum].SetScale({ 20.0f,20.0f,20.0f });

			//プレイヤー数を+1
			m_plaNum++;
		}
	}
	for (int plaNum = 0; plaNum < 5; plaNum++)
	{
		m_pushPlayer[plaNum] = 4;	//初期値は誰にもポイントが入らない4。
	}

	//Start関数のreturn文
	return true;
}


Player::~Player()
{
	//登録されているプレイヤー数ループ
	for (int plaNum = Player1; plaNum < m_plaNum; plaNum++)
	{
		//プレイヤーを削除
		DeleteGO(m_player[plaNum]);
	}
	//ため攻撃の際の段階文字表示の削除。
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		DeleteGO(m_DASpr1[plaNum]);
		DeleteGO(m_DASpr2[plaNum]);
	}
}


void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int plaNum = Player1; plaNum < m_plaNum; plaNum++)
	{
		//クラクションを鳴らす
		SoundPlayBack(CarHornSound,plaNum);
		//落ちるときの落下効果音をならす
		SoundPlayBack(FallSound,plaNum);

		//制限時間が0秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() != TIME0) {

			//重力の影響を与える
			Gravity(plaNum);

			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (!m_gameScene->GetCountDownFlg())
			{
				//回転処理
				PlaTurn(plaNum);

				//プレイヤーの状態
				PlaNowState(plaNum);

				//ベクトルを可視化させるデバック関数
				//PlaMooveSpeedDebug(i);

				if (m_charaCon[plaNum].IsOnGround()) {

					if (!m_isBPushFlg[plaNum])
					{
						if (m_attackTimer[plaNum] == 0)
						{
							//移動処理
							PlaMove(plaNum);
						}
						if (m_isCharge1Flg[plaNum])
						{
							if (m_isCharge1EffectSoundFlg[plaNum])
							{
								//チャージ１サウンド
								SoundPlayBack(Dash2Sound, plaNum);

								m_isCharge1EffectSoundFlg[plaNum] = false;
							}

							//チャージ攻撃1の処理
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 8.0f;
						}
						if (m_isCharge2Flg[plaNum])
						{
							if (m_isCharge2EffectSoundFlg[plaNum])
							{
								//チャージ２サウンド
								SoundPlayBack(Dash1Sound,plaNum);

								//ジェットエフェクト再生
								m_jetEffect[plaNum].Play();

								m_isCharge2EffectSoundFlg[plaNum] = false;
							}
							//チャージ攻撃2処理
							m_moveSpeed[plaNum] = m_plaDir[plaNum] * 20.0f;
						}

					}
					if (m_isBPushFlg[plaNum])
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

				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//ベクトルを可視化させるデバック関数
				//PlaMooveSpeedDebug(i);

				//重力の影響を与える
				Gravity(plaNum);

				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);
			}
			//登録されているプレイヤーの情報を更新
			PlaDataUpdate(plaNum);
		}
	}
}


//プレイヤーのリスポーン処理関数
void Player::PlaResporn(int plaNum)
{
	if (m_pos[plaNum].y < -1000.0f)
	{
		//撃墜サウンド
		SoundPlayBack(ShootDownSound,plaNum);

		//撃墜エフェクト再生開始。
		m_shootDownEffect[plaNum].Play();
		//撃墜エフェクトの位置をプレイヤーが落ちた位置に設定
		m_shootDownEffect[plaNum].SetPosition(m_pos[plaNum]);
		//更新
		m_shootDownEffect[plaNum].Update();

		//プレイヤーの座標をリスポーン座標にセット
		PlaResPos(plaNum);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[plaNum].SetPosition(m_pos[plaNum]);
		//着地エフェクトを出せるかどうかのフラグを立てる
		m_isLandingOKFlg[plaNum] = true;

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
		m_DASpr1[plaNum]->Deactivate();
		m_DASpr2[plaNum]->Deactivate();

		//押したときのタイマー初期化
		m_chargeTimer[plaNum] = 0;
		m_attackTimer[plaNum] = 0;
		m_attackHanteiTimer[plaNum] = 0;

		//キャラクターコントローラーを使った移動処理に変更。
		m_pos[plaNum] = m_charaCon[plaNum].Execute(m_moveSpeed[plaNum], 1.0f);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきた敵のナンバー
		m_gameScene->GetPlayerAddScore(m_pushPlayer[plaNum], plaNum);

		for (int plaNum = 0; plaNum < 5; plaNum++)
		{
			m_pushPlayer[plaNum] = 4;	//誰にもポイントが入らない4にする。
		}
	}

	if (m_isLandingOKFlg[plaNum])
	{
		m_landingEffectDelayTimer[plaNum]++;

		if (m_landingEffectDelayTimer[plaNum] == 40)
		{
			//着地エフェクト再生
			m_landingEffect[plaNum].Play();
			//着地エフェクトの位置をプレイヤーが着地した位置に設定
			m_landingEffect[plaNum].SetPosition(m_pos[plaNum]);
			//更新
			m_landingEffect[plaNum].Update();
			//フラグをおる
			m_isLandingOKFlg[plaNum] = false;

			m_landingEffectDelayTimer[plaNum] = 0;
		}
	}
}


//落ちたプレイヤーの初期位置をセットさせる関数
void Player::PlaResPos(int plaNum)
{
	switch (plaNum)
	{
		//1P
	case Player1:
		m_pos[plaNum] = PLAYER1_RESPOS;		//リスポーン座標(左上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[plaNum] = 2.5f;
		break;
		//2P
	case Player2:
		m_pos[plaNum] = PLAYER2_RESPOS;		//リスポーン座標(右上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[plaNum] = 3.7f;
		break;
		//3P
	case Player3:
		m_pos[plaNum] = PLAYER3_RESPOS;		//リスポーン座標(左下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[plaNum] = 1.0f;
		break;
		//4P
	case Player4:
		m_pos[plaNum] = PLAYER4_RESPOS;		//リスポーン座標(右下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[plaNum] = 5.5f;
		break;
	}

	//回転情報をセットする
	m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);

	//プレイヤーの位置,回転の情報を更新する
	PlaDataUpdate(plaNum);
}


//プレイヤーの位置,回転の情報を更新する関数
void Player::PlaDataUpdate(int plaNum)
{
	//位置をセット
	m_player[plaNum]->SetPosition(m_pos[plaNum]);
	//回転をセット
	m_player[plaNum]->SetRotation(m_rot[plaNum]);

	//ブーストエフェクト位置をプレイヤー位置に設定
	m_jetEffect[plaNum].SetPosition(m_pos[plaNum]);
	m_jetEffect[plaNum].SetRotation(m_rot[plaNum]);
	//更新
	m_jetEffect[plaNum].Update();
}


//プレイヤーの現在の状態を伝える関数
void Player::PlaNowState(int plaNum)
{

	//Aボタンが押されてるとき、
	if (g_pad[plaNum]->IsPress(enButtonA))
	{
		if (m_chargeTimer[plaNum] == 0)
		{
			//チャージ音を鳴らす
			SoundPlayBack(ChargeSound,plaNum);
		}

		m_isBPushFlg[plaNum] = true;

		m_isCharge1EffectSoundFlg[plaNum] = true;
		m_isCharge2EffectSoundFlg[plaNum] = true;

		//チャージしているときのタイマーを加算
		m_chargeTimer[plaNum]++;

		//チャージ時間によって攻撃フラグを変える

		if (m_chargeTimer[plaNum] >= 0 && m_chargeTimer[plaNum] < 30)
		{
			m_isAttack0Flg[plaNum] = true;
		}
		if (m_chargeTimer[plaNum] >= 30 && m_chargeTimer[plaNum] < 90)
		{
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = true;
			m_isAttack1HanteiFlg[plaNum] = true;

			//「1」表示
			if (m_chargeTimer[plaNum] == 30) {
				m_DASpr2[plaNum]->Deactivate();
				m_DASpr1[plaNum]->Activate();
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
				m_DASpr1[plaNum]->Deactivate();
				m_DASpr2[plaNum]->Activate();
			}
		}
	}

	//Aボタンが押されてないとき、
	if (!g_pad[plaNum]->IsPress(enButtonA))
	{
		m_isBPushFlg[plaNum] = false;

		//押したときのタイマー初期化
		m_chargeTimer[plaNum] = 0;

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
				m_attackTimer[plaNum] = 0;
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
				m_attackHanteiTimer[plaNum] = 0;
				m_isCharge1HanteiFlg[plaNum] = false;
				m_isAttack1HanteiFlg[plaNum] = false;
				m_DASpr1[plaNum]->Deactivate();
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
				m_attackTimer[plaNum] = 0;
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
				m_attackHanteiTimer[plaNum] = 0;
				m_isCharge2HanteiFlg[plaNum] = false;
				m_isAttack2HanteiFlg[plaNum] = false;
				m_DASpr2[plaNum]->Deactivate();
			}
		}
	}
}


//プレイヤーの通常移動処理関数
void Player::PlaMove(int plaNum)
{
	//左スティックの入力量を加算する
	m_moveSpeed[plaNum].x += m_leftStick_x[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_leftStick_y[plaNum] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[plaNum] = m_moveSpeed[plaNum];
	m_friction[plaNum] *= -2.0f;

	///下のifはステージの処理なのでステージクラスに書く。
	//アイスステージが選択されているとき、
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//摩擦を減らす
		m_friction[plaNum] /= 3.0f;
	}

	//摩擦力を加算する
	m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーの移動速度に補正を入れる関数
void Player::PlaSpeedCorrection(int plaNum)
{
	//スピードの補正
	m_moveSpeed[plaNum].x = min(m_moveSpeed[plaNum].x, 5.0f);//右方向の最大速度
	m_moveSpeed[plaNum].x = max(m_moveSpeed[plaNum].x, -5.0f);//左方向の最大速度

	m_moveSpeed[plaNum].z = min(m_moveSpeed[plaNum].z, 5.0f);//上方向の最大速度
	m_moveSpeed[plaNum].z = max(m_moveSpeed[plaNum].z, -5.0f);//下方向の最大速度
}


//プレイヤーの回転処理関数
void Player::PlaTurn(int plaNum)
{
	//左スティックの入力量を受け取る
	m_leftStick_x[plaNum] = g_pad[plaNum]->GetLStickXF();
	m_leftStick_y[plaNum] = g_pad[plaNum]->GetLStickYF();

	//移動してないときは回転しない
	if (fabsf(m_moveSpeed[plaNum].x) < 0.001f && fabsf(m_moveSpeed[plaNum].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[plaNum] = atan2(m_moveSpeed[plaNum].x, m_moveSpeed[plaNum].z);

	m_rot[plaNum].SetRotation(Vector3::AxisY, m_rotAngle[plaNum]);
}


//プレイヤーのDA(ダッシュアタック)処理関数
void Player::PlaAttackBefore(int plaNum)
{
	m_moveSpeed[plaNum].x += m_leftStick_x[plaNum] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_leftStick_y[plaNum] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[plaNum] = m_moveSpeed[plaNum];
	m_friction[plaNum] *= -2.0f;

	//摩擦力を加算する
	m_moveSpeed[plaNum].x += m_friction[plaNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[plaNum].z += m_friction[plaNum].z * g_gameTime->GetFrameDeltaTime();

	m_plaDir[plaNum] = m_moveSpeed[plaNum];
	m_plaDir->Normalize();
}


//プレイヤーと敵がぶつかったときの処理関数
void Player::PlaAndEneClash(int plaNum)
{
	for (int eneNum = 0; eneNum < 6; eneNum++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_enemy->GetEnemyPos(eneNum) - m_pos[plaNum];

		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 30.0f && m_isCharge1HanteiFlg[plaNum] == false && m_isCharge2HanteiFlg[plaNum] == false)
		{
			m_enePushSpeed = m_enemy->GetEnemySpeed(eneNum);
			//これだとプッシュパワーが強すぎるため、威力を弱める
			m_enePushSpeed.x /= 5;
			m_enePushSpeed.y /= 5;
			m_enePushSpeed.z /= 5;

			//チャージ中に敵と衝突したらチャージがキャンセルされる
			m_isAttack0Flg[plaNum] = false;
			m_isAttack1Flg[plaNum] = false;
			m_isAttack2Flg[plaNum] = false;
			//押されたらチャージサウンドを止める
			if (m_chargeTimer[plaNum] > 0)
			{
				m_ChargeSound[plaNum]->Stop();
			}

			m_DASpr1[plaNum]->Deactivate();
			m_DASpr2[plaNum]->Deactivate();

			//押したときのタイマー初期化
			m_chargeTimer[plaNum] = 0;

			//プレイヤーに影響
			m_moveSpeed[plaNum] += m_enePushSpeed;
		}
	}
}


//プレイヤーとプレイヤーがぶつかったときの処理関数
void Player::PlaAndPlaClash(int plaNum)
{
	//ほかプレイヤー(u)と自分(i)がぶつかったとき、ほかプレイヤーに押される処理
	for (int otherPlaNum = Player1; otherPlaNum < m_plaNum; otherPlaNum++) {
		if (otherPlaNum == plaNum)
		{
			//uとiの値が同じのときは下の処理は行わずスキップする
			continue;
		}
		//プレイヤー同士の距離を計算
		m_diff = m_pos[otherPlaNum] - m_pos[plaNum];
		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 40.0f)
		{
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
			SoundPlayBack(PlaAndPlaClashSound,plaNum);

			//プレイヤーに影響
			m_moveSpeed[plaNum] += m_enePushSpeed;

			//誰が押してきたかを保存
			m_pushPlayer[plaNum] = otherPlaNum;
		}
	}
}


//プレイヤーにかかる重力を設定する関数
void Player::Gravity(int plaNum)
{
	//重力の影響を与える
	m_moveSpeed[plaNum].y -= 0.2f;
}


//ベクトルを可視化させるデバック関数
void Player::PlaMooveSpeedDebug(int plaNum)
{
	Vector3 Dir = m_moveSpeed[plaNum];
	Dir.y = 0;
	Dir.Normalize();//大きさを位置にする
	float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
	Dir.z *= -1;
	float angleX = acosf(x);//アークコサイン
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[plaNum].SetRotationY(angleX);//ｘ度だけY軸を回す
	m_skinModelRenderArrow[plaNum]->SetRotation(m_arrowRot[plaNum]);//角度を設定する
	m_arrowPos[plaNum] = m_pos[plaNum];
	m_arrowPos[plaNum].y += 30.0f;
	m_skinModelRenderArrow[plaNum]->SetPosition(m_arrowPos[plaNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[plaNum].Length() / 5;
	m_skinModelRenderArrow[plaNum]->SetScale(m_arrowSize);
}


//サウンドを一括にまとめる関数
void Player::SoundPlayBack(int soundNum, int plaNum)
{
	switch (soundNum)
	{
	case ShootDownSound:
		//撃墜サウンドの初期化
		m_shootDownSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_shootDownSound[plaNum]->Init(L"Assets/sound/ShootDown.wav");
		m_shootDownSound[plaNum]->SetVolume(1.0f);
		m_shootDownSound[plaNum]->Play(false);	//偽でワンショット再生

		break;

	case CarHornSound:
		//Xボタンが押されたとき再生
		if (g_pad[plaNum]->IsTrigger(enButtonX))
		{
			//クラクションサウンドの初期化
			m_carHorn[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_carHorn[plaNum]->Init(L"Assets/sound/CarHorn.wav");
			m_carHorn[plaNum]->SetVolume(0.5f);
			m_carHorn[plaNum]->Play(false);	//偽でワンショット再生
		}

		break;

	case FallSound:
		//高さが-10以下のとき再生
		if (m_pos[plaNum].y < -10.0f && m_isFallSoundFlg[plaNum])
		{
			//クラクションサウンドの初期化
			m_FallSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_FallSound[plaNum]->Init(L"Assets/sound/Fall.wav");
			m_FallSound[plaNum]->SetVolume(0.1f);
			m_FallSound[plaNum]->Play(false);	//偽でワンショット再生

			m_isFallSoundFlg[plaNum] = false;
		}
		//リスポーン位置に移動したときにフラグを復活させる
		if (m_pos[plaNum].y == 150.0f)
		{
			m_isFallSoundFlg[plaNum] = true;
		}

		break;

	case ChargeSound:
		//チャージサウンドの初期化
		m_ChargeSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_ChargeSound[plaNum]->Init(L"Assets/sound/Charge.wav");
		m_ChargeSound[plaNum]->SetVolume(0.1f);
		m_ChargeSound[plaNum]->Play(false);	//偽でワンショット再生

		break;

	case Dash1Sound:
		//ダッシュ１サウンドの初期化
		m_Dash1Sound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_Dash1Sound[plaNum]->Init(L"Assets/sound/PlaDash1.wav");
		m_Dash1Sound[plaNum]->SetVolume(0.5f);
		m_Dash1Sound[plaNum]->Play(false);	//偽でワンショット再生

		break;

	case Dash2Sound:
		//ダッシュ２サウンドの初期化
		m_Dash2Sound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_Dash2Sound[plaNum]->Init(L"Assets/sound/PlaDash2.wav");
		m_Dash2Sound[plaNum]->SetVolume(0.5f);
		m_Dash2Sound[plaNum]->Play(false);	//偽でワンショット再生

		break;
	case PlaAndPlaClashSound:
		//プレイヤーとプレイヤーがぶつかったときのサウンドの初期化
		m_PlaAndPlaClashSound[plaNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_PlaAndPlaClashSound[plaNum]->Init(L"Assets/sound/Clash1.wav");
		m_PlaAndPlaClashSound[plaNum]->SetVolume(1.0f);
		m_PlaAndPlaClashSound[plaNum]->Play(false);	//偽でワンショット再生

		break;
	}
}