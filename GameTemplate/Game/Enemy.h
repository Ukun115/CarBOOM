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
	int m_startDelayTimer = 0;		//�X�^�[�g��x�点��^�C�}�[
	int m_startDelay[6];			//�G�U�̕��̃X�^�[�g�x������
	int m_cTime[6];					//�G�U�̕��̍U��CT�^�C�}�[
	int m_eneCTCount[6];			//�G�U�̕���CT����


	//�G���
	Vector3    m_enePos[6];			//�G�U�̕��̓G�̈ʒu
	Quaternion m_rot[6];			//�G�U�̕��̓G�̉�]
	float m_rotAngle[6];			//�G�U�̕��̉�]�p�x
	Vector3 m_moveSpeed[6];			//�G�U�̕��̈ړ����x
	Vector3 m_friction[6];			//�G�U�̕��̖��C
	Vector3    m_plaPos[4];			//�v���C���[4�̕��̃v���C���[�̈ʒu
	Vector3    m_mostShortKyori[4];	 //�v���C���[4�̕��ƓG�̋���
	Vector3 m_randEneResPos[10];	//�G�̃��X�|�[���ʒu�v10����


	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
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
	};

public:

	bool Start()override;
	~Enemy()override;
	void Update()override;


	//�G�̈ړ������֐�
	void EneMove(int x);
	//�G�̉�]�����֐�
	void EneTurn(int x);
	//�G����Ŋ��̃v���C���[����������֐�
	void Distance(int x);
	//�G�̃��X�|�[�������֐�
	void EneResporn(int x);


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//�G�̈ʒu���擾����֐�
	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
	//�G�̑��x���擾����֐�
	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }
};