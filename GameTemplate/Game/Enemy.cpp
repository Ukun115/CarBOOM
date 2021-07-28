///<<summary>
///敵NPC（パトカー）クラス
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード
		//↑2階層上にディレクトリを移動してからフォルダに潜っている。


//TODO: 影を落とせるようにする


namespace nsEnemy
{
	const int RES_POS_NUM = 10;	//リスポーン位置の総数
	//敵の各リスポーン位置
	const Vector3 ENE_RES_POS_1 = { -150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,150.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,150.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 0.0f,150.0f,0.0f };
	//敵の各リスポーン回転
	const float ENE_RES_ROT_1 = 1.0f;
	const float ENE_RES_ROT_2 = 2.5f;
	const float ENE_RES_ROT_3 = 3.7f;
	const float ENE_RES_ROT_4 = 5.5f;
	const float ENE_RES_ROT_5 = 0.5f;
	const float ENE_RES_ROT_6 = 1.25f;
	const float ENE_RES_ROT_7 = 1.85f;
	const float ENE_RES_ROT_8 = 2.85f;

	const float POILIG_RANGE = 50.0f;	//ポイントライトの影響範囲

	const int TIME0 = 0;

	const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };

	const float DELTATIME = 1.0f;
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
	m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
	m_light = FindGO<Light>(nsStdafx::LIGHT_NAME);
	m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);
	m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

	//敵のリスポーン位置１～１０
	m_ranEneResPos[ResPos1] = nsEnemy::ENE_RES_POS_1;
	m_ranEneResPos[ResPos2] = nsEnemy::ENE_RES_POS_2;
	m_ranEneResPos[ResPos3] = nsEnemy::ENE_RES_POS_3;
	m_ranEneResPos[ResPos4] = nsEnemy::ENE_RES_POS_4;
	m_ranEneResPos[ResPos5] = nsEnemy::ENE_RES_POS_5;
	m_ranEneResPos[ResPos6] = nsEnemy::ENE_RES_POS_6;
	m_ranEneResPos[ResPos7] = nsEnemy::ENE_RES_POS_7;
	m_ranEneResPos[ResPos8] = nsEnemy::ENE_RES_POS_8;
	m_ranEneResPos[ResPos9] = nsEnemy::ENE_RES_POS_9;
	if (m_stageSelectNum == nsStdafx::STAGE2)
	{
		m_ranEneResPos[ResPos10] = nsEnemy::ENE_RES_POS_10;
	}

	m_randEneResAngle[0] = nsEnemy::ENE_RES_ROT_1;
	m_randEneResAngle[1] = nsEnemy::ENE_RES_ROT_2;
	m_randEneResAngle[2] = nsEnemy::ENE_RES_ROT_3;
	m_randEneResAngle[3] = nsEnemy::ENE_RES_ROT_4;
	m_randEneResAngle[4] = nsEnemy::ENE_RES_ROT_5;
	m_randEneResAngle[5] = nsEnemy::ENE_RES_ROT_6;
	m_randEneResAngle[6] = nsEnemy::ENE_RES_ROT_7;
	m_randEneResAngle[7] = nsEnemy::ENE_RES_ROT_8;

	//敵の最大数繰り返す
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		//敵モデルオブジェクト生成
		m_enemy[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0,nullptr);
		//モデルのファイルパスを設定
		m_enemy[eneNum]->Init("LowPoly_PoliceCar");	//敵モデル

		//デバック用の敵スピードの矢印表示
		//m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

		//初期座標(リスポーン座標)の設定。
		switch (eneNum)
		{
		case Enemy1:
			m_enePos[Enemy1] = m_ranEneResPos[Enemy1];		//敵１の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		case Enemy2:
			m_enePos[Enemy2] = m_ranEneResPos[Enemy2];		//敵２の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		case Enemy3:
			m_enePos[Enemy3] = m_ranEneResPos[Enemy3];		//敵3の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		case Enemy4:
			m_enePos[Enemy4] = m_ranEneResPos[Enemy4];		//敵4の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		case Enemy5:
			m_enePos[Enemy5] = m_ranEneResPos[Enemy5];		//敵5の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		case Enemy6:
			m_enePos[Enemy6] = m_ranEneResPos[Enemy6];		//敵6の場所
			//m_skinModelRenderArrow[eneNum]->Init("Arrow");	//矢印
			break;
		}
		//当たり判定のイニシャライズ(初期化)
		m_charaCon[eneNum].Init(15.0f, 85.0f, m_enePos[eneNum]);
		//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));

		//落下したときの撃墜エフェクトの初期化。
		m_shootDownEffect[eneNum].Init(u"Enemy_ShootDown");
		//大きさ調整
		m_shootDownEffect[eneNum].SetScale(nsEnemy::SHOOTDOWNEFFECT_SCALE);
		//エフェクトが横倒しになっているのでこちらで調整
		Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
		//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
		m_shootDownEffectRot.AddRotationX(-1.5708f);	//X軸を基点に、-1.5708rad(-90°)回転
		m_shootDownEffect[eneNum].SetRotation(m_shootDownEffectRot);

		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8]; //敵の向き
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//回転情報更新
	}
	return true;
}


