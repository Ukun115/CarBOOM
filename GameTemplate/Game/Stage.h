#pragma once
class Stage : public IGameObject
{
public:
	bool Start() override;
	~Stage()override;
	void Update() override;

private:
	SkinModelRender* m_stage[1] = { nullptr };

	//静的物理オブジェクト
	PhysicsStaticObject m_physicsStaticObject;
};