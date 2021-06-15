#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	m_stage[0] = NewGO<SkinModelRender>(0);
	//ステージ１をロード
	m_stage[0]->Init("Assets/modelData/bg/stage_00.tkm");

	m_physicsStaticObject.CreateFromModel(*m_stage[0]->GetModel(), m_stage[0]->GetModel()->GetWorldMatrix());

	return true;
}

Stage::~Stage()
{

}

void Stage::Update()
{
	//物理的な動きはしないからUpdate関数内はなにもなし。
}