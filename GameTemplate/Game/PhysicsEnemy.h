#pragma once
class PhysicsEnemy : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
private:
	SkinModelRender* m_skinModelRender = nullptr;
	BoxCollider m_boxCollider;
	RigidBody m_rigidBody;
};