#pragma once
class GameScene;
class Player;
class StageSelectScene;
class TitleScene;
class Fade;


class ResultScene : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	GameScene* m_gameScene = nullptr;
	Fade* m_fadeOut = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;
	Player* m_player = nullptr;
	TitleScene* m_titleScene = nullptr;
	SpriteRender* m_resultSprite = nullptr;
	SpriteRender* m_plaNum[4] = { nullptr };			//�v���C���[4�l���p��
	SpriteRender* m_rankingSprite[4] = { nullptr };	//�v���C���[4�l���p��
	SoundSource* m_resultGingle = nullptr;
	SoundSource* m_gameBGM = nullptr;	//�Q�[������BGM�T�E���h
	SoundSource* m_decideSound = nullptr;	//����T�E���h


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_enableTimerCountFlg = false;
	bool m_pla4MoveFlg = false;
	bool m_pla3MoveFlg = false;
	bool m_pla2MoveFlg = false;
	bool m_pla1MoveFlg = false;
	bool m_delayTimerOnFlg = true;
	bool m_plaJumpFlg = false;
	bool m_muriFlg = false;


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_exitTimer = 0;
	int m_plaMoveDelayTimer = 0;
	int m_verticalMoveTimer = 0;


	unsigned int m_plaScore[4] = { 0 };		//�v���C���[4�l���̃X�R�A������z��
	int m_totalPlaNum = 0;

	unsigned int m_select = 0;
	float m_moveSpeed = 0.0f;

	Vector3 m_number1Pos = { 900.0f,50.0f,0.0f };		//�P�ʃv���C���[�̕\���ʒu
	Vector3 m_number2Pos = { 900.0f,-50.0f,0.0f };		//�Q�ʃv���C���[�̕\���ʒu
	Vector3 m_number3Pos = { 900.0f,-150.0f,0.0f };	//�R�ʃv���C���[�̕\���ʒu
	Vector3 m_number4Pos = { 900.0f,-250.0f,0.0f };	//�S�ʃv���C���[�̕\���ʒu


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum SoundNum
	{
		ResultGingle,
		GameBGM,
		DecideSound,
	};

	//�񋓌^
	enum enumState
	{
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};


	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
	void RankingSort();
	//���ǂ̃V�[���ɍs�����؂�ւ���֐�
	void SelectScene();
	//�v���C���[����ʊO�i�E���j����X���C�h���Ă��鏈���֐�
	void SlidePlayerName();
	//�摜���c�ړ�����֐�
	void VerticalMove(int width, float speed);
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum);


public:
	void SetTotalPlayerNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
};