Enemy::~Enemy()
{
	//全ての敵を削除。
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		DeleteGO(m_enemy[eneNum]);
	}
}


void Enemy::Update()
{
	//ポーズ中のときアップデート処理を全て止める
	if (m_isPauseFlg)
	{
		return;
	}
	//制限時間が０秒になったらアップデート処理を全て止める
	if (m_gameScene->GetNowTime() == nsEnemy::TIME0)
	{
		return;
	}

	m_poiLigNum = nsStdafx::INT_ZERO;

	//全敵分ループ
	for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
	{
		//落下の際効果音を鳴らせる関数
		FallSoundPlayBack(eneNum);

		//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
		if (!m_gameScene->GetCountDownFlg())
		{
			//スタートした瞬間に敵がダッシュしてしまうのを回避する処理
			if (m_startDelayTimer < m_startDelay[eneNum])
			{
				//スタート時にDAを遅らせるタイマーを加算
				m_startDelayTimer++;
			}
			else
			{
				//回転処理
				EneTurn(eneNum);

				//プレイヤーが敵とぶつかったとき敵に押される処理
				PlaAndEneClash(eneNum);

				//DA攻撃処理
				EneDA(eneNum);

				//プレイヤーの座標をリスポーン座標に移動
				EneResporn(eneNum);

				//パトランプを敵の上にセットする関数
				PointLightSetting(eneNum);

				m_enePos[eneNum] += m_moveSpeed[eneNum];
			}
		}

		//ベクトルを可視化させるデバック関数
		//EneMooveSpeedDebug(eneNum);

		//重力の影響を与える
		Gravity(eneNum);

		bool isHitGround;
		Vector3 hitGroundNormal;
		//キャラクターコントローラーを使った移動処理に変更。
		m_enePos[eneNum] = m_charaCon[eneNum].Execute(
			m_moveSpeed[eneNum],
			nsEnemy::DELTATIME,
			isHitGround,
			hitGroundNormal
		);

		//敵の位置と回転情報を更新
		EneDataUpdate(eneNum);
	}
}


//敵の位置,回転情報を更新する関数
void Enemy::EneDataUpdate(const int eneNum)const
{
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//回転情報更新
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);	//位置情報更新
}


