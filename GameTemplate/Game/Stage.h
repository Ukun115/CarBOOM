#pragma once


namespace nsCARBOOM
{
	class GameScene;
	class TitleScene;
	class StageSelectScene;
	class Player;
	class Enemy;


	class Stage : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		//�X�e�[�W�ԍ�
		enum enStageNum
		{
			ehehe,	//Stage1���P�Ԃɂ��邽�߂�ehehe�����Ē���
			Stage1,
			Stage2,
			Stage3,
			Stage4,
			Stage5
		};

		enum enWindDirection
		{
			UpWind,		//������̕�
			DownWind,	//�������̕�
			LeftWind,	//�������̕�
			RightWind,	//�E�����̕�
		};


		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		Enemy* m_enemy = nullptr;
		SkinModelRender* m_stage = nullptr;


		PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�N���X���쐬
		Effect m_fallSnowEffect[2];		//�A�C�X�X�e�[�W�̍~���Ă����G�t�F�N�g


		bool m_isPauseFlg = false;
		bool m_eneFrictionFlg[6] = { false };
		bool m_plaFrictionFlg[4];


		/// <summary>
		/// �^�C�}�[
		/// </summary>
		int m_fallSnowTimer = nsStdafx::INT_ZERO;
		int m_windDirection = nsStdafx::INT_ZERO;	//���݂̕�


		Vector3 m_plaPos[4];			//�v���C���[4�̕��̃v���C���[�̈ʒu
		Vector3 m_LengthFromStaPivToPla[4];	//�X�e�[�W�̊�_����v���C���[�܂ł̋���

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