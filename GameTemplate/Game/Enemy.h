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

	Light* m_light = { nullptr };

	SkinModelRender* m_enemy[6] = { nullptr };		//�G6�̕�
	Player* m_player = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;
	SoundSource* m_shootDownSound[6] = {nullptr};
	SoundSource* m_FallSound[6];	//�����T�E���h
	SoundSource* m_DashSound[6];	//�_�b�V���T�E���h
	SoundSource* m_PlaAndEneClashSound[6];	//�Փ˃T�E���h


	CharacterController m_charaCon[6];		//�G�U�̕��̃L�����N�^�R���g���[���[�N���X���쐬
	Effect m_shootDownEffect[6];		//���������Ƃ��̌��ăG�t�F�N�g


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCtFlg[6] = { false };		//�G�U�̕���CT�̃t���O
	bool m_stage2Flg = false;
	bool m_isFallSoundFlg[6] = { false };			//�������𗎉���������Ȃ�Ȃ��悤�ɂ���t���O
	bool m_isPlaAndEneClashSoundFlg[6] = { false };


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
	//�����ɓr���ŕύX���Ȃ��l�Ȃ̂ŁAconst�g�������B
	Vector3 m_ranEneResPos[10];		//�G�̃��X�|�[���ʒu�v10����

	float m_randEneResAngle[8];		//�G�̃��X�|�[����]�p�x4����
	Vector3 m_eneDir[6];			//����
	Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
	unsigned int m_pushPlayer[6];
	unsigned int m_randomDashSoundNum;


	Vector3 m_enePoiLigPos;
	int	m_poiLigNum = 0;


	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow[6] = { nullptr };
	Vector3 m_arrowPos[6];
	Quaternion m_arrowRot[6];
	Vector3 m_arrowSize = Vector3::One;


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

	enum SoundNum
	{
		ShootDownSound,
		FallSound,
		DashSound,
		PlaAndEneClashSound
	};


	bool Start()override;
	~Enemy()override;
	void Update()override;


	//�G�̈ʒu,��]���X�V����֐�
	void EneDataUpdate(int eneNum);
	//�G��DA�����֐�
	void EneDA(int eneNum);
	//�G�̉�]�����֐�
	void EneTurn(int eneNum);
	//�G����Ŋ��̃v���C���[����������֐�
	void Distance(int eneNum);
	//�G�̃��X�|�[�������֐�
	void EneResporn(int eneNum);
	//�G�̖��C�����֐�
	void EneFriction(int eneNum);
	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void PlaAndEneClash(int eneNum);
	//�G�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(int eneNum);
	//�G�̃X�s�[�h�x�N�g��������������f�o�b�N�֐�
	void EneMooveSpeedDebug(int eneNum);
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum,int eneNum);


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�G�̈ʒu���擾����֐�
	Vector3 GetEnemyPos(int eneNum) { return m_enePos[eneNum]; }
	//�G�̑��x���擾����֐�
	Vector3 GetEnemySpeed(int eneNum) { return m_moveSpeed[eneNum]; }
};