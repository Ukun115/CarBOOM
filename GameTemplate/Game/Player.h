#pragma once
class TitleScene;
class GameScene;
class Enemy;
class StageSelectScene;


class Player : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SkinModelRender* m_player[4] = { nullptr };		//�v���C���[4�l��
	SpriteRender* m_DASpr1[4] = { nullptr };		//�v���C���[4�l��
	SpriteRender* m_DASpr2[4] = { nullptr };		//�v���C���[4�l��
	Enemy* m_enemy = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;


	CharacterController m_charaCon[4];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬
	Effect m_shootDownEffect[4];		//�v���C���[4�l���̗��������Ƃ��̌��ăG�t�F�N�g
	Effect m_jetEffect[4];		//�v���C���[4�l���̃W�F�b�g�G�t�F�N�g


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isTyazi1Flg[4] = { false };
	bool m_isTyazi2Flg[4] = { false };
	bool m_isBPushFlg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack0Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack1Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack2Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isTyaziEffectFlg[4] = { false };


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_tyaziTimer[4];		//�������Ƃ��̃^�C�}�[
	unsigned int m_releaseTimer[4];		//�������Ƃ��̃^�C�}�[
	unsigned int m_atackTimer[4];			//�U���̃^�C�}�[
	unsigned int m_atackHanteiTimer[4] = { 0 };			//�U������̃^�C�}�[


	Vector3    m_pos[4];		//�v���C���[�̈ʒu
	Quaternion m_rot[4];		//�v���C���[�̉�]
	unsigned int m_plaNum = 0;	//�v���C���[�����J�E���g����ϐ�
	Vector3 m_moveSpeed[4];		//�ړ����x
	Vector3 m_enePushSpeed;		//�G����^������v�b�V���p���[
	Vector3 m_plaDir[4];		//����
	float m_leftStick_x[4];		//���X�e�B�b�N��x���͗�
	float m_leftStick_y[4];		//���X�e�B�b�N��y���͗�
	float m_rotAngle[4];		//��]�p�x
	Vector3 m_friction[4];		//���C
	Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
	unsigned int m_pushPlayer[5];
	Quaternion m_shootDownEffectRot;


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


	bool Start() override;
	~Player() override;
	void Update() override;


	//�v���C���[�̃��X�|�[�������֐�
	void PlaResporn(int planum);
	//�������v���C���[�̏����ʒu���Z�b�g������֐�
	void PlaResPos(int planum);
	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void PlaDataUpdate(int planum);
	//�v���C���[�̒ʏ�ړ������֐�
	void PlaMove(int planum);
	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void PlaSpeedCorrection(int planum);
	//�v���C���[�̉�]�����֐�
	void PlaTurn(int planum);
	//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
	void PlaAttackBefore(int planum);
	//�v���C���[��DA�̗��ߏ�Ԃ̔��ʏ����֐�
	void PlaDAState(int planum);
	//�v���C���[�̌��݂̏�Ԃ�`����֐�
	void PlaNowState(int planum);
	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void PlaAndEneClash(int planum);
	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
	void PlaAndPlaClash(int planum);
	//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(int planum);


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�v���C���[�̐l�����擾����֐�
	int GetPlaNum() { return m_plaNum; }
	//�v���C���[�̈ʒu���擾����֐�
	Vector3 GetPlaPos(int planum) { return  m_pos[planum]; }
	//�v���C���[�̑��x���擾����֐�
	Vector3 GetPlaSpeed(int planum) { return m_moveSpeed[planum]; }
	//�v���C���[�̌������擾����֐�
	Vector3 GetPlaDir(int planum) { return m_plaDir[planum]; }
	//�v���C���[�̃`���[�W���擾����֐�
	bool GetPlaisTyazi1Flg(int planum) { return m_isTyazi1Flg[planum]; }
	bool GetPlaisTyazi2Flg(int planum) { return m_isTyazi2Flg[planum]; }
};