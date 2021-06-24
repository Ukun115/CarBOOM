#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
	const int SNOW1 = 0;
	const int SNOW2 = 1;
}


bool Stage::Start()
{
	//インスタンスを探す
	m_stageSelectScene = FindGO<StageSelectScene>("stageselectscene");

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

		for (int i = 0; i < 2; i++)
		{
			//降る雪エフェクトの初期化。
			m_fallSnowEffect[i].Init(u"Assets/effect/efk/Snow.efk");
			//エフェクトの大きさ調整
			m_fallSnowEffect[i].SetScale({ 10.0f,10.0f,10.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			Quaternion m_shootDownEffectRot = m_fallSnowEffect[i].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-0);	//X軸を基点に、-1.5708rad(-90°)回転
			m_fallSnowEffect[i].SetRotation(m_shootDownEffectRot);
			//降る雪エフェクトの位置をプカメラの上位の位置に設定
			m_fallSnowEffect[i].SetPosition({ 0,500,0 });
		}
	}

	//当たり判定を適応
	m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

	//Start関数のreturn文
	return true;
}


Stage::~Stage()
{

}


void Stage::Update()
{
	if (m_stageSelectScene->GetStageNum() == Stage3)
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
}

//リザルト画面に遷移時降る雪が重い