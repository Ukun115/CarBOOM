///<<summary>
///�X�e�[�W����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;
	class TitleScene;
	class StageSelectScene;
	class Player;
	class EnemyMoveSpeed;

	class Stage : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		//�X�e�[�W�ԍ�
		enum enStageNum
		{
			Stage1 = 1,
			Stage2,
			Stage3,
			Stage4,
			Stage5
		};

		enum enPlayer
		{
			Player1,
			TotalPlaNum = 4
		};
		enum enEnemy
		{
			Enemy1,
			TotalEneNum = 6
		};

		enum enWindDirection
		{
			UpWind,		//������̕�
			DownWind,	//�������̕�
			LeftWind,	//�������̕�
			RightWind,	//�E�����̕�
		};

		enum enSnowNum
		{
			Snow1,
			Snow2,
			TotalSnowNum
		};

		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		EnemyMoveSpeed* m_enemyMoveSpeed = nullptr;
		SkinModelRender* m_stage = nullptr;

		PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�N���X���쐬
		Effect m_fallSnowEffect[TotalSnowNum];		//�A�C�X�X�e�[�W�̍~���Ă����G�t�F�N�g

		bool m_isPauseFlg = false;
		bool m_eneFrictionFlg[TotalEneNum] = { false };
		bool m_plaFrictionFlg[TotalPlaNum];

		/// <summary>
		/// �^�C�}�[
		/// </summary>
		int m_fallSnowTimer = nsStdafx::INT_ZERO;
		int m_windDirection = nsStdafx::INT_ZERO;	//���݂̕�

		Vector3 m_plaPos[TotalPlaNum];			//�v���C���[4�̕��̃v���C���[�̈ʒu
		Vector3 m_LengthFromStaPivToPla[TotalPlaNum];	//�X�e�[�W�̊�_����v���C���[�܂ł̋���

		int m_stageSelectNum = nsStdafx::INT_ZERO;
		int m_nowTime = nsStdafx::INT_ZERO;
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		char m_stageModelFilePath[256];

		bool Start() override final;
		~Stage()override final;
		void Update() override final;

		//��G�t�F�N�g�����֐�
		void SnowFall();
		//���̉e����^���鏈��
		void WindInpact();
		//�X�����鏈��
		void Tilt();

	public:
		int GetWindDirection()const { return m_windDirection; }

		void SetNowTime(const int nowTime) { m_nowTime = nowTime; }
		void SetSelectStageNum(const int stageSelectNum) { m_stageSelectNum = stageSelectNum; }
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
		void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }
	};
}