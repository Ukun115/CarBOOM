#pragma once


class Stage : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	SkinModelRender* m_stage[1] = { nullptr };	//�S�X�e�[�W���p��


	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�N���X���쐬

public:

	bool Start() override;
	~Stage()override;
	void Update() override;
};