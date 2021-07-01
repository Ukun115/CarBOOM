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
	const int RES_POS_NUM = 10;	//リスポーン位置の総数
	//敵の各リスポーン位置
	const Vector3 ENE_RES_POS_1 = { -150.0f,200.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,200.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,200.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,200.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 150.0f,200.0f,150.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,200.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,200.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 0.0f,200.0f,0.0f };

	const float POILIG_RANGE = 50.0f;	//ポイントライトの影響範囲

	const int TIME0 = 0;

	const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_gameScene  = FindGO<GameScene>(GAMESCENE_NAME);
	m_player	 = FindGO<Player>(PLAYER_NAME);
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);

	m_light = FindGO<Light>(LIGHT_NAME);

	//敵のリスポーン位置１～１０
	m_ranEneResPos[ResPos1] = ENE_RES_POS_1;
	m_ranEneResPos[ResPos2] = ENE_RES_POS_2;
	m_ranEneResPos[ResPos3] = ENE_RES_POS_3;
	m_ranEneResPos[ResPos4] = ENE_RES_POS_4;
	m_ranEneResPos[ResPos5] = ENE_RES_POS_5;
	m_ranEneResPos[ResPos6] = ENE_RES_POS_6;
	m_ranEneResPos[ResPos7] = ENE_RES_POS_7;
	m_ranEneResPos[ResPos8] = ENE_RES_POS_8;
	m_ranEneResPos[ResPos9] = ENE_RES_POS_9;
	if (m_stageSelectScene->GetStageNum() == STAGE2)
	{
		m_ranEneResPos[ResPos10] = ENE_RES_POS_10;
	}

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
	m_randEneResAngle[4] = 0.5f;
	m_randEneResAngle[5] = 1.25f;
	m_randEneResAngle[6] = 1.85f;
	m_randEneResAngle[7] = 2.85f;

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
			m_enePos[Enemy6] = m_ranEneResPos[8];		//敵6の場所
		}
		//当たり判定のイニシャライズ(初期化)
		m_charaCon[i].Init(15.0f, 85.0f, m_enePos[i]);
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[i] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[i] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
		//４で初期化。４は特にターゲット無し。
		m_pushPlayer[i] = 4;

		//落下したときの撃墜エフェクトの初期化。
		m_shootDownEffect[i].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
		//大きさ調整
		m_shootDownEffect[i].SetScale(SHOOTDOWNEFFECT_SCALE);
		//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
		Quaternion m_shootDownEffectRot = m_shootDownEffect[i].GetRotation();
		//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
		m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
		m_shootDownEffect[i].SetRotation(m_shootDownEffectRot);

		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		m_rotAngle[i] = m_randEneResAngle[rand() % 8]; //敵の向き
		m_rot[i].SetRotation(Vector3::AxisY, m_rotAngle[i]);
		m_enemy[i]->SetRotation(m_rot[i]);		//回転情報更新
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
	m_poiLigNum = 0;

	//全敵分ループ
	for (int i = Enemy1; i < MaxEnemyNum; i++)
	{
		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() != TIME0) {
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

					//赤ポイントライトを設定
					m_enePoiLigPos = m_enePos[i];
					m_enePoiLigPos.x -= 10.0f;
					m_enePoiLigPos.y += 10.0f;
					m_light->SetPointLightData(m_enePoiLigPos, RED, POILIG_RANGE, m_poiLigNum);
					m_poiLigNum++;
					//青ポイントライトを設定
					m_enePoiLigPos = m_enePos[i];
					m_enePoiLigPos.x += 10.0f;
					m_enePoiLigPos.y += 10.0f;
					m_light->SetPointLightData(m_enePoiLigPos, BLUE, POILIG_RANGE, m_poiLigNum);
					m_poiLigNum++;

					m_enePos[i] += m_moveSpeed[i];
				}
			}
			else
			{
				//重力の影響を与える
				Gravity(i);
				//キャラクターコントローラーを使った移動処理に変更。
				m_enePos[i] = m_charaCon[i].Execute(m_moveSpeed[i], 1.0f);
			}

			//敵の位置と回転情報を更新
			EneDataUpdate(i);
		}
	}
}


//敵の位置,回転情報を更新する関数
void Enemy::EneDataUpdate(int enenum)
{
	m_enemy[enenum]->SetRotation(m_rot[enenum]);		//回転情報更新
	m_enemy[enenum]->SetPosition(m_enePos[enenum]);	//位置情報更新
}


