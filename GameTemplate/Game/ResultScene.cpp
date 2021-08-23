///<<summary>
///���U���g��ʂ̃��C������
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "Ranking.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const float RESULT_SPRITE_WIDTH = 600.0f;
		const float RESULT_SPRITE_HEIGHT = 300.0f;
		const float RESULT_SPRITE_POS_Y = 160.0f;
	}

	bool ResultScene::Start()
	{
		//�C���X�^���X��T���B
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//���U���g�W���O��
		m_soundPlayBack->ResultSceneSoundPlayBack(ResultGingle);
		//�Q�[������BGM�T�E���h
		m_soundPlayBack->ResultSceneSoundPlayBack(GameBGM);

		m_ranking = NewGO<Ranking>(nsStdafx::PRIORITY_0, nullptr);
		m_ranking->SetTotalPlaNum(m_totalPlaNum);

		//���U���g�����摜�I�u�W�F�N�g����
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		m_resultSprite->Init("Result", nsResultScene:: RESULT_SPRITE_WIDTH, nsResultScene::RESULT_SPRITE_HEIGHT);
		Vector3 m_resSprPos = { nsStdafx::FLOAT_ZERO,nsResultScene::RESULT_SPRITE_POS_Y,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		return true;
	}

	ResultScene::~ResultScene()
	{
		//���ʉ摜�̍폜�B
		DeleteGO(m_resultSprite);

		DeleteGO(m_fadeOut);

		DeleteGO(m_ranking);
	}

	void ResultScene::Update()
	{
		//�Q�[���I������
		SelectScene();
	}

	//���ǂ̃V�[���ɍs�����؂�ւ���֐�
	void ResultScene::SelectScene()
	{
		if (m_fadeOut == nullptr)
		{
			//�v���C���[�̓��A�N���̃Z���N�g�{�^���������ꂽ��A
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++) {
				//�Z���N�g�{�^���������ꂽ��A
				if (g_pad[plaNum]->IsTrigger(enButtonSelect))
				{
					//����T�E���h
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextGameEnd;

					//�t�F�[�h�A�E�g
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
				//�X�^�[�g�{�^���������ꂽ��A
				if (g_pad[plaNum]->IsTrigger(enButtonStart))
				{
					//����T�E���h
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextTitleScene;

					//�t�F�[�h�A�E�g
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
				//Y�{�^���������ꂽ��A
				if (g_pad[plaNum]->IsTrigger(enButtonY))
				{
					//����T�E���h
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextStageSelectScene;

					//�t�F�[�h�A�E�g
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
			}
		}
		else
		{
			if (m_fadeOut->GetNowState() != StateWait && !m_muriFlg)
			{
				return;
			}

			//���̑J�ڐ�
			switch (m_select)
			{
			case NextGameEnd:
				//exe����ăQ�[���I��
				exit(EXIT_SUCCESS);
				//����//
				//exit(EXIT_FAILURE);�ُ͈�I��		EXIT_FAILURE = 1
				//exit(EXIT_SUCCESS);�͐���I��		EXIT_SUCCESS = 0
				break;
			case NextTitleScene:
				//�^�C�g����ʂɖ߂�
				NewGO<TitleScene>(nsStdafx::PRIORITY_0, nullptr);
				//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I��
				m_gameScene->SetDeleteFlg(true);
				//���U���g��ʂŎg����T�E���h��j��
				m_soundPlayBack->ResultSceneDeleteGO();

				m_muriFlg = true;
				break;
			case NextStageSelectScene:
				//�X�e�[�W�I����ʂɖ߂�
				m_stageSelectScene = NewGO<StageSelectScene>(nsStdafx::PRIORITY_0, nullptr);
				m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);

				//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I��
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			}
		}
	}
}