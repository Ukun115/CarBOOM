#include "stdafx.h"
#include "PhysicsEnemy.h"

bool PhysicsEnemy::Start()
{
	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->Init("Assets/modelData/LowPoly_PoliceCar.tkm");

	//�R���C�_�[���������B
	Vector3 boxcollider = { 18.0f,10.0f,40.0f };
	m_boxCollider.Create(boxcollider);

	//���̂��������B
	RigidBodyInitData rbInitData;
	//���ʂ�ݒ肷��B
	//rbInitData.mass = 3.0f;
	rbInitData.collider = &m_boxCollider;
	//rbInitData.pos.y = 100.0f;
	//��]�̂��₷����ݒ肷��B0�`1
	rbInitData.localInteria.Set(
		0.0f,
		0.0f,
		0.0f
	);
	m_rigidBody.Init(rbInitData);
	//���C�͂�ݒ肷��B0�`10
	m_rigidBody.SetFriction(0.1f);
	//���`�ړ�����v�f��ݒ肷��B
	//0���w�肵�����͈ړ����Ȃ��B
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

	return true;
}
void PhysicsEnemy::Update()
{
	//���̂̍��W�Ɖ�]���擾�B
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_skinModelRender->SetPosition(pos);
	m_skinModelRender->SetRotation(rot);
	//���̂ɗ͂�������B
	Vector3 force;
	//�͂�������
	m_rigidBody.AddForce(
		force,		//��
		g_vec3Zero	//�͂������鍄�̂̑��Έʒu
	);
}