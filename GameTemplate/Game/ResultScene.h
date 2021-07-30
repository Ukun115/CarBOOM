#pragma once


namespace nsCARBOOM
{
	class TitleScene;
	class StageSelectScene;
	class GameScene;
	class Player;
	class Fade;


	class ResultScene : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:

		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enSoundNum
		{
			ResultGingle,
			GameBGM,
			DecideSound,
			TotalSoundNumm
		};

		enum enState
		{
			StateIn,	//�t�F�[�h�C��
			StateOut,	//�t�F�[�h�A�E�g
			StateWait,	//�ҋ@
		};

		enum enPlayer
		{
			Player1,
			Player2,
			Player3,
			Player4,
			TotalPlaNum
		};

		enum enNextScene
		{
			NextGameEnd,
			NextTitleScene,
			NextStageSelectScene
		};


		/// <summary>
		/// �N���X�̃|�C���^
		/// </summary>
		Fade* m_fadeOut = nullptr;
		TitleScene* m_titleScene = nullptr;
		StageSelectScene* m_stageSelectScene = nullptr;
		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		SpriteRender* m_resultSprite = nullptr;
		SpriteRender* m_plaNum[TotalPlaNum] = { nullptr };			//�v���C���[4�l���p��
		SpriteRender* m_rankingSprite[TotalPlaNum] = { nullptr };	//�v���C���[4�l���p��
		SoundPlayBack* m_soundPlayBack = nullptr;


		/// <summary>
		/// �t���O
		/// </summary>
		bool m_enableTimerCountFlg = false;
		bool m_plaMoveFlg[TotalPlaNum] = { false };
		bool m_delayTimerOnFlg = true;
		bool m_plaJumpFlg = false;
		bool m_muriFlg = false;


		/// <summary>
		/// �^�C�}�[
		/// </summary>
		unsigned int m_exitTimer = nsStdafx::INT_ZERO;
		int m_plaMoveDelayTimer = nsStdafx::INT_ZERO;
		int m_verticalMoveTimer = nsStdafx::INT_ZERO;


		unsigned int m_plaScore[TotalPlaNum] = { nsStdafx::INT_ZERO };		//�v���C���[4�l���̃X�R�A������z��
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		unsigned int m_select = nsStdafx::INT_ZERO;
		float m_moveSpeed = nsStdafx::FLOAT_ZERO;

		char m_filePath[256];

		Vector3 m_number1Pos = { 900.0f,50.0f,0.0f };		//�P�ʃv���C���[�̕\���ʒu
		Vector3 m_number2Pos = { 900.0f,-50.0f,0.0f };		//�Q�ʃv���C���[�̕\���ʒu
		Vector3 m_number3Pos = { 900.0f,-150.0f,0.0f };	//�R�ʃv���C���[�̕\���ʒu
		Vector3 m_number4Pos = { 900.0f,-250.0f,0.0f };	//�S�ʃv���C���[�̕\���ʒu


		bool Start()override final;
		~ResultScene()override final;
		void Update()override final;


		//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
		void RankingSort();
		//���ǂ̃V�[���ɍs�����؂�ւ���֐�
		void SelectScene();
		//�v���C���[����ʊO�i�E���j����X���C�h���Ă��鏈���֐�
		void SlidePlayerName();
		//�摜���c�ړ�����֐�
		void VerticalMove(const int width, const float speed);
		//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
		void InitRankingImage();
		//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
		void InitPlayerImage();


	public:
		void SetTotalPlayerNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}