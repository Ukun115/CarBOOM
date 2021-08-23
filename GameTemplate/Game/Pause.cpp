///<<summary>
///ポーズ機能処理
///</summary>

#include "stdafx.h"
#include "Pause.h"
#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "SoundPlayBack.h"

namespace nsCARBOOM
{
	namespace nsPause
	{
		const float PAUSE_SPRITE_TATE = 600.0f;
		const float PAUSE_SPRITE_YOKO = 300.0f;
		const float GRAYBACK_SCA = 1500.0f;
		const float HALF_VOLUME = 0.5f;
	}

	bool Pause::Start()
	{
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		m_stage = FindGO<Stage>(nsStdafx::STAGE_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		m_pauseSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		//ポーズ画像を初期化
		m_pauseSprite->Init("Pause", nsPause::PAUSE_SPRITE_TATE, nsPause::PAUSE_SPRITE_YOKO);
		m_pauseSprite->Deactivate();

		m_grayBack = NewGO<SpriteRender>(nsStdafx::PRIORITY_5, nullptr);
		//ポーズ中灰色にする画像を初期化
		m_grayBack->Init("GrayBack", nsPause::GRAYBACK_SCA, nsPause::GRAYBACK_SCA);
		m_grayBack->Deactivate();

		return true;
	}

	Pause::~Pause()
	{
		DeleteGO(m_pauseSprite);
		DeleteGO(m_grayBack);
	}

	void Pause::Update()
	{
		//ポーズ機能
		for (int plaNum = Player1; plaNum < m_gameScene->GetTotalPlaNum(); plaNum++)
		{
			//セレクトボタンが押されたときのみreturn以降を処理する
			if (!g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				return;
			}
			//ポーズ画面を開く音
			m_soundPlayBack->GameSceneSoundPlayBack(PauseSound);

			//ポーズ中じゃないとき、
			if (!m_isPauseFlg)
			{
				//ポーズにする
				m_pauseSprite->Activate();
				m_grayBack->Activate();
				if (m_soundPlayBack->m_gameSceneSound[GameBGM] != nullptr)
				{
					m_soundPlayBack->m_gameSceneSound[GameBGM]->SetVolume(nsStdafx::FLOAT_ZERO);
				}

				m_isPauseFlg = true;
			}
			//ポーズ中の時、
			else
			{
				m_pauseSprite->Deactivate();
				m_grayBack->Deactivate();
				if (m_soundPlayBack->m_gameSceneSound[GameBGM] != nullptr)
				{
					m_soundPlayBack->m_gameSceneSound[GameBGM]->SetVolume(nsPause::HALF_VOLUME);
				}

				//ポーズを外す
				m_isPauseFlg = false;
			}

			m_gameScene->SetPauseFlg(m_isPauseFlg);
			m_player->SetPauseFlg(m_isPauseFlg);
			m_enemy->SetPauseFlg(m_isPauseFlg);
			m_stage->SetPauseFlg(m_isPauseFlg);
		}
	}

	void Pause::GrayBackActive()
	{
		m_grayBack->Activate();
	}
}