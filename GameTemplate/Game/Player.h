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
	SoundSource* m_carHorn[4];	//�N���N�V�����T�E���h
	SoundSource* m_shootDownSound[4];	//���ăT�E���h
	SoundSource* m_FallSound[4];	//�����T�E���h
	SoundSource* m_ChargeSound[4];	//�`���[�W�T�E���h
	SoundSource* m_Dash1Sound[4];	//�_�b�V���P�T�E���h
	SoundSource* m_Dash2Sound[4];	//�_�b�V���Q�T�E���h
	SoundSource* m_PlaAndPlaClashSound[4];	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h


	CharacterController m_charaCon[4];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬
	Effect m_shootDownEffect[4];		//�v���C���[4�l���̗��������Ƃ��̌��ăG�t�F�N�g
	Effect m_jetEffect[4];		//�v���C���[4�l���̃W�F�b�g�G�t�F�N�g
	Effect m_landingEffect[4];		//�v���C���[4�l���̒��n�G�t�F�N�g


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isTyazi1Flg[4] = { false };
	bool m_isTyazi2Flg[4] = { false };
	bool m_isBPushFlg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack0Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack1Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAtack2Flg[4] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isCharge1EffectSoundFlg[4] = { false };
	bool m_isCharge2EffectSoundFlg[4] = { false };
	bool m_isFallSoundFlg[4] = { false };			//�������𗎉���������Ȃ�Ȃ��悤�ɂ���t���O
	bool m_isLandingOKFlg[4] = { false };


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_tyaziTimer[4];		//�������Ƃ��̃^�C�}�[
	unsigned int m_releaseTimer[4];		//�������Ƃ��̃^�C�}�[
	unsigned int m_atackTimer[4];			//�U���̃^�C�}�[
	unsigned int m_atackHanteiTimer[4] = { 0 };			//�U������̃^�C�}�[
	unsigned int m_landingEffectDelayTimer[4] = { 0 };			//���n�G�t�F�N�g���v���C���[�����n�����Ƃ��ɍĐ������邽�߂̃^�C�}�[


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

	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow[4] = { nullptr };
	Vector3 m_arrowPos[4];
	Quaternion m_arrowRot[4];
	Vector3 m_arrowSize = Vector3::One;


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
	bool GetPlaisTyazi1Flg(int plaNum) { return m_isTyazi1Flg[plaNum]; }
	bool GetPlaisTyazi2Flg(int plaNum) { return m_isTyazi2Flg[plaNum]; }
};