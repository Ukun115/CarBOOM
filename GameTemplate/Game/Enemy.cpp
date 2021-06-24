#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード
		//↑2階層上にディレクトリを移動してからフォルダを潜っている。


namespace
{
	const int PRIORITY_0 = 0;	//優先度0

	const int RES_POS_NUM = 10;	//リスポーン位置の総数
	//敵の各リスポーン位置
	const Vector3 ENE_RES_POS_1 = { -150.0f,200.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,200.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,200.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,200.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 0.0f,200.0f,0.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,200.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 150.0f,200.0f,150.0f };

	const int STAGE3 = 3;		//ステージ番号
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>("titlescene");
	m_gameScene  = FindGO<GameScene>("gamescene");
	m_player	 = FindGO<Player>("player");
	m_stageSelectScene = FindGO<StageSelectScene>("stageselectscene");

	//敵のリスポーン位置１～１０
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

	//リスポーン座標がプレイヤー1P～4Pの座標と同じにならないようにしないといけない。
	//【プレイヤーのリスポーン位置】
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	m_randEneResAngle[0] = 1.0f;
	m_randEneResAngle[1] = 2.5f;
	m_randEneResAngle[2] = 3.7f;
	m_randEneResAngle[3] = 5.5f;

	//敵の最大数繰り返す
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		//敵モデルオブジェクト生成
		m_enemy[i] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//モデルのファイルパスを設定
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//敵モデル
		//初期座標(リスポーン座標)の設定。
		if (i == Enemy1)
		{
			m_enePos[Enemy1] = m_ranEneResPos[0];		//敵１の場所
		}
		else if (i == Enemy2)
		{
			m_enePos[Enemy2] = m_ranEneResPos[1];		//敵２の場所
		}
		else if (i == Enemy3)
		{
			m_enePos[Enemy3] = m_ranEneResPos[3];		//敵3の場所
		}
		else if (i == Enemy4)
		{
			m_enePos[Enemy4] = m_ranEneResPos[4];		//敵4の場所
		}
		else if (i == Enemy5)
		{
			m_enePos[Enemy5] = m_ranEneResPos[7];		//敵5の場所
		}
		else if (i == Enemy6)
		{
			m_enePos[Enemy6] = m_ranEneResPos[9];		//敵6の場所
		}
		//大きさを少し小さくする
		m_enemy[i]->SetScale({0.7f,0.7f,0.7f});

		//当たり判定のイニシャライズ(初期化)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
		//４で初期化。４は特にターゲット無し。
		m_pushPlayer[i] = 4;

		//落下したときの撃墜エフェクトの初期化。
		m_shootDownEffect[i].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
		//大きさ調整
		m_shootDownEffect[i].SetScale({ 40.0f,40.0f,40.0f });
		//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
		Quaternion m_shootDownEffectRot = m_shootDownEffect[i].GetRotation();
		//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
		m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
		m_shootDownEffect[i].SetRotation(m_shootDownEffectRot);
	}

	//Start関数のreturn文
	return true;
}


Enemy::~Enemy()
{
	//全ての敵を削除。
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}


void Enemy::Update()
{
	//全敵分ループ
	for (int i = Enemy1; i < MaxEnemyNum; i++)
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

					//プレイヤーが敵とぶつかったとき敵に押される処理
					PlaAndEneClash(i);

					//DA攻撃処理
					EneDA(i);

					//キャラクターコントローラーを使った移動処理に変更。
					m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);

					//プレイヤーの座標をリスポーン座標に移動
					EneResporn(i);

					m_enePos[i] += m_moveSpeed[i];
				}
			}
			else
			{
				//重力の影響を与える
				m_moveSpeed[i].y -= 0.2f;
				//キャラクターコントローラーを使った移動処理に変更。
				m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}

			//敵の位置と回転情報を更新
			EneDataUpdate(i);
		}
	}
}


