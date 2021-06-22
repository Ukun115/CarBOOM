#pragma once
class Player;
class TitleScene;
class GameScene;
class StageSelectScene;


class Enemy : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SkinModelRender* m_enemy[6] = { nullptr };		//�G6�̕�
	Player* m_player = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;


	CharacterController m_charaCon[6];		//�G�U�̕��̃L�����N�^�R���g���[���[�N���X���쐬


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCtFlg[6] = { false };		//�G�U�̕���CT�̃t���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_startDelayTimer = 0;		//�X�^�[�g��x�点��^�C�}�[
	unsigned int m_startDelay[6];			//�G�U�̕��̃X�^�[�g�x������
	unsigned int m_CTTime[6];					//�G�U�̕��̍U��CT�^�C�}�[
	unsigned int m_eneCTCount[6];			//�G�U�̕���CT����


	//�G���
	Vector3    m_enePos[6];			//�G�U�̕��̓G�̈ʒu
	Quaternion m_rot[6];			//�G�U�̕��̓G�̉�]
	float m_rotAngle[6];			//�G�U�̕��̉�]�p�x
	Vector3 m_moveSpeed[6];			//�G�U�̕��̈ړ����x
	Vector3 m_samDir[6];			//�G�ƃv���C���[�̌���
	Vector3 m_friction[6];			//�G�U�̕��̖��C
	Vector3    m_plaPos[4];			//�v���C���[4�̕��̃v���C���[�̈ʒu
	Vector3    m_mostShortKyori[4];	//�v���C���[4�̕��ƓG�̋���
	Vector3 m_ranEneResPos[10];		//�G�̃��X�|�[���ʒu�v10����
	float m_randEneResAngle[4];		//�G�̃��X�|�[����]�p�x4����
	Vector3 m_eneDir[6];			//����
	Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
	unsigned int m_pushPlayer[5];


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enumEnemy
	{
		Enemy1,		 //�G�P�̔z��ł̔ԍ�
		Enemy2,		 //�G�Q�̔z��ł̔ԍ�
		Enemy3,		 //�G�R�̔z��ł̔ԍ�
		Enemy4,		 //�G�S�̔z��ł̔ԍ�
		Enemy5,		 //�G�T�̔z��ł̔ԍ�
		Enemy6,		 //�G�U�̔z��ł̔ԍ�
		MaxEnemyNum	 //�G�̑���
	};
	enum enumPlayer
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		MaxPlaNum	//�v���C���[�̍ő吔
	};
	//�G�̃����_�����X�|�[���ʒu
	enum enumRanEneResPos
	{
		ResPos1,	//�P��
		ResPos2,	//�Q��
		ResPos3,	//�R��
		ResPos4,	//�S��
		ResPos5,	//�T��
		ResPos6,	//�U��
		ResPos7,	//�V��
		ResPos8,	//�W��
		ResPos9,	//�X��
		ResPos10,	//�P�O��
	};

public:

	bool Start()override;
	~Enemy()override;
	void Update()override;


	//�G�̈ʒu,��]���X�V����֐�
	void EneDataUpdate(int x);
	//�G��DA�����֐�
	void EneDA(int x);
	//�G�̉�]�����֐�
	void EneTurn(int x);
	//�G����Ŋ��̃v���C���[����������֐�
	void Distance(int x);
	//�G�̃��X�|�[�������֐�
	void EneResporn(int x);
	//�G�̖��C�����֐�
	void EneFriction(int x);
	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void PlaAndEneClash(int x);
	//�G�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(int x);


	/// <summary>
	/// �Q�b�^�[�֐�
	/// </summary>
	//�G�̈ʒu���擾����֐�
	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
	//�G�̑��x���擾����֐�
	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }
};