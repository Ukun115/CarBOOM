#pragma once
class TitleScene;
class GameScene;
class Enemy;


class Player : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SkinModelRender* m_player[4] = { nullptr };		//�v���C���[4�l��
	SpriteRender* m_sprite1[4] = { nullptr };		//�v���C���[4�l��
	SpriteRender* m_sprite2[4] = { nullptr };		//�v���C���[4�l��
	Enemy* m_enemy = nullptr;


	CharacterController m_charaCon[4];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isTyazi2Flg = false;
	bool m_isBPushFlg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack0Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack1Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack2Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O


	/// <summary>
	/// �^�C�}�[
	/// </summary>


	Vector3    m_pos[4];		//�v���C���[�̈ʒu
	Quaternion m_rot[4];		//�v���C���[�̉�]
	Vector3    m_sca[4];		//�v���C���[�̊g�嗦
	int m_plaNum = 0;	//�v���C���[�����J�E���g����ϐ�
	Vector3 m_moveSpeed[4];				//�ړ����x
	Vector3 m_enePushSpeed;				//�G����^������v�b�V���p���[
	Vector3 m_plaDir[4];					//����
	float m_leftStick_x[4];				//���X�e�B�b�N��x���͗�
	float m_leftStick_y[4];				//���X�e�B�b�N��y���͗�
	int m_pressTimer[4];				//�������Ƃ��̃^�C�}�[
	int m_releaseTimer[4];				//�������Ƃ��̃^�C�}�[
	float m_rotAngle[4];				//��]�p�x
	Vector3 m_friction[4];				//���C
	Vector3 m_diff;								//�v���C���[�ƓG�Ƃ̋���
	int m_atackTime[4];				    //�U���̃^�C�}�[
	int m_pushPlayer[5];


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

	bool Start() override;
	~Player() override;
	void Update() override;


	//�v���C���[�������ʒu�Ƀ��X�|�[��������֐�
	void PlaResporn(int x);
	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void PlaDataUpdate(int x);
	//�v���C���[�̒ʏ�ړ������֐�
	void PlaMove(int x);
	//�v���C���[�̉�]�����֐�
	void PlaTurn(int x);
	//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
	void PlaAttackBefore(int x);
	//�v���C���[�̌��݂̏�Ԃ�`����֐�
	void PlaNowSpeed(int x);


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//�v���C���[�̐l�����擾����֐�
	int GetPlaNum() { return m_plaNum; }
	//�v���C���[�̈ʒu���擾����֐�
	Vector3 GetPlaPos(int x) { return  m_pos[x]; }
	//�v���C���[�̑��x���擾����֐�
	Vector3 GetPlaSpeed(int x) { return m_moveSpeed[x]; }
};