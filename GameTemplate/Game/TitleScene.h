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
	SpriteRender* m_plaActiveName[4] = {nullptr};		//�v���C���[4�l���p��
	SpriteRender* m_plaDeactiveName[4] = {nullptr};		//�v���C���[4�l���p��
	StageSelectScene* m_stageSelectScene = nullptr;


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isAddPlayerFlg[4] = { false };		//�e�v���C���[���o�^����Ă��邩�̔��ʃt���O
	bool m_isCanStageSelectSceneFlg = true;			//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������
	bool m_isFlashingFontTimerActiveFlg = true;		//true�̂Ƃ��_�ŕ����̕\���^�C�~���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_flashingFontTimer = 0;		//�_�ŕ����̕\����\���̐؂�ւ��^�C�}�[


	unsigned int m_totalPlaNum = 1;			//�v���C���[�̍��v�����v��


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

public:

	bool Start()override;
	~TitleScene()override;
	void Update()override;


	//�v���C���[��ǉ�����֐�
	void AddPlayer();
	//�Q�[����ʂɑJ�ڂ���֐�
	void StageSelectSceneTransition();
	//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
	void FlashingFont();


	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�v���C���[���ǉ�����Ă��邩�ǂ������擾����֐�
	bool GetPlaFlg(int x) { return m_isAddPlayerFlg[x]; }
	//�o�^���ꂽ�v���C���[�̍��v�l�����擾����֐�
	int GetTotalPlaNum(){ return m_totalPlaNum; }
};