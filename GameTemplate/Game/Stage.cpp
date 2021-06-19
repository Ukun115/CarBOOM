#include "stdafx.h"
#include "Stage.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
}


bool Stage::Start()
{
	m_stage[0] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
	//ステージ１をロード
	m_stage[0]->Init("Assets/modelData/bg/stage_00.tkm");

	m_physicsStaticObject.CreateFromModel(*m_stage[0]->GetModel(), m_stage[0]->GetModel()->GetWorldMatrix());

	//Start関数のreturn文
	return true;
}


Stage::~Stage()
{

}


void Stage::Update()
{
	//物理的な動きはしないからUpdate関数内はなにもなし。
}