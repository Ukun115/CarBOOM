#pragma once
class TitleScene;


class StageSelectScene : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	SkinModelRender* m_stage[7]{ nullptr };	//�S�X�e�[�W���p��
	SpriteRender* m_stageName[7]{ nullptr };	//�S�X�e�[�W���p��
	SkinModelRender* m_pla{ nullptr };	//�v���C���[
	TitleScene* m_titleScene{ nullptr };
	SpriteRender* m_titleSprite{ nullptr };
	SpriteRender* m_Ahukidasi[6]{ nullptr };
	SoundSource* m_carHorn{ nullptr };	//�N���N�V�����T�E���h
	SoundSource* m_decideSound{ nullptr };	//����T�E���h
	SoundSource* m_onStageSound{ nullptr };	//�X�e�[�W�ɏ�����Ƃ��̃T�E���h
	SoundSource* m_titleBGM{ nullptr };	//�^�C�g��BGM�T�E���h


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_enableUpdateFlg{ true };
	bool m_canOnStageSoundPlayFlg[4]{ false };


	int m_stageNum{ 1 };				//�ǂ̃X�e�[�W��I�����Ă��邩���i�[
	Vector3 m_stagePos[7];			//�X�e�[�W�̈ʒu
	Vector3    m_pos;				//�v���C���[�̈ʒu
	Quaternion m_rot;				//�v���C���[�̉�]
	Vector3 m_moveSpeed;			//�ړ����x
	float m_leftStick_x{ 0.0f };			//���X�e�B�b�N��x���͗�
	float m_leftStick_y{ 0.0f };			//���X�e�B�b�N��y���͗�
	float m_rotAngle{ 0.0f };				//��]�p�x
	Vector3 m_friction;				//���C
	Vector3 m_diff[4];		//�X�e�[�W�ƃv���C���[�Ƃ̋���
	Vector3 m_AhukidasiPos[6];


	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow{ nullptr };
	Vector3 m_arrowPos;
	Quaternion m_arrowRot;
	Vector3 m_arrowSize;


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
		Stage4,
		Stage5,
		RandomStage,
		TotalStageNum
	};

	enum SoundNum
	{
		TitleSceneBGM,
		DecideSound,
		OnStageSound,
		CarHornSound
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
	//�x�N�g��������������f�o�b�N�֐�
	void PlaMooveSpeedDebug();
	//�N���N�V������炷�֐�
	void CarHorn();
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum);


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�I�����ꂽ�X�e�[�W�ԍ��𓾂�֐�
	 int GetStageNum() { return m_stageNum; };
};