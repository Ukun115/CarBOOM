#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "Enemy.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = { 1.4f,1.4f,1.4f };			//プレイヤーの初期サイズ
	const Vector3 PLAYER1_RESPOS = { -100.0f,150.0f, 100.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = {  100.0f,150.0f, 100.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -100.0f,150.0f,-100.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = {  100.0f,150.0f,-100.0f };		//リスポーン座標(右下)
	const float PLANAME_WIDTHSIZE = 230.0f;			//プレイヤーの画面角に置かれている名前の画像の「横の」大きさ
	const float PLANAME_HEIGHTSIZE = 120.0f;		//プレイヤーの画面角に置かれている名前の画像の「縦の」大きさ
}

bool Player::Start()
{
	//インスタンスを探す。
	m_gamescene = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_enemy = FindGO<Enemy>("enemy");

	//各プレイヤーの２段階溜め攻撃の可視化
	for (int i = 0; i < 4; i++)
	{
		m_sprite1[i] = NewGO<SpriteRender>(3);
		m_sprite1[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		m_sprite1[i]->Deactivate();

		m_sprite2[i] = NewGO<SpriteRender>(3);
		m_sprite2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		m_sprite2[i]->Deactivate();
	}
	m_sprite1[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite1[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite1[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite1[3]->SetPosition({ 550.0f,-200.0f,0.0f });
	m_sprite2[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite2[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite2[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite2[3]->SetPosition({ 550.0f,-200.0f,0.0f });

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//登録されていたら実行
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//プレイヤーをロード
			m_player[i] = NewGO<SkinModelRender>(0);

			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			//追加されたプレイヤーの名前画像の表示と位置決め
			//１P
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車
			}
			//大きさ調整。元のモデルが小さかったため、モデルの大きさを1.5倍。
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//プレイヤーを初期位置に持っていく。
			PlaResporn(i);
			m_pos[i].y = 0.0f;

			m_charaCon[i].Init(15.0f, 85.0f, m_pos[i]);

			//プレイヤー数を+1
			m_plaNum++;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		m_pushPlayer[i] = 4;	//初期値は自滅判定の4。
	}

	//Start関数のreturn文
	return true;
}

Player::~Player()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//プレイヤーを削除
		DeleteGO(m_player[i]);
	}
	//ため攻撃の際の段階文字表示の削除。
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_sprite1[i]);
		DeleteGO(m_sprite2[i]);
	}
}

void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gamescene->GetNowTime() != 0) {

			//重力の影響を与える
			m_moveSpeed[i].y -= 0.2f;

			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (m_gamescene->GetCountDownFlg() == false)
			{

				//押しているとき、
				if (g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == false)
				{
					//押した時のタイマーを加算
					m_pressTimer[i]++;

					//離した時のタイマー初期化
					m_releaseTimer[i] = 0;

					isBPushFlg[i] = true;
				}
				//離したとき、
				if (!g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == true)
				{
					//離した時のタイマーを加算
					m_releaseTimer[i]++;

					//押した時のタイマー初期化
					m_pressTimer[i] = 0;

					m_sprite1[i]->Deactivate();
					m_sprite2[i]->Deactivate();
				}

				//プレイヤーの状態
				PlaNowSpeed(i);

				//スピードの補正
				if (m_moveSpeed[i].x > 5.0f) {
					m_moveSpeed[i].x = 5.0f;	//右方向の最大速度
				}
				if (m_moveSpeed[i].x < -5.0f) {
					m_moveSpeed[i].x = -5.0f;	//左方向の最大速度
				}
				if (m_moveSpeed[i].z > 5.0f) {
					m_moveSpeed[i].z = 5.0f;	//上方向の最大速度
				}
				if (m_moveSpeed[i].z < -5.0f) {
					m_moveSpeed[i].z = -5.0f;	//下方向の最大速度
				}

				//回転処理
				PlaTurn(i);

				/// <summary>
				/// 衝突処理
				/// </summary>
				//パトカーとぶつかったときパトカーに押される処理
				for (int u = 0; u < 6; u++)
				{
					//プレイヤーとパトカーとの距離を計算
					m_diff = m_enemy->GetEnemyPos(u) - m_pos[i];
					//距離の長さが30.0fより小さかったら、
					if (m_diff.Length() < 30.0f)
					{
						m_enePushSpeed = m_enemy->GetEnemySpeed(u);
						//これだとプッシュパワーが強すぎるため、威力を弱める
						m_enePushSpeed.x /= 20;
						m_enePushSpeed.y /= 20;
						m_enePushSpeed.z /= 20;

						//プレイヤーに影響
						m_moveSpeed[i] += m_enePushSpeed;
					}
				}
				//ほかプレイヤー(u)と自分(i)がぶつかったとき、ほかプレイヤーに押される処理
				for (int u = PLAYER1; u < m_plaNum; u++) {
					if (u == i)
					{
						//uとiの値が同じの時はしたの処理は行わずスキップする
						continue;
					}
					//プレイヤー同士の距離を計算
					m_diff = m_pos[u] - m_pos[i];
					//距離の長さが30.0fより小さかったら、
					if (m_diff.Length() < 40.0f)
					{
						//衝突しているほかプレイヤーの力を保存
						m_enePushSpeed = m_moveSpeed[u];
						////これだとプッシュパワーが強すぎるため、威力を弱める
						//m_enePushSpeed.x /= 20;
						//m_enePushSpeed.y /= 20;
						//m_enePushSpeed.z /= 20;

						//プレイヤーに影響
						m_moveSpeed[i] += m_enePushSpeed;

						//誰が押してきたかを保存
						m_pushPlayer[i] = u;
					}
				}

				//キャラクターコントローラーを使った移動処理に変更。
				m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

				/// <summary>
				/// リスポーン処理
				/// </summary>
				if (m_pos[i].y < -1000.0f)
				{
					//プレイヤーの座標をリスポーン座標に移動
					PlaResporn(i);

					//キャラコンの座標にプレイヤーの座標をいれる
					m_charaCon[i].SetPosition(m_pos[i]);

					//スピードを初期化
					m_moveSpeed[i] = { Vector3::Zero };

					//キャラクターコントローラーを使った移動処理に変更。
					m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきた敵のナンバー
					m_gamescene->GetPlayerAddScore(m_pushPlayer[i],i);
					//４で初期化し、４のまま落ちると、
					//自滅とみなし自身のポイントが減るようにセットしておく
					m_pushPlayer[i] = 4;
				}
				///// <summary>
				///// 動けなくなったらリスポーンする処理
				///// </summary>
				//if (m_moveSpeed[i].Length() < 2.0f)
				//{
				//	m_noMooveTimer[i]++;
				//}
				////動いたらタイマーを初期化
				//else
				//{
				//	m_noMooveTimer[i] = 0;
				//}
				//if (m_noMooveTimer[i] > 240)
				//{
				//	//リスポーンさせる
				//	PlaResporn(i);

				//	//キャラコンの座標にプレイヤーの座標をいれる
				//	m_charaCon[i].SetPosition(m_pos[i]);

				//	//スピードを初期化
				//	m_moveSpeed[i] = { Vector3::Zero };

				//	//キャラクターコントローラーを使った移動処理に変更。
				//	m_pos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

				//	m_noMooveTimer[i] = 0;
				//}
			}
			//登録されているプレイヤーの情報を更新
			PlaDataUpdate(i);
		}
	}
}
//選択されたプレイヤーをリスポーン位置まで戻す関数
void Player::PlaResporn(int x)
{
	switch (x)
	{
		//1P
	 case PLAYER1:
			m_pos[x] = PLAYER1_RESPOS;		//リスポーン座標(左上)

			//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
			//リスポーン時違和感がないので、ステージ中央を向かせておく。
			m_rotAngle[x] = 2.5f;
			break;
		//2P
	 case PLAYER2:
			m_pos[x] = PLAYER2_RESPOS;		//リスポーン座標(右上)

			//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
			//リスポーン時違和感がないので、ステージ中央を向かせておく。
			m_rotAngle[x] = 3.7f;
			break;
		//3P
	 case PLAYER3:
			m_pos[x] = PLAYER3_RESPOS;		//リスポーン座標(左下)

			//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
			//リスポーン時違和感がないので、ステージ中央を向かせておく。
			m_rotAngle[x] = 1.0f;
			break;
		//4P
	 case PLAYER4:
			m_pos[x] = PLAYER4_RESPOS;		//リスポーン座標(右下)

			//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
			//リスポーン時違和感がないので、ステージ中央を向かせておく。
			m_rotAngle[x] = 5.5f;
			break;
	}

	//位置をセット
	m_player[x]->SetPosition(m_pos[x]);

	//回転情報をセットする
	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

	m_player[x]->SetRotation(m_rot[x]);
}