//敵から最寄りのプレイヤーを検索する関数
void Enemy::Distance(const int eneNum)
{
	//プレイヤーと敵との距離を測り一番近いプレイヤーを算出する
	DistanceOfPlaToEne(eneNum);

	//一番近いプレイヤーから敵のベクトルを正規化して方向だけの情報にする
	m_mostShortDistanceDir[0] = m_mostShortDistance[0];
	m_mostShortDistanceDir[0].Normalize();

	//ドーナツステージが選ばれていなかったらreturn以降は処理を行わない
	if (m_stageSelectNum != nsStdafx::STAGE2)
	{
		return;
	}

	m_centerKyori[eneNum] = m_center - m_enePos[eneNum];

	//ドーナツの穴の中心との距離が60.0f以上だったらreturn以降の処理を行わない
	if (m_centerKyori[eneNum].Length() <= 60.0f)
	{
		return;
	}

	if (!m_enePos[eneNum].x == nsStdafx::INT_ZERO && !m_enePos[eneNum].z == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = (m_hankei * m_enePos[eneNum].x + m_enePos[eneNum].z * powf(m_hankei * ((powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f) - m_hankei)), 1.0f / 2.0f)) / (powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f));
		m_settenPos1[eneNum].z = (m_hankei - m_enePos[eneNum].x * m_settenPos1[eneNum].x) / m_enePos[eneNum].z;
		m_settenPos2[eneNum].x = (m_hankei * m_enePos[eneNum].x - m_enePos[eneNum].z * powf(m_hankei * ((powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f) - m_hankei)), 1.0f / 2.0f)) / (powf(m_enePos[eneNum].x, 2.0f) + powf(m_enePos[eneNum].z, 2.0f));
		m_settenPos2[eneNum].z = (m_hankei - m_enePos[eneNum].x * m_settenPos2[eneNum].x) / m_enePos[eneNum].z;

	}
	else if (m_enePos[eneNum].x == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = (powf(m_hankei * (powf(m_enePos[eneNum].z, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].z);
		m_settenPos1[eneNum].z = m_hankei / m_enePos[eneNum].z;
		m_settenPos2[eneNum].x = (powf(m_hankei * (powf(m_enePos[eneNum].z, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].z) * (-1);
		m_settenPos2[eneNum].z = m_hankei / m_enePos[eneNum].z;

	}
	else if (m_enePos[eneNum].z == nsStdafx::INT_ZERO) {
		m_settenPos1[eneNum].x = m_hankei / m_enePos[eneNum].x;
		m_settenPos1[eneNum].z = (powf(m_hankei * (powf(m_enePos[eneNum].x, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].x);
		m_settenPos2[eneNum].x = m_hankei / m_enePos[eneNum].x;
		m_settenPos2[eneNum].z = (powf(m_hankei * (powf(m_enePos[eneNum].x, 2.0f) - m_hankei), 1.0f / 2.0f) / m_enePos[eneNum].x) * (-1);
	}

	m_EneToSetten1[eneNum] = m_settenPos1[eneNum] - m_enePos[eneNum];
	m_EneToSetten1[eneNum].y = nsStdafx::FLOAT_ZERO;
	m_EneToSetten1Dir[eneNum] = m_EneToSetten1[eneNum];
	m_EneToSetten1Dir[eneNum].Normalize();
	m_EneToSetten2[eneNum] = m_settenPos2[eneNum] - m_enePos[eneNum];
	m_EneToSetten2[eneNum].y = nsStdafx::FLOAT_ZERO;
	m_EneToSetten2Dir[eneNum] = m_EneToSetten2[eneNum];
	m_EneToSetten2Dir[eneNum].Normalize();
}


//敵のDA処理関数
void Enemy::EneDA(const int eneNum)
{
	if (!m_canCtCountFlg[eneNum]) {
		//距離設定
		Distance(eneNum);

		if (m_charaCon[eneNum].IsOnGround()) {

			//ドーナツステージが選択されたとき
			if (m_stageSelectNum == nsStdafx::STAGE2)
			{
				m_centerKyori[eneNum].y = nsStdafx::FLOAT_ZERO;
				m_centerKyori[eneNum].Normalize();
				m_CenterToEneAngle[eneNum] = m_centerKyori[eneNum].Dot(m_mostShortDistanceDir[0]);
				m_CenterToSettenAngle[eneNum] = m_centerKyori[eneNum].Dot(m_EneToSetten1Dir[eneNum]);

				if (m_CenterToEneAngle[eneNum] > m_CenterToSettenAngle[eneNum] && m_mostShortDistance[0].Length() > m_EneToSetten1[eneNum].Length())
				{
					m_PlayerToSetten1Angle[eneNum] = m_mostShortDistanceDir[0].Dot(m_EneToSetten1Dir[eneNum]);
					m_PlayerToSetten2Angle[eneNum] = m_mostShortDistanceDir[0].Dot(m_EneToSetten2Dir[eneNum]);
					//接点１の方向か接点２の方向に行くかを判別
					m_moveSpeed[eneNum] = (m_PlayerToSetten1Angle[eneNum] > m_PlayerToSetten2Angle[eneNum]) ? m_EneToSetten1Dir[eneNum] : m_EneToSetten2Dir[eneNum];
					m_moveSpeed[eneNum] *= 5.0f;
				}
				else
				{
					//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
					m_moveSpeed[eneNum] = m_mostShortDistanceDir[0] * 5.0f;
				}
			}
			else
			{
				//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
				m_moveSpeed[eneNum] = m_mostShortDistanceDir[0] * 5.0f;
			}

		}
		//ダッシュサウンド
		m_soundPlayBack->EnemySoundPlayBack(DashSound,eneNum);

		m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

		//CTをカウントするフラグを立てる
		m_canCtCountFlg[eneNum] = true;
	}
	//CTフラグが立ってるとき、
	if (m_canCtCountFlg[eneNum]) {

		//CTをカウントする
		m_CTTime[eneNum]++;

		//摩擦を加えていく
		EneFriction(eneNum);
	}
	//CTのカウントが120秒～140秒のとき、
	if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

		//CTフラグを下ろす
		m_canCtCountFlg[eneNum] = false;

		//CTのカウントを0にする
		m_CTTime[eneNum] = nsStdafx::INT_ZERO;
	}
}


//敵の回転処理関数
void Enemy::EneTurn(const int eneNum)
{
	//fabsf()は浮動小数点の絶対値を返す関数
	if (fabsf(m_moveSpeed[eneNum].x) < 0.001f && fabsf(m_moveSpeed[eneNum].z) < 0.001f)
	{
		return;
	}
	//回転角度
	m_rotAngle[eneNum] = atan2(m_moveSpeed[eneNum].x, m_moveSpeed[eneNum].z);

	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);

	m_eneDir[eneNum] = m_moveSpeed[eneNum];
	m_eneDir[eneNum].Normalize();
}


//敵のリスポーン処理関数
void Enemy::EneResporn(const int eneNum)
{
	//敵のY座標の位置が最大落下地点まで行ってなかったらreturn以降の処理は行わない
	if (m_enePos[eneNum].y >= -1000.0f)
	{
		return;
	}

	//撃墜サウンド
	m_soundPlayBack->EnemySoundPlayBack(ShootDownSound,eneNum);

	//撃墜エフェクト再生開始。
	m_shootDownEffect[eneNum].Play();
	//撃墜エフェクトの位置を敵が落ちた位置に設定
	m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
	//更新
	m_shootDownEffect[eneNum].Update();

	//ランダムでリスポーン位置を入れる
	m_enePos[eneNum] = m_ranEneResPos[rand() % nsEnemy::RES_POS_NUM];
	if (m_stageSelectNum == nsStdafx::STAGE2)
	{
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//ランダムでリスポーン位置を入れる
		m_enePos[eneNum] = m_ranEneResPos[rand() % 9];
	}
	//ランダム関数のSEED（種）を設定
	//（これによりランダム値を本当の意味でランダムにしている）
	srand((int)time(nullptr));
	//ランダムでリスポーン回転を入れる
	m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8];

	//位置をセット
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);

	//回転情報をセットする
	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);

	//キャラコンの座標にプレイヤーの座標をいれる
	m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

	//スピードを0にする
	m_moveSpeed[eneNum] = { Vector3::Zero };

	bool isHitGround;
	Vector3 hitGroundNormal;
	//キャラクターコントローラーを使った移動処理に変更。
	m_enePos[eneNum] = m_charaCon[eneNum].Execute(
		m_moveSpeed[eneNum],
		nsEnemy::DELTATIME,
		isHitGround,
		hitGroundNormal
	);

	m_canFallSoundPlayFlg[eneNum] = true;

	//落下時最後に触れた敵にポイントを与える
	m_gameScene->GetPlayerAddScoreNext(m_pushPlayer[eneNum]);
}


