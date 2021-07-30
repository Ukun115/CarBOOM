///<<summary>
///ステージ表示とステージごとの処理クラス
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
		const int SNOW1 = 0;
		const int SNOW2 = 1;

		const float ENEMY_WIND_POWER = 0.02f;
		const float PLAYER_WIND_POWER = 0.05f;
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
			for (int snowEffectNum = 0; snowEffectNum < 2; snowEffectNum++)
			{
				//降る雪エフェクトの初期化。
				m_fallSnowEffect[snowEffectNum].Init(u"Snow");
				//エフェクトの大きさ調整
				m_fallSnowEffect[snowEffectNum].SetScale({ 10.0f,10.0f,10.0f });
				//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
				Quaternion m_shootDownEffectRot = m_fallSnowEffect[snowEffectNum].GetRotation();
				//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
				m_shootDownEffectRot.AddRotationX(-0);	//X軸を基点に、-1.5708rad(-90°)回転
				m_fallSnowEffect[snowEffectNum].SetRotation(m_shootDownEffectRot);
				//降る雪エフェクトの位置をプカメラの上位の位置に設定
				m_fallSnowEffect[snowEffectNum].SetPosition({ 0,500,0 });
			}
		}
		//選択されたのが風ステージの時
		if (m_stageSelectNum == Stage4)
		{
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<int> windNum(0, 3);		//最初の風の向きもランダムにする

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
		case 0:
			//1つ目の降る雪エフェクト再生開始。
			m_fallSnowEffect[nsStage::SNOW1].Play();
			//更新
			m_fallSnowEffect[nsStage::SNOW1].Update();
			break;
		case 200:
			//2つ目の降る雪エフェクト再生開始。
			m_fallSnowEffect[nsStage::SNOW2].Play();
			//更新
			m_fallSnowEffect[nsStage::SNOW2].Update();
			break;
		case 400:
			//タイマーを戻す
			m_fallSnowTimer = 0;
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
				std::uniform_int_distribution<int> windNum(0, 3);


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
		for (int eneNum = 0; eneNum < 6; eneNum++)
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
				m_enemy->AddWindPowerZ(eneNum, -nsStage::ENEMY_WIND_POWER);
				break;
			case RightWind:
				m_enemy->AddWindPowerZ(eneNum, nsStage::ENEMY_WIND_POWER);
				break;
			}
		}
		for (int plaNum = 0; plaNum < m_totalPlaNum; plaNum++)
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
				m_player->AddWindPowerZ(plaNum, -nsStage::PLAYER_WIND_POWER);
				break;
			case RightWind:
				m_player->AddWindPowerZ(plaNum, nsStage::PLAYER_WIND_POWER);
				break;
			}
		}
	}


	void Stage::Tilt()
	{
		//ステージを傾けるためにステージの中心からプレイヤーまでの距離を測る
		for (int i = 0; i < m_totalPlaNum; i++)
		{
			m_plaPos[i] = m_player->GetPlaPos(i);
		}
	}
}