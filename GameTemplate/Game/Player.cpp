#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "TitleScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = {1.5f,1.5f,1.5f};			//プレイヤーの初期サイズ
	const int PLAYER1 = 0;			//1P
	const int PLAYER2 = 1;			//2P
	const int PLAYER3 = 2;			//3P
	const int PLAYER4 = 3;			//4P
	const int MAXPLAYERNUM = 4;		//プレイヤーの最大人数
	const Vector3 PLAYER1_RESPOS = { -100.0f,0.0f,100.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = { 100.0f,0.0f,100.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -100.0f,0.0f,-100.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = { 100.0f,0.0f,-100.0f };		//リスポーン座標(右下)
	const float PLANAME_WIDTHSIZE = 230.0f;		//プレイヤーの画面角に置かれている名前の画像の「横の」大きさ
	const float PLANAME_HEIGHTSIZE = 120.0f;		//プレイヤーの画面角に置かれている名前の画像の「縦の」大きさ
}

bool Player::Start()
{
	m_getAddPlayerFlg = FindGO<TitleScene>("titlescene");

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//登録されていたら実行
		if (m_getAddPlayerFlg->GetPlaFlg(i) == true)
		{
			m_player[i] = NewGO<SkinModelRender>(0);

			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			//追加されたプレイヤーの名前画像の表示と位置決め
			//１P
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//大きさ調整。元のモデルが小さかったため、モデルの大きさを1.5倍。
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//プレイヤーを初期位置に持っていく。
			PlaResporn(i);
		}
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
}

void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
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

		m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる
		m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
		m_player[i]->SetRotation(m_rot2[i]); //回転情報更新
		m_player[i]->SetPosition(m_pos[i]);	//位置情報更新

	//登録されているプレイヤーの情報を更新
	//PlaDataUpdate(i);
	}
}

//選択されたプレイヤーをリスポーン位置まで戻す関数
void Player::PlaResporn(int x)
{
	//1P
	if (x == PLAYER1)
	{
		m_pos[PLAYER1] = PLAYER1_RESPOS;		//リスポーン座標(左上)
	}
	//2P
	else if (x == PLAYER2)
	{
		m_pos[PLAYER2] = PLAYER2_RESPOS;		//リスポーン座標(右上)
	}
	//3P
	else if (x == PLAYER3)
	{
		m_pos[PLAYER3] = PLAYER3_RESPOS;		//リスポーン座標(左下)
	}
	//4P
	else if (x == PLAYER4)
	{
		m_pos[PLAYER4] = PLAYER4_RESPOS;		//リスポーン座標(右下)
	}
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
void Player::PlaMove(int x)
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
void Player::PlaTurn(int x)
{
		//左スティックの入力量を受け取る
		m_leftStick_x[x] = g_pad[x]->GetLStickXF();
		m_leftStick_y[x] = g_pad[x]->GetLStickYF();

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
void Player::PlaAttackBefore(int x)
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
void Player::PlaAtack(int x)
{
	m_moveSpeed[x] = m_plaDir[x] * 5.0f;
}