//敵の摩擦処理関数
void Enemy::EneFriction(const int eneNum)
{
	//摩擦力を設定する
	m_friction[eneNum] = m_moveSpeed[eneNum];
	m_friction[eneNum] *= -1.5f;

	///下のif文はステージの処理なのでステージクラスに移したい。
	//アイスステージが選択されているとき、
	if (m_stageSelectNum == nsStdafx::STAGE3)
	{
		//摩擦を減らす
		m_friction[eneNum] /= 2.0f;
	}

	//摩擦力を加算する
	m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーと敵がぶつかったときの処理関数
void Enemy::PlaAndEneClash(const int eneNum)
{
	for (int plaNum = nsStdafx::INT_ZERO; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_player->GetPlaPos(plaNum) - m_enePos[eneNum];

		//距離の長さが40.0fより大きかったら処理を行わない
		if (m_diff.Length() >= 40.0f)
		{
			return;
		}

		if (m_canPlaAndEneClashSoundPlayFlg[eneNum])
		{
			//衝突音4
			m_soundPlayBack->EnemySoundPlayBack(PlaAndEneClashSound, eneNum);

			m_canPlaAndEneClashSoundPlayFlg[eneNum] = false;
		}

		if (m_player->GetPlaisTyazi1HanteiFlg(plaNum)) {
			m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 20.0f;
		}
		if (m_player->GetPlaisTyazi2HanteiFlg(plaNum)) {

			m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 30.0f;

		}
		//最後に押してきたプレイヤーを記録
		m_pushPlayer[eneNum] = plaNum;
	}
}


//ベクトルを可視化させるデバック関数
void Enemy::EneMooveSpeedDebug(const int eneNum)
{
	Vector3 Dir = m_moveSpeed[eneNum];
	Dir.y = nsStdafx::INT_ZERO;
	Dir.Normalize();//大きさを位置にする
	float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
	Dir.z *= -1;
	float angleX = acosf(x);//アークコサイン
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[eneNum].SetRotationY(angleX);//ｘ度だけY軸を回す
	m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//角度を設定する
	m_arrowPos[eneNum] = m_enePos[eneNum];
	m_arrowPos[eneNum].y += 50.0f;
	m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[eneNum].Length() / 10;
	m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize);
}


