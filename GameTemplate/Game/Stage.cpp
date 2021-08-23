///<<summary>
///ステージ処理
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include <random>

namespace nsCARBOOM
{
	namespace nsStage
	{
		const float ENEMY_WIND_POWER = 0.02f;
		const float PLAYER_WIND_POWER = 0.05f;
		const Vector3 FALL_SNOW_EFFECT_SCALE = { 10.0f,10.0f,10.0f };
		const Vector3 FALL_SNOW_EFFECT_POS = { 0.0f,500.0f,0.0f };
		const int SNOW_FALL_TIMING1 = 0;
		const int SNOW_FALL_TIMING2 = 200;
		const int SNOW_FALL_TIMING3 = 2400;
	}

	bool Stage::Start()
	{
		//インスタンスを探す
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		//ステージモデルオブジェクト生成
		m_stage = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);

		sprintf(m_stageModelFilePath, "bg/stage_%d", m_stageSelectNum);
		m_stage->Init(m_stageModelFilePath);



		//選択されたのがアイスステージのとき、
		if (m_stageSelectNum == Stage3)
		{
			for (int snowEffectNum = Snow1; snowEffectNum < TotalSnowNum; snowEffectNum++)
			{
				//降る雪エフェクトの初期化。
				m_fallSnowEffect[snowEffectNum].Init(u"Assets/effect/efk/Snow.efk");
				//エフェクトの大きさ調整
				m_fallSnowEffect[snowEffectNum].SetScale({ nsStage::FALL_SNOW_EFFECT_SCALE });
				//降る雪エフェクトの位置をカメラの上位の位置に設定
				m_fallSnowEffect[snowEffectNum].SetPosition(nsStage::FALL_SNOW_EFFECT_POS);
			}
		}
		//選択されたのが風ステージの時
		if (m_stageSelectNum == Stage4)
		{
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<int> windNum(UpWind, RightWind);		//最初の風の向きもランダムにする

			m_windDirection = windNum(mt);
		}

		////選択されたのがかたむきステージの時
		//if (m_stageSelectNum == Stage5) {
		//	Quaternion qRotX, qRotZ, qRot;
		//	qRotX.SetRotationDegX(10.0f);
		//	qRotZ.SetRotationDegZ(40.0f);
		//	qRot.Multiply(qRotX, qRotZ);
		//	m_stage->SetRotation(qRot);
		//}

		//当たり判定を適応
		m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

		return true;
	}

	Stage::~Stage()
	{
		//ステージを削除
		DeleteGO(m_stage);
	}

	void Stage::Update()
	{
		//ポーズ中でないとき、
		if (m_isPauseFlg)
		{
			return;
		}
		//選択されたステージがアイスステージのとき、
		if (m_stageSelectNum == Stage3)
		{
			//雪エフェクト処理
			SnowFall();
		}
		if (m_stageSelectNum == Stage4)
		{
			//風の影響を与える
			WindInpact();
		}

		//if (m_stageSelectNum == Stage5)
		//{
		//	//傾かせる
		//	Tilt();
		//}
		//m_physicsStaticObject.Update(m_stage->GetPosition(), m_stage->GetRotation());
	}

	//雪エフェクト処理関数
	void Stage::SnowFall()
	{
		switch (m_fallSnowTimer)
		{
		case nsStage::SNOW_FALL_TIMING1:
			//1つ目の降る雪エフェクト再生開始。
			m_fallSnowEffect[Snow1].Play();
			//更新
			m_fallSnowEffect[Snow1].Update();
			break;
		case nsStage::SNOW_FALL_TIMING2:
			//2つ目の降る雪エフェクト再生開始。
			m_fallSnowEffect[Snow2].Play();
			//更新
			m_fallSnowEffect[Snow2].Update();
			break;
		case nsStage::SNOW_FALL_TIMING3:
			//タイマーを戻す
			m_fallSnowTimer = nsStdafx::INT_ZERO;
			break;
		}

		//タイマー加算
		m_fallSnowTimer++;
	}

	void Stage::WindInpact()
	{
		//風ステージが選択されている場合、風の影響を与える
		if (m_stageSelectNum != nsStdafx::STAGE4 || m_gameScene->GetCountDownFlg())
		{
			return;
		}

		//１０秒ごとに風の向きを変える。
		for (int s = 1; s <= 6; s++) {
			if (m_gameScene->GetNowTime() == s * 10) {
				//ここで、乱数を使用して、ランダムに風の向きを決める。
				//いいかんじに、前の風の向きと変わるようにする。
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<int> windNum(UpWind, RightWind);

				int w = windNum(mt);	//新しい風

				if (w == m_windDirection)
				{
					if (m_windDirection == 3)
					{
						m_windDirection = 0;		//5番目の風が生まれてしまうので阻止!
					}
					else
					{
						m_windDirection += 1; //被らないように
					}
				}
				else
				{
					m_windDirection = w;	//被ってなかったらそのまま大丈夫。
				}
			}
		}
		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//現在の風の向きに応じた処理
			switch (m_windDirection) {
			case UpWind://下から上への風
				m_enemy->AddWindPowerZ(eneNum, nsStage::ENEMY_WIND_POWER);
				break;
			case DownWind:
				m_enemy->AddWindPowerZ(eneNum, -nsStage::ENEMY_WIND_POWER);
				break;
			case LeftWind:
				m_enemy->AddWindPowerX(eneNum, -nsStage::ENEMY_WIND_POWER);
				break;
			case RightWind:
				m_enemy->AddWindPowerX(eneNum, nsStage::ENEMY_WIND_POWER);
				break;
			}
		}
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//現在の風の向きに応じた処理
			switch (m_windDirection) {
			case UpWind://下から上への風
				m_player->AddWindPowerZ(plaNum, nsStage::PLAYER_WIND_POWER);
				break;
			case DownWind:
				m_player->AddWindPowerZ(plaNum, -nsStage::PLAYER_WIND_POWER);
				break;
			case LeftWind:
				m_player->AddWindPowerX(plaNum, -nsStage::PLAYER_WIND_POWER);
				break;
			case RightWind:
				m_player->AddWindPowerX(plaNum, nsStage::PLAYER_WIND_POWER);
				break;
			}
		}
	}

	void Stage::Tilt()
	{
		//ステージを傾けるためにステージの中心からプレイヤーまでの距離を測る
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			m_plaPos[plaNum] = m_player->GetPlaPos(plaNum);
		}
	}
}