//プレイヤーの情報を更新する関数
void Player::PlaDataUpdate(int x)
{
	//位置をセット
	m_player[x]->SetPosition(m_pos[x]);
	//回転をセット
	m_player[x]->SetRotation(m_rot[x]);
}

void Player::PlaNowSpeed(int x)
{
	if (m_pressTimer[x] == 0 && m_releaseTimer[x] == 0)
	{
		//移動処理
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;

	}
	if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
	{
		//攻撃準備処理
		PlaAttackBefore(x);
	}

	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack0Flg[x] == true)
	{
		//押した時のタイマー初期化
		m_pressTimer[x] = 0;

		//離した時のタイマー初期化
		m_releaseTimer[x] = 0;
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack1Flg[x] == true)
	{
		//チャージ攻撃1の処理
		m_moveSpeed[x] *= 2.0f;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack2Flg[x] == true)
	{
		//チャージ攻撃2処理
		m_moveSpeed[x] *= 4.0f;
	}

	if (m_releaseTimer[x] == 20 && m_pressTimer[x] == 0)
	{
		//移動処理
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
}

//移動処理
void Player::PlaMove(int x)
{
	//左スティックの入力量を加算する
	m_moveSpeed[x].x += m_leftStick_x[x] * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 10.0f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -2.0f;

	//摩擦力を加算する
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}

