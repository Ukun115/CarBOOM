///<<summary>
///���U���g��ʂ̃��C������
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Fade.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const float RESULT_SPRITE_WIDTH = 600.0f;
		const float RESULT_SPRITE_HEIGHT = 300.0f;
		const float RESULT_SPRITE_POS_Y = 160.0f;
		const float GRAYBACK_SCA = 1500.0f;
		const Vector3 RANKING1_POS = { -150.0f,50.0f,0.0f };	//�P�ʉ摜�̈ʒu
		const Vector3 RANKING2_POS = { -150.0f,-50.0f,0.0f };	//�Q�ʉ摜�̈ʒu
		const Vector3 RANKING3_POS = { -150.0f,-150.0f,0.0f };	//�R�ʉ摜�̈ʒu
		const Vector3 RANKING4_POS = { -150.0f,-250.0f,0.0f };	//�S�ʉ摜�̈ʒu
		const int JUMP_WIDTH = 10;
		const float JUMP_SPEED = 1.0f;
		const int DELAYTIMER = 100;
		const int PLUS_ONE = 1;
		const float RANKING_FONT_SCALE = 150.0f;
		const int NIBAI = 2;
		const float PLAYERNAME_SPRITE_WIDTH = 340.0f;
		const float PLAYERNAME_SPRITE_HEIGHT = 170.0f;
		const float NEXT_JUNNI_CHANGE_SPEED = 2.0f;
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

		m_grayBack = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		//�D�F�ɂ���摜��������
		m_grayBack->Init("GrayBack", nsResultScene::GRAYBACK_SCA, nsResultScene::GRAYBACK_SCA);

		//���U���g�����摜�I�u�W�F�N�g����
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		m_resultSprite->Init("Result", nsResultScene:: RESULT_SPRITE_WIDTH, nsResultScene::RESULT_SPRITE_HEIGHT);
		m_resSprPos = { nsStdafx::FLOAT_ZERO,nsResultScene::RESULT_SPRITE_POS_Y,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
			InitRankingImage(plaNum);
			//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
			InitPlayerImage(plaNum);
		}

		//���ʏ�����ёւ�
		RankingSort();

		return true;
	}

	ResultScene::~ResultScene()
	{
		//���ʉ摜�̍폜�B
		DeleteGO(m_resultSprite);

		DeleteGO(m_fadeOut);

		DeleteGO(m_grayBack);

		//�v���C���[���摜�̍폜�B
		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++)
		{
			DeleteGO(m_plaNum[plaNum]);

			DeleteGO(m_rankingSprite[plaNum]);
		}
	}

	void ResultScene::Update()
	{
		//�f�B���C��������
		if (m_delayTimerOnFlg)
		{
			m_plaMoveDelayTimer++;
			if (m_plaMoveDelayTimer > nsResultScene::DELAYTIMER)
			{
				m_plaMoveFlg[Player4] = true;
				m_delayTimerOnFlg = false;
			}
		}
		//�v���C���[����ʊO�i�E���j����X���C�h���Ă��鏈��
		PlayerNameMove();

		if (!m_plaJumpFlg)
		{
			return;
		}
		//�摜���W�����v����
		VerticalMove(nsResultScene::JUMP_WIDTH, nsResultScene::JUMP_SPEED);

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
				//���U���g��ʂŎg����T�E���h��j��
				m_soundPlayBack->ResultSceneDeleteGO();
				//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I��
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			}
		}
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
			for (int nextPlaNum = plaNum + nsResultScene::PLUS_ONE; nextPlaNum < m_totalPlaNum; nextPlaNum++)
			{
				if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
				{
					SpriteRender* tmp = m_plaNum[plaNum];
					m_plaNum[plaNum] = m_plaNum[nextPlaNum];
					m_plaNum[nextPlaNum] = tmp;
				}
			}
		}

		//�v���C���[�̐l���ɉ����ĉ�����v���C���[�����o�Ă��鑬�x���ω�
		for (int plaNum = Player1; plaNum <= m_totalPlaNum; plaNum)
		{
			MoveSpeedChange(plaNum);
			PlaRankingPosSet(plaNum);
		}
	}

	//�摜���W�����v����֐�
	void ResultScene::VerticalMove(const int width, const float speed)
	{
		if (m_verticalMoveTimer < width)
		{
			//��ɃW�����v
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, speed);
			}
		}
		else if (m_verticalMoveTimer < (width * nsResultScene::NIBAI))
		{
			//�W�����v��̗���
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, -speed);
			}
		}
		else
		{
			m_plaJumpFlg = false;
		}

		m_verticalMoveTimer++;

		for (int plaNum = Player2; plaNum <= TotalPlaNum; plaNum)
		{
			PlaRankingPosSet(plaNum);
		}
	}

	//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	void ResultScene::InitRankingImage(const int plaNum)
	{
		//���ʕ��������������A�\��
		//���ʉ摜�I�u�W�F�N�g����
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "%dst", (plaNum + nsResultScene::PLUS_ONE));
		m_rankingSprite[plaNum]->Init(m_filePath, nsResultScene::RANKING_FONT_SCALE, nsResultScene::RANKING_FONT_SCALE);
		m_rankingSprite[plaNum]->SetPosition(WhatRankingNumPos(plaNum));
	}

	//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
	void ResultScene::InitPlayerImage(const int plaNum)
	{
		//�v���C���[�����摜�I�u�W�F�N�g����
		m_plaNum[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "Player%d_ActiveName", plaNum);
		m_plaNum[plaNum]->Init(m_filePath, nsResultScene::PLAYERNAME_SPRITE_WIDTH, nsResultScene::PLAYERNAME_SPRITE_HEIGHT);
	}

	void ResultScene::PlayerNameMove()
	{
		for (int plaNum = Player4; plaNum >= Player1; plaNum--)
		{
			if (!m_plaMoveFlg[Player4])
			{
				return;
			}
			if (m_totalPlaNum >= (plaNum + nsResultScene::PLUS_ONE))
			{
				if (m_number4Pos.x > 150.0f)
				{
					m_number4Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[plaNum - nsResultScene::PLUS_ONE] = true;
					if (plaNum != Player1)
					{
						m_plaMoveFlg[plaNum] = false;
					}
					else
					{
						m_plaJumpFlg = true;
					}
					//���o�ꂷ��摜�̃X�s�[�h��ω�������
					m_moveSpeed /= nsResultScene::NEXT_JUNNI_CHANGE_SPEED;
				}
				m_plaNum[plaNum]->SetPosition(m_number4Pos);
			}
			else
			{
				m_plaMoveFlg[plaNum] = false;
				if (plaNum != Player1)
				{
					m_plaMoveFlg[plaNum - nsResultScene::PLUS_ONE] = true;
				}
				else
				{
					m_plaJumpFlg = true;
				}
			}
		}
	}

	void ResultScene::MoveSpeedChange(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_moveSpeed = WhatMoveSpeed(plaNum);
		}
	}

	void ResultScene::PlaRankingPosSet(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_plaNum[plaNum]->SetPosition(WhatNumberPos(plaNum));
		}
	}

	void ResultScene::PlaNameJumpState(const int plaNum, const float speed)
	{
		if (m_totalPlaNum >= plaNum)
		{
			switch (plaNum)
			{
			case Player2:
				m_number1Pos.y += speed;
				break;
			case Player3:
				m_number2Pos.y += speed;
				break;
			case Player4:
				m_number3Pos.y += speed;
				break;
			case TotalPlaNum:
				m_number4Pos.y += speed;
				break;
			}
		}
	}

	Vector3 ResultScene::WhatRankingNumPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return nsResultScene::RANKING1_POS;
			break;
		case Player2:
			return nsResultScene::RANKING2_POS;
			break;
		case Player3:
			return nsResultScene::RANKING3_POS;
			break;
		case TotalPlaNum:
			return nsResultScene::RANKING4_POS;
			break;
		}
	}

	float ResultScene::WhatMoveSpeed(const int plaNum)
	{
		switch (plaNum)
		{
		case Player2:
			return 20.0f;
			break;
		case Player3:
			return 5.0f;
			break;
		case Player4:
			return 10.0f;
			break;
		case TotalPlaNum:
			return 20.0f;
			break;
		}
	}

	Vector3 ResultScene::WhatNumberPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return m_number1Pos;
			break;
		case Player2:
			return m_number2Pos;
			break;
		case Player3:
			return m_number3Pos;
			break;
		case Player4:
			return m_number4Pos;
			break;
		}
	}
}