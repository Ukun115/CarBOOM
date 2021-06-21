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
<<<<<<< HEAD

	const int RES_POS_NUM = 10;	//リスポーン位置の総数
	//敵の各リスポーン位置
	const Vector3 ENE_RES_POS_1 = { -150.0f,0.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,0.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,0.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,0.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 0.0f,0.0f,0.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,0.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,0.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 150.0f,0.0f,150.0f };
=======
>>>>>>> remotes/origin/master
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>("titlescene");
	m_gameScene  = FindGO<GameScene>("gamescene");
	m_player	 = FindGO<Player>("player");

	//敵のリスポーン位置１〜１０
	m_ranEneResPos[ResPos1]  = ENE_RES_POS_1;
	m_ranEneResPos[ResPos2]  = ENE_RES_POS_2;
	m_ranEneResPos[ResPos3]  = ENE_RES_POS_3;
	m_ranEneResPos[ResPos4]  = ENE_RES_POS_4;
	m_ranEneResPos[ResPos5]  = ENE_RES_POS_5;
	m_ranEneResPos[ResPos6]  = ENE_RES_POS_6;
	m_ranEneResPos[ResPos7]  = ENE_RES_POS_7;
	m_ranEneResPos[ResPos8]  = ENE_RES_POS_8;
	m_ranEneResPos[ResPos9]  = ENE_RES_POS_9;
	m_ranEneResPos[ResPos10] = ENE_RES_POS_10;

	//リスポーン座標がプレイヤー1P〜4Pの座標と同じにならないようにしないといけない。
	//【プレイヤーのリスポーン位置】
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	//敵の最大数繰り返す
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
<<<<<<< HEAD
		//敵モデルオブジェクト生成
		m_enemy[i] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//モデルのファイルパスを設定
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//パトカーモデル
		//敵の初期座標(リスポーン座標)の設定。
		EneResporn(i);
		//元が少し大きかったので、大きさを小さくする
=======
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
>>>>>>> remotes/origin/master
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});
		//当たり判定のイニシャライズ(初期化)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);
<<<<<<< HEAD
=======

>>>>>>> remotes/origin/master
		//300〜600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120〜140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
	}

	//Start関数のreturn文
	return true;
}


Enemy::~Enemy()
{
	//全ての敵を削除。
<<<<<<< HEAD
	for (int i = Enemy1; i < MaxEnemyNum; i++)
=======
	for (int i = ENEMY1; i < ENEMYNUM; i++)
>>>>>>> remotes/origin/master
	{
		DeleteGO(m_enemy[i]);
	}
}


void Enemy::Update()
{
	//全敵分ループ
<<<<<<< HEAD
	for (int i = Enemy1; i < MaxEnemyNum; i++)
=======
	for (int i = ENEMY1; i < ENEMYNUM; i++)
>>>>>>> remotes/origin/master
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() != 0) {
			//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
			if (m_gameScene->GetCountDownFlg() == false)
			{
				//重力の影響を与える
				Gravity(i);

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

<<<<<<< HEAD
					//DA攻撃処理
					EneDA(i);
=======
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

					//CTのカウントが120秒〜140秒のとき、
					if (m_cTime[i] == m_eneCTCount[i]) {

						//CTフラグを下ろす
						m_isCtFlg[i] = false;

						//CTのカウントを0にする
						m_cTime[i] = 0;
					}
>>>>>>> remotes/origin/master

					//キャラクターコントローラーを使った移動処理に変更。
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					//プレイヤーの座標をリスポーン座標に移動
					EneResporn(i);

					m_enePos[i] += m_moveSpeed[i];
				}
			}
<<<<<<< HEAD
			//敵の位置と回転情報を更新
			EneDataUpdate(i);
=======
			m_enemy[i]->SetRotation(m_rot[i]);		//回転情報更新
			m_enemy[i]->SetPosition(m_enePos[i]);	//位置情報更新
>>>>>>> remotes/origin/master
		}
	}
}


<<<<<<< HEAD
//敵の位置,回転情報を更新する関数
void Enemy::EneDataUpdate(int x)
{
	m_enemy[x]->SetRotation(m_rot[x]);		//回転情報更新
	m_enemy[x]->SetPosition(m_enePos[x]);	//位置情報更新
}


=======
>>>>>>> remotes/origin/master
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

<<<<<<< HEAD
	//一番近い距離(m_mostShortKyori[0])のように並び替え(ソート)
=======
	//m_mostShortKyori[0].Length()の値が一番小さくなるように並び替え(ソート)
>>>>>>> remotes/origin/master
	for (int s = 0; s < m_titleScene->GetTotalPlaNum() - 1; s++) {
		for (int t = s + 1; t < m_titleScene->GetTotalPlaNum(); t++) {
			if (m_mostShortKyori[t].Length() < m_mostShortKyori[s].Length()) {
				//交換
				Vector3 tmp = m_mostShortKyori[t];
				m_mostShortKyori[t] = m_mostShortKyori[s];
				m_mostShortKyori[s] = tmp;
			}
		}
	}

<<<<<<< HEAD
	//一番近いプレイヤーから敵のベクトルを正規化して方向だけの情報にする
=======
	//プレイヤーから敵のベクトルを正規化して方向だけの情報にする
>>>>>>> remotes/origin/master
	m_mostShortKyori[0].Normalize();
}


<<<<<<< HEAD
//敵のDA処理関数
void Enemy::EneDA(int x)
=======
//敵の移動処理関数
void Enemy::EneMove(int x)
>>>>>>> remotes/origin/master
{
	if (m_isCtFlg[x] == false) {

		//CTをカウントするフラグを立てる
		m_isCtFlg[x] = true;

		//距離設定
		Distance(x);

		//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
		m_moveSpeed[x] = m_mostShortKyori[0] * 5.0f;
	}
	//CTフラグが立ってるとき、
	if (m_isCtFlg[x] == true) {

		//CTをカウントする
		m_cTime[x]++;

		//摩擦を加えていく
		EneFriction(x);
	}
	//CTのカウントが120秒〜140秒のとき、
	if (m_cTime[x] == m_eneCTCount[x]) {

		//CTフラグを下ろす
		m_isCtFlg[x] = false;

		//CTのカウントを0にする
		m_cTime[x] = 0;
	}
}


//敵の回転処理関数
void Enemy::EneTurn(int x)
{
	//fabsf()は浮動小数点の絶対値を返す関数
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
	if (m_enePos[x].y < -1000.0f)
	{
		//ランダムでリスポーン位置を入れる
		m_enePos[x] = m_ranEneResPos[rand() % RES_POS_NUM];

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[x].SetPosition(m_enePos[x]);

		//スピードを0にする
		m_moveSpeed[x] = { Vector3::Zero };

		//キャラクターコントローラーを使った移動処理に変更。
		m_enePos[x] = m_charaCon[x].Execute(m_moveSpeed[x], 1.0f);
	}
}


//敵の摩擦処理関数
void Enemy::EneFriction(int x)
{
	//摩擦力を設定する
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -1.5f;
	//摩擦力を加算する
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}


//敵にかかる重力を設定する関数
void Enemy::Gravity(int x)
{
	//重力の影響を与える
	m_moveSpeed[x].y -= 0.2f;
}