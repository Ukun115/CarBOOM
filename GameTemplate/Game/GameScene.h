#pragma once

class Player;
class Enemy;
class Stage;
class TitleScene;
class ResultScene;
class Fade;
class StageSelectScene;


class GameScene :public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	Light* m_light = nullptr;
	Fade* m_fadeIn = nullptr;
	Fade* m_fadeOut = nullptr;
	TitleScene* m_titleScene = { nullptr };
	StageSelectScene* m_stageSelectScene = { nullptr };
	ResultScene* m_resultScene = { nullptr };
	Stage* m_stage = { nullptr };
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_grayBack = nullptr;
	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_timeLimit = nullptr;
	SoundSource* m_gameStartGingle = nullptr;	//�N���N�V�����T�E���h
	SoundSource* m_gameBGM = nullptr;	//�Q�[������BGM�T�E���h
	SoundSource* m_countDown = nullptr;	//�J�E���g�_�E���T�E���h
	SpriteRender* m_syutyusen = nullptr;
	SpriteRender* m_pauseSprite = nullptr;
	SoundSource* m_whistleSound = nullptr;
	SoundSource* m_pauseSound = nullptr;
	SoundSource* m_decideSound = nullptr;
	FontRender* m_PlaNameFont[4] = { nullptr };


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
	unsigned int m_resultsenniTimer = 0;
	unsigned int m_countDownTimer = 0;
	int m_timer = 360;	//3600/60 = 60�b
	int m_countTime = 0;


	int m_plaScore[4] = { 0 };
	Vector2 m_plaScorePos[4];
	unsigned int m_nowNumOnePla = 4;
	wchar_t text1[64];	//�������ԃt�H���g
	wchar_t text2[64];	//�v���C���[�X�R�A�t�H���g


	int m_totalPlaNum = 0;
	int m_stageSelecttNum = 0;


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enumPlayerNum
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		MaxPlayerNum	//�v���C���[�̍ő吔
	};

	enum enumSoundNum
	{
		GameStartGingle,	//�Q�[���X�^�[�g�W���O��
		CountDownSound,		//�J�E���g�_�E���T�E���h
		GameBGM,			//�Q�[����BGM
		WhistleSound,		//�z�C�b�X���T�E���h
		PauseSound,			//�|�[�Y�T�E���h
		DecideSound
	};


	//�񋓌^
	enum enumState
	{
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};


	bool Start()override;
	~GameScene()override;
	void Update()override;


	//�������ԏ����֐�
	void TimeLimit();
	//�v���C���[�̃X�R�A�`��֐�
	void PlaScoreDraw();
	//�J�E���g�_�E�������֐�
	void CountDown();
	//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
	void SetScoreTextPos(int plaNum);
	//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
	Vector2 GetScorePos(int plaNum);
	//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
	Vector4 ScoreColor(int plaNum);
	//�P�ʂɉ����摜�Ɖ������f����n���֐�
	void NowCrown();
	//���U���g��ʂɑJ�ڂ���֐�
	void ResultSceneTransition();
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum);


public:

	/*�v���C���[�̓��_�ϓ������֐�
	(plaNum1�͗��Ƃ����v���C���[�AplaNum2�͎��ł����v���C���[)*/
	void GetPlayerAddScore(int plaNum1, int plaNum2);

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ�����X�e�[�W�Z���N�g�V�[���𒆌p�ɂ��Ď����Ă���
	void SetTotalPlaNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	//�X�e�[�W�Ȃ�ڂ��I�΂�Ă��邩���Q�[���N���X�ɓn��
	void SetSelectStageNum(int stageNum) { m_stageSelecttNum = stageNum ; }
	void SetDeleteFlg(bool deleteFlg) { m_deleteFlg = deleteFlg; }

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//���݂̎c�萧�����Ԃ��擾����֐�
	int GetNowTime() { return m_countTime; }
	//�Q�[���J�n�̃J�E���g�_�E�����I���������ǂ����̃t���O���擾����֐�
	bool GetCountDownFlg() { return m_isFinishCountDownFlg; }
	//�v���C���[�̃X�R�A���擾����֐�
	int GetPlaScore(int x) { return m_plaScore[x]; };
	//���݂̂P�ʂ̃v���C���[���N�����擾
	int GetNumber1Player() { return m_nowNumOnePla; }
};