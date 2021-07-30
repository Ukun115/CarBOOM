#include "stdafx.h"
#include "SoundPlayBack.h"
#include<random>


namespace nsCARBOOM
{
	namespace nsSoundPlayBack
	{
		const float MAX_VOLUME = 1.0f;
		const float HALF_VOLUME = 0.5f;
	}


	bool SoundPlayBack::Start()
	{

		return true;
	}


	SoundPlayBack::~SoundPlayBack()
	{

	}


	//�폜�֐�

	void SoundPlayBack::TitleSceneDeleteGO()const
	{
		if (m_titleSceneSound[TitleSceneGingle] != nullptr)
		{
			//�^�C�g��BGM���폜
			DeleteGO(m_titleSceneSound[TitleSceneGingle]);
		}
		if (m_titleSceneSound[TitleSceneBGM] != nullptr)
		{
			//�G���W�������폜
			DeleteGO(m_titleSceneSound[TitleSceneBGM]);
		}
		if (m_titleSceneSound[TitleSceneDecideSound] != nullptr)
		{
			//�^�C�g���W���O�����폜
			DeleteGO(m_titleSceneSound[TitleSceneDecideSound]);
		}
		if (m_titleSceneSound[EngineSound] != nullptr)
		{
			DeleteGO(m_titleSceneSound[EngineSound]);
		}
	}

	void SoundPlayBack::StageSelectSceneDeleteGO()const
	{
		if (m_stageSelectSceneSound[StageSelectSceneTitleSceneBGM] != nullptr)
		{
			DeleteGO(m_stageSelectSceneSound[StageSelectSceneTitleSceneBGM]);
		}
		if (m_stageSelectSceneSound[StageSelectSceneDecideSound] != nullptr)
		{
			DeleteGO(m_stageSelectSceneSound[StageSelectSceneDecideSound]);
		}
		if (m_stageSelectSceneSound[OnStageSound] != nullptr)
		{
			DeleteGO(m_stageSelectSceneSound[OnStageSound]);
		}
		if (m_stageSelectSceneSound[CarHornSound] != nullptr)
		{
			DeleteGO(m_stageSelectSceneSound[CarHornSound]);
		}
	}

