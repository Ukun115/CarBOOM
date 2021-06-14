#pragma once
class Stage : public IGameObject
{
public:
	bool Start() override;
	~Stage()override;
	void Update() override;

private:
	SkinModelRender* m_stage[1] = { nullptr };
	MeshCollider m_meshCollider;	//メッシュコライダー
	RigidBody m_rigidBody;			//リジッドボディ
};