//プレイヤーと敵との距離を測り一番近いプレイヤーを算出する関数
void Enemy::DistanceOfPlaToEne(const int eneNum)
{
	//登録されているプレイヤーの分処理をする
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		//プレイヤーの位置を取得
		m_plaPos[plaNum] = m_player->GetPlaPos(plaNum);
		//プレイヤーの位置と敵の位置の距離を取得
		m_mostShortDistance[plaNum] = m_plaPos[plaNum] - m_enePos[eneNum];
		m_mostShortDistance[plaNum].y = nsStdafx::FLOAT_ZERO;
	}
	//一番近い距離(m_mostShortDistance[0])のように並び替え(ソート)
	for (int plaNum = Player1; plaNum < m_totalPlaNum - 1; plaNum++) {
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_totalPlaNum; nextPlaNum++) {
			if (m_mostShortDistance[nextPlaNum].Length() < m_mostShortDistance[plaNum].Length()) {
				//交換
				Vector3 tmp = m_mostShortDistance[nextPlaNum];
				m_mostShortDistance[nextPlaNum] = m_mostShortDistance[plaNum];
				m_mostShortDistance[plaNum] = tmp;
			}
		}
	}
}


//落下時サウンドを鳴らす関数
void Enemy::FallSoundPlayBack(const int eneNum)
{
	//高さが-10以下のとき再生

	if (m_enePos[eneNum].y > -10.0f || !m_canFallSoundPlayFlg[eneNum])
	{
		return;
	}
	//落ちる時に落下音を鳴らせる処理
	m_soundPlayBack->EnemySoundPlayBack(FallSound, eneNum);
	m_canFallSoundPlayFlg[eneNum] = false;
}


//パトランプをパトカーの上にセットする関数
void Enemy::PointLightSetting(const int eneNum)
{
	//赤ポイントライトを設定
	m_enePoiLigPos = m_enePos[eneNum];
	m_enePoiLigPos.x -= 10.0f;
	m_enePoiLigPos.y += 10.0f;
	m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::RED, nsEnemy::POILIG_RANGE, m_poiLigNum);
	m_poiLigNum++;
	//青ポイントライトを設定
	m_enePoiLigPos = m_enePos[eneNum];
	m_enePoiLigPos.x += 10.0f;
	m_enePoiLigPos.y += 10.0f;
	m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::BLUE, nsEnemy::POILIG_RANGE, m_poiLigNum);
	m_poiLigNum++;
}