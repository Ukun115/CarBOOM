/// <summary>
/// �^�C�g����ʂ̃��C������
/// (���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I)
/// </summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"
#include "TitleName.h"
#include "PressStartButton.h"
#include "PressASpeechBalloon.h"
#include "PlayerName.h"

namespace nsCARBOOM
{
	namespace nsTitleScene
	{

	}

	bool TitleScene::Start()
	{
		//�t�F�[�h�C��
		m_fade[FadeIn] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeIn]->SetState(StateIn);
		m_fade[FadeIn]->SetAlphaValue(1.0f);

		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		m_titleName = NewGO<TitleName>(nsStdafx::PRIORITY_0, nullptr);

		m_pressStartButton = NewGO<PressStartButton>(nsStdafx::PRIORITY_0, nullptr);

		m_pressASpeechBalloon = NewGO<PressASpeechBalloon>(nsStdafx::PRIORITY_0, nullptr);

		//�^�C�g�����W���O���T�E���h
		m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneGingle);

		//�^�C�g��BGM�T�E���h
		m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneBGM);

		//�^�C�g�����S�I�u�W�F�N�g����
		m_titleSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		m_titleSprite->Init("TitleRogo", 1600.0f, 800.0f);

		m_playerName = NewGO<PlayerName>(nsStdafx::PRIORITY_0, nullptr);

		return true;
	}

	TitleScene::~TitleScene()
	{
		DeleteGO(m_titleName);

		DeleteGO(m_titleName);

		DeleteGO(m_pressStartButton);

		DeleteGO(m_pressASpeechBalloon);

		//�^�C�g�����S���폜�B
		DeleteGO(m_titleSprite);

		for (int fadeNum = FadeIn; fadeNum < TotalFadeNum; fadeNum++)
		{
			DeleteGO(m_fade[fadeNum]);
		}
	}

	void TitleScene::Update()
	{
		//�v���C���[��o�^����
		AddPlayer();

		if (m_fade[FadeOut] == nullptr)
		{
			//�o�^����Ă���N���̃X�^�[�g�{�^���������ꂽ��A
			for (unsigned int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
				PushStartButton(plaNum);
				//�{�^���������ꂽ�Ƃ��̏����֐�
				PushSelectButton(plaNum);
			}
		}
		else
		{
			//�I�����ꂽ���̃V�[���ɍs�������֐�
			NextScene();
		}
	}

	//�v���C���[��ǉ�����֐�
	void TitleScene::AddPlayer()
	{
		//�o�^���ꂽ�v���C���[�����ő吔4�l�ɂȂ�܂Œǉ��ł���
		if (m_totalPlaNum == TotalPlaNum)
		{
			return;
		}
		/*�o�^����Ă��Ȃ��R���g���[���[��A�{�^���������ꂽ��A
		�y���ӁzUSB�|�[�g�Ɍq���ꂽ������Ȃ��Ɠo�^����Ă����܂���B*/
		if (!g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
		{
			return;
		}
		//�G���W���T�E���h
		m_soundPlayBack->TitleSceneSoundPlayBack(EngineSound);

		//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
		m_playerName->AddPlayerFlgOn(m_totalPlaNum);

		//�A�N�e�B�u�������v���C���[�̖��O�̃J���[�`�F���W
		m_playerName->ColorChange(m_totalPlaNum);

		//�����o���̃|�W�V�����ύX
		m_pressASpeechBalloon->NextState(m_totalPlaNum);

		//���̃v���C���[��
		m_totalPlaNum++;
	}

	//�X�e�[�W�I����ʂɑJ�ڂ���֐�
	void TitleScene::StageSelectSceneTransition()
	{
		//�X�e�[�W�I����ʂɑJ��
		m_stageSelectScene = NewGO<StageSelectScene>(nsStdafx::PRIORITY_0, nullptr);
		//�o�^���ꂽ�l���f�[�^�����̃N���X�ɓn��
		m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);
		//���̃N���X�̍폜
		DeleteGO(this);
		//�^�C�g���V�[���Ŏg����T�E���h��j��
		m_soundPlayBack->TitleSceneDeleteGO();
	}

	//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
	void TitleScene::PushStartButton(int plaNum)
	{
		//�X�^�[�g�{�^���������ꂽ��A
		if (!g_pad[plaNum]->IsTrigger(enButtonStart))
		{
			return;
		}
		//����T�E���h
		m_soundPlayBack->TitleSceneSoundPlayBack(DecideSound);

		//�t�F�[�h�A�E�g
		m_fade[FadeOut] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeOut]->SetState(StateOut);
		m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

		m_nextScene = StateSelectScene;
	}

	//�{�^���������ꂽ�Ƃ��̏����֐�
	void TitleScene::PushSelectButton(int plaNum)
	{
		//�Z���N�g�{�^���������ꂽ��A�A
		if (!g_pad[plaNum]->IsTrigger(enButtonSelect))
		{
			return;
		}
		//�t�F�[�h�A�E�g
		m_fade[FadeOut] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeOut]->SetState(StateOut);
		m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

		m_nextScene = GameEnd;
	}

	//�I�����ꂽ���̃V�[���ɍs�������֐�
	void TitleScene::NextScene()
	{
		//�^�����ɂȂ�����J��
		if (m_fade[FadeOut]->GetNowState() != StateWait)
		{
			return;
		}
		switch (m_nextScene)
		{
		case StateSelectScene:
			//�X�e�[�W�I����ʂɑJ��
			StageSelectSceneTransition();
			break;
		case GameEnd:
			//exe����ăQ�[���I��
			exit(EXIT_SUCCESS);
			//����//
			//exit(EXIT_FAILURE);�ُ͈�I��		EXIT_FAILURE = 1
			//exit(EXIT_SUCCESS);�͐���I��		EXIT_SUCCESS = 0
			break;
		}
	}
}