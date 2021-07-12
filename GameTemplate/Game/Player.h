#pragma once
class TitleScene;
class GameScene;
class Enemy;
class StageSelectScene;
class Stage;


class Player : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene{ nullptr };
	GameScene* m_gameScene{ nullptr };
	SkinModelRender* m_player[PLAYER_MAX_NUM]{ nullptr };		//�v���C���[4�l��
	SpriteRender* m_DASpr1[PLAYER_MAX_NUM]{ nullptr };		//�v���C���[4�l��
	SpriteRender* m_DASpr2[PLAYER_MAX_NUM]{ nullptr };		//�v���C���[4�l��
	SpriteRender* m_chargeUI1_1[PLAYER_MAX_NUM];		//�`���[�W�摜
	SpriteRender* m_chargeUI1_2[PLAYER_MAX_NUM];		//�`���[�W�摜
	SpriteRender* m_chargeUI2_1[PLAYER_MAX_NUM];		//�`���[�W�摜
	SpriteRender* m_chargeUI2_1_1[PLAYER_MAX_NUM];		//�`���[�W�摜
	SpriteRender* m_chargeUI2_2[PLAYER_MAX_NUM];		//�`���[�W�摜
	Enemy* m_enemy{ nullptr };
	StageSelectScene* m_stageSelectScene{ nullptr };
	SoundSource* m_carHorn[PLAYER_MAX_NUM]{ nullptr };	//�N���N�V�����T�E���h
	SoundSource* m_shootDownSound[PLAYER_MAX_NUM]{ nullptr };	//���ăT�E���h
	SoundSource* m_FallSound[PLAYER_MAX_NUM]{ nullptr };	//�����T�E���h
	SoundSource* m_ChargeSound[PLAYER_MAX_NUM]{ nullptr };	//�`���[�W�T�E���h
	SoundSource* m_Dash1Sound[PLAYER_MAX_NUM]{ nullptr };	//�_�b�V���P�T�E���h
	SoundSource* m_Dash2Sound[PLAYER_MAX_NUM]{ nullptr };	//�_�b�V���Q�T�E���h
	SoundSource* m_PlaAndPlaClashSound[PLAYER_MAX_NUM]{ nullptr };	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h
	Stage* m_stage = nullptr;

	CharacterController m_charaCon[PLAYER_MAX_NUM];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬
	Effect m_shootDownEffect[PLAYER_MAX_NUM];		//�v���C���[4�l���̗��������Ƃ��̌��ăG�t�F�N�g
	Effect m_jetEffect[PLAYER_MAX_NUM];		//�v���C���[4�l���̃W�F�b�g�G�t�F�N�g
	Effect m_landingEffect[PLAYER_MAX_NUM];		//�v���C���[4�l���̒��n�G�t�F�N�g


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCharge1Flg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2Flg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge1HanteiFlg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2HanteiFlg[PLAYER_MAX_NUM]{ false };
	bool m_isBPushFlg[PLAYER_MAX_NUM]{ false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack0Flg[PLAYER_MAX_NUM]{ false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack1Flg[PLAYER_MAX_NUM]{ false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack2Flg[PLAYER_MAX_NUM]{ false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack1HanteiFlg[PLAYER_MAX_NUM]{ false };		//�U��1�̔���t���O
	bool m_isAttack2HanteiFlg[PLAYER_MAX_NUM]{ false };		//�U��2�̔���t���O
	bool m_isCharge1EffectSoundFlg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2EffectSoundFlg[PLAYER_MAX_NUM]{ false };
	bool m_isFallSoundFlg[PLAYER_MAX_NUM]{ false };			//�������𗎉���������Ȃ�Ȃ��悤�ɂ���t���O
	bool m_isLandingOKFlg[PLAYER_MAX_NUM]{ false };


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_chargeTimer[PLAYER_MAX_NUM]{ 0 };		//�������Ƃ��̃^�C�}�[
	unsigned int m_releaseTimer[PLAYER_MAX_NUM]{ 0 };		//�������Ƃ��̃^�C�}�[
	unsigned int m_attackTimer[PLAYER_MAX_NUM]{ 0 };			//�U���̃^�C�}�[
	unsigned int m_attackHanteiTimer[PLAYER_MAX_NUM]{ 0 };			//�U������̃^�C�}�[
	unsigned int m_landingEffectDelayTimer[PLAYER_MAX_NUM]{ 0 };			//���n�G�t�F�N�g���v���C���[�����n�����Ƃ��ɍĐ������邽�߂̃^�C�}�[


	Vector3    m_pos[PLAYER_MAX_NUM];		//�v���C���[�̈ʒu
	Quaternion m_rot[PLAYER_MAX_NUM];		//�v���C���[�̉�]
	Quaternion m_charge1_1Rot[PLAYER_MAX_NUM];		//�v���C���[�̉�]
	Quaternion m_charge1_2Rot[PLAYER_MAX_NUM];		//�v���C���[�̉�]
	unsigned int m_plaNum{ 0 };	//�v���C���[�����J�E���g����ϐ�
	Vector3 m_moveSpeed[PLAYER_MAX_NUM];		//�ړ����x
	Vector3 m_enePushSpeed;		//�G����^������v�b�V���p���[
	Vector3 m_plaDir[PLAYER_MAX_NUM];		//����
	float m_leftStick_x[PLAYER_MAX_NUM]{ 0.0f };		//���X�e�B�b�N��x���͗�
	float m_leftStick_y[PLAYER_MAX_NUM]{ 0.0f };		//���X�e�B�b�N��y���͗�
	float m_rotAngle[PLAYER_MAX_NUM]{ 0.0f };		//��]�p�x
	Vector3 m_friction[PLAYER_MAX_NUM];		//���C
	Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
	unsigned int m_pushPlayer[5]{ 0 };
	Quaternion m_shootDownEffectRot;

	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow[PLAYER_MAX_NUM]{ nullptr };
	Vector3 m_arrowPos[PLAYER_MAX_NUM];
	Quaternion m_arrowRot[PLAYER_MAX_NUM];
	Vector3 m_arrowSize;


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

	enum SoundNum
	{
		ShootDownSound,
		CarHornSound,
		FallSound,
		ChargeSound,
		Dash1Sound,
		Dash2Sound,
		PlaAndPlaClashSound,
		PlaAndEneClashSound
	};

	enum Wind
	{
		Up,		//�������ւ̕�
		Down,	//�ォ�牺�ւ̕�
		Left,	//�E���獶�ւ̕�
		Right,	//������E�ւ̕�
		Max		//�ő吔
	};


	bool Start() override;
	~Player() override;
	void Update() override;


	//�v���C���[�̃��X�|�[�������֐�
	void PlaResporn(int plaNum);
	//�������v���C���[�̏����ʒu���Z�b�g������֐�
	void PlaResPos(int plaNum);
	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void PlaDataUpdate(int plaNum);
	//�v���C���[�̒ʏ�ړ������֐�
	void PlaMove(int plaNum);
	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void PlaSpeedCorrection(int plaNum);
	//�v���C���[�̉�]�����֐�
	void PlaTurn(int plaNum);
	//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
	void PlaAttackBefore(int plaNum);
	//�v���C���[�̌��݂̏�Ԃ�`����֐�
	void PlaNowState(int plaNum);
	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void PlaAndEneClash(int plaNum);
	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
	void PlaAndPlaClash(int plaNum);
	//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(int plaNum);
	//�x�N�g��������������f�o�b�N�֐�
	void PlaMooveSpeedDebug(int plaNum);
	//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
	void SoundPlayBack(int soundNum, int plaNum);
	//�v���C���[�ɉe�����y�ڂ�����
	void WindPower(int planum);


public:

	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//�v���C���[�̐l�����擾����֐�
	int GetPlaNum() { return m_plaNum; }
	//�v���C���[�̈ʒu���擾����֐�
	Vector3 GetPlaPos(int plaNum) { return  m_pos[plaNum]; }
	//�v���C���[�̑��x���擾����֐�
	Vector3 GetPlaSpeed(int plaNum) { return m_moveSpeed[plaNum]; }
	//�v���C���[�̌������擾����֐�
	Vector3 GetPlaDir(int plaNum) { return m_plaDir[plaNum]; }
	//�v���C���[�̃`���[�W���擾����֐�
	bool GetPlaisTyazi1HanteiFlg(int plaNum) { return m_isCharge1HanteiFlg[plaNum]; }
	bool GetPlaisTyazi2HanteiFlg(int plaNum) { return m_isCharge2HanteiFlg[plaNum]; }
};