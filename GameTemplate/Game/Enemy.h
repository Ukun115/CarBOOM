///<<summary>
///�GNPC�̃��C������
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Player;
	class Stage;
	class EnemyMoveSpeedArrow;
	class EnemyTurn;
	class EnemyEffect;
	class EnemyMoveSpeed;
	class EnemyPatoLump;

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
		//�G�̃��X�|�[�������_���ʒu
		enum enRandomEneRespornPos
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
		GameScene* m_gameScene = nullptr;
		SkinModelRender* m_enemy[TotalEnemyNum] = { nullptr };
		Stage* m_stage = nullptr;
		Player* m_player = nullptr;
		SoundPlayBack* m_soundPlayBack = nullptr;
		EnemyMoveSpeedArrow* m_enemyMoveSpeedArrow = nullptr;
		EnemyTurn* m_enemyTurn = nullptr;
		EnemyEffect* m_enemyEffect = nullptr;
		EnemyMoveSpeed* m_enemyMoveSpeed = nullptr;
		EnemyPatoLump* m_enemyPatoLump = nullptr;

		CharacterController m_charaCon[TotalEnemyNum];		//�G�U�̕��̃L�����N�^�R���g���[���[�N���X���쐬

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
		Vector3 m_moveSpeed[TotalEnemyNum];			//�G�U�̕��̈ړ����x
		Vector3 m_samDir[TotalEnemyNum];			//�G�ƃv���C���[�̌���
		Vector3    m_plaPos[TotalPlayerNum];			//�v���C���[4�̕��̃v���C���[�̈ʒu
		Vector3    m_mostShortDistance[TotalPlayerNum];	//�v���C���[4�̕��ƓG�̋���
		//�����ɓr���ŕύX���Ȃ��l�Ȃ̂ŁAconst�g�������B
		Vector3 m_ranEneResPos[TotalResPos];		//�G�̃��X�|�[���ʒu�v10����

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
		int m_windDirection = nsStdafx::INT_ZERO;	//���݂̕�
		int m_totalPlaNum = nsStdafx::INT_ZERO;
		int m_stageSelectNum = nsStdafx::INT_ZERO;

		bool Start()override final;
		~Enemy()override final;
		void Update()override final;

		//�G�̈ʒu,��]���X�V����֐�
		void EneDataUpdate(const int eneNum) const;
		//�G��DA�����֐�
		void EneDA(const int eneNum);
		//�G����Ŋ��̃v���C���[����������֐�
		void Distance(const int eneNum);
		//�G�̃��X�|�[�������֐�
		void EneResporn(const int eneNum);
		//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
		void PlaAndEneClash(const int eneNum);
		//�v���C���[�ƓG�Ƃ̋����𑪂��ԋ߂��v���C���[���Z�o����֐�
		void DistanceOfPlaToEne(const int eneNum);
		//�������T�E���h��炷�֐�
		void FallSoundPlayBack(const int eneNum);
		//
		Vector3 WhatEneRandomResPos(const int eneNum);

	public:
		/// <summary>
		/// �Q�b�^�[
		/// </summary>
		//�G�̈ʒu���擾����֐�
		Vector3 GetEnemyPos(const int eneNum)const { return m_enePos[eneNum]; }
		//��ԋ߂��v���C���[���擾����֐�
		Vector3 GetMostShortDistanceDir(const int eneNum)const { return m_mostShortDistanceDir[0]; }
		//
		float GetPlayerToSetten1Angle(const int eneNum)const { return m_PlayerToSetten1Angle[eneNum]; }
		//
		float GetPlayerToSetten2Angle(const int eneNum)const { return m_PlayerToSetten2Angle[eneNum]; }
		//
		Vector3 GetEneToSetten1Dir(const int eneNum)const { return  m_EneToSetten1Dir[eneNum]; }
		//
		Vector3 GetEneToSetten2Dir(const int eneNum)const { return m_EneToSetten2Dir[eneNum]; }

		int GetStageNum()const { return m_stageSelectNum; }
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