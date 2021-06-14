#include "stdafx.h"
#include "Enemy.h"
#include "PhysicsPlayer.h"
#include "TitleScene.h"
#include "GameScene.h"

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

	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int MAXPLAYERNUM = 4;
}

bool Enemy::Start()
{
	//インスタンスを探す。
	m_gamescene = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");
	m_player = FindGO<PhysicsPlayer>("physicsplayer");

	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		m_mostShortKyori[i] = {1000.0f,1000.0f,1000.0f};

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

		////当たり判定

		////コライダーを初期化。
		////コライダーの大きさを初期化。
		//m_boxColliderSize[i] = { 18.0f,10.0f,40.0f };
		//m_boxCollider[i].Create(m_boxColliderSize[i]);
		////質量を設定する。
		//rbInitData[i].mass = 3.0f;
		//rbInitData[i].collider = &m_boxCollider[i];
		//if (i == ENEMY1)
		//	rbInitData[i].pos = ENEMY1_RESPOS;
		//if (i == ENEMY2)
		//	rbInitData[i].pos = ENEMY2_RESPOS;
		//if (i == ENEMY3)
		//	rbInitData[i].pos = ENEMY3_RESPOS;
		//if (i == ENEMY4)
		//	rbInitData[i].pos = ENEMY4_RESPOS;
		//if (i == ENEMY5)
		//	rbInitData[i].pos = ENEMY5_RESPOS;
		//if (i == ENEMY6)
		//	rbInitData[i].pos = ENEMY6_RESPOS;
		////はじめはちょっと上から
		//rbInitData[i].pos.y = 100.0f;
		//m_rigidBody[i].Init(rbInitData[i]);
		////摩擦力を設定する。0～10
		//m_rigidBody[i].SetFriction(0.1f);
		////線形移動する要素を設定する。
		////0を指定した軸は移動しない。
		//m_rigidBody[i].SetLinearFactor(1.0f, 1.0f, 1.0f);
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
				//スタートした瞬間にパトカーがダッシュしてしまうのを回避する処理
				if (m_startDelayTimer < 600)
				{
					//タイマー加算
					m_startDelayTimer++;
				}
				else
				{
					//ステージの中心()原点とプレイヤーとの距離を計算
					m_diff = m_enePos[i] - m_origin;
					//ステージ上から外れているとき、
					//(ベクトルの長さを取得し、それが250.0fより大きく、500以下の値だったら、)
					if (m_diff.Length() > 250.0f && m_diff.Length() <= 500.0f)
					{
						//落下させる
						m_enePos[i].y -= 2.0f;
					}
					//落下から少し時間が経過したら、
					//基本はステータスの初期化をここでしています。
					else if (m_diff.Length() > 500.0f)
					{
						//パトカーを初期位置に持っていく。
						EneResporn(i);
						//ちょっと上にパトカーを戻す。
						m_enePos[i].y += 50.0f;

						//フラグを立てる
						m_respornFallFlg[i] = true;
					}
					//ステージ上にリスポーンしたというフラグが立ったら、
					else if (m_respornFallFlg[i])
					{
						//ステージ上に落下させる処理
						if (m_enePos[i].y != 0.0f)
						{
							m_enePos[i].y -= 1.0f;
						}
						else
						{
							//プレイヤーの蓄積されているスピードを初期化。
							m_moveSpeed[i] = { 0.0f,0.0f,0.0f };

							//フラグを折る
							m_respornFallFlg[i] = false;
						}
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

						//CTのカウントが180秒の時
						if (m_cTime[i] == 180) {

							//CTフラグを下ろす
							ctFlg[i] = false;

							//CTのカウントを0にする
							m_cTime[i] = 0;
						}


						m_enePos[i] += m_moveSpeed[i];
						m_rot2[i].SetRotationDeg(Vector3::AxisX, 0.0f);	//3dsMaxで設定されているアニメーションでキャラが回転しているので、補正を入れる
						m_rot2[i].Multiply(m_rot[i], m_rot2[i]);

						////剛体の座標と回転を設定。
						////m_rigidBody[i].SetPositionAndRotation(m_enePos[i], m_rot[i]);
						////剛体の座標と回転を取得。
						//m_rigidBody[i].GetPositionAndRotation(m_enePos[i], m_rot[i]);
						////剛体の座標と回転をモデルに反映。
						//m_enemy[i]->GetModel().UpdateWorldMatrix(m_enePos[i], m_rot[i], g_vec3One);
						////剛体に力を加える。
						//m_rigidBody[i].AddForce(
						//	m_moveSpeed[i],		//力
						//	g_vec3Zero	//力を加える剛体の相対位置
						//);
					}
				}
			}
			m_enemy[i]->SetRotation(m_rot2[i]); //回転情報更新
			m_enemy[i]->SetPosition(m_enePos[i]);	//位置情報更新
		}
	}

	//残り30秒になったらポイントライトでパトランプを光らせるようにする
}

//距離設定
void Enemy::Kyori(int x)
{
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//登録されていたら実行
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//地面に着地しているプレイヤーの距離だけ計算。
			//地面にいないプレイヤーの距離を計算するとパトカーが空中に飛んで行ったりするため。
			if (m_player->GetIsPlaLanding(i) == true)
			{
				m_plaPos[i] = m_player->GetPlaPos(i);
				m_newKyori[x] = m_plaPos[i] - m_enePos[x];

				//距離を比較して、現在の最短距離より新しく取得した
				//プレイヤーとの距離のほうが近かったら、
				if (m_mostShortKyori[x].Length() > m_newKyori[x].Length())
				{
					//最短距離を上書きする
					m_mostShortKyori[x] = m_newKyori[x];
				}
			}
		}
	}
	//プレイヤーからエネミーのベクトルを正規化して方向だけの情報にする
	m_mostShortKyori[x].Normalize();
}

//移動処理
void Enemy::EneMove(int x)
{
	//方向だけのm_kyori[x]に速さを掛けて速度にする
	m_moveSpeed[x] = m_mostShortKyori[x] * 5.0f;

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