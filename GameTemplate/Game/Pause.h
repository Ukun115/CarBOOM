///<<summary>
///�|�[�Y�@�\����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;
	class Player;
	class Enemy;
	class Stage;
	class SoundPlayBack;
	class EnemyPatoLump;

	class Pause : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
		};

		enum enSoundNum
		{
			GameStartGingle,	//�Q�[���X�^�[�g�W���O��
			CountDownSound,		//�J�E���g�_�E���T�E���h
			GameBGM,			//�Q�[����BGM
			WhistleSound,		//�z�C�b�X���T�E���h
			PauseSound,			//�|�[�Y�T�E���h
			DecideSound,
			TotalSoundNum
		};

		SpriteRender* m_pauseSprite = nullptr;
		SpriteRender* m_grayBack = nullptr;
		SoundPlayBack* m_soundPlayBack = nullptr;
		EnemyPatoLump* m_enemyPatoLump = nullptr;

		GameScene* m_gameScene = nullptr;
		Player* m_player = nullptr;
		Enemy* m_enemy = nullptr;
		Stage* m_stage = nullptr;

		bool m_isPauseFlg = false;

		bool Start() override final;
		~Pause()override final;
		void Update() override final;

	public:
		void GrayBackActive();
	};
}