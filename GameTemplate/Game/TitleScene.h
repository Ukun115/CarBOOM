#pragma once
class StageSelectScene;
class Fade;


class TitleScene : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
{
private:
	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enPlayer
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		TotalPlaNum	//�v���C���[�̍ő吔
	};

	enum enSoundNum
	{
		TitleSceneGingle,	//�^�C�g���W���O��
		TitleSceneBGM,		//�^�C�g���V�[����BGM
		DecideSound,		//���艹
		EngineSound,		//�G���W���T�E���h
		TotalSoundNum
	};

	enum enFadeState
	{
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};
	enum enFadeNum
	{
		FadeIn,
		FadeOut,
		TotalFadeNum
	};

	enum enNextScene
	{
		StateSelectScene,
		GameEnd
	};


	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	Fade* m_fade[TotalFadeNum] = { nullptr };
	SoundPlayBack* m_soundPlayBack = nullptr;
	StageSelectScene* m_stageSelectScene = { nullptr };
	SpriteRender* m_titleSprite = { nullptr };
	SpriteRender* m_titleBaraBaraSprite[9] = { nullptr };
	SpriteRender* m_titleNameSprite = { nullptr };
	SpriteRender* m_pushStartButtonSprite = { nullptr };
	SpriteRender* m_plaActiveName[TotalPlaNum] = { nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_plaDeactiveName[TotalPlaNum] = { nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_pressASpeechBalloon = { nullptr };
	SpriteRender* m_pressASpeechBalloonArrow = { nullptr };
	FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isAddPlayerFlg[TotalPlaNum] = { false };		//�e�v���C���[���o�^����Ă��邩�̔��ʃt���O
	bool m_enableUpdateFlg = { true };			//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������
	bool m_isFlashingFontActiveFlg = { true };		//true�̂Ƃ��_�ŕ����̕\���^�C�~���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_flashingFontTimer = { nsStdafx::INT_ZERO };		//�_�ŕ����̕\����\���̐؂�ւ��^�C�}�[
	int m_sideMoveTimer = nsStdafx::INT_ZERO;
	int m_waveTimer = nsStdafx::INT_ZERO;
	int m_verticalMoveTimer[9] = { nsStdafx::INT_ZERO };


	float m_scaUpValue = 0.0f;
	Vector3 m_titleNameSca;
	unsigned int m_totalPlaNum = { 1 };			//�v���C���[�̍��v�����v��
	Vector3 m_pressASpeechBalloonPos;		//�v���C���[�ǉ������o���̈ʒu
	Vector3 m_arrowSca;
	Vector3 m_titleBaraBaraSpritePos[9];

	int m_nextScene = nsStdafx::INT_ZERO;

	char m_filePath[256];


	bool Start()override final;
	~TitleScene()override final;
	void Update()override final;


	//�v���C���[��ǉ�����֐�
	void AddPlayer();
	//�Q�[����ʂɑJ�ڂ���֐�
	void StageSelectSceneTransition();
	//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
	void FlashingFont();
	//�摜�����ړ�����֐�
	void SideMove(const int width, const float speed);
	//�摜���c�ړ�����֐�
	void VerticalMove(const int width, const float speed, const int spriteNum);
	//�^�C�g�������g�傷��֐�
	void TitleNameScaUp();
	//�^�C�g�������E�F�[�u������֐�
	void TitleNameWave();
	//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
	void PushStartButton(int plaNum);
	//�{�^���������ꂽ�Ƃ��̏����֐�
	void PushSelectButton(int plaNum);
	//�I�����ꂽ���̃V�[���ɍs�������֐�
	void NextScene();
	//PLAYER�t�H���g�̏��������܂Ƃ߂Ă���֐�
	void InitPlayerFont();
	//�^�C�g����ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	void InitTitleSceneImage();


public:
};