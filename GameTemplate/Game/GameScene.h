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


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCountTimeFlg = true;


	/// <summary>
	/// �^�C�}�[
	/// </summary>


	int m_counttime = 0;
	int m_timer = 3600;	//60�b
	int m_plscore[4] = { 0 };
<<<<<<< HEAD
	unsigned int m_countDownTimer = 0;
	unsigned int m_nowNumOnePla = 0;
	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};
	unsigned int m_resultsenniTimer = 0;
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
=======
	int m_countDownTimer = 0;
	int m_nowNumOnePla = 0;
	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};
	int m_resultsenniTimer = 0;
>>>>>>> remotes/origin/master


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

public:

	bool Start()override;
	~GameScene()override;
	void Update()override;


<<<<<<< HEAD
	//�������ԏ����֐�
	void TimeLimit();
	//�v���C���[�̃X�R�A�`��֐�
	void PlaScoreDraw();
	//�J�E���g�_�E�������֐�
	void CountDown();
=======
>>>>>>> remotes/origin/master
	//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
	Vector2 SetScoreTextPos(int t);
	//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
	Vector2 GetScorePos(int x);
	//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
	Vector4 ScoreColor(int c);
	/*�v���C���[�̓��_�ϓ������֐�
     (���͗��Ƃ����v���C���[�Ay�͎��ł����v���C���[)*/
	void GetPlayerAddScore(int x,int y);
	//�P�ʂɉ����摜�Ɖ������f����n���֐�
	void NowCrown();
<<<<<<< HEAD
	//���U���g��ʂɑJ�ڂ���֐�
	void ResultSceneTransition();
=======
>>>>>>> remotes/origin/master


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//���݂̎c�萧�����Ԃ��擾����֐�
	int GetNowTime() { return m_counttime; }
	//�Q�[���J�n�̃J�E���g�_�E�����I���������ǂ����̃t���O���擾����֐�
	bool GetCountDownFlg() { return m_isCountTimeFlg; }
	//�v���C���[�̃X�R�A���擾����֐�
	int GetPlaScore(int x) { return m_plscore[x]; };
};