//敵から最寄りのプレイヤーを検索する関数
void Enemy::Distance(int enenum)
{
	//登録されているプレイヤーの分処理をする
	for (int i = 0; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		//プレイヤーの位置を取得
		m_plaPos[i] = m_player->GetPlaPos(i);
		//プレイヤーの位置と敵の位置の距離を取得
		m_mostShortKyori[i] = m_plaPos[i] - m_enePos[enenum];
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
void Enemy::EneDA(int enenum)
{
	if (m_isCtFlg[enenum] == false) {

		//CTをカウントするフラグを立てる
		m_isCtFlg[enenum] = true;

		//距離設定
		Distance(enenum);

		if (m_charaCon[enenum].IsOnGround()) {
			//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
			m_moveSpeed[enenum] = m_mostShortKyori[0] * 5.0f;
		}
	}
	//CTフラグが立ってるとき、
	if (m_isCtFlg[enenum] == true) {

		//CTをカウントする
		m_CTTime[enenum]++;

		//摩擦を加えていく
		EneFriction(enenum);
	}
	//CTのカウントが120秒～140秒のとき、
	if (m_CTTime[enenum] == m_eneCTCount[enenum]) {

		//CTフラグを下ろす
		m_isCtFlg[enenum] = false;

		//CTのカウントを0にする
		m_CTTime[enenum] = 0;
	}
}


//敵の回転処理関数
void Enemy::EneTurn(int enenum)
{
	//fabsf()は浮動小数点の絶対値を返す関数
	if (fabsf(m_moveSpeed[enenum].x) < 0.001f && fabsf(m_moveSpeed[enenum].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[enenum] = atan2(m_moveSpeed[enenum].x, m_moveSpeed[enenum].z);

	m_rot[enenum].SetRotation(Vector3::AxisY, m_rotAngle[enenum]);

	m_eneDir[enenum] = m_moveSpeed[enenum];
	m_eneDir[enenum].Normalize();
}


//敵のリスポーン処理関数
void Enemy::EneResporn(int enenum)
{
	if (m_enePos[enenum].y < -1000.0f)
	{
		//撃墜エフェクト再生開始。
		m_shootDownEffect[enenum].Play();
		//撃墜エフェクトの位置を敵が落ちた位置に設定
		m_shootDownEffect[enenum].SetPosition(m_enePos[enenum]);
		//更新
		m_shootDownEffect[enenum].Update();

		//ランダムでリスポーン位置を入れる
		m_enePos[enenum] = m_ranEneResPos[rand() % RES_POS_NUM];
		if (m_stageSelectScene->GetStageNum() == STAGE2)
		{
			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			//ランダムでリスポーン位置を入れる
			m_enePos[enenum] = m_ranEneResPos[rand() % 9];
		}
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//ランダムでリスポーン回転を入れる
		m_rotAngle[enenum] = m_randEneResAngle[rand() % 8];

		//位置をセット
		m_enemy[enenum]->SetPosition(m_enePos[enenum]);

		//回転情報をセットする
		m_rot[enenum].SetRotation(Vector3::AxisY, m_rotAngle[enenum]);
		m_enemy[enenum]->SetRotation(m_rot[enenum]);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[enenum].SetPosition(m_enePos[enenum]);

		//スピードを0にする
		m_moveSpeed[enenum] = { Vector3::Zero };

		//キャラクターコントローラーを使った移動処理に変更。
		m_enePos[enenum] = m_charaCon[enenum].Execute(m_moveSpeed[enenum], 1.0f);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきたプレイヤーのナンバー
		//y=5にして、5の時は落としてきたプレイヤーのスコアを+10ptするようにする。
		m_gameScene->GetPlayerAddScore(m_pushPlayer[enenum], 5);
	}
}


//敵の摩擦処理関数
void Enemy::EneFriction(int enenum)
{
	//摩擦力を設定する
	m_friction[enenum] = m_moveSpeed[enenum];
	m_friction[enenum] *= -1.5f;
	//アイスステージが選択されているとき、
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//摩擦を減らす
		m_friction[enenum] /= 2.0f;
	}
	//摩擦力を加算する
	m_moveSpeed[enenum].x += m_friction[enenum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[enenum].z += m_friction[enenum].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーと敵がぶつかったときの処理関数
void Enemy::PlaAndEneClash(int enenum)
{
	for (int u = 0; u < m_player->GetPlaNum(); u++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_player->GetPlaPos(u) - m_enePos[enenum];

		//距離の長さが30.0fより小さかったら、
		if (m_diff.Length() < 40.0f)
		{
			if (m_player->GetPlaisTyazi1Flg(u) == true) {
				m_samDir[enenum] = m_eneDir[enenum] * -1.0f + m_player->GetPlaDir(u);
				m_samDir[enenum].Normalize();
				m_moveSpeed[enenum] = m_samDir[enenum] * 20.0f;
			}
			if (m_player->GetPlaisTyazi2Flg(u) == true) {

				m_samDir[enenum] = m_eneDir[enenum] * -1.0f + m_player->GetPlaDir(u);
				m_samDir[enenum].Normalize();
				m_moveSpeed[enenum] = m_samDir[enenum] * 30.0f;

			}
			//最後に押してきたプレイヤーを記録
			m_pushPlayer[enenum] = u;
		}
	}
}


//敵にかかる重力を設定する関数
void Enemy::Gravity(int enenum)
{
	//重力の影響を与える
	m_moveSpeed[enenum].y -= GRAVITY;
}