//敵の位置,回転情報を更新する関数
void Enemy::EneDataUpdate(int x)
{
	m_enemy[x]->SetRotation(m_rot[x]);		//回転情報更新
	m_enemy[x]->SetPosition(m_enePos[x]);	//位置情報更新
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

	//一番近い距離(m_mostShortKyori[0])のように並び替え(ソート)
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

	//一番近いプレイヤーから敵のベクトルを正規化して方向だけの情報にする
	m_mostShortKyori[0].Normalize();
}


//敵のDA処理関数
void Enemy::EneDA(int x)
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
		m_CTTime[x]++;

		//摩擦を加えていく
		EneFriction(x);
	}
	//CTのカウントが120秒～140秒のとき、
	if (m_CTTime[x] == m_eneCTCount[x]) {

		//CTフラグを下ろす
		m_isCtFlg[x] = false;

		//CTのカウントを0にする
		m_CTTime[x] = 0;
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

	m_eneDir[x] = m_moveSpeed[x];
	m_eneDir[x].Normalize();
}


//敵のリスポーン処理関数
void Enemy::EneResporn(int x)
{
	if (m_enePos[x].y < -1000.0f)
	{
		//撃墜エフェクト再生開始。
		m_shootDownEffect[x].Play();
		//撃墜エフェクトの位置を敵が落ちた位置に設定
		m_shootDownEffect[x].SetPosition(m_enePos[x]);
		//更新
		m_shootDownEffect[x].Update();

		//ランダムでリスポーン位置を入れる
		m_enePos[x] = m_ranEneResPos[rand() % RES_POS_NUM];
		//ランダムでリスポーン回転を入れる
		m_rotAngle[x] = m_randEneResAngle[rand() % 4];

		//位置をセット
		m_enemy[x]->SetPosition(m_enePos[x]);

		//回転情報をセットする
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
		m_enemy[x]->SetRotation(m_rot[x]);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[x].SetPosition(m_enePos[x]);

		//スピードを0にする
		m_moveSpeed[x] = { Vector3::Zero };

		//キャラクターコントローラーを使った移動処理に変更。
		m_enePos[x] = m_charaCon[x].Execute(m_moveSpeed[x], 1.0f);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきたプレイヤーのナンバー
		//y=5にして、5の時は落としてきたプレイヤーのスコアを+10ptするようにする。
		m_gameScene->GetPlayerAddScore(m_pushPlayer[x], 5);
	}
}


//敵の摩擦処理関数
void Enemy::EneFriction(int x)
{
	//摩擦力を設定する
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -1.5f;
	//アイスステージが選択されているとき、
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//摩擦が一切ない変数を定義
		Vector3 m_stage3Friction = { Vector3::Zero };
		//摩擦を0にする
		m_friction[x] = m_stage3Friction;
	}
	//摩擦力を加算する
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーと敵がぶつかったときの処理関数
void Enemy::PlaAndEneClash(int x)
{
	for (int u = 0; u < m_player->GetPlaNum(); u++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_player->GetPlaPos(u) - m_enePos[x];

		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 40.0f)
		{
			if (m_player->GetPlaisTyazi1Flg(u) == true) {
				m_samDir[x] = m_eneDir[x] * -1.0f + m_player->GetPlaDir(u);
				m_samDir[x].Normalize();
				m_moveSpeed[x] = m_samDir[x] * 20.0f;

			}
			if (m_player->GetPlaisTyazi2Flg(u) == true) {

				m_samDir[x] = m_eneDir[x] * -1.0f + m_player->GetPlaDir(u);
				m_samDir[x].Normalize();
				m_moveSpeed[x] = m_samDir[x] * 30.0f;

			}
			//最後に押してきたプレイヤーを記録
			m_pushPlayer[x] = u;
		}
	}
}


//敵にかかる重力を設定する関数
void Enemy::Gravity(int x)
{
	//重力の影響を与える
	m_moveSpeed[x].y -= 0.2f;
}