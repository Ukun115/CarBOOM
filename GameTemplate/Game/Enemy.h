#pragma once
class Player;
class TitleScene;
class GameScene;


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


	CharacterController m_charaCon[6];		//�G�U�̕��̃L�����N�^�R���g���[���[�N���X���쐬


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCtFlg[6] = { false };		//�G�U�̕���CT�̃t���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>
<<<<<<< HEAD
	unsigned int m_startDelayTimer = 0;		//�X�^�[�g��x�点��^�C�}�[
	unsigned int m_startDelay[6];			//�G�U�̕��̃X�^�[�g�x������
	unsigned int m_cTime[6];					//�G�U�̕��̍U��CT�^�C�}�[
	unsigned int m_eneCTCount[6];			//�G�U�̕���CT����
=======
	int m_startDelayTimer = 0;		//�X�^�[�g��x�点��^�C�}�[
	int m_startDelay[6];			//�G�U�̕��̃X�^�[�g�x������
	int m_cTime[6];					//�G�U�̕��̍U��CT�^�C�}�[
	int m_eneCTCount[6];			//�G�U�̕���CT����
>>>>>>> remotes/origin/master


	//�G���
	Vector3    m_enePos[6];			//�G�U�̕��̓G�̈ʒu
	Quaternion m_rot[6];			//�G�U�̕��̓G�̉�]
	float m_rotAngle[6];			//�G�U�̕��̉�]�p�x
	Vector3 m_moveSpeed[6];			//�G�U�̕��̈ړ����x
	Vector3 m_friction[6];			//�G�U�̕��̖��C
	Vector3    m_plaPos[4];			//�v���C���[4�̕��̃v���C���[�̈ʒu
	Vector3    m_mostShortKyori[4];	 //�v���C���[4�̕��ƓG�̋���
<<<<<<< HEAD
	Vector3 m_ranEneResPos[10];	//�G�̃��X�|�[���ʒu�v10����
=======
	Vector3 m_randEneResPos[10];	//�G�̃��X�|�[���ʒu�v10����
>>>>>>> remotes/origin/master


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
<<<<<<< HEAD
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
=======
	enum ENEMY
	{
		ENEMY1,		 //�G�P�̔z��ł̔ԍ�
		ENEMY2,		 //�G�Q�̔z��ł̔ԍ�
		ENEMY3,		 //�G�R�̔z��ł̔ԍ�
		ENEMY4,		 //�G�S�̔z��ł̔ԍ�
		ENEMY5,		 //�G�T�̔z��ł̔ԍ�
		ENEMY6,		 //�G�U�̔z��ł̔ԍ�
		ENEMYNUM	 //�G�̑���
	};
	enum PLAYER
	{
		PLAYER1,		//1P�̔z��ł̔ԍ�
		PLAYER2,		//2P�̔z��ł̔ԍ�
		PLAYER3,		//3P�̔z��ł̔ԍ�
		PLAYER4,		//4P�̔z��ł̔ԍ�
		MAXPLAYERNUM	//�v���C���[�̍ő吔
>>>>>>> remotes/origin/master
	};

public:

	bool Start()override;
	~Enemy()override;
	void Update()override;

<<<<<<< HEAD
	//�G�̈ʒu,��]���X�V����֐�
	void EneDataUpdate(int x);
	//�G��DA�����֐�
	void EneDA(int x);
=======

	//�G�̈ړ������֐�
	void EneMove(int x);
>>>>>>> remotes/origin/master
	//�G�̉�]�����֐�
	void EneTurn(int x);
	//�G����Ŋ��̃v���C���[����������֐�
	void Distance(int x);
	//�G�̃��X�|�[�������֐�
	void EneResporn(int x);
	//�G�̖��C�����֐�
	void EneFriction(int x);
	//�G�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(int x);


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//�G�̈ʒu���擾����֐�
	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
	//�G�̑��x���擾����֐�
	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }
};