//回転処理
void Player::PlaTurn(int x)
{
	//左スティックの入力量を受け取る
	m_leftStick_x[x] = g_pad[x]->GetLStickXF();
	m_leftStick_y[x] = g_pad[x]->GetLStickYF();

	//移動してない時は回転しない
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//移動してない時は回転しない
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}

//攻撃準備処理
void Player::PlaAttackBefore(int x)
{
		m_moveSpeed[x].x += m_leftStick_x[x] * 1.5f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_leftStick_y[x] * 1.5f * g_gameTime->GetFrameDeltaTime();

		//摩擦力を設定する
		m_friction[x] = m_moveSpeed[x];
		m_friction[x] *= -2.0f;

		//摩擦力を加算する
		m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
		m_atackTime[x]++;
		if (m_atackTime[x] > 0 && m_atackTime[x] < 30)
		{
			isAtack0Flg[x] = true;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = false;


		}
		if (m_atackTime[x] >= 30 && m_atackTime[x] < 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = true;
			isAtack2Flg[x] = false;
			//「1」表示
			if (m_atackTime[x] == 30) {
				m_sprite2[x]->Deactivate();
				m_sprite1[x]->Activate();
			}
		}
		if (m_atackTime[x] > 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = true;
			if (m_atackTime[x] == 91) {
				//「2」表示
				m_sprite1[x]->Deactivate();
				m_sprite2[x]->Activate();

			}
		}
}