#include "stdafx.h"
#include "PhysicsBall.h"

bool PhysicsBall::Start() 
{
	//モデルを初期化。
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/ball.tkm";
	initData.m_fxFilePath = "Assets/shader/model.fx";
	m_model.Init(initData);

	//コライダーを初期化。
	m_sphereCollider.Create(10.0f);
	
	//剛体を初期化。
	RigidBodyInitData rbInitData;
	rbInitData.mass = 3.0f;
	rbInitData.collider = &m_sphereCollider;
	rbInitData.pos.y = 100.0f;
	rbInitData.localInteria.Set(0.5f, 0.5f, 0.5f);
	m_rigidBody.Init(rbInitData);
	m_rigidBody.SetFriction(10.0f);
	return true;
}
void PhysicsBall::Update()
{
	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
	//剛体に力を加える。
	Vector3 linearVelocity;

	linearVelocity.x = -g_pad[0]->GetLStickXF() * 500.0f;
	linearVelocity.z = -g_pad[0]->GetLStickYF() * 500.0f;
	m_rigidBody.AddForce(linearVelocity, g_vec3Zero);
	m_rigidBody.SetLinearFactor( 1.0f, 1.0f, 0.0f );
	Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
	g_camera3D->SetTarget(pos);
	toCamere.y = 100.0f;
	g_camera3D->SetPosition(pos + toCamere);
}
void PhysicsBall::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}
