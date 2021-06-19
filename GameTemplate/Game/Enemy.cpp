#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード
		//↑2階層上にディレクトリを移動してからフォルダを潜っている。


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>("titlescene");
	m_gameScene  = FindGO<GameScene>("gamescene");
	m_player	 = FindGO<Player>("player");

	m_randEneResPos[0] = { -150.0f,0.0f,150.0f };
	m_randEneResPos[1] = { 0.0f,0.0f,100.0f };
	m_randEneResPos[2] = { 100.0f,0.0f,100.0f };
	m_randEneResPos[3] = { -100.0f,0.0f,00.0f };
	m_randEneResPos[4] = { 0.0f,0.0f,0.0f };
	m_randEneResPos[5] = { 100.0f,0.0f,0.0f };
	m_randEneResPos[6] = { -100.0f,0.0f,-100.0f };
	m_randEneResPos[7] = { 0.0f,0.0f,-100.0f };
	m_randEneResPos[8] = { 100.0f,0.0f,-100.0f };
	m_randEneResPos[9] = { 150.0f,0.0f,150.0f };

	//リスポーン座標がプレイヤー1P～4Pの座標と同じにならないようにしないといけない。
	//【プレイヤーのリスポーン位置】
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//敵をロード
		m_enemy[i] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//モデルのファイルパスを設定
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//敵モデル
		//初期座標(リスポーン座標)の設定。
		if (i == ENEMY1)
		{
			m_enePos[ENEMY1] = m_randEneResPos[0];		//敵１の場所
		}
		else if (i == ENEMY2)
		{
			m_enePos[ENEMY2] = m_randEneResPos[1];		//敵２の場所
		}
		else if (i == ENEMY3)
		{
			m_enePos[ENEMY3] = m_randEneResPos[3];		//敵3の場所
		}
		else if (i == ENEMY4)
		{
			m_enePos[ENEMY4] = m_randEneResPos[4];		//敵4の場所
		}
		else if (i == ENEMY5)
		{
			m_enePos[ENEMY5] = m_randEneResPos[7];		//敵5の場所
		}
		else if (i == ENEMY6)
		{
			m_enePos[ENEMY6] = m_randEneResPos[9];		//敵6の場所
		}
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});

		//当たり判定のイニシャライズ(初期化)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);

		//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
	}

	//Start関数のreturn文
	return true;
}


Enemy::~Enemy()
{
	//全ての敵を削除。
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}


void Enemy::Update()
{
	//全敵分ループ
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() != 0) {
			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (m_gameScene->GetCountDownFlg() == false)
			{
				//重力の影響を与える
				m_moveSpeed[i].y -= 0.2f;

				//スタートした瞬間に敵がダッシュしてしまうのを回避する処理
				if (m_startDelayTimer < m_startDelay[i])
				{
					//スタート時にDAを遅らせるタイマーを加算
					m_startDelayTimer++;
				}
				//落ちていないときは基本ここの処理が実行される。
				else
				{
					//回転処理
					EneTurn(i);

					if (m_isCtFlg[i] == false) {

						//CTをカウントするフラグを立てる
						m_isCtFlg[i] = true;

						//距離設定
						Distance(i);

						//移動処理
						EneMove(i);
					}

					//CTフラグが立ってるとき、
					if (m_isCtFlg[i] == true) {

						//CTをカウントする
						m_cTime[i]++;

						//摩擦力を設定する
						m_friction[i] = m_moveSpeed[i];
						m_friction[i] *= -1.5f;

						//摩擦力を加算する
						m_moveSpeed[i].x += m_friction[i].x * g_gameTime->GetFrameDeltaTime();
						m_moveSpeed[i].z += m_friction[i].z * g_gameTime->GetFrameDeltaTime();
					}

					//CTのカウントが120秒～140秒のとき、
					if (m_cTime[i] == m_eneCTCount[i]) {

						//CTフラグを下ろす
						m_isCtFlg[i] = false;

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
				}
			}
			m_enemy[i]->SetRotation(m_rot[i]);		//回転情報更新
			m_enemy[i]->SetPosition(m_enePos[i]);	//位置情報更新
		}
	}
}


//敵から最寄りのプレイヤーを検索する関数
void Enemy::Distance(int x)
{
	//登録されているプレイヤーの分処理をする
	for (int i = 0; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		//プレイヤーの位置を取得
		m_plaPos[i] = m_player->GetPlaPos(i);
		//プレイヤーの位置と敵の位置の距離を取得
		m_mostShortKyori[i] = m_plaPos[i] - m_enePos[x];
	}

	//m_mostShortKyori[0].Length()の値が一番小さくなるように並び替え(ソート)
	for (int s = 0; s < m_titleScene->GetTotalPlaNum() - 1; s++) {
		for (int t = s + 1; t < m_titleScene->GetTotalPlaNum(); t++) {
			if (m_mostShortKyori[t].Length() < m_mostShortKyori[s].Length()) {
				Vector3 tmp = m_mostShortKyori[t];
				m_mostShortKyori[t] = m_mostShortKyori[s];
				m_mostShortKyori[s] = tmp;
			}
		}
	}

	//プレイヤーから敵のベクトルを正規化して方向だけの情報にする
	m_mostShortKyori[0].Normalize();
}


//敵の移動処理関数
void Enemy::EneMove(int x)
{
	//方向だけのm_kyori[x]に速さを掛けて速度にする
	m_moveSpeed[x] = m_mostShortKyori[0] * 5.0f;
}


//敵の回転処理関数
void Enemy::EneTurn(int x)
{
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
}


//敵のリスポーン処理関数
void Enemy::EneResporn(int x)
{
	//ランダムでリスポーン位置を入れる
	m_enePos[x] = m_randEneResPos[rand() % 10];
}