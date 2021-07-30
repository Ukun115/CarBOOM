#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Player;


	class Enemy : public IGameObject	//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enEnemy
		{
			Enemy1,		 //�G�P�̔z��ł̔ԍ�
			Enemy2,		 //�G�Q�̔z��ł̔ԍ�
			Enemy3,		 //�G�R�̔z��ł̔ԍ�
			Enemy4,		 //�G�S�̔z��ł̔ԍ�
			Enemy5,		 //�G�T�̔z��ł̔ԍ�
			Enemy6,		 //�G�U�̔z��ł̔ԍ�
			TotalEnemyNum	 //�G�̑���
		};
		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
			Player2,		//2P�̔z��ł̔ԍ�
			Player3,		//3P�̔z��ł̔ԍ�
			Player4,		//4P�̔z��ł̔ԍ�
			TotalPlayerNum	//�v���C���[�̍ő吔
		};
		//�G�̃����_�����X�|�[���ʒu
		enum enRanEneResPos
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
			TotalResPos
		};

		enum enSoundNum
		{
			ShootDownSound,
			FallSound,
			DashSound,
			PlaAndEneClashSound,
			TotalSoundNum
		};


		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		Light* m_light = nullptr;
		GameScene* m_gameScene = nullptr;
		SkinModelRender* m_enemy[TotalEnemyNum] = { nullptr };
		Stage* m_stage = nullptr;
		Player* m_player = nullptr;
		SoundPlayBack* m_soundPlayBack = nullptr;


		CharacterController m_charaCon[TotalEnemyNum];		//�G�U�̕��̃L�����N�^�R���g���[���[�N���X���쐬
		Effect m_shootDownEffect[TotalEnemyNum];		//���������Ƃ��̌��ăG�t�F�N�g


		/// <summary>
		/// �t���O
		/// </summary>
		bool m_canCtCountFlg[TotalEnemyNum] = { false };		//�G�U�̕���CT�̃t���O
		bool m_canFallSoundPlayFlg[TotalEnemyNum] = { false };			//�������𗎉���������Ȃ�Ȃ��悤�ɂ���t���O
		bool m_canPlaAndEneClashSoundPlayFlg[TotalEnemyNum] = { false };
		bool m_isPauseFlg = false;

		/// <summary>
		/// �^�C�}�[
		/// </summary>
		unsigned int m_startDelayTimer = nsStdafx::INT_ZERO;		//�X�^�[�g��x�点��^�C�}�[
		unsigned int m_startDelay[TotalEnemyNum] = { nsStdafx::INT_ZERO };			//�G�U�̕��̃X�^�[�g�x������
		unsigned int m_CTTime[TotalEnemyNum] = { nsStdafx::INT_ZERO };					//�G�U�̕��̍U��CT�^�C�}�[
		unsigned int m_eneCTCount[TotalEnemyNum] = { nsStdafx::INT_ZERO };			//�G�U�̕���CT����


		//�G���
		Vector3    m_enePos[TotalEnemyNum];			//�G�U�̕��̓G�̈ʒu
		Quaternion m_rot[TotalEnemyNum];			//�G�U�̕��̓G�̉�]
		float m_rotAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };			//�G�U�̕��̉�]�p�x
		Vector3 m_moveSpeed[TotalEnemyNum];			//�G�U�̕��̈ړ����x
		Vector3 m_samDir[TotalEnemyNum];			//�G�ƃv���C���[�̌���
		Vector3 m_friction[TotalEnemyNum];			//�G�U�̕��̖��C
		Vector3    m_plaPos[TotalPlayerNum];			//�v���C���[4�̕��̃v���C���[�̈ʒu
		Vector3    m_mostShortDistance[TotalPlayerNum];	//�v���C���[4�̕��ƓG�̋���
		//�����ɓr���ŕύX���Ȃ��l�Ȃ̂ŁAconst�g�������B
		Vector3 m_ranEneResPos[TotalResPos];		//�G�̃��X�|�[���ʒu�v10����

		float m_randEneResAngle[8] = { nsStdafx::FLOAT_ZERO };		//�G�̃��X�|�[����]�p�x4����
		Vector3 m_eneDir[TotalPlayerNum];			//����
		Vector3 m_diff;				//�v���C���[�ƓG�Ƃ̋���
		unsigned int m_pushPlayer[TotalEnemyNum] = { nsStdafx::INT_ZERO };
		unsigned int m_randomDashSoundNum = nsStdafx::INT_ZERO;
		Vector3 m_mostShortDistanceDir[TotalPlayerNum]; //�v���C���[4�̕�����G�̌���
		Vector3 m_settenPos1[TotalEnemyNum];		 //�G�Ɖ~�̐ړ_1�̍��W
		Vector3 m_settenPos2[TotalEnemyNum];		 //�G�Ɖ~�̐ړ_2�̍��W
		Vector3 m_EneToSetten1[TotalEnemyNum];		 //�G����ړ_1�̋���
		Vector3 m_EneToSetten2[TotalEnemyNum];		 //�G����ړ_2�̋���
		Vector3 m_EneToSetten1Dir[TotalEnemyNum];    //�G����ړ_1�̌���
		Vector3 m_EneToSetten2Dir[TotalEnemyNum];	 //�G����ړ_2�̌���
		Vector3 m_centerKyori[TotalEnemyNum];		 //�G���璆�S�̋���
		float m_CenterToEneAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };		//���S����G��cos
		float m_CenterToSettenAngle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };		//���S����ړ_��cos
		float m_PlayerToSetten1Angle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };	//�v���C���[����ړ_1��cos
		float m_PlayerToSetten2Angle[TotalEnemyNum] = { nsStdafx::FLOAT_ZERO };	//�v���C���[����ړ_2��cos
		int m_hankei = 3600;       //���̔��a��2��
		Vector3 m_center;  //���S�̍��W
		Vector3 m_enePoiLigPos;
		int	m_poiLigNum = nsStdafx::INT_ZERO;
		int m_windDirection = nsStdafx::INT_ZERO;	//���݂̕�
		int m_totalPlaNum = nsStdafx::INT_ZERO;
		int m_stageSelectNum = nsStdafx::INT_ZERO;


		//�f�o�b�O�p���
		SkinModelRender* m_skinModelRenderArrow[TotalEnemyNum] = { nullptr };
		Vector3 m_arrowPos[TotalEnemyNum];
		Quaternion m_arrowRot[TotalEnemyNum];
		Vector3 m_arrowSize;


		bool Start()override final;
		~Enemy()override final;
		void Update()override final;


		//�G�̈ʒu,��]���X�V����֐�
		void EneDataUpdate(const int eneNum) const;
		//�G��DA�����֐�
		void EneDA(const int eneNum);
		//�G�̉�]�����֐�
		void EneTurn(const int eneNum);
		//�G����Ŋ��̃v���C���[����������֐�
		void Distance(const int eneNum);
		//�G�̃��X�|�[�������֐�
		void EneResporn(const int eneNum);
		//�G�̖��C�����֐�
		void EneFriction(const int eneNum);
		//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
		void PlaAndEneClash(const int eneNum);
		//�G�ɂ�����d�͂�ݒ肷��֐�
		void Gravity(const int eneNum)
		{
			m_moveSpeed[eneNum].y -= nsStdafx::GRAVITY;
		}
		//�G�̃X�s�[�h�x�N�g��������������f�o�b�N�֐�
		void EneMooveSpeedDebug(const int eneNum);
		//�v���C���[�ƓG�Ƃ̋����𑪂��ԋ߂��v���C���[���Z�o����֐�
		void DistanceOfPlaToEne(const int eneNum);
		//�������T�E���h��炷�֐�
		void FallSoundPlayBack(const int eneNum);
		//�p�g�����v���p�g�J�[�̏�ɃZ�b�g����֐�
		void PointLightSetting(const int eneNum);
		//
		int WhatEneRandomResRot(const int eneNum);
		//
		Vector3 WhatEneRandomResPos(const int eneNum);

	public:

		/// <summary>
		/// �Q�b�^�[
		/// </summary>
		//�G�̈ʒu���擾����֐�
		Vector3 GetEnemyPos(const int eneNum)const { return m_enePos[eneNum]; }
		//�G�̑��x���擾����֐�
		Vector3 GetEnemySpeed(const int eneNum)const { return m_moveSpeed[eneNum]; }
		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetStageSelectNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }

		void AddWindPowerX(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].x += windSpeed; }
		void AddWindPowerZ(const int eneNum, const float windSpeed) { m_moveSpeed[eneNum].z += windSpeed; }
	};
}