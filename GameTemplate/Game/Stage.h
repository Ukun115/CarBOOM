#pragma once
class StageSelectScene;


class Stage : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	SkinModelRender* m_stage = { nullptr };
	StageSelectScene* m_stageSelectScene;


	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�N���X���쐬


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	//�X�e�[�W�ԍ�
	enum StageNum
	{
		ehehe,	//Stage1���P�Ԃɂ��邽�߂�ehehe�����Ē���
		Stage1,
		Stage2,
		Stage3,
	};

public:

	bool Start() override;
	~Stage()override;
	void Update() override;
};