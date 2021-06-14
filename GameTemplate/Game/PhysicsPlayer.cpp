#include "stdafx.h"
#include "PhysicsPlayer.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = { 1.4f,1.4f,1.4f };			//プレイヤーの初期サイズ
	const int PLAYER1 = 0;			//1P
	const int PLAYER2 = 1;			//2P
	const int PLAYER3 = 2;			//3P
	const int PLAYER4 = 3;			//4P
	const int MAXPLAYERNUM = 4;		//プレイヤーの最大人数
	const Vector3 PLAYER1_RESPOS = { -100.0f,0.0f, 100.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = {  100.0f,0.0f, 100.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -100.0f,0.0f,-100.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = {  100.0f,0.0f,-100.0f };		//リスポーン座標(右下)
	const float PLANAME_WIDTHSIZE = 230.0f;			//プレイヤーの画面角に置かれている名前の画像の「横の」大きさ
	const float PLANAME_HEIGHTSIZE = 120.0f;		//プレイヤーの画面角に置かれている名前の画像の「縦の」大きさ
}

bool PhysicsPlayer::Start()
{
	//インスタンスを探す。
	m_nowTime = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//登録されていたら実行
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//プレイヤーをロード
			m_player[i] = NewGO<SkinModelRender>(0);

			////当たり判定

			////コライダーを初期化。
			////コライダーの大きさを初期化。
			//m_boxColliderSize[i] = { 18.0f,10.0f,40.0f };
			//m_boxCollider[i].Create(m_boxColliderSize[i]);
			////質量を設定する。
			//rbInitData[i].mass = 3.0f;
			//rbInitData[i].collider = &m_boxCollider[i];
			//if (i == PLAYER1)
			//rbInitData[i].pos = PLAYER1_RESPOS;
			//if (i == PLAYER2)
			//	rbInitData[i].pos = PLAYER2_RESPOS;
			//if (i == PLAYER3)
			//	rbInitData[i].pos = PLAYER3_RESPOS;
			//if (i == PLAYER4)
			//	rbInitData[i].pos = PLAYER4_RESPOS;
			////はじめはちょっと上から
			//rbInitData[i].pos.y = 100.0f;
			//m_rigidBody[i].Init(rbInitData[i]);
			////摩擦力を設定する。0～10
			//m_rigidBody[i].SetFriction(0.1f);
			////線形移動する要素を設定する。
			////0を指定した軸は移動しない。
			//m_rigidBody[i].SetLinearFactor(1.0f, 1.0f, 1.0f);

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

			//プレイヤー数を+1
			m_plaNum++;
		}
	}

	//Start関数のreturn文
	return true;
}

PhysicsPlayer::~PhysicsPlayer()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//プレイヤーを削除
		DeleteGO(m_player[i]);
	}
}

void PhysicsPlayer::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_nowTime->GetNowTime() != 0) {
			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (m_nowTime->GetCountDownFlg() == false)
			{
				//ステージの中心()原点とプレイヤーとの距離を計算
				m_diff = m_pos[i] - m_origin;
				//ステージ上から外れているとき、
				//(ベクトルの長さを取得し、それが250.0fより大きく、500以下の値だったら、)
				if (m_diff.Length() > 250.0f && m_diff.Length() <= 500.0f)
				{
					//プレイヤーが着地しているフラグを折る
					m_isPlaLanding[i] = false;

					//落下させる
					m_pos[i].y -= 2.0f;
				}
				//落下から少し時間が経過したら、
				//基本はステータスの初期化をここでしています。
				else if (m_diff.Length() > 500.0f)
				{
					//プレイヤーを初期位置に持っていく。
					PlaResporn(i);
					//ちょっと上にプレイヤーを戻す。
					m_pos[i].y += 50.0f;

					//フラグを立てる
					m_respornFallFlg[i] = true;
				}
				//ステージ上にリスポーンしたというフラグが立ったら、
				else if (m_respornFallFlg[i])
				{
					//ステージ上に落下させる処理
					if (m_pos[i].y != 0.0f)
					{
						m_pos[i].y -= 1.0f;
					}
					else
					{
						//プレイヤーの蓄積されているスピードを初期化。
						m_moveSpeed[i] = { 0.0f,0.0f,0.0f };

						//押した時のタイマー初期化
						m_pressTimer[i] = 0;
						//離した時のタイマー初期化
						m_releaseTimer[i] = 0;
						isBPushFlg[i] = false;
						//これらを初期化しないと、着地した際に勝手にダッシュ攻撃するバグが発生します。


						//フラグを折る
						m_respornFallFlg[i] = false;
					}
				}
				//ステージ上にいるとき実行、
				else
				{
					m_isPlaLanding[i] = true;

					//回転処理
					PlaTurn(i);

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

					}

					//プレイヤーの状態
					PlaNowSpeed(i);

					m_pos[i] += m_moveSpeed[i];

					////剛体の座標と回転を設定。
					////m_rigidBody[i].SetPositionAndRotation(m_pos[i], m_rot[i]);
					////剛体の座標と回転を取得。
					//m_rigidBody[i].GetPositionAndRotation(m_pos[i], m_rot[i]);
					////剛体の座標と回転をモデルに反映。
					//m_player[i]->GetModel().UpdateWorldMatrix(m_pos[i], m_rot[i], g_vec3One);
					////剛体に力を加える。
					//m_rigidBody[i].AddForce(
					//	m_moveSpeed[i],		//力
					//	g_vec3Zero	//力を加える剛体の相対位置
					//);
				}
			}
			//登録されているプレイヤーの情報を更新
			PlaDataUpdate(i);
		}
	}
}