	void SoundPlayBack::GameSceneDeleteGO()const
	{
		//�o�^����Ă���v���C���[�����[�v
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//�T�E���h���폜
			if (m_gameSceneSound[GameStartGingle] != nullptr)
			{
				DeleteGO(m_gameSceneSound[GameStartGingle]);
			}
			if (m_gameSceneSound[CountDownSound] != nullptr)
			{
				DeleteGO(m_gameSceneSound[CountDownSound]);
			}
			if (m_gameSceneSound[GameSceneGameBGM] != nullptr)
			{
				DeleteGO(m_gameSceneSound[GameSceneGameBGM]);
			}
			if (m_gameSceneSound[WhistleSound] != nullptr)
			{
				DeleteGO(m_gameSceneSound[WhistleSound]);
			}
			if (m_gameSceneSound[PauseSound] != nullptr)
			{
				DeleteGO(m_gameSceneSound[PauseSound]);
			}
			if (m_gameSceneSound[GameSceneDecideSound] != nullptr)
			{
				DeleteGO(m_gameSceneSound[GameSceneDecideSound]);
			}
		}
	}

	void SoundPlayBack::PlayerDeleteGO()const
	{
		//�o�^����Ă���v���C���[�����[�v
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//�T�E���h���폜
			if (m_playerSound[plaNum][PlaShootDownSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][PlaShootDownSound]);
			}
			if (m_playerSound[plaNum][CarHornSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][CarHornSound]);
			}
			if (m_playerSound[plaNum][PlaFallSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][PlaFallSound]);
			}
			if (m_playerSound[plaNum][ChargeSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][ChargeSound]);
			}
			if (m_playerSound[plaNum][Dash1Sound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][Dash1Sound]);
			}
			if (m_playerSound[plaNum][Dash2Sound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][Dash2Sound]);
			}
			if (m_playerSound[plaNum][PlaAndPlaClashSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][PlaAndPlaClashSound]);
			}
			if (m_playerSound[plaNum][PlaPlaAndEneClashSound] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][PlaPlaAndEneClashSound]);
			}
			if (m_playerSound[plaNum][ChargeEnd] != nullptr)
			{
				DeleteGO(m_playerSound[plaNum][ChargeEnd]);
			}
		}
	}

	void SoundPlayBack::EnemyDeleteGO()const
	{
		//�S�Ă̓G���폜�B
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			if (m_enemySound[eneNum][EneShootDownSound] != nullptr)
			{
				DeleteGO(m_enemySound[eneNum][EneShootDownSound]);
			}
			if (m_enemySound[eneNum][EneFallSound] != nullptr)
			{
				DeleteGO(m_enemySound[eneNum][EneFallSound]);
			}
			if (m_enemySound[eneNum][DashSound] != nullptr)
			{
				DeleteGO(m_enemySound[eneNum][DashSound]);
			}
			if (m_enemySound[eneNum][EnePlaAndEneClashSound] != nullptr)
			{
				DeleteGO(m_enemySound[eneNum][EnePlaAndEneClashSound]);
			}
		}
	}

	void SoundPlayBack::ResultSceneDeleteGO()const
	{
		//�o�^����Ă���v���C���[�����[�v
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//�T�E���h���폜
			if (m_resultSceneSceneSound[ResultGingle] != nullptr)
			{
				DeleteGO(m_resultSceneSceneSound[ResultGingle]);
			}
			if (m_resultSceneSceneSound[ResultSceneGameBGM] != nullptr)
			{
				DeleteGO(m_resultSceneSceneSound[ResultSceneGameBGM]);
			}
			if (m_resultSceneSceneSound[ResultSceneDecideSound] != nullptr)
			{
				DeleteGO(m_resultSceneSceneSound[ResultSceneDecideSound]);
			}
		}
	}


	void SoundPlayBack::Update()
	{

	}


	void SoundPlayBack::TitleSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case TitleSceneGingle:
			//�^�C�g�����W���O���T�E���h�̏�����
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneGingle.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case TitleSceneBGM:
			//�^�C�g��BGM�T�E���h�̏�����
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneBGM.wav");
			m_titleSceneSound[soundNum]->SetVolume(0.01f);
			m_titleSceneSound[soundNum]->Play(true);	//�^�Ń��[�v�Đ�

			break;

		case TitleSceneDecideSound:
			//����T�E���h
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case EngineSound:

			//�G���W���T�E���h
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/AddPlayer.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		}
	}

	void SoundPlayBack::StageSelectSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case StageSelectSceneTitleSceneBGM:
			//�^�C�g��BGM�T�E���h�̏�����
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneBGM.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(0.1f);
			m_stageSelectSceneSound[soundNum]->Play(true);	//�^�Ń��[�v�Đ�

			break;

		case StageSelectSceneDecideSound:
			//����T�E���h
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case OnStageSound:
			//�X�e�[�W��I���ł���悤�ɂȂ�����炷�T�E���h�̏�����
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/OnStage.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case StageSelectSceneCarHornSound:
			//�N���N�V�����T�E���h�̏�����
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/CarHorn.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		}
	}

	void SoundPlayBack::GameSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case GameStartGingle:
			//�Q�[���X�^�[�g�W���O���T�E���h�̏�����
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/GameStartGingle.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case CountDownSound:
			//�J�E���g�_�E���T�E���h�̏�����
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/CountDown.wav");
			m_gameSceneSound[soundNum]->SetVolume(1.0f);
			m_gameSceneSound[soundNum]->Play(false);	//�^�Ń����V���b�g�Đ�

			break;

		case GameSceneGameBGM:
			//�Q�[������BGM�T�E���h�̏�����
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/GameBGM.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(true);	//�^�Ń��[�v�Đ�

			break;

		case WhistleSound:
			//�z�C�b�X���T�E���h�̏�����
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/Whistle.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case PauseSound:
			//�|�[�Y�T�E���h�̏�����
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/PauseSound.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case GameSceneDecideSound:
			//����T�E���h
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		}
	}

	void SoundPlayBack::PlayerSoundPlayBack(const int soundNum, const int plaNum)
	{
		switch (soundNum)
		{
		case PlaShootDownSound:
			//���ăT�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/ShootDown.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case CarHornSound:
			//�N���N�V�����T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/CarHorn.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case PlaFallSound:
			//�����T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Fall.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case ChargeSound:
			//�`���[�W�T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Charge.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case Dash1Sound:
			//�_�b�V���P�T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/PlaDash1.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case Dash2Sound:
			//�_�b�V���Q�T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/PlaDash2.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		case PlaAndPlaClashSound:
			//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Clash1.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		case ChargeEnd:
			//�`���[�W�����T�E���h�̏�����
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/ChargeEnd.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�
		}
	}

	void SoundPlayBack::EnemySoundPlayBack(const int soundNum, const int eneNum)
	{
		switch (soundNum)
		{
		case EneShootDownSound:
			//���ăT�E���h�̏�����
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/ShootDown.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(0.2f);
			m_enemySound[eneNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case EneFallSound:
			//�����T�E���h�̏�����
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/Fall.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(0.1f);
			m_enemySound[eneNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case DashSound:
			//�����T�E���h�̏�����
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			//�����_���֐���SEED�i��j��ݒ�
			//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
			srand((int)time(nullptr));
			m_randomDashSoundNum = rand() % 9;

			//TODO: �T�E���h�̃t�@�C���p�X��ǂݍ��ނ̂����f���f�[�^�̃t�@�C���p�X�ǂݍ��ݕ��@�̂悤�ɂ���B

			switch (m_randomDashSoundNum)
			{
			case 0:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash1.wav");
				break;
			case 1:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash2.wav");
				break;
			case 2:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash3.wav");
				break;
			case 3:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash4.wav");
				break;
			case 4:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash5.wav");
				break;
			case 5:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash6.wav");
				break;
			case 6:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash7.wav");
				break;
			case 7:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash8.wav");
				break;
			case 8:
				m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/EneDash9.wav");
				break;
			}
			m_enemySound[eneNum][soundNum]->SetVolume(0.3f);
			m_enemySound[eneNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case EnePlaAndEneClashSound:
			//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h�̏�����
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/Clash2.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_enemySound[eneNum][soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		}
	}

	void SoundPlayBack::ResultSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case ResultGingle:
			//���U���g�W���O���̏�����
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/ResultGingle.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_resultSceneSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;

		case ResultSceneGameBGM:
			//�Q�[������BGM�T�E���h�̏�����
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/GameBGM.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(0.01f);
			m_resultSceneSceneSound[soundNum]->Play(true);	//�^�Ń��[�v�Đ�

			break;

		case ResultSceneDecideSound:
			//����T�E���h
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_resultSceneSceneSound[soundNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			break;
		}
	}
}