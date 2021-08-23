///<<summary>
///�|�[�Y�@�\����
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
		//�|�[�Y�摜��������
		m_pauseSprite->Init("Pause", nsPause::PAUSE_SPRITE_TATE, nsPause::PAUSE_SPRITE_YOKO);
		m_pauseSprite->Deactivate();

		m_grayBack = NewGO<SpriteRender>(nsStdafx::PRIORITY_5, nullptr);
		//�|�[�Y���D�F�ɂ���摜��������
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
		//�|�[�Y�@�\
		for (int plaNum = Player1; plaNum < m_gameScene->GetTotalPlaNum(); plaNum++)
		{
			//�Z���N�g�{�^���������ꂽ�Ƃ��̂�return�ȍ~����������
			if (!g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				return;
			}
			//�|�[�Y��ʂ��J����
			m_soundPlayBack->GameSceneSoundPlayBack(PauseSound);

			//�|�[�Y������Ȃ��Ƃ��A
			if (!m_isPauseFlg)
			{
				//�|�[�Y�ɂ���
				m_pauseSprite->Activate();
				m_grayBack->Activate();
				if (m_soundPlayBack->m_gameSceneSound[GameBGM] != nullptr)
				{
					m_soundPlayBack->m_gameSceneSound[GameBGM]->SetVolume(nsStdafx::FLOAT_ZERO);
				}

				m_isPauseFlg = true;
			}
			//�|�[�Y���̎��A
			else
			{
				m_pauseSprite->Deactivate();
				m_grayBack->Deactivate();
				if (m_soundPlayBack->m_gameSceneSound[GameBGM] != nullptr)
				{
					m_soundPlayBack->m_gameSceneSound[GameBGM]->SetVolume(nsPause::HALF_VOLUME);
				}

				//�|�[�Y���O��
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