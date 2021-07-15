#pragma once
class TitleScene;
class GameScene;
class Fade;


class StageSelectScene : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	Light* m_light = nullptr;
	Fade* m_fadeOut = nullptr;
	Fade* m_fadeIn = nullptr;
	SkinModelRender* m_stage[7] = { nullptr };	//�S�X�e�[�W���p��
	SpriteRender* m_stageName[7] = { nullptr };	//�S�X�e�[�W���p��
	SpriteRender* m_stageDiscription[7] = { nullptr };	//�����w�i�摜�{�S�X�e�[�W���p��
	SpriteRender* m_operatorDiscription[7] = { nullptr };	//����������摜
	SpriteRender* m_stageSelectSprite = nullptr;
	SkinModelRender* m_pla = nullptr;	//�v���C���[
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_Ahukidasi[6] = { nullptr };
	SoundSource* m_carHorn = nullptr;	//�N���N�V�����T�E���h
	SoundSource* m_decideSound = nullptr;	//����T�E���h
	SoundSource* m_onStageSound = nullptr;	//�X�e�[�W�ɏ�����Ƃ��̃T�E���h
	SoundSource* m_titleBGM = nullptr;	//�^�C�g��BGM�T�E���h


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_enableUpdateFlg = true;
	bool m_canOnStageSoundPlayFlg[4] = { false };

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

	int m_totalPlaNum = 0;

	Vector3 m_stageDiscriptionLetterPos = { -370.0f,-20.0f,0.0f };
	bool m_isOperatorFlg[7] = { false };

	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow = nullptr;
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

	//�񋓌^
	enum enumState
	{
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
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
	/// �Z�b�^�[
	/// </summary>
	//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ���������Ă���
	void SetTotalPlaNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }


	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�I�����ꂽ�X�e�[�W�ԍ��𓾂�֐�
	 int GetStageNum() { return m_stageNum; };
};