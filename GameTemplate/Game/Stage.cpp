///<<summary>
///ステージ表示とステージごとの処理クラス
///</summary>


#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Player.h"
#include "Enemy.h"
#include <random>


namespace
{
	const int SNOW1 = 0;
	const int SNOW2 = 1;
}


bool Stage::Start()
{
	//インスタンスを探す
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_player = FindGO<Player>(PLAYER_NAME);
	//ステージモデルオブジェクト生成
	m_stage = NewGO<SkinModelRender>(PRIORITY_0,nullptr);

	//選択されたのがどひょうステージのとき、
	if (m_stageSelectScene->GetStageNum() == Stage1)
	{
		//どひょうステージをロード
		m_stage->Init("Assets/modelData/bg/stage_1.tkm");
	}
	//選択されたのがドーナツステージのとき、
	if (m_stageSelectScene->GetStageNum() == Stage2)
	{
		//ドーナツステージをロード
		m_stage->Init("Assets/modelData/bg/stage_2.tkm");
	}
	//選択されたのがアイスステージのとき、
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		//アイスステージをロード
		m_stage->Init("Assets/modelData/bg/stage_3.tkm");

		for (int snowEffectNum = 0; snowEffectNum < 2; snowEffectNum++)
		{
			//降る雪エフェクトの初期化。
			m_fallSnowEffect[snowEffectNum].Init(u"Assets/effect/efk/Snow.efk");
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
	if (m_stageSelectScene->GetStageNum() == Stage4)
	{
		//風ステージをロード
		m_stage->Init("Assets/modelData/bg/stage_4.tkm");

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> windNum(0, 3);		//最初の風の向きもランダムにする

		m_windDirection = windNum(mt);
	}

	//選択されたのがかたむきステージの時
	if (m_stageSelectScene->GetStageNum() == Stage5) {

		//かたむきステージをロード
		m_stage->Init("Assets/modelData/bg/stage_5.tkm");
	}

	//当たり判定を適応
	m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

	//Start関数のreturn文
	return true;
}


Stage::~Stage()
{
	//ステージを削除
	DeleteGO(m_stage);
}


void Stage::Update()
{
	//選択されたステージがアイスステージのとき、
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		//雪エフェクト処理
		SnowFall();
	}
	if (m_stageSelectScene->GetStageNum() == Stage4)
	{
		//風の影響を与える
		WindStage();
	}

	if (m_stageSelectScene->GetStageNum() == Stage5)
	{
		//傾かせる
		Tilt();
	}
}


//雪エフェクト処理関数
void Stage::SnowFall()
{
	if (m_fallSnowTimer == 0)
	{
		//1つ目の降る雪エフェクト再生開始。
		m_fallSnowEffect[SNOW1].Play();
		//更新
		m_fallSnowEffect[SNOW1].Update();
	}
	if (m_fallSnowTimer == 200)
	{
		//2つ目の降る雪エフェクト再生開始。
		m_fallSnowEffect[SNOW2].Play();
		//更新
		m_fallSnowEffect[SNOW2].Update();
	}
	if (m_fallSnowTimer == 400)
	{
		//タイマーを戻す
		m_fallSnowTimer = 0;
	}

	//タイマー加算
	m_fallSnowTimer++;
}


void Stage::WindStage()
{
	//風ステージが選択されている場合、風の影響を与える
	if (m_stageSelectScene->GetStageNum() == STAGE4)
	{
		//10秒毎にプレイヤーに風の影響を与える角度を決める(ランダム)
		//while (m_game_Scene->GetNowTime() == 0) {
		//	for(int i = 3600; i)
		//}

		//１０秒ごとに風の向きを変える。
		for (int s = 1; s <= 6; s++) {
			if (m_gameScene->GetNowTime() == s * 10) {
				//ここで、乱数を使用して、ランダムに風の向きを決める。
				//いいかんじに、前の風の向きと変わるようにする。
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<int> windNum(0, 3);


				int w = windNum(mt);	//新しい風

				if (w == m_windDirection) {
					if (m_windDirection == 3) {
						m_windDirection = 0;		//5番目の風が生まれてしまうので阻止!
					}
					else {

						m_windDirection += 1; //被らないように
					}
				}
				else {
					m_windDirection = w;	//被ってなかったらそのまま大丈夫。
				}
			}
		}
	}
}

void Stage::Tilt()
{
	//ステージを傾けるためにステージの中心からプレイヤーまでの距離を測る
	for (int i = 0; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		m_plaPos[i] = m_player->GetPlaPos(i);
	}
}