#pragma once
class Stage : public IGameObject
{
public:
	bool Start() override;
	~Stage();
	void Update() override;

private:
	SkinModelRender* m_skinModelRender = nullptr;
	MeshCollider m_meshCollider;	//メッシュコライダー
	RigidBody m_rigidBody;			//リジッドボディ
};