#pragma once


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


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isAddPlayerFlg[4] = { false };		//�v���C���[���o�^���ꂽ���̔��ʃt���O
	bool m_isCanGameStartFlg = true;		//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������
	bool m_isButtonTimerActiveFlg = true;


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	int m_buttonTimer = 0;


	int m_totalPlayerNum = 1;			//�v���C���[�̍��v�����v��


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
	~TitleScene()override;
	void Update()override;


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//�v���C���[���ǉ�����Ă��邩�ǂ������擾����֐�
	bool GetPlaFlg(int x) { return m_isAddPlayerFlg[x]; }
	//�o�^���ꂽ�v���C���[�̍��v�l�����擾����֐�
	int GetTotalPlaNum(){ return m_totalPlayerNum; }
};