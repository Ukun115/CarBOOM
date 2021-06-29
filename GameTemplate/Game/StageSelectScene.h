#pragma once
class TitleScene;


class StageSelectScene : public IGameObject
{
private:

	SkinModelRender* m_stage[5] = { nullptr };	//�S�X�e�[�W���p��
	SpriteRender* m_stageName[5] = { nullptr };	//�S�X�e�[�W���p��
	SkinModelRender* m_pla = nullptr;	//�v���C���[
	TitleScene* m_titleScene = nullptr;
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_Ahukidasi[4] = { nullptr };


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCanGameStartFlg = true;


	int m_stageNum = 1;				//�ǂ̃X�e�[�W��I�����Ă��邩���i�[
	Vector3 m_stagePos[5];			//�X�e�[�W�̈ʒu
	Vector3    m_pos;				//�v���C���[�̈ʒu
	Quaternion m_rot;				//�v���C���[�̉�]
	Vector3 m_moveSpeed;			//�ړ����x
	float m_leftStick_x;			//���X�e�B�b�N��x���͗�
	float m_leftStick_y;			//���X�e�B�b�N��y���͗�
	float m_rotAngle;				//��]�p�x
	Vector3 m_friction;				//���C
	Vector3 m_diff = { 0,0,0 };		//�X�e�[�W�ƃv���C���[�Ƃ̋���
	Vector3 m_AhukidasiPos[4];


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
		RandomStage,
		TotalStageNum
	};


	bool Start()override;
	~StageSelectScene()override;
	void Update()override;


	//�Q�[����ʑJ�ڏ����֐�
	void GameSceneTransition();
	//�v���C���[�̒ʏ�ړ������֐�
	void PlaMove();
	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void PlaSpeedCorrection();
	//�v���C���[�̉�]�����֐�
	void PlaTurn();
	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void PlaDataUpdate();
	//�X�e�[�W�̏�ɂ���Ƃ����̃X�e�[�W��I���ł���֐�
	void TouchStage();
	//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���֐�
	void AvoidScreenOutSide();


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�I�����ꂽ�X�e�[�W�ԍ��𓾂�֐�
	int GetStageNum() { return m_stageNum; };
};