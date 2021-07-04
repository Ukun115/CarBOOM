#pragma once

class Player;
class Enemy;
class Stage;
class TitleScene;


class GameScene :public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	Stage* m_normalStage = nullptr;
	SkinModelRender* m_crownModel = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_timeLimit = nullptr;
	SoundSource* m_gameStartGingle;	//�N���N�V�����T�E���h
	SoundSource* m_gameBGM;	//�Q�[������BGM�T�E���h
	SoundSource* m_countDown;	//�J�E���g�_�E���T�E���h
	SpriteRender* m_syutyusen = nullptr;
	SoundSource* m_whistleSound = nullptr;


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCountTimeFlg = true;


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_resultsenniTimer = 0;
	unsigned int m_countDownTimer = 0;
	int m_timer = 3600;	//60�b
	int m_countTime = 0;


	int m_plaScore[4] = { 0 };
	Vector2 m_plaScorePos[4];
	unsigned int m_nowNumOnePla = 0;
	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};
	wchar_t text1[64];	//�������ԃt�H���g
	wchar_t text2[64];	//�v���C���[�X�R�A�t�H���g


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum PLAYER
	{
		PLAYER1,		//1P�̔z��ł̔ԍ�
		PLAYER2,		//2P�̔z��ł̔ԍ�
		PLAYER3,		//3P�̔z��ł̔ԍ�
		PLAYER4,		//4P�̔z��ł̔ԍ�
		MAXPLAYERNUM	//�v���C���[�̍ő吔
	};

	enum soundNum
	{
		GameStartGingle,	//�Q�[���X�^�[�g�W���O��
		CountDownSound,		//�J�E���g�_�E���T�E���h
		GameBGM,			//�Q�[����BGM
		WhistleSound,		//�z�C�b�X���T�E���h
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
	/// �Q�b�^�[
	/// </summary>
	//���݂̎c�萧�����Ԃ��擾����֐�
	int GetNowTime() { return m_countTime; }
	//�Q�[���J�n�̃J�E���g�_�E�����I���������ǂ����̃t���O���擾����֐�
	bool GetCountDownFlg() { return m_isCountTimeFlg; }
	//�v���C���[�̃X�R�A���擾����֐�
	int GetPlaScore(int x) { return m_plaScore[x]; };
};