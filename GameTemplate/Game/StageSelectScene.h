///<<summary>
///�X�e�[�W�I����ʂ̃��C������
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleScene;
	class GameScene;
	class Fade;
	class StageSelectScenePlayer;

	class StageSelectScene : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		//�X�e�[�W�ԍ�
		enum enStageNum
		{
			FlatStage = 1,
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
		SpriteRender* m_stageName[TotalStageNum] = { nullptr };
		SpriteRender* m_stageDiscription[TotalStageNum] = { nullptr };	//�����w�i�摜
		SpriteRender* m_operatorDiscription[TotalStageNum] = { nullptr };	//����������摜
		SpriteRender* m_stageSelectSprite = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		SpriteRender* m_Ahukidasi[TotalStageNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;
		StageSelectScenePlayer* m_stageSelectScenePlayer = nullptr;

		/// <summary>
		/// �t���O
		/// </summary>
		bool m_enableUpdateFlg = true;
		bool m_canOnStageSoundPlayFlg[RandomStage] = { false };
		bool m_isOperatorFlg[TotalStageNum] = { false };
		int m_nextTitleSceneFlg = nsStdafx::INT_ZERO;

		int m_stageNum = { nsStdafx::INT_ZERO };				//�ǂ̃X�e�[�W��I�����Ă��邩���i�[
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		Vector3 m_stageDiscriptionLetterPos = { -370.0f,-20.0f,0.0f };

		Vector3 m_diff[TotalStageNum];		//�X�e�[�W�ƃv���C���[�Ƃ̋���

		char m_filePath[256];

		bool Start()override final;
		~StageSelectScene()override final;
		void Update()override final;

		//�Q�[����ʑJ�ڏ����֐�
		void GameSceneTransition();
		//
		Vector3 WhatStageModelPos(const int stageNum);
		//
		Vector3 WhatStageNamePos(int stageNum);
		//
		Vector3 WhatFukidasiPos(int stageNum);
		//�X�e�[�W�̏�ɂ���Ƃ����̃X�e�[�W��I���ł���֐�
		void TouchStage();

	public:
		/// <summary>
		/// �Z�b�^�[
		/// </summary>
		//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ���������Ă���
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}