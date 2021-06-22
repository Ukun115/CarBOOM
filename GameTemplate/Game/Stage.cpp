#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
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

}