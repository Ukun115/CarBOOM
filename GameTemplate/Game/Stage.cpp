#include "stdafx.h"
#include "Stage.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
<<<<<<< HEAD

	const int STAGE_1 = 0;		//ステージ１の配列番号
=======
>>>>>>> remotes/origin/master
}


bool Stage::Start()
{
<<<<<<< HEAD
	//ステージ１モデルオブジェクト生成
	m_stage[STAGE_1] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
=======
	m_stage[0] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
>>>>>>> remotes/origin/master
	//ステージ１をロード
	m_stage[STAGE_1]->Init("Assets/modelData/bg/stage_00.tkm");

	//当たり判定を適応
	m_physicsStaticObject.CreateFromModel(*m_stage[STAGE_1]->GetModel(), m_stage[STAGE_1]->GetModel()->GetWorldMatrix());

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