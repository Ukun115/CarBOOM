#include "stdafx.h"
#include "Seesaw.h"

bool Seesaw::Start()
{
	//モデルを初期化。
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/seesaw.tkm";
	initData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(initData);

	//コライダーを初期化。
	Vector3 size;
	size.x = 100.0f;
	size.y = 10.0f;
	size.z = 40.0f;
	
	m_boxCollider.Create(size);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	rbInitData.mass = 10.0f;
	rbInitData.collider = &m_boxCollider;
	rbInitData.pos.y = 20.0f;
	rbInitData.localInteria.Set(0.0f, 0.0f, 0.0f);
	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(10.0f);
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);
	return true;
}
void Seesaw::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}
btVector3 angularVel = {0.0f, 0.0f, 0.0f};

void Seesaw::Update()
{
	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	auto rb = m_rigidBody.GetBody();

	if (fabsf(g_pad[0]->GetRStickXF()) > 0.0f) {
		angularVel.setValue(0.0f, 0.0f, g_pad[0]->GetRStickXF() * 2.0f);

	}
	//徐々に減衰
	angularVel *= 0.98f;
	rb->setAngularFactor(0.0f);
	rb->setAngularVelocity(angularVel);
	rb->activate();
	//剛体の座標と回転をモデルに反映。
	m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
}
