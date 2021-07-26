#pragma once
class TitleScene;
class StageSelectScene;
class GameScene;
class Stage;
class Enemy;


class Player : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	enum enumPlayer
	{
		Player1,		//1P�̔z��ł̔ԍ�
		Player2,		//2P�̔z��ł̔ԍ�
		Player3,		//3P�̔z��ł̔ԍ�
		Player4,		//4P�̔z��ł̔ԍ�
		TotalPlayerNum	//�v���C���[�̍ő吔
	};

	enum enumEnemy
	{
		Enemy1,
		TotalEnemyNum = 6
	};

	enum enumSoundNum
	{
		ShootDownSound,
		CarHornSound,
		FallSound,
		ChargeSound,
		Dash1Sound,
		Dash2Sound,
		PlaAndPlaClashSound,
		PlaAndEneClashSound,
		ChargeEnd,
		TotalSoundNum
	};

	enum enumWind
	{
		UpWind,		//�������ւ̕�
		DownWind,	//�ォ�牺�ւ̕�
		LeftWind,	//�E���獶�ւ̕�
		RightWind,	//������E�ւ̕�
	};


	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;
	GameScene* m_gameScene = nullptr;
	Stage* m_stage = nullptr;
	Enemy* m_enemy = nullptr;
	SkinModelRender* m_player[TotalPlayerNum] = { nullptr };		//�v���C���[4�l��
	SpriteRender* m_chargeUI1_1[TotalPlayerNum] = { nullptr };		//�`���[�W�摜
	SpriteRender* m_chargeUI1_2[TotalPlayerNum] = { nullptr };		//�`���[�W�摜
	SpriteRender* m_chargeUI2_1[TotalPlayerNum] = { nullptr };		//�`���[�W�摜
	SpriteRender* m_chargeUI2_1_1[TotalPlayerNum] = { nullptr };		//�`���[�W�摜
	SpriteRender* m_chargeUI2_2[TotalPlayerNum] = { nullptr };		//�`���[�W�摜
	SpriteRender* m_crown = nullptr;		//�v���C���[�̏�ɒu�������摜
	SoundPlayBack* m_soundPlayBack = nullptr;

	CharacterController m_charaCon[TotalPlayerNum];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬
	Effect m_shootDownEffect[TotalPlayerNum];		//�v���C���[4�l���̗��������Ƃ��̌��ăG�t�F�N�g
	Effect m_jetEffect[TotalPlayerNum];		//�v���C���[4�l���̃W�F�b�g�G�t�F�N�g
	Effect m_landingEffect[TotalPlayerNum];		//�v���C���[4�l���̒��n�G�t�F�N�g


	/// <summary>
	/// �t���O
	/// </summary>
	bool m_isCharge1Flg[TotalPlayerNum] = { false };
	bool m_isCharge2Flg[TotalPlayerNum] = { false };
	bool m_isCharge1HanteiFlg[TotalPlayerNum] = { false };
	bool m_isCharge2HanteiFlg[TotalPlayerNum] = { false };
	bool m_isBPushFlg[TotalPlayerNum] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack0Flg[TotalPlayerNum] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack1Flg[TotalPlayerNum] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack2Flg[TotalPlayerNum] = { false };		//B�{�^���������ꂽ�Ƃ��̃t���O
	bool m_isAttack1HanteiFlg[TotalPlayerNum] = { false };		//�U��1�̔���t���O
	bool m_isAttack2HanteiFlg[TotalPlayerNum] = { false };		//�U��2�̔���t���O
	bool m_isCharge1EffectSoundFlg[TotalPlayerNum] = { false };
	bool m_isCharge2EffectSoundFlg[TotalPlayerNum] = { false };
	bool m_isFallSoundFlg[TotalPlayerNum] = { false };			//�������𗎉���������Ȃ�Ȃ��悤�ɂ���t���O
	bool m_isLandingOKFlg[TotalPlayerNum] = { false };

	bool m_plaTourokuFlg[TotalPlayerNum] = { false };
	bool m_isPauseFlg = false;


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	unsigned int m_chargeTimer[TotalPlayerNum] = { INT_ZERO };		//�������Ƃ��̃^�C�}�[
	unsigned int m_releaseTimer[TotalPlayerNum] = { INT_ZERO };		//�������Ƃ��̃^�C�}�[
	unsigned int m_attackTimer[TotalPlayerNum] = { INT_ZERO };			//�U���̃^�C�}�[
	unsigned int m_attackHanteiTimer[TotalPlayerNum] = { INT_ZERO };			//�U������̃^�C�}�[
	unsigned int m_landingEffectDelayTimer[TotalPlayerNum] = { INT_ZERO };			//���n�G�t�F�N�g���v���C���[�����n�����Ƃ��ɍĐ������邽�߂̃^�C�}�[


	Vector3    m_fallSpeed[TotalPlayerNum];	//�v���C���[�̗������x�B
	Vector3    m_pos[TotalPlayerNum];		//�v���C���[�̈ʒu
	Quaternion m_rot[TotalPlayerNum];		//�v���C���[�̉�]
	Quaternion m_charge1_1Rot[TotalPlayerNum];		//�v���C���[�̉�]
	float m_chargeRotValue1[TotalPlayerNum] = { FLOAT_ZERO };
	Quaternion m_charge1_2Rot[TotalPlayerNum];		//�v���C���[�̉�]
	float m_chargeRotValue2[TotalPlayerNum] = { FLOAT_ZERO };
	unsigned int m_plaNum = INT_ZERO;	//�v���C���[�����J�E���g����ϐ�
	Vector3 m_moveSpeed[TotalPlayerNum];		//�ړ����x
	Vector3 m_enePushSpeed;		//�G����^������v�b�V���p���[
	Vector3 m_plaDir[TotalPlayerNum];		//����
	float m_leftStick_x[TotalPlayerNum] = { FLOAT_ZERO };		//���X�e�B�b�N��x���͗�
	float m_leftStick_y[TotalPlayerNum] = { FLOAT_ZERO };		//���X�e�B�b�N��y���͗�
	float m_rotAngle[TotalPlayerNum] = { FLOAT_ZERO };		//��]�p�x
	Vector3 m_friction[TotalPlayerNum];		//���C
	Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
	unsigned int m_pushPlayer[5] = { INT_ZERO };
	Quaternion m_shootDownEffectRot;
	Vector2 plaScreenPos[4];
	Vector3 m_plaChargeUIPos[4];
	Vector3 m_crownPos;

	//�f�o�b�O�p
	SkinModelRender* m_skinModelRenderArrow[TotalPlayerNum] = { nullptr };
	Vector3 m_arrowPos[TotalPlayerNum];
	Quaternion m_arrowRot[TotalPlayerNum];
	Vector3 m_arrowSize;

	int m_totalPlaNum = INT_ZERO;
	int m_stageSelectNum = INT_ZERO;


	bool Start() override final;
	~Player() override final;
	void Update() override final;


	//�v���C���[�̃��X�|�[�������֐�
	void PlaResporn(const int plaNum);
	//�������v���C���[�̏����ʒu���Z�b�g������֐�
	void PlaResPos(const int plaNum);
	//�v���C���[�̈ʒu,��]�̏����X�V����֐�
	void PlaDataUpdate(const int plaNum);
	//�v���C���[�̒ʏ�ړ������֐�
	void PlaMove(const int plaNum);
	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void PlaSpeedCorrection(const int plaNum);
	//�v���C���[�̉�]�����֐�
	void PlaTurn(const int plaNum);
	//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
	void PlaAttackBefore(const int plaNum);
	//�v���C���[�̌��݂̏�Ԃ�`����֐�
	void PlaNowState(const int plaNum);
	//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
	void PlaAndEneClash(const int plaNum);
	//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
	void PlaAndPlaClash(const int plaNum);
	//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
	void Gravity(const int plaNum);
	//�x�N�g��������������f�o�b�N�֐�
	void PlaMooveSpeedDebug(const int plaNum);
	//�v���C���[�ɉe�����y�ڂ�����
	void WindPower(const int planum);
	//�������T�E���h��炷�֐�
	void FallSoundPlayBack(const int plaNum);
	//�v���C���[�̒��n�G�t�F�N�g���Đ�������֐�
	void LandingEffectPlay(const int plaNum);


public:


	//�v���C���[�̐l�����擾����֐�
	int GetPlaNum()const { return m_plaNum; }
	//�v���C���[�̈ʒu���擾����֐�
	const Vector3& GetPlaPos(const int plaNum)const { return  m_pos[plaNum]; }
	//�v���C���[�̑��x���擾����֐�

	/// @brief
	/// @param plaNum
	/// @return
	const Vector3& GetPlaSpeed(const int plaNum)const { return m_moveSpeed[plaNum]; }
	//�v���C���[�̌������擾����֐�
	Vector3 GetPlaDir(const int plaNum)const { return m_plaDir[plaNum]; }
	//�v���C���[�̃`���[�W���擾����֐�
	bool GetPlaisTyazi1HanteiFlg(const int plaNum)const { return m_isCharge1HanteiFlg[plaNum]; }
	bool GetPlaisTyazi2HanteiFlg(const int plaNum)const { return m_isCharge2HanteiFlg[plaNum]; }

	void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	void SetStageSelectNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
	void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }
};