//選択されたプレイヤーをリスポーン位置まで戻す関数
void PhysicsPlayer::PlaResporn(int x)
{
	//1P
	if (x == PLAYER1)
	{
		m_pos[x] = PLAYER1_RESPOS;		//リスポーン座標(左上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[x] = 2.5f;
		//回転情報をセットする
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//2P
	else if (x == PLAYER2)
	{
		m_pos[x] = PLAYER2_RESPOS;		//リスポーン座標(右上)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[x] = 3.7f;
		//回転情報をセットする
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//3P
	else if (x == PLAYER3)
	{
		m_pos[x] = PLAYER3_RESPOS;		//リスポーン座標(左下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[x] = 1.0f;
		//回転情報をセットする
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//4P
	else if (x == PLAYER4)
	{
		m_pos[x] = PLAYER4_RESPOS;		//リスポーン座標(右下)

		//プレイヤーがリスポーンしたときに全プレイヤー統一でステージ中央を向かせておいたほうが
		//リスポーン時違和感がないので、ステージ中央を向かせておく。
		m_rotAngle[x] = 5.5f;
		//回転情報をセットする
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
}

//プレイヤーの情報を更新する関数
void PhysicsPlayer::PlaDataUpdate(int x)
{
	//位置をセット
	m_player[x]->SetPosition(m_pos[x]);
	//回転をセット
	m_player[x]->SetRotation(m_rot[x]);
}

void PhysicsPlayer::PlaNowSpeed(int x)
{
	if (m_pressTimer[x] == 0 && m_releaseTimer[x] == 0)
	{
		//移動処理
		PlaMove(x);
	}
	if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
	{
		//攻撃準備処理
		PlaAttackBefore(x);

	}
	if (m_releaseTimer[x] > 0 && m_releaseTimer[x] < 10 && m_pressTimer[x] == 0)
	{
		//攻撃処理
		PlaAtack(x);
	}

	if (m_releaseTimer[x] == 10 && m_pressTimer[x] == 0)
	{
		//移動処理
		PlaMove(x);
		isBPushFlg[x] = false;
	}
}

//移動処理
void PhysicsPlayer::PlaMove(int x)
{
	//左スティックの入力量を加算する
	m_moveSpeed[x].x += m_leftStick_x[x] * 5.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 5.0f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -1.5f;

	//摩擦力を加算する
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}

//回転処理
void PhysicsPlayer::PlaTurn(int x)
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

	//向きを設定する
	m_plaDir[x] = m_moveSpeed[x];
	m_plaDir[x].Normalize();
}

//攻撃準備処理
void PhysicsPlayer::PlaAttackBefore(int x)
{
	m_moveSpeed[x].x += m_leftStick_x[x] * 1.5f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 1.5f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -5.0f;

	//摩擦力を加算する
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}

//攻撃処理
void PhysicsPlayer::PlaAtack(int x)
{
	m_moveSpeed[x] = m_plaDir[x] * 5.0f;
}