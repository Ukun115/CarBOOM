///<<summary>
///���U���g��ʂ̃��C������
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"
#include "Fade.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const Vector3 RANKING1_POS = { -150.0f,50.0f,nsStdafx::FLOAT_ZERO };	//�P�ʉ摜�̈ʒu
		const Vector3 RANKING2_POS = { -150.0f,-50.0f,nsStdafx::FLOAT_ZERO };	//�Q�ʉ摜�̈ʒu
		const Vector3 RANKING3_POS = { -150.0f,-150.0f,nsStdafx::FLOAT_ZERO };	//�R�ʉ摜�̈ʒu
		const Vector3 RANKING4_POS = { -150.0f,-250.0f,nsStdafx::FLOAT_ZERO };	//�S�ʉ摜�̈ʒu
	}


	bool ResultScene::Start()
	{
		//�C���X�^���X��T���B
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
		InitRankingImage();

		//���U���g�W���O��
		m_soundPlayBack->ResultSceneSoundPlayBack(ResultGingle);

		//�Q�[������BGM�T�E���h
		m_soundPlayBack->ResultSceneSoundPlayBack(GameBGM);

		//���U���g�����摜�I�u�W�F�N�g����
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		m_resultSprite->Init("Result", 600.0f, 300.0f);
		Vector3 m_resSprPos = { nsStdafx::FLOAT_ZERO,160.0f,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
		InitPlayerImage();

		//���ʏ�����ёւ�
		RankingSort();

		return true;
	}


	ResultScene::~ResultScene()
	{
		//���ʉ摜�̍폜�B
		DeleteGO(m_resultSprite);

		//�v���C���[���摜�̍폜�B
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			DeleteGO(m_plaNum[plaNum]);

			DeleteGO(m_rankingSprite[plaNum]);
		}

		DeleteGO(m_fadeOut);
	}


	void ResultScene::Update()
	{
		//�v���C���[����ʊO�i�E���j����X���C�h���Ă��鏈��
		SlidePlayerName();

		//�Q�[���I������
		SelectScene();
	}


	//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
	void ResultScene::RankingSort()
	{
		//�v���C���[�̐l�����X�R�A���Q�b�g
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			m_plaScore[plaNum] = m_gameScene->GetPlaScore(plaNum);

		}
		//�\�[�g
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			for (int nextPlaNum = plaNum + 1; nextPlaNum < m_totalPlaNum; nextPlaNum++)
			{
				if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
				{
					SpriteRender* tmp = m_plaNum[plaNum];
					m_plaNum[plaNum] = m_plaNum[nextPlaNum];
					m_plaNum[nextPlaNum] = tmp;
				}
			}
		}

		//1P
		if (m_totalPlaNum >= 1)
		{
			m_plaNum[0]->SetPosition(m_number1Pos);
			m_moveSpeed = 20.0f;
		}
		//2P
		if (m_totalPlaNum >= 2)
		{
			m_plaNum[1]->SetPosition(m_number2Pos);
			m_moveSpeed = 5.0f;
		}
		//3P
		if (m_totalPlaNum >= 3)
		{
			m_plaNum[2]->SetPosition(m_number3Pos);
			m_moveSpeed = 10.0f;
		}
		//4P
		if (m_totalPlaNum >= 4)
		{
			m_plaNum[3]->SetPosition(m_number4Pos);
			m_moveSpeed = 20.0f;
		}
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


	//�v���C���[����ʊO�i�E���j����X���C�h���Ă��鏈���֐�
	void ResultScene::SlidePlayerName()
	{
		//�f�B���C��������
		if (m_delayTimerOnFlg)
		{
			m_plaMoveDelayTimer++;
			if (m_plaMoveDelayTimer > 100)
			{
				m_plaMoveFlg[Player4] = true;
				m_delayTimerOnFlg = false;
			}
		}
		//4P
		if (m_plaMoveFlg[Player4])
		{
			if (m_totalPlaNum >= 4)
			{
				if (m_number4Pos.x > 150.0f)
				{
					m_number4Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player3] = true;
					m_plaMoveFlg[Player4] = false;
					//���o�ꂷ��摜�̃X�s�[�h��ω�������
					m_moveSpeed /= 2.0;
				}
				m_plaNum[3]->SetPosition(m_number4Pos);
			}
			else
			{
				m_plaMoveFlg[Player4] = false;
				m_plaMoveFlg[Player3] = true;
			}
		}
		//3P
		if (m_plaMoveFlg[Player3])
		{
			if (m_totalPlaNum >= 3)
			{
				if (m_number3Pos.x > 150.0f)
				{
					m_number3Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player2] = true;
					m_plaMoveFlg[Player3] = false;
					//���o�ꂷ��摜�̃X�s�[�h��ω�������
					m_moveSpeed /= 2.0;
				}
				m_plaNum[2]->SetPosition(m_number3Pos);
			}
			else
			{
				m_plaMoveFlg[Player2] = true;
				m_plaMoveFlg[Player3] = false;
			}
		}
		//2P
		if (m_plaMoveFlg[Player2])
		{
			if (m_totalPlaNum >= 2)
			{
				if (m_number2Pos.x > 150.0f)
				{
					m_number2Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player1] = true;
					m_plaMoveFlg[Player2] = false;
					//���o�ꂷ��摜�̃X�s�[�h��ω�������
					m_moveSpeed /= 2.0;
				}
				m_plaNum[1]->SetPosition(m_number2Pos);
			}
			else
			{
				m_plaMoveFlg[Player1] = true;
				m_plaMoveFlg[Player2] = false;
			}
		}
		//1P
		if (m_plaMoveFlg[Player1])
		{
			if (m_totalPlaNum >= 1)
			{
				if (m_number1Pos.x > 150.0f)
				{
					m_number1Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player1] = false;
					m_plaJumpFlg = true;
				}
				m_plaNum[0]->SetPosition(m_number1Pos);
			}
			else
			{
				m_plaMoveFlg[Player1] = false;
				m_plaJumpFlg = true;
			}
		}


		if (m_plaJumpFlg)
		{
			//�摜���W�����v����
			VerticalMove(10, 1.0f);
		}
	}


	//�摜���W�����v����֐�
	void ResultScene::VerticalMove(const int width, const float speed)
	{
		if (m_verticalMoveTimer < width)
		{
			//1�l
			if (m_totalPlaNum >= 1)
			{
				m_number1Pos.y += speed;
			}
			//2�l
			if (m_totalPlaNum >= 2)
			{
				m_number2Pos.y += speed;
			}
			//3�l
			if (m_totalPlaNum >= 3)
			{
				m_number3Pos.y += speed;
			}
			//4�l
			if (m_totalPlaNum >= 4)
			{
				m_number4Pos.y += speed;
			}
		}
		else if (m_verticalMoveTimer < (width * 2))
		{
			//1�l
			if (m_totalPlaNum >= 1)
			{
				m_number1Pos.y -= speed;
			}
			//2�l
			if (m_totalPlaNum >= 2)
			{
				m_number2Pos.y -= speed;
			}
			//3�l
			if (m_totalPlaNum >= 3)
			{
				m_number3Pos.y -= speed;
			}
			//4�l
			if (m_totalPlaNum >= 4)
			{
				m_number4Pos.y -= speed;
			}
		}
		else
		{
			m_plaJumpFlg = false;
		}

		m_verticalMoveTimer++;

		//1�l
		if (m_totalPlaNum >= 1)
		{
			m_plaNum[0]->SetPosition(m_number1Pos);
		}
		//2�l
		if (m_totalPlaNum >= 2)
		{
			m_plaNum[1]->SetPosition(m_number2Pos);
		}
		//3�l
		if (m_totalPlaNum >= 3)
		{
			m_plaNum[2]->SetPosition(m_number3Pos);
		}
		//4�l
		if (m_totalPlaNum >= 4)
		{
			m_plaNum[3]->SetPosition(m_number4Pos);
		}
	}


	//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	void ResultScene::InitRankingImage()
	{
		//���ʕ��������������A�\��
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//���ʉ摜�I�u�W�F�N�g����
			m_rankingSprite[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);

			sprintf(m_filePath, "%dst", plaNum + 1);
			m_rankingSprite[plaNum]->Init(m_filePath, 150.0f, 150.0f);
			switch (plaNum)
			{
				//�P�ʉ摜
			case Player1:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING1_POS);
				break;
				//�Q�ʉ摜
			case Player2:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING2_POS);
				break;
				//�R�ʉ摜
			case Player3:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING3_POS);
				break;
				//�S�ʉ摜
			case Player4:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING4_POS);
				break;
			}
		}
	}


	//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
	void ResultScene::InitPlayerImage()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//�v���C���[�����摜�I�u�W�F�N�g����
			m_plaNum[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);

			sprintf(m_filePath, "Player%d_ActiveName", plaNum + 1);
			m_plaNum[plaNum]->Init(m_filePath, 340.0f, 170.0f);
		}
	}
}