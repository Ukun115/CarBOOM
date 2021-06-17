#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{
	const Vector3 ENEMY1_RESPOS = { -50.0f,0.0f,50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY2_RESPOS = { 50.0f,0.0f,50.0f };			//初期座標(リスポーン座標)
	const Vector3 ENEMY3_RESPOS = { 0.0f,0.0f,0.0f };			//初期座標(リスポーン座標)
	const Vector3 ENEMY4_RESPOS = { -50.0f,0.0f,-50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY5_RESPOS = { 50.0f,0.0f,-50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY6_RESPOS = { 0.0f,0.0f,-50.0f };			//初期座標(リスポーン座標)
}

bool Enemy::Start()
{
	//インスタンスを探す。
	m_gamescene  = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_player	 = FindGO<Player>("player");

	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//パトカー(敵)をロード
		m_enemy[i] = NewGO<SkinModelRender>(0);
		//モデルのファイルパスを設定
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//パトカー
		//初期座標(リスポーン座標)の設定。
		if (i == ENEMY1)
		{
			m_enePos[ENEMY1] = ENEMY1_RESPOS;		//エネミー１の場所
		}
		else if (i == ENEMY2)
		{
			m_enePos[ENEMY2] = ENEMY2_RESPOS;		//エネミー２の場所
		}
		else if (i == ENEMY3)
		{
			m_enePos[ENEMY3] = ENEMY3_RESPOS;		//エネミー３の場所
		}
		else if (i == ENEMY4)
		{
			m_enePos[ENEMY4] = ENEMY4_RESPOS;		//エネミー４の場所
		}
		else if (i == ENEMY5)
		{
			m_enePos[ENEMY5] = ENEMY5_RESPOS;		//エネミー５の場所
		}
		else if (i == ENEMY6)
		{
			m_enePos[ENEMY6] = ENEMY6_RESPOS;		//エネミー６の場所
		}
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});

		//当たり判定のイニシャライズ(初期化)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);
	}

	//Start関数のreturn文
	return true;
}

Enemy::~Enemy()
{
	//全エネミーを削除。
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}

void Enemy::Update()
{
	//登録されているエネミー数ループ
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gamescene->GetNowTime() != 0) {
			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (m_gamescene->GetCountDownFlg() == false)
			{
				//重力の影響を与える
				m_moveSpeed[i].y -= 0.2f;

				//スタートした瞬間にパトカーがダッシュしてしまうのを回避する処理
				if (m_startDelayTimer < 600)
				{
					//キャラクターコントローラーを使った移動処理に変更。
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					m_enePos[i] += m_moveSpeed[i];
					m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる
					m_rot2[i].Multiply(m_rot[i], m_rot2[i]);

					//タイマー加算
					m_startDelayTimer++;
				}
				//落ちていないときは基本ここの処理が実行される。
				else
				{
					//回転処理
					EneTurn(i);

					if (ctFlg[i] == false) {

						//CTをカウントするフラグを立てる
						ctFlg[i] = true;

						//距離設定
						Distance(i);

						//移動処理
						EneMove(i);
					}

					//CTフラグが立ってる時
					if (ctFlg[i] == true) {

						//CTをカウントする
						m_cTime[i]++;

						//摩擦力を設定する
						m_friction[i] = m_moveSpeed[i];
						m_friction[i] *= -1.5f;

						//摩擦力を加算する
						m_moveSpeed[i].x += m_friction[i].x * g_gameTime->GetFrameDeltaTime();
						m_moveSpeed[i].z += m_friction[i].z * g_gameTime->GetFrameDeltaTime();
					}

					//CTのカウントが180秒の時
					if (m_cTime[i] == 120) {

						//CTフラグを下ろす
						ctFlg[i] = false;

						//CTのカウントを0にする
						m_cTime[i] = 0;
					}

					//キャラクターコントローラーを使った移動処理に変更。
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					/// <summary>
					/// リスポーン処理
					/// </summary>
					if (m_enePos[i].y < -1000.0f)
					{
						//プレイヤーの座標をリスポーン座標に移動
						EneResporn(i);

						//キャラコンの座標にプレイヤーの座標をいれる
						m_charaCon[i].SetPosition(m_enePos[i]);

						//スピードを初期化
						m_moveSpeed[i] = { Vector3::Zero };

						//キャラクターコントローラーを使った移動処理に変更。
						m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
					}

					m_enePos[i] += m_moveSpeed[i];
					m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる
					m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
				}
			}
			m_enemy[i]->SetRotation(m_rot2[i]);		//回転情報更新
			m_enemy[i]->SetPosition(m_enePos[i]);	//位置情報更新
		}
	}
}

//距離設定
void Enemy::Distance(int x)
{
	//登録されているプレイヤーの分処理をする
	for (int i = 0; i < m_titlescene->GetTotalPlaNum(); i++)
	{
		//車の位置を取得
		m_plaPos[i] = m_player->GetPlaPos(i);
		//車の位置とパトカーの位置の距離を取得
		m_mostShortKyori[i] = m_plaPos[i] - m_enePos[x];
	}

	//m_mostShortKyori[0].Length()の値が一番小さくなるように並び替え(ソート)
	for (int s = 0; s < m_titlescene->GetTotalPlaNum() - 1; s++) {
		for (int t = s + 1; t < m_titlescene->GetTotalPlaNum(); t++) {
			if (m_mostShortKyori[t].Length() < m_mostShortKyori[s].Length()) {
				Vector3 tmp = m_mostShortKyori[t];
				m_mostShortKyori[t] = m_mostShortKyori[s];
				m_mostShortKyori[s] = tmp;
			}
		}
	}

	//プレイヤーからエネミーのベクトルを正規化して方向だけの情報にする
	m_mostShortKyori[0].Normalize();
}

//移動処理
void Enemy::EneMove(int x)
{
	//方向だけのm_kyori[x]に速さを掛けて速度にする
	m_moveSpeed[x] = m_mostShortKyori[0] * 5.0f;
}

//回転処理
void Enemy::EneTurn(int x)
{
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}

//パトカーをリスポーン位置まで戻す関数
void Enemy::EneResporn(int x)
{
	//1
	if (x == ENEMY1)
	{
		m_enePos[x] = ENEMY1_RESPOS;
	}
	//2
	else if (x == ENEMY2)
	{
		m_enePos[x] = ENEMY2_RESPOS;
	}
	//3
	else if (x == ENEMY3)
	{
		m_enePos[x] = ENEMY3_RESPOS;
	}
	//4
	else if (x == ENEMY4)
	{
		m_enePos[x] = ENEMY4_RESPOS;
	}
	//5
	else if (x == ENEMY5)
	{
		m_enePos[x] = ENEMY5_RESPOS;
	}
	//6
	else if (x == ENEMY6)
	{
		m_enePos[x] = ENEMY6_RESPOS;
	}
}