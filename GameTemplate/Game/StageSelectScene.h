#pragma once


namespace nsCARBOOM
{
	class TitleScene;
	class GameScene;
	class Fade;


	class StageSelectScene : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		//�X�e�[�W�ԍ�
		enum enStageNum
		{
			ehehe,	//Stage1���P�Ԃɂ��邽�߂�ehehe�����Ē���
			FlatStage,
			DonutStage,
			IceStage,
			WindStage,
			TiltStage,
			RandomStage,
			TotalStageNum
		};

		enum enSoundNum
		{
			TitleSceneBGM,
			DecideSound,
			OnStageSound,
			CarHornSound,
			TotalSoundNum
		};

		//�񋓌^
		enum enFadeState
		{
			StateIn,	//�t�F�[�h�C��
			StateOut,	//�t�F�[�h�A�E�g
			StateWait,	//�ҋ@
		};
		enum enFadeNum
		{
			FadeIn,
			FadeOutBadk,
			FadeOutNext,
			TotalFadeNum
		};


		Light* m_light = nullptr;
		Fade* m_fade[TotalFadeNum] = { nullptr };
		TitleScene* m_titleScene = nullptr;
		GameScene* m_gameScene = nullptr;
		SkinModelRender* m_stage[TotalStageNum] = { nullptr };
		SkinModelRender* m_pla = nullptr;	//�v���C���[
		SpriteRender* m_stageName[TotalStageNum] = { nullptr };
		SpriteRender* m_stageDiscription[TotalStageNum] = { nullptr };	//�����w�i�摜
		SpriteRender* m_operatorDiscription[TotalStageNum] = { nullptr };	//����������摜
		SpriteRender* m_stageSelectSprite = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		SpriteRender* m_Ahukidasi[TotalStageNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;


		/// <summary>
		/// �t���O
		/// </summary>
		bool m_enableUpdateFlg = true;
		bool m_canOnStageSoundPlayFlg[4] = { false };
		bool m_isOperatorFlg[TotalStageNum] = { false };
		int m_nextTitleSceneFlg = nsStdafx::INT_ZERO;

		int m_stageNum = { nsStdafx::INT_ZERO };				//�ǂ̃X�e�[�W��I�����Ă��邩���i�[
		Vector3    m_pos;				//�v���C���[�̈ʒu
		Quaternion m_rot;				//�v���C���[�̉�]
		Vector3 m_moveSpeed;			//�ړ����x
		float m_leftStick_x = { nsStdafx::FLOAT_ZERO };			//���X�e�B�b�N��x���͗�
		float m_leftStick_y = { nsStdafx::FLOAT_ZERO };			//���X�e�B�b�N��y���͗�
		float m_rotAngle = { nsStdafx::FLOAT_ZERO };				//��]�p�x
		Vector3 m_friction;				//���C
		Vector3 m_diff[4];		//�X�e�[�W�ƃv���C���[�Ƃ̋���
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector3 m_stageDiscriptionLetterPos = { -370.0f,-20.0f,0.0f };

		//�f�o�b�O�p
		SkinModelRender* m_skinModelRenderArrow = nullptr;
		Vector3 m_arrowPos;
		Quaternion m_arrowRot;
		Vector3 m_arrowSize;

		char m_filePath[256];


		bool Start()override final;
		~StageSelectScene()override final;
		void Update()override final;


		//�Q�[����ʑJ�ڏ����֐�
		void GameSceneTransition();
		//�v���C���[�̒ʏ�ړ������֐�
		void PlaMove();
		//�v���C���[�̈ړ����x�ɕ␳������֐�
		void PlaSpeedCorrection();
		//�v���C���[�̉�]�����֐�
		void PlaTurn();
		//�v���C���[�̈ʒu,��]�̏����X�V����֐�
		void PlaDataUpdate()
		{
			//�ʒu���Z�b�g
			m_pla->SetPosition(m_pos);
			//��]���Z�b�g
			m_pla->SetRotation(m_rot);
		}
		//�X�e�[�W�̏�ɂ���Ƃ����̃X�e�[�W��I���ł���֐�
		void TouchStage();
		//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���֐�
		void AvoidScreenOutSide();
		//�x�N�g��������������f�o�b�N�֐�
		void PlaMooveSpeedDebug();
		//�N���N�V������炷�֐�
		void CarHorn();
		//�v���C���[������܂Ƃ߂Ă���֐�
		void PlayerInformation();
		//
		Vector3 WhatStageModelPos(const int stageNum);
		//
		Vector3 WhatStageNamePos(int stageNum);
		//
		Vector3 WhatFukidasiPos(int stageNum);


	public:

		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ���������Ă���
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}