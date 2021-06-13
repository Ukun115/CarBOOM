#include "stdafx.h"
#include "PhysicsEnemy.h"

bool PhysicsEnemy::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/LowPoly_PoliceCar.tkm");

	//コライダーを初期化。
	Vector3 boxcollider = { 18.0f,10.0f,40.0f };
	m_boxCollider.Create(boxcollider);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	//rbInitData.mass = 3.0f;
	rbInitData.collider = &m_boxCollider;
	//rbInitData.pos.y = 100.0f;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(
		0.0f,
		0.0f,
		0.0f
	);
	m_rigidBody.Init(rbInitData);
	//摩擦力を設定する。0～10
	m_rigidBody.SetFriction(0.1f);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

	return true;
}
void PhysicsEnemy::Update()
{
	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	//剛体に力を加える。
	Vector3 force;
	//力を加える
	m_rigidBody.AddForce(
		force,		//力
		g_vec3Zero	//力を加える剛体の相対位置
	);
}