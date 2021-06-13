#pragma once
class Stage : public IGameObject
{
public:
	bool Start() override;
	~Stage();
	void Update() override;

private:
	SkinModelRender* m_skinModelRender = nullptr;
	MeshCollider m_meshCollider;	//���b�V���R���C�_�[
	RigidBody m_rigidBody;			//���W�b�h�{�f�B
};