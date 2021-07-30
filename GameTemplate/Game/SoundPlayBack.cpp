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


	//削除関数

	void SoundPlayBack::TitleSceneDeleteGO()const
	{
		if (m_titleSceneSound[TitleSceneGingle] != nullptr)
		{
			//タイトルBGMを削除
			DeleteGO(m_titleSceneSound[TitleSceneGingle]);
		}
		if (m_titleSceneSound[TitleSceneBGM] != nullptr)
		{
			//エンジン音を削除
			DeleteGO(m_titleSceneSound[TitleSceneBGM]);
		}
		if (m_titleSceneSound[TitleSceneDecideSound] != nullptr)
		{
			//タイトルジングルを削除
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
		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//サウンドを削除
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
		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//サウンドを削除
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
		//全ての敵を削除。
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
		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < TotalPlayerNum; plaNum++)
		{
			//サウンドを削除
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
			//タイトル名ジングルサウンドの初期化
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneGingle.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case TitleSceneBGM:
			//タイトルBGMサウンドの初期化
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneBGM.wav");
			m_titleSceneSound[soundNum]->SetVolume(0.01f);
			m_titleSceneSound[soundNum]->Play(true);	//真でループ再生

			break;

		case TitleSceneDecideSound:
			//決定サウンド
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case EngineSound:

			//エンジンサウンド
			m_titleSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_titleSceneSound[soundNum]->Init(L"Assets/sound/AddPlayer.wav");
			m_titleSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_titleSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;
		}
	}

	void SoundPlayBack::StageSelectSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case StageSelectSceneTitleSceneBGM:
			//タイトルBGMサウンドの初期化
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/TitleSceneBGM.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(0.1f);
			m_stageSelectSceneSound[soundNum]->Play(true);	//真でループ再生

			break;

		case StageSelectSceneDecideSound:
			//決定サウンド
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case OnStageSound:
			//ステージを選択できるようになったら鳴らすサウンドの初期化
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/OnStage.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case StageSelectSceneCarHornSound:
			//クラクションサウンドの初期化
			m_stageSelectSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_stageSelectSceneSound[soundNum]->Init(L"Assets/sound/CarHorn.wav");
			m_stageSelectSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_stageSelectSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;
		}
	}

	void SoundPlayBack::GameSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case GameStartGingle:
			//ゲームスタートジングルサウンドの初期化
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/GameStartGingle.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case CountDownSound:
			//カウントダウンサウンドの初期化
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/CountDown.wav");
			m_gameSceneSound[soundNum]->SetVolume(1.0f);
			m_gameSceneSound[soundNum]->Play(false);	//真でワンショット再生

			break;

		case GameSceneGameBGM:
			//ゲーム中のBGMサウンドの初期化
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/GameBGM.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(true);	//真でループ再生

			break;

		case WhistleSound:
			//ホイッスルサウンドの初期化
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/Whistle.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case PauseSound:
			//ポーズサウンドの初期化
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/PauseSound.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case GameSceneDecideSound:
			//決定サウンド
			m_gameSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_gameSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_gameSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_gameSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;
		}
	}

	void SoundPlayBack::PlayerSoundPlayBack(const int soundNum, const int plaNum)
	{
		switch (soundNum)
		{
		case PlaShootDownSound:
			//撃墜サウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/ShootDown.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case CarHornSound:
			//クラクションサウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/CarHorn.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case PlaFallSound:
			//落下サウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Fall.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case ChargeSound:
			//チャージサウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Charge.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case Dash1Sound:
			//ダッシュ１サウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/PlaDash1.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case Dash2Sound:
			//ダッシュ２サウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/PlaDash2.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;
		case PlaAndPlaClashSound:
			//プレイヤーとプレイヤーがぶつかったときのサウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/Clash1.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(nsSoundPlayBack::MAX_VOLUME);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生

			break;
		case ChargeEnd:
			//チャージ完了サウンドの初期化
			m_playerSound[plaNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_playerSound[plaNum][soundNum]->Init(L"Assets/sound/ChargeEnd.wav");
			m_playerSound[plaNum][soundNum]->SetVolume(0.1f);
			m_playerSound[plaNum][soundNum]->Play(false);	//偽でワンショット再生
		}
	}

	void SoundPlayBack::EnemySoundPlayBack(const int soundNum, const int eneNum)
	{
		switch (soundNum)
		{
		case EneShootDownSound:
			//撃墜サウンドの初期化
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/ShootDown.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(0.2f);
			m_enemySound[eneNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case EneFallSound:
			//落下サウンドの初期化
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/Fall.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(0.1f);
			m_enemySound[eneNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case DashSound:
			//落下サウンドの初期化
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			m_randomDashSoundNum = rand() % 9;

			//TODO: サウンドのファイルパスを読み込むのもモデルデータのファイルパス読み込み方法のようにする。

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
			m_enemySound[eneNum][soundNum]->Play(false);	//偽でワンショット再生

			break;

		case EnePlaAndEneClashSound:
			//プレイヤーとプレイヤーがぶつかったときのサウンドの初期化
			m_enemySound[eneNum][soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_enemySound[eneNum][soundNum]->Init(L"Assets/sound/Clash2.wav");
			m_enemySound[eneNum][soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_enemySound[eneNum][soundNum]->Play(false);	//偽でワンショット再生

			break;
		}
	}

	void SoundPlayBack::ResultSceneSoundPlayBack(const int soundNum)
	{
		switch (soundNum)
		{
		case ResultGingle:
			//リザルトジングルの初期化
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/ResultGingle.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_resultSceneSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;

		case ResultSceneGameBGM:
			//ゲーム中のBGMサウンドの初期化
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/GameBGM.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(0.01f);
			m_resultSceneSceneSound[soundNum]->Play(true);	//真でループ再生

			break;

		case ResultSceneDecideSound:
			//決定サウンド
			m_resultSceneSceneSound[soundNum] = NewGO<SoundSource>(nsStdafx::PRIORITY_0, nullptr);
			m_resultSceneSceneSound[soundNum]->Init(L"Assets/sound/Decide.wav");
			m_resultSceneSceneSound[soundNum]->SetVolume(nsSoundPlayBack::HALF_VOLUME);
			m_resultSceneSceneSound[soundNum]->Play(false);	//偽でワンショット再生

			break;
		}
	}
}