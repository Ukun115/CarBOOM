#pragma once
class Stage : public IGameObject
{
public:
	bool Start() override;
	~Stage()override;
	void Update() override;

private:
	SkinModelRender* m_stage[1] = { nullptr };

	//�ÓI�����I�u�W�F�N�g
	PhysicsStaticObject m_physicsStaticObject;
};