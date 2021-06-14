#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	m_stage[0] = NewGO<SkinModelRender>(0);
	//ステージ１をロード
	m_stage[0]->Init("Assets/modelData/bg/stage_00.tkm");

	//メッシュコライダーを初期化。
	m_meshCollider.CreateFromModel(m_stage[0]->GetModel(), m_stage[0]->GetModel().GetWorldMatrix());

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	rbInitData.collider = &m_meshCollider;
	m_rigidBody.Init(rbInitData);
	//線形移動する要素を設定する。0を指定した軸は移動しない。
	//つまり、当たり(剛体)判定固定
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);

	return true;
}

Stage::~Stage()
{

}

void Stage::Update()
{
	//物理的な動きはしないからUpdate関数内はなにもなし。
}