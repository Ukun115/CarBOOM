#pragma once


class TitleScene;
class StageSelectScene;
class Stage;
class Player;
class Enemy;
class Fade;
class ResultScene;


class GameScene :public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enumPlayerNum
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		TotalPlaNum	//�v���C���[�̍ő吔
	};

	enum enumSoundNum
	{
		GameStartGingle,	//�Q�[���X�^�[�g�W���O��
		CountDownSound,		//�J�E���g�_�E���T�E���h
		GameBGM,			//�Q�[����BGM
		WhistleSound,		//�z�C�b�X���T�E���h
		PauseSound,			//�|�[�Y�T�E���h
		DecideSound,
		TotalSoundNum
	};


	//�񋓌^
	enum enumState
	{
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};
	enum enumFade
	{
		FadeIn,
		FadeOut,
		TotalFade
	};


	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	Light* m_light = nullptr;
	Fade* m_fade[TotalFade] = { nullptr };
	TitleScene* m_titleScene = { nullptr };
	StageSelectScene* m_stageSelectScene = { nullptr };
	ResultScene* m_resultScene = { nullptr };
	Stage* m_stage = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_ScoreFontRender[TotalPlaNum] = { nullptr };
	FontRender* m_TextScoreFontRender[TotalPlaNum] = { nullptr };
	FontRender* m_timeLimit = nullptr;
	FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };
	SpriteRender* m_sprite[TotalPlaNum] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_grayBack = nullptr;
	SpriteRender* m_gameBackScreen = nullptr;
	SpriteRender* m_pauseSprite = nullptr;
	SoundPlayBack* m_soundPlayBack = nullptr;


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isFinishCountDownFlg = true;
	bool m_deleteFlg = false;
	bool m_isPauseFlg = false;
	bool m_pauseOkFlg = true;

	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_resultsenniTimer = INT_ZERO;
	unsigned int m_countDownTimer = INT_ZERO;
	int m_timer = 3600;	//3600/60 = 60�b
	int m_countTime = INT_ZERO;


	int m_plaScore[TotalPlaNum] = { INT_ZERO };
	Vector2 m_plaScorePos[TotalPlaNum];
	unsigned int m_nowNumOnePla = TotalPlaNum;
	wchar_t text1[64];	//�������ԃt�H���g
	wchar_t text2[64];	//�v���C���[�X�R�A�t�H���g


	int m_totalPlaNum = INT_ZERO;
	int m_stageSelecttNum = INT_ZERO;


	bool Start()override final;
	~GameScene()override final;
	void Update()override final;


	//�������ԏ����֐�
	void TimeLimit();
	//�v���C���[�̃X�R�A�`��֐�
	void PlaScoreDraw();
	//�J�E���g�_�E�������֐�
	void CountDown();
	//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
	void SetScoreTextPos(const int plaNum);
	//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
	Vector2 GetScorePos(const int plaNum);
	//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
	Vector4 ScoreColor(const int plaNum);
	//�P�ʂɉ����摜�Ɖ������f����n���֐�
	void NowCrown();
	//���U���g��ʂɑJ�ڂ���֐�
	void ResultSceneTransition();
	//PLAYER�t�H���g�̏��������܂Ƃ߂Ă���֐�
	void InitPlayerFont();
	//�v���C���[�̃|�C���g�t�H���g�̏��������܂Ƃ߂Ă���֐�
	void InitPlayerPtFont();
	//�������ԃt�H���g�̏��������܂Ƃ߂Ă���֐�
	void InitTimeLimitFont();
	//�|�[�Y��ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	void InitPauseSceneImage();
	//�|�[�Y�@�\
	void PauseMenue();


public:

	/*�v���C���[�̓��_�ϓ������֐�
	(plaNum1�͗��Ƃ����v���C���[�AplaNum2�͎��ł����v���C���[)*/
	void GetPlayerAddScore(const int plaNum1, const int plaNum2);

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ�����X�e�[�W�Z���N�g�V�[���𒆌p�ɂ��Ď����Ă���
	void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	//�X�e�[�W�Ȃ�ڂ��I�΂�Ă��邩���Q�[���N���X�ɓn��
	void SetSelectStageNum(const int stageNum) { m_stageSelecttNum = stageNum ; }
	void SetDeleteFlg(const bool deleteFlg) { m_deleteFlg = deleteFlg; }

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//���݂̎c�萧�����Ԃ��擾����֐�
	int GetNowTime()const { return m_countTime; }
	//�Q�[���J�n�̃J�E���g�_�E�����I���������ǂ����̃t���O���擾����֐�
	bool GetCountDownFlg()const { return m_isFinishCountDownFlg; }
	//�v���C���[�̃X�R�A���擾����֐�
	int GetPlaScore(const int x)const { return m_plaScore[x]; };
	//���݂̂P�ʂ̃v���C���[���N�����擾
	int GetNumber1Player()const { return m_nowNumOnePla; }
};