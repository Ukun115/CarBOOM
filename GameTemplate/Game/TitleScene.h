#pragma once
class StageSelectScene;


class TitleScene : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_pushStartButtonSprite = nullptr;
	SpriteRender* m_plaActiveName[4] = { nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_plaDeactiveName[4] = { nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_pressASpeechBalloon[3] = { nullptr };
	StageSelectScene* m_stageSelectScene = nullptr;
	SoundSource* m_addPlayer = nullptr;
	SoundSource* m_gameNameGingle;	//�Q�[�����W���O���T�E���h
	SoundSource* m_titleCall;	//�^�C�g���R�[���T�E���h
	SoundSource* m_titleBGM;	//�^�C�g��BGFM�T�E���h
	SoundSource* m_decideSound;	//�X�^�[�g�{�^���������ꂽ�Ƃ��̃T�E���h


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isAddPlayerFlg[4] = { false };		//�e�v���C���[���o�^����Ă��邩�̔��ʃt���O
	bool m_isCanStageSelectSceneFlg = true;			//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������
	bool m_isFlashingFontTimerActiveFlg = true;		//true�̂Ƃ��_�ŕ����̕\���^�C�~���O
	bool m_isTitleCallOneShotFlg = true;		//true�̂Ƃ��^�C�g���R�[���Đ��\


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_flashingFontTimer = 0;		//�_�ŕ����̕\����\���̐؂�ւ��^�C�}�[
	unsigned int m_titleCallDelayTimer = 0;


	unsigned int m_totalPlaNum = 1;			//�v���C���[�̍��v�����v��
	Vector3 m_pressASpeechBalloonPos = Vector3::Zero;		//�v���C���[�ǉ������o���̈ʒu


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enumPlayer
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		MaxPlayerNum	//�v���C���[�̍ő吔
	};

	enum soundNum
	{
		TitleSceneGingle,	//�^�C�g���W���O��
		TitleSceneBGM,		//�^�C�g���V�[����BGM
		TitleCallSound,		//�^�C�g���R�[��
		DecideSound,		//���艹
		EngineSound,		//�G���W���T�E���h
	};


	bool Start()override;
	~TitleScene()override;
	void Update()override;


	//�v���C���[��ǉ�����֐�
	void AddPlayer();
	//�Q�[����ʂɑJ�ڂ���֐�
	void StageSelectSceneTransition();
	//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
	void FlashingFont();
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum);


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�v���C���[���ǉ�����Ă��邩�ǂ������擾����֐�
	 bool GetPlaFlg(int planum) { return m_isAddPlayerFlg[planum]; }
	//�o�^���ꂽ�v���C���[�̍��v�l�����擾����֐�
	int GetTotalPlaNum(){ return m_totalPlaNum; }
};