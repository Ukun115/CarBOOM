#pragma once
class StageSelectScene;


class TitleScene : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	SpriteRender* m_titleSprite{ nullptr };
	SpriteRender* m_titleBaraBaraSprite[9]{ nullptr };
	SpriteRender* m_titleNameSprite{ nullptr };
	SpriteRender* m_pushStartButtonSprite{ nullptr };
	SpriteRender* m_plaActiveName[4]{ nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_plaDeactiveName[4]{ nullptr };		//�v���C���[4�l���p��
	SpriteRender* m_pressASpeechBalloon{ nullptr };
	SpriteRender* m_pressASpeechBalloonArrow{ nullptr };
	StageSelectScene* m_stageSelectScene{ nullptr };
	SoundSource* m_addPlayer{ nullptr };
	SoundSource* m_gameNameGingle{ nullptr };	//�Q�[�����W���O���T�E���h
	SoundSource* m_titleCall{ nullptr };	//�^�C�g���R�[���T�E���h
	SoundSource* m_titleBGM{ nullptr };	//�^�C�g��BGFM�T�E���h
	SoundSource* m_decideSound{ nullptr };	//�X�^�[�g�{�^���������ꂽ�Ƃ��̃T�E���h


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isAddPlayerFlg[4]{ false };		//�e�v���C���[���o�^����Ă��邩�̔��ʃt���O
	bool m_enableUpdateFlg{ true };			//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������
	bool m_isFlashingFontActiveFlg{ true };		//true�̂Ƃ��_�ŕ����̕\���^�C�~���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_flashingFontTimer{ 0 };		//�_�ŕ����̕\����\���̐؂�ւ��^�C�}�[
	int m_sideMoveTimer = 0;
	int m_waveTimer = 0;
	int m_verticalMoveTimer[9];


	float m_scaUpValue = 0;
	Vector3 m_titleNameSca = Vector3::One;
	unsigned int m_totalPlaNum{ 1 };			//�v���C���[�̍��v�����v��
	Vector3 m_pressASpeechBalloonPos;		//�v���C���[�ǉ������o���̈ʒu
	Vector3 m_arrowSca;
	Vector3 m_titleBaraBaraSpritePos[9];


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
	//�摜�����ړ�����֐�
	void SideMove(int width, float speed);
	//�摜���c�ړ�����֐�
	void VerticalMove(int width, float speed, int spriteNum);
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum);
	//�^�C�g�������g�傷��֐�
	void TitleNameScaUp();
	//�^�C�g�������E�F�[�u������֐�
	void TitleNameWave();


	FontRender* m_PlaNameFont[4] = { nullptr };


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�v���C���[���ǉ�����Ă��邩�ǂ������擾����֐�
	 bool GetPlaFlg(int planum) { return m_isAddPlayerFlg[planum]; }
	//�o�^���ꂽ�v���C���[�̍��v�l�����擾����֐�
	int GetTotalPlaNum(){ return m_totalPlaNum; }
};