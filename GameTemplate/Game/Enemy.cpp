#include "stdafx.h"
#include "Enemy.h"
#include "PhysicsPlayer.h"

namespace
{
	const int ENEMY1 = 0;		//エネミー１
	const int ENEMY2 = 1;		//エネミー２
	const int ENEMY3 = 2;		//エネミー３
	const int ENEMY4 = 3;		//エネミー４
	const int ENEMY5 = 4;		//エネミー５
	const int ENEMY6 = 5;		//エネミー６
	const int ENEMYNUM = 6;		//敵の総数
	const Vector3 ENEMY1_RESPOS = { -50.0f,0.0f,50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY2_RESPOS = { 50.0f,0.0f,50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY3_RESPOS = { 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY4_RESPOS = { -50.0f,0.0f,-50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY5_RESPOS = { 50.0f,0.0f,-50.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY6_RESPOS = { 0.0f,0.0f,-50.0f };		//初期座標(リスポーン座標)
}

bool Enemy::Start()
{
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
			m_enePos[ENEMY3] = ENEMY3_RESPOS;	//エネミー３の場所
		}
		else if (i == ENEMY4)
		{
			m_enePos[ENEMY4] = ENEMY4_RESPOS;	//エネミー４の場所
		}
		else if (i == ENEMY5)
		{
			m_enePos[ENEMY5] = ENEMY5_RESPOS;	//エネミー５の場所
		}
		else if (i == ENEMY6)
		{
			m_enePos[ENEMY6] = ENEMY6_RESPOS;		//エネミー６の場所
		}
	}

	//プレイヤーのインスタンスを探す。
	m_player = FindGO<PhysicsPlayer>("physicsplayer");

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
		//回転処理
		EneTurn(i);

		if (ctFlg[i] == false) {

			//CTをカウントするフラグを立てる
			ctFlg[i] = true;

			//距離設定
			Kyori(i);

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

		//CTのカウントが120秒の時
		if (m_cTime[i] == 120) {

			//CTフラグを下ろす
			ctFlg[i] = false;

			//CTのカウントを0にする
			m_cTime[i] = 0;

		}


		m_enePos[i] += m_moveSpeed[i];
		m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる
		m_rot2[i].Multiply(m_rot[i], m_rot2[i]);
		m_enemy[i]->SetRotation(m_rot2[i]); //回転情報更新
		m_enemy[i]->SetPosition(m_enePos[i]);	//位置情報更新
	}

	//残り30秒になったらポイントライトでパトランプを光らせるようにする
}

//距離設定
void Enemy::Kyori(int x)
{
	//プレイヤーの座標を取得する
	m_plaPos[0] = m_player->GetPlaPos();

	//プレイヤーとエネミーのベクトルを取得する
	m_kyori[x] = m_plaPos[0] - m_enePos[x];

	//プレイヤーからエネミーのベクトルを正規化して方向だけの情報にする
	m_kyori[x].Normalize();

}

//移動処理
void Enemy::EneMove(int x)
{
	//方向だけのm_kyori[x]に速さを掛けて速度にする
	m_moveSpeed[x] = m_kyori[x] * 7.0f;

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

	////向きを設定する
	//m_eneDir[x] = m_moveSpeed[x];
	//m_eneDir[x].Normalize();

}