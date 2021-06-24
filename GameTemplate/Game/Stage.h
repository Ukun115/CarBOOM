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
	Effect m_fallSnowEffect[2];		//�A�C�X�X�e�[�W�̍~���Ă����G�t�F�N�g


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	int m_fallSnowTimer = 0;


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


	bool Start() override;
	~Stage()override;
	void Update() override;


public:

};