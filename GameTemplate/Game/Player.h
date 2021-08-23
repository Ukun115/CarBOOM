///<<summary>
///�v���C���[�̃��C������
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Stage;
	class Enemy;
	class PlayerMoveSpeedArrow;
	class PlayerTurn;
	class PlayerChargeUI;
	class PlayerEffect;

	class Player : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
			Player2,		//2P�̔z��ł̔ԍ�
			Player3,		//3P�̔z��ł̔ԍ�
			Player4,		//4P�̔z��ł̔ԍ�
			TotalPlayerNum	//�v���C���[�̍ő吔
		};

		enum enEnemy
		{
			Enemy1,
			TotalEnemyNum = 6
		};

		enum enSoundNum
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

		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Stage* m_stage = nullptr;
		Enemy* m_enemy = nullptr;
		SkinModelRender* m_player[TotalPlayerNum] = { nullptr };		//�v���C���[4�l��
		SpriteRender* m_crown = nullptr;		//�v���C���[�̏�ɒu�������摜
		SoundPlayBack* m_soundPlayBack = nullptr;
		PlayerMoveSpeedArrow* m_playerMoveSpeedArrow = nullptr;
		PlayerTurn* m_playerTurn = nullptr;
		PlayerChargeUI* m_playerChargeUI = nullptr;
		PlayerEffect* m_playerEffect = nullptr;

		CharacterController m_charaCon[TotalPlayerNum];		//�v���C���[4�l���̃L�����N�^�R���g���[���[�N���X���쐬

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

		bool m_plaTourokuFlg[TotalPlayerNum] = { false };
		bool m_isPauseFlg = false;

		/// <summary>
		/// �^�C�}�[
		/// </summary>
		unsigned int m_chargeTimer[TotalPlayerNum] = { 0 };		//�������Ƃ��̃^�C�}�[
		unsigned int m_releaseTimer[TotalPlayerNum] = { 0 };		//�������Ƃ��̃^�C�}�[
		unsigned int m_attackTimer[TotalPlayerNum] = { 0 };			//�U���̃^�C�}�[
		unsigned int m_attackHanteiTimer[TotalPlayerNum] = { 0 };			//�U������̃^�C�}�[

		Vector3    m_fallSpeed[TotalPlayerNum];	//�v���C���[�̗������x�B
		Vector3    m_pos[TotalPlayerNum];		//�v���C���[�̈ʒu
		Vector3 m_moveSpeed[TotalPlayerNum];		//�ړ����x
		Vector3 m_enePushSpeed;		//�G����^������v�b�V���p���[
		Vector3 m_plaDir[TotalPlayerNum];		//����
		Vector3 m_friction[TotalPlayerNum];		//���C
		Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
		unsigned int m_pushPlayer[5] = { 0 };
		Quaternion m_shootDownEffectRot;
		Vector2 m_plaScreenPos[TotalPlayerNum];
		Vector3 m_crownPos;

		char m_filePath[256];

		int m_totalPlaNum = 0;
		int m_stageSelectNum = 0;

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
		//�v���C���[��DA(�_�b�V���A�^�b�N)�����֐�
		void PlaAttackBefore(const int plaNum);
		//�v���C���[�̌��݂̏�Ԃ�`����֐�
		void PlaNowState(const int plaNum);
		//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
		void PlaAndEneClash(const int plaNum);
		//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̏����֐�
		void PlaAndPlaClash(const int plaNum);
		//�v���C���[�ɂ�����d�͂�ݒ肷��֐�
		void Gravity(const int plaNum)
		{
			m_moveSpeed[plaNum].y -= nsStdafx::GRAVITY;
		}
		//�������T�E���h��炷�֐�
		void FallSoundPlayBack(const int plaNum);

		//���C
		void Friction(const int plaNum);

	public:
		//�v���C���[�̐l�����擾����֐�
		int GetPlaNum()const { return m_totalPlaNum; }

		Vector2 GetPlaScreenPos(const int plaNum)const { return m_plaScreenPos[plaNum]; }

		//�v���C���[�̈ʒu���擾����֐�
		const Vector3& GetPlaPos(const int plaNum)const { return  m_pos[plaNum]; }

		/// @brief
		/// @param plaNum
		/// @return
		const Vector3& GetPlaSpeed(const int plaNum)const { return m_moveSpeed[plaNum]; }
		const float& GetPlaSpeedX(const int plaNum)const { return m_moveSpeed[plaNum].x; }
		const float& GetPlaSpeedZ(const int plaNum)const { return m_moveSpeed[plaNum].z; }
		//�v���C���[�̌������擾����֐�
		Vector3 GetPlaDir(const int plaNum)const { return m_plaDir[plaNum]; }
		//�v���C���[�̃`���[�W���擾����֐�
		bool GetPlaisTyazi1HanteiFlg(const int plaNum)const { return m_isCharge1HanteiFlg[plaNum]; }
		bool GetPlaisTyazi2HanteiFlg(const int plaNum)const { return m_isCharge2HanteiFlg[plaNum]; }

		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetStageSelectNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }

		void AddWindPowerX(const int plaNum, const float windSpeed) { m_moveSpeed[plaNum].x += windSpeed; }
		void AddWindPowerZ(const int plaNum, const float windSpeed) { m_moveSpeed[plaNum].z += windSpeed; }
	};
}