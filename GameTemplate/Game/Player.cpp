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
	for (int i = 0; i < 4; i++)
	{
		//溜め１段階目の「１」画像オブジェクト生成
		m_DASpr1[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		//非表示
		m_DASpr1[i]->Deactivate();
		//溜め１段階目の「２」画像オブジェクト生成
		m_DASpr2[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_DASpr2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_DASpr2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		//非表示
		m_DASpr2[i]->Deactivate();
	}
	m_DASpr1[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr1[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr1[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr1[3]->SetPosition({ 500.0f,-150.0f,0.0f });
	m_DASpr2[0]->SetPosition({ -500.0f,150.0f,0.0f });
	m_DASpr2[1]->SetPosition({ 500.0f,150.0f,0.0f });
	m_DASpr2[2]->SetPosition({ -500.0f,-150.0f,0.0f });
	m_DASpr2[3]->SetPosition({ 500.0f,-150.0f,0.0f });

	for (int i = Player1; i < MaxPlayerNum; i++)
	{
		//登録されていたら実行
		if (m_titleScene->GetPlaFlg(i))
		{
			//プレイヤーモデルオブジェクト生成
			m_player[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//デバック用のプレイヤースピードの矢印表示
			m_skinModelRenderArrow[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			//追加されたプレイヤーの名前画像の表示と位置決め
			//１P
			if (i == Player1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player1_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetRed.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//2P
			else if (i == Player2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player2_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetBlue.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//3P
			else if (i == Player3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player3_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetYellow.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//4P
			else if (i == Player4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車
				//落下したときの撃墜エフェクトの初期化。
				m_shootDownEffect[i].Init(u"Assets/effect/efk/Player4_ShootDown.efk");
				m_jetEffect[i].Init(u"Assets/effect/efk/JetGreen.efk");

				m_skinModelRenderArrow[i]->Init("Assets/modelData/Arrow.tkm");	//矢印
			}
			//プレイヤーを初期位置に持っていく。
			PlaResPos(i);

			m_charaCon[i].Init(15.0f, 85.0f, m_pos[i]);

			//エフェクトの大きさ調整
			m_shootDownEffect[i].SetScale({ 70.0f,70.0f,70.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			Quaternion m_shootDownEffectRot = m_shootDownEffect[i].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
			m_shootDownEffect[i].SetRotation(m_shootDownEffectRot);

			//エフェクトの大きさ調整
			m_jetEffect[i].SetScale({ 3.0f,3.0f,3.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			m_shootDownEffectRot = m_jetEffect[i].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
			m_jetEffect[i].SetRotation(m_shootDownEffectRot);

			//プレイヤー数を+1
			m_plaNum++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		m_pushPlayer[i] = 4;	//初期値は誰にもポイントが入らない4。
	}

	//Start関数のreturn文
	return true;
}


Player::~Player()
{
	//登録されているプレイヤー数ループ
	for (int i = Player1; i < m_plaNum; i++)
	{
		//プレイヤーを削除
		DeleteGO(m_player[i]);
	}
	//ため攻撃の際の段階文字表示の削除。
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_DASpr1[i]);
		DeleteGO(m_DASpr2[i]);
	}
}


void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = Player1; i < m_plaNum; i++)
	{
		//クラクションを鳴らす
		SoundPlayBack(CarHornSound,i);
		//落ちるときの落下効果音をならす
		SoundPlayBack(FallSound,i);

		//制限時間が0秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() != TIME0) {

			//重力の影響を与える
			Gravity(i);

			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (!m_gameScene->GetCountDownFlg())
			{
				//回転処理
				PlaTurn(i);

				//プレイヤーの状態
				PlaNowState(i);

				//ベクトルを可視化させるデバック関数
				PlaMooveSpeedDebug(i);

				if (m_charaCon[i].IsOnGround()) {

					if (!m_isBPushFlg[i])
					{
						if (m_atackTimer[i] == 0)
						{
							//移動処理
							PlaMove(i);
						}
						if (m_isTyazi1Flg[i])
						{
							if (m_isCharge1EffectSoundFlg[i])
							{
								//チャージ１サウンド
								SoundPlayBack(Dash2Sound, i);

								m_isCharge1EffectSoundFlg[i] = false;
							}

							//チャージ攻撃1の処理
							m_moveSpeed[i] = m_plaDir[i] * 8.0f;
						}
						if (m_isTyazi2Flg[i])
						{
							if (m_isCharge2EffectSoundFlg[i])
							{
								//チャージ２サウンド
								SoundPlayBack(Dash1Sound,i);

								//ジェットエフェクト再生
								m_jetEffect[i].Play();

								m_isCharge2EffectSoundFlg[i] = false;
							}
							//チャージ攻撃2処理
							m_moveSpeed[i] = m_plaDir[i] * 20.0f;
						}

					}
					if (m_isBPushFlg[i])
					{
						//攻撃準備処理
						PlaAttackBefore(i);

					}
				}

				//プレイヤーのリスポーン処理
				PlaResporn(i);
				//プレイヤーの移動速度に補正を入れる
				PlaSpeedCorrection(i);

				//プレイヤーが敵とぶつかったとき敵に押される処理
				PlaAndEneClash(i);

				//プレイヤーとプレイヤーがぶつかったときの処理
				PlaAndPlaClash(i);

				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}

			if (m_gameScene->GetCountDownFlg())
			{
				//ベクトルを可視化させるデバック関数
				PlaMooveSpeedDebug(i);

				//重力の影響を与える
				Gravity(i);

				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}
			//登録されているプレイヤーの情報を更新
			PlaDataUpdate(i);
		}
	}
}


//プレイヤーのリスポーン処理関数
void Player::PlaResporn(int planum)
{
	if (m_pos[planum].y < -1000.0f)
	{
		//撃墜サウンド
		SoundPlayBack(ShootDownSound,planum);

		//撃墜エフェクト再生開始。
		m_shootDownEffect[planum].Play();
		//撃墜エフェクトの位置をプレイヤーが落ちた位置に設定
		m_shootDownEffect[planum].SetPosition(m_pos[planum]);
		//更新
		m_shootDownEffect[planum].Update();

		//プレイヤーの座標をリスポーン座標にセット
		PlaResPos(planum);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[planum].SetPosition(m_pos[planum]);

		//スピードを初期化
		m_moveSpeed[planum] = { Vector3::Zero };

		m_isBPushFlg[planum] = false;
		m_isTyazi1Flg[planum] = false;
		m_isTyazi2Flg[planum] = false;
		m_isAtack0Flg[planum] = false;
		m_isAtack1Flg[planum] = false;
		m_isAtack2Flg[planum] = false;
		m_DASpr1[planum]->Deactivate();
		m_DASpr2[planum]->Deactivate();

		//押したときのタイマー初期化
		m_tyaziTimer[planum] = 0;
		m_atackTimer[planum] = 0;

		//キャラクターコントローラーを使った移動処理に変更。
		m_pos[planum] = m_charaCon[planum].Execute(m_moveSpeed[planum], 1.0f);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきた敵のナンバー
		m_gameScene->GetPlayerAddScore(m_pushPlayer[planum], planum);

		for (int i = 0; i < 5; i++)
		{
			m_pushPlayer[i] = 4;	//誰にもポイントが入らない4にする。
		}
	}
}


//落ちたプレイヤーの初期位置をセットさせる関数
void Player::PlaResPos(int planum)
{
	switch (planum)
	{
		//1P
	case Player1:
		m_pos[planum] = PLAYER1_RESPOS;		//リスポーン座標(左上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[planum] = 2.5f;
		break;
		//2P
	case Player2:
		m_pos[planum] = PLAYER2_RESPOS;		//リスポーン座標(右上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[planum] = 3.7f;
		break;
		//3P
	case Player3:
		m_pos[planum] = PLAYER3_RESPOS;		//リスポーン座標(左下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[planum] = 1.0f;
		break;
		//4P
	case Player4:
		m_pos[planum] = PLAYER4_RESPOS;		//リスポーン座標(右下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[planum] = 5.5f;
		break;
	}

	//回転情報をセットする
	m_rot[planum].SetRotation(Vector3::AxisY, m_rotAngle[planum]);

	//プレイヤーの位置,回転の情報を更新する
	PlaDataUpdate(planum);
}


//プレイヤーの位置,回転の情報を更新する関数
void Player::PlaDataUpdate(int planum)
{
	//位置をセット
	m_player[planum]->SetPosition(m_pos[planum]);
	//回転をセット
	m_player[planum]->SetRotation(m_rot[planum]);

	//ブーストエフェクト位置をプレイヤー位置に設定
	m_jetEffect[planum].SetPosition(m_pos[planum]);
	m_jetEffect[planum].SetRotation(m_rot[planum]);
	//更新
	m_jetEffect[planum].Update();
}


//プレイヤーの現在の状態を伝える関数
void Player::PlaNowState(int planum)
{

	//Aボタンが押されてるとき、
	if (g_pad[planum]->IsPress(enButtonA))
	{
		if (m_tyaziTimer[planum] == 0)
		{
			//チャージ音を鳴らす
			SoundPlayBack(ChargeSound,planum);
		}

		m_isBPushFlg[planum] = true;

		m_isCharge1EffectSoundFlg[planum] = true;
		m_isCharge2EffectSoundFlg[planum] = true;

		//チャージしているときのタイマーを加算
		m_tyaziTimer[planum]++;

		//チャージ時間によって攻撃フラグを変える

		if (m_tyaziTimer[planum] >= 0 && m_tyaziTimer[planum] < 30)
		{
			m_isAtack0Flg[planum] = true;
		}
		if (m_tyaziTimer[planum] >= 30 && m_tyaziTimer[planum] < 90)
		{
			m_isAtack0Flg[planum] = false;
			m_isAtack1Flg[planum] = true;

			//「1」表示
			if (m_tyaziTimer[planum] == 30) {
				m_DASpr2[planum]->Deactivate();
				m_DASpr1[planum]->Activate();
			}
		}
		if (m_tyaziTimer[planum] >= 90)
		{
			m_isAtack1Flg[planum] = false;
			m_isAtack2Flg[planum] = true;

			//「2」表示
			if (m_tyaziTimer[planum] == 90) {
				m_DASpr1[planum]->Deactivate();
				m_DASpr2[planum]->Activate();
			}
		}
	}

	//Aボタンが押されてないとき、
	if (!g_pad[planum]->IsPress(enButtonA))
	{
		m_isBPushFlg[planum] = false;

		m_DASpr1[planum]->Deactivate();
		m_DASpr2[planum]->Deactivate();

		//押したときのタイマー初期化
		m_tyaziTimer[planum] = 0;

		//攻撃フラグによって攻撃処理を変える

		//チャージ失敗
		if (m_isAtack0Flg[planum])
		{
			m_isAtack0Flg[planum] = false;
		}

		//チャージ1
		if (m_isAtack1Flg[planum])
		{
			m_atackTimer[planum]++;
			m_atackHanteiTimer[planum]++;

			if (m_atackTimer[planum] > 0 && m_atackTimer[planum] < 20)
			{
				m_isTyazi1Flg[planum] = true;
			}
			if (m_atackTimer[planum] == 20)
			{
				m_atackTimer[planum] = 0;
				m_isAtack1Flg[planum] = false;
				m_isTyazi1Flg[planum] = false;
				////押したときのタイマー初期化
				//m_tyaziTimer[x] = 0;
			}


		}

		//チャージ2
		if (m_isAtack2Flg[planum])
		{
			m_atackTimer[planum]++;
			if (0 < m_atackTimer[planum] && m_atackTimer[planum] < 20)
			{
				m_isTyazi2Flg[planum] = true;
			}
			if (m_atackTimer[planum] == 20)
			{
				m_atackTimer[planum] = 0;
				m_isAtack2Flg[planum] = false;
				m_isTyazi2Flg[planum] = false;
				////押したときのタイマー初期化
				//m_tyaziTimer[x] = 0;
			}
		}
	}
}


//プレイヤーの通常移動処理関数
void Player::PlaMove(int planum)
{
	//左スティックの入力量を加算する
	m_moveSpeed[planum].x += m_leftStick_x[planum] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_leftStick_y[planum] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[planum] = m_moveSpeed[planum];
	m_friction[planum] *= -2.0f;

	///下のifはステージの処理なのでステージクラスに書く。
	//アイスステージが選択されているとき、
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//摩擦を減らす
		m_friction[planum] /= 3.0f;
	}

	//摩擦力を加算する
	m_moveSpeed[planum].x += m_friction[planum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_friction[planum].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーの移動速度に補正を入れる関数
void Player::PlaSpeedCorrection(int planum)
{
	//スピードの補正
	m_moveSpeed[planum].x = min(m_moveSpeed[planum].x, 5.0f);//右方向の最大速度
	m_moveSpeed[planum].x = max(m_moveSpeed[planum].x, -5.0f);//左方向の最大速度

	m_moveSpeed[planum].z = min(m_moveSpeed[planum].z, 5.0f);//上方向の最大速度
	m_moveSpeed[planum].z = max(m_moveSpeed[planum].z, -5.0f);//下方向の最大速度
}


//プレイヤーの回転処理関数
void Player::PlaTurn(int planum)
{
	//左スティックの入力量を受け取る
	m_leftStick_x[planum] = g_pad[planum]->GetLStickXF();
	m_leftStick_y[planum] = g_pad[planum]->GetLStickYF();

	//移動してないときは回転しない
	if (fabsf(m_moveSpeed[planum].x) < 0.001f && fabsf(m_moveSpeed[planum].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[planum] = atan2(m_moveSpeed[planum].x, m_moveSpeed[planum].z);

	m_rot[planum].SetRotation(Vector3::AxisY, m_rotAngle[planum]);
}


//プレイヤーのDA(ダッシュアタック)処理関数
void Player::PlaAttackBefore(int planum)
{
	m_moveSpeed[planum].x += m_leftStick_x[planum] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_leftStick_y[planum] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[planum] = m_moveSpeed[planum];
	m_friction[planum] *= -2.0f;

	//摩擦力を加算する
	m_moveSpeed[planum].x += m_friction[planum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[planum].z += m_friction[planum].z * g_gameTime->GetFrameDeltaTime();

	m_plaDir[planum] = m_moveSpeed[planum];
	m_plaDir->Normalize();
}


//プレイヤーと敵がぶつかったときの処理関数
void Player::PlaAndEneClash(int planum)
{
	for (int u = 0; u < 6; u++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_enemy->GetEnemyPos(u) - m_pos[planum];

		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 30.0f && !m_isTyazi1Flg[planum] && !m_isTyazi2Flg[planum])
		{
			m_enePushSpeed = m_enemy->GetEnemySpeed(u);
			//これだとプッシュパワーが強すぎるため、威力を弱める
			m_enePushSpeed.x /= 5;
			m_enePushSpeed.y /= 5;
			m_enePushSpeed.z /= 5;

			//チャージ中に敵と衝突したらチャージがキャンセルされる
			m_isAtack0Flg[planum] = false;
			m_isAtack1Flg[planum] = false;
			m_isAtack2Flg[planum] = false;
			//押されたらチャージサウンドを止める
			if (m_tyaziTimer[planum] > 0)
			{
				m_ChargeSound[planum]->Stop();
			}

			m_DASpr1[planum]->Deactivate();
			m_DASpr2[planum]->Deactivate();

			//押したときのタイマー初期化
			m_tyaziTimer[planum] = 0;

			//プレイヤーに影響
			m_moveSpeed[planum] += m_enePushSpeed;
		}
	}
}


//プレイヤーとプレイヤーがぶつかったときの処理関数
void Player::PlaAndPlaClash(int planum)
{
	//ほかプレイヤー(u)と自分(i)がぶつかったとき、ほかプレイヤーに押される処理
	for (int u = Player1; u < m_plaNum; u++) {
		if (u == planum)
		{
			//uとiの値が同じのときは下の処理は行わずスキップする
			continue;
		}
		//プレイヤー同士の距離を計算
		m_diff = m_pos[u] - m_pos[planum];
		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 40.0f)
		{
			//ぶつかってきたプレイヤーの力を保存
			m_enePushSpeed = m_moveSpeed[u];

			//ぶつかってきたプレイヤーはそのままステージ外に落ちないように減速させる
			m_moveSpeed[u] /= 2.0;

			if (m_isTyazi2Flg[planum])
			{
				m_enePushSpeed *= 5.0f;
				//チャージ２を受けたとき割る２しただけではそのまま落ちちゃうので
				//止まるようにする
				m_moveSpeed[u] = { 0.0f,0.0f,0.0f };
			}

			//衝突音
			SoundPlayBack(PlaAndPlaClashSound,planum);

			//プレイヤーに影響
			m_moveSpeed[planum] += m_enePushSpeed;

			//誰が押してきたかを保存
			m_pushPlayer[planum] = u;
		}
	}
}


//プレイヤーにかかる重力を設定する関数
void Player::Gravity(int planum)
{
	//重力の影響を与える
	m_moveSpeed[planum].y -= 0.2f;
}


//ベクトルを可視化させるデバック関数
void Player::PlaMooveSpeedDebug(int planum)
{
	Vector3 Dir = m_moveSpeed[planum];
	Dir.y = 0;
	Dir.Normalize();//大きさを位置にする
	float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
	Dir.z *= -1;
	float angleX = acosf(x);//アークコサイン
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[planum].SetRotationY(angleX);//ｘ度だけY軸を回す
	m_skinModelRenderArrow[planum]->SetRotation(m_arrowRot[planum]);//角度を設定する
	m_arrowPos[planum] = m_pos[planum];
	m_arrowPos[planum].y += 30.0f;
	m_skinModelRenderArrow[planum]->SetPosition(m_arrowPos[planum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[planum].Length() / 5;
	m_skinModelRenderArrow[planum]->SetScale(m_arrowSize);
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