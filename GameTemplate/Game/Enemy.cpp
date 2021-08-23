///<<summary>
///敵NPCのメイン処理
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
#include "EnemyMoveSpeedArrow.h"
#include "EnemyTurn.h"
#include "EnemyEffect.h"
#include "EnemyMoveSpeed.h"
#include "EnemyPatoLump.h"

//TODO: 影を落とせるようにする

namespace nsCARBOOM
{
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
		const int TIME0 = 0;
		const float DELTATIME = 1.0f;
		const float MAX_FALL_POSITION = -1000.0f;
		const float CHARACON_RADIUS = 15.0f;
		const float CHARACON_HEIGHT = 85.0f;
		const float FRICTION_POWER = -1.5f;
		const float REDUCE_FRICTION_POWER = 2.0f;
		const int MOST_SHORT_DIR_NUM = 0;
		const float FALLSOUND_PLAYBACK_HEIGHT = -10.0f;
	}

	bool Enemy::Start()
	{
		//インスタンスを探す。
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		m_enemyEffect = NewGO<EnemyEffect>(nsStdafx::PRIORITY_0, nullptr);

		m_enemyPatoLump = NewGO<EnemyPatoLump>(nsStdafx::PRIORITY_0, nullptr);

		//敵のリスポーン位置
		for (int resPosNum = ResPos1; resPosNum < TotalResPos; resPosNum++)
		{
			m_ranEneResPos[resPosNum] = WhatEneRandomResPos(resPosNum);
		}

		m_enemyTurn = NewGO<EnemyTurn>(nsStdafx::PRIORITY_0, nsStdafx::ENEMYTURN_NAME);

		//敵の最大数繰り返す
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//敵モデルオブジェクト生成
			m_enemy[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
			//モデルのファイルパスを設定
			m_enemy[eneNum]->Init("LowPoly_PoliceCar");	//敵モデル

			//初期座標(リスポーン座標)の設定。
			m_enePos[eneNum] = m_ranEneResPos[eneNum];		//敵１の場所
			//m_skinModelRenderArrow[WhatEnemyNum(eneNum)]->Init("Arrow");	//矢印

			//当たり判定のイニシャライズ(初期化)
			m_charaCon[eneNum].Init(nsEnemy::CHARACON_RADIUS, nsEnemy::CHARACON_HEIGHT, m_enePos[eneNum]);
			//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
			m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
			//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
			m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));

			m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));		//回転情報更新
		}

		m_enemyMoveSpeed = NewGO<EnemyMoveSpeed>(nsStdafx::PRIORITY_0, nullptr);

		//デバック用の敵移動ベクトルの矢印の初期化
		m_enemyMoveSpeedArrow = NewGO<EnemyMoveSpeedArrow>(nsStdafx::PRIORITY_0, nullptr);

		return true;
	}

	Enemy::~Enemy()
	{
		//全ての敵を削除。
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			if (m_enemy[eneNum] != nullptr)
			{
				DeleteGO(m_enemy[eneNum]);
			}
		}
		//敵の移動ベクトル矢印を削除
		DeleteGO(m_enemyMoveSpeedArrow);

		DeleteGO(m_enemyEffect);
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

		m_enemyPatoLump->PoiLigNumInit();

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
					m_enemyTurn->EneTurn(eneNum);

					//プレイヤーが敵とぶつかったとき敵に押される処理
					PlaAndEneClash(eneNum);

					//DA攻撃処理
					EneDA(eneNum);

					//プレイヤーの座標をリスポーン座標に移動
					EneResporn(eneNum);

					m_enePos[eneNum] += m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
				}
			}

			//重力の影響を与える
			m_enemyMoveSpeed->Gravity(eneNum);

			bool isHitGround;
			Vector3 hitGroundNormal;
			m_moveSpeed[eneNum] = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
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
		m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));		//回転情報更新
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
					m_CenterToEneAngle[eneNum] = m_centerKyori[eneNum].Dot(m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM]);
					m_CenterToSettenAngle[eneNum] = m_centerKyori[eneNum].Dot(m_EneToSetten1Dir[eneNum]);

					if (m_CenterToEneAngle[eneNum] > m_CenterToSettenAngle[eneNum] && m_mostShortDistance[nsEnemy::MOST_SHORT_DIR_NUM].Length() > m_EneToSetten1[eneNum].Length())
					{
						m_PlayerToSetten1Angle[eneNum] = m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM].Dot(m_EneToSetten1Dir[eneNum]);
						m_PlayerToSetten2Angle[eneNum] = m_mostShortDistanceDir[nsEnemy::MOST_SHORT_DIR_NUM].Dot(m_EneToSetten2Dir[eneNum]);
						//接点１の方向か接点２の方向に行くかを判別
						m_enemyMoveSpeed->EneSettenMove(eneNum);
					}
					else
					{
						m_enemyMoveSpeed->EneNormalMove(eneNum);
					}
				}
				else
				{
					m_enemyMoveSpeed->EneNormalMove(eneNum);
				}

			}
			//ダッシュサウンド
			m_soundPlayBack->EnemySoundPlayBack(DashSound, eneNum);

			m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

			//CTをカウントするフラグを立てる
			m_canCtCountFlg[eneNum] = true;
		}
		//CTフラグが立ってるとき、
		if (m_canCtCountFlg[eneNum]) {

			//CTをカウントする
			m_CTTime[eneNum]++;

			//摩擦を加えていく
			m_enemyMoveSpeed->EneFriction(eneNum);
		}
		//CTのカウントが120秒～140秒のとき、
		if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

			//CTフラグを下ろす
			m_canCtCountFlg[eneNum] = false;

			//CTのカウントを0にする
			m_CTTime[eneNum] = nsStdafx::INT_ZERO;
		}
	}

	//敵のリスポーン処理関数
	void Enemy::EneResporn(const int eneNum)
	{
		//敵のY座標の位置が最大落下地点まで行ってなかったらreturn以降の処理は行わない
		if (m_enePos[eneNum].y >= nsEnemy::MAX_FALL_POSITION)
		{
			return;
		}

		//撃墜サウンド
		m_soundPlayBack->EnemySoundPlayBack(ShootDownSound, eneNum);

		m_enemyEffect->SetEnemyPos(m_enePos[eneNum],eneNum);
		m_enemyEffect->ShootDownEffectPlay(eneNum);

		//ランダムでリスポーン位置を入れる
		m_enePos[eneNum] = m_ranEneResPos[rand() % nsEnemy::RES_POS_NUM];
		if (m_stageSelectNum == nsStdafx::STAGE2)
		{
			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			//ランダムでリスポーン位置を入れる
			m_enePos[eneNum] = m_ranEneResPos[rand() % TotalResPos];
		}
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));

		m_enemyTurn->EneRespornAngleDecide(eneNum);

		//位置をセット
		m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);
		//回転情報をセットする
		m_enemy[eneNum]->SetRotation(m_enemyTurn->GetEneRot(eneNum));

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

		//スピードを0にする
		m_enemyMoveSpeed->EneMoveSpeedZero(eneNum);

		bool isHitGround;
		Vector3 hitGroundNormal;
		m_moveSpeed[eneNum] = m_enemyMoveSpeed->GetEneMoveSpeed(eneNum);
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

			if (m_player->GetPlaisTyazi1HanteiFlg(plaNum))
			{
				m_enemyMoveSpeed->EneCharge1Move(eneNum);
			}
			if (m_player->GetPlaisTyazi2HanteiFlg(plaNum))
			{
				m_enemyMoveSpeed->EneCharge2Move(eneNum);
			}
			//最後に押してきたプレイヤーを記録
			m_pushPlayer[eneNum] = plaNum;
		}
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

		if (m_enePos[eneNum].y > nsEnemy::FALLSOUND_PLAYBACK_HEIGHT || !m_canFallSoundPlayFlg[eneNum])
		{
			return;
		}
		//落ちる時に落下音を鳴らせる処理
		m_soundPlayBack->EnemySoundPlayBack(FallSound, eneNum);
		m_canFallSoundPlayFlg[eneNum] = false;
	}

	//
	Vector3 Enemy::WhatEneRandomResPos(const int eneResPosNum)
	{
		switch (eneResPosNum)
		{
		case ResPos1:
			return nsEnemy::ENE_RES_POS_1;
			break;
		case ResPos2:
			return nsEnemy::ENE_RES_POS_2;
			break;
		case ResPos3:
			return nsEnemy::ENE_RES_POS_3;
			break;
		case ResPos4:
			return nsEnemy::ENE_RES_POS_4;
			break;
		case ResPos5:
			return nsEnemy::ENE_RES_POS_5;
			break;
		case ResPos6:
			return nsEnemy::ENE_RES_POS_6;
			break;
		case ResPos7:
			return nsEnemy::ENE_RES_POS_7;
			break;
		case ResPos8:
			return nsEnemy::ENE_RES_POS_8;
			break;
		case ResPos9:
			return nsEnemy::ENE_RES_POS_9;
			break;
		case ResPos10:
			if (m_stageSelectNum == nsStdafx::STAGE2)
			{
				return nsEnemy::ENE_RES_POS_10;
			}
			break;
		}
	}
}