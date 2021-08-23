///<<summary>
///�^�C�g����ʂ̃��C������
///</summary>

#pragma once

namespace nsCARBOOM
{
	class StageSelectScene;
	class Fade;
	class TitleName;
	class PressStartButton;
	class PressASpeechBalloon;
	class PlayerName;

	class TitleScene : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
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
			TotalPlaNum	//�v���C���[�̍ő吔
		};

		enum enSoundNum
		{
			TitleSceneGingle,	//�^�C�g���W���O��
			TitleSceneBGM,		//�^�C�g���V�[����BGM
			DecideSound,		//���艹
			EngineSound,		//�G���W���T�E���h
			TotalSoundNum
		};

		enum enFadeState
		{
			StateIn,	//�t�F�[�h�C��
			StateOut,	//�t�F�[�h�A�E�g
			StateWait,	//�ҋ@
		};
		enum enFadeNum
		{
			FadeIn,
			FadeOut,
			TotalFadeNum
		};

		enum enNextScene
		{
			StateSelectScene,
			GameEnd
		};

		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		Fade* m_fade[TotalFadeNum] = { nullptr };
		SoundPlayBack* m_soundPlayBack = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		TitleName* m_titleName = nullptr;
		SpriteRender* m_titleSprite = nullptr;
		PressStartButton* m_pressStartButton = nullptr;
		PressASpeechBalloon* m_pressASpeechBalloon = nullptr;
		PlayerName* m_playerName = nullptr;

		/// <summary>
		/// �t���O
		/// </summary>
		bool m_enableUpdateFlg = true;			//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������

		unsigned int m_totalPlaNum = Player2;			//�v���C���[�̍��v�����v��
		int m_nextScene = nsStdafx::INT_ZERO;

		bool Start()override final;
		~TitleScene()override final;
		void Update()override final;

		//�v���C���[��ǉ�����֐�
		void AddPlayer();
		//�Q�[����ʂɑJ�ڂ���֐�
		void StageSelectSceneTransition();
		//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
		void PushStartButton(int plaNum);
		//�{�^���������ꂽ�Ƃ��̏����֐�
		void PushSelectButton(int plaNum);
		//�I�����ꂽ���̃V�[���ɍs�������֐�
		void NextScene();

	public:

	};
}