///<<summary>
///���U���g��ʎ��̏����N���X
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"
#include "Fade.h"


namespace
{
	Vector3 NUMBER1_END_POS = { 150.0f,50.0f,FLOAT_ZERO };		//�P�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER2_END_POS = { 150.0f,-50.0f,FLOAT_ZERO };		//�Q�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER3_END_POS = { 150.0f,-150.0f,FLOAT_ZERO };	//�R�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER4_END_POS = { 150.0f,-250.0f,FLOAT_ZERO };	//�S�ʃv���C���[�̕\���ʒu

	const Vector3 RANKING1_POS = { -150.0f,50.0f,FLOAT_ZERO };	//�P�ʉ摜�̈ʒu
	const Vector3 RANKING2_POS = { -150.0f,-50.0f,FLOAT_ZERO };	//�Q�ʉ摜�̈ʒu
	const Vector3 RANKING3_POS = { -150.0f,-150.0f,FLOAT_ZERO };	//�R�ʉ摜�̈ʒu
	const Vector3 RANKING4_POS = { -150.0f,-250.0f,FLOAT_ZERO };	//�S�ʉ摜�̈ʒu
}


bool ResultScene::Start()
{
	//�C���X�^���X��T���B
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_player = FindGO<Player>(PLAYER_NAME);
	m_soundPlayBack = FindGO<SoundPlayBack>(SOUNDPLAYBACK_NAME);

	//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	InitRankingImage();

	//���U���g�W���O��
	m_soundPlayBack->ResultSceneSoundPlayBack(ResultGingle);

	//�Q�[������BGM�T�E���h
	m_soundPlayBack->ResultSceneSoundPlayBack(GameBGM);

	//���U���g�����摜�I�u�W�F�N�g����
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_6, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { FLOAT_ZERO,160.0f,FLOAT_ZERO };
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
	for (int plaNum = 0; plaNum < 4; plaNum++)
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
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		m_plaScore[plaNum] = m_gameScene->GetPlaScore(plaNum);

	}
	//�\�[�g
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_player->GetPlaNum(); nextPlaNum++)
		{
			if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
			{
				SpriteRender *tmp = m_plaNum[plaNum];
				m_plaNum[plaNum] = m_plaNum[nextPlaNum];
				m_plaNum[nextPlaNum] = tmp;
			}
		}
	}

	//1P
	if (m_player->GetPlaNum() >= 1)
	{
		m_plaNum[0]->SetPosition(m_number1Pos);
		m_moveSpeed = 20.0f;
	}
	//2P
	if (m_player->GetPlaNum() >= 2)
	{
		m_plaNum[1]->SetPosition(m_number2Pos);
		m_moveSpeed = 5.0f;
	}
	//3P
	if (m_player->GetPlaNum() >= 3)
	{
		m_plaNum[2]->SetPosition(m_number3Pos);
		m_moveSpeed = 10.0f;
	}
	//4P
	if (m_player->GetPlaNum() >= 4)
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

				m_select = 0;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, nullptr);
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(FLOAT_ZERO);
			}
			//�X�^�[�g�{�^���������ꂽ��A
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//����T�E���h
				m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

				m_select = 1;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, nullptr);
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(FLOAT_ZERO);
			}
			//Y�{�^���������ꂽ��A
			if (g_pad[plaNum]->IsTrigger(enButtonY))
			{
				//����T�E���h
				m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

				m_select = 2;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, nullptr);
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(FLOAT_ZERO);
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
		case 0:
			//exe����ăQ�[���I��
			exit(EXIT_SUCCESS);
			//����//
			//exit(EXIT_FAILURE);�ُ͈�I��		EXIT_FAILURE = 1
			//exit(EXIT_SUCCESS);�͐���I��		EXIT_SUCCESS = 0
			break;
		case 1:
			//�^�C�g����ʂɖ߂�
			NewGO<TitleScene>(0, nullptr);
			//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I��
			m_gameScene->SetDeleteFlg(true);
			//���U���g��ʂŎg����T�E���h��j��
			m_soundPlayBack->ResultSceneDeleteGO();

			m_muriFlg = true;
			break;
		case 2:
			//�X�e�[�W�I����ʂɖ߂�
			m_stageSelectScene = NewGO<StageSelectScene>(0, nullptr);
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
			m_pla4MoveFlg = true;
			m_delayTimerOnFlg = false;
		}
	}
	//4P
	if (m_pla4MoveFlg)
	{
		if (m_player->GetPlaNum() >= 4)
		{
			if (m_number4Pos.x > 150.0f)
			{
				m_number4Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla3MoveFlg = true;
				m_pla4MoveFlg = false;
				//���o�ꂷ��摜�̃X�s�[�h��ω�������
				m_moveSpeed /= 2.0;
			}
			m_plaNum[3]->SetPosition(m_number4Pos);
		}
		else
		{
			m_pla4MoveFlg = false;
			m_pla3MoveFlg = true;
		}
	}
	//3P
	if (m_pla3MoveFlg)
	{
		if (m_player->GetPlaNum() >= 3)
		{
			if (m_number3Pos.x > 150.0f)
			{
				m_number3Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla2MoveFlg = true;
				m_pla3MoveFlg = false;
				//���o�ꂷ��摜�̃X�s�[�h��ω�������
				m_moveSpeed /= 2.0;
			}
			m_plaNum[2]->SetPosition(m_number3Pos);
		}
		else
		{
			m_pla2MoveFlg = true;
			m_pla3MoveFlg = false;
		}
	}
	//2P
	if (m_pla2MoveFlg)
	{
		if (m_player->GetPlaNum() >= 2)
		{
			if (m_number2Pos.x > 150.0f)
			{
				m_number2Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla1MoveFlg = true;
				m_pla2MoveFlg = false;
				//���o�ꂷ��摜�̃X�s�[�h��ω�������
				m_moveSpeed /= 2.0;
			}
			m_plaNum[1]->SetPosition(m_number2Pos);
		}
		else
		{
			m_pla1MoveFlg = true;
			m_pla2MoveFlg = false;
		}
	}
	//1P
	if (m_pla1MoveFlg)
	{
		if (m_player->GetPlaNum() >= 1)
		{
			if (m_number1Pos.x > 150.0f)
			{
				m_number1Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla1MoveFlg = false;
				m_plaJumpFlg = true;
			}
			m_plaNum[0]->SetPosition(m_number1Pos);
		}
		else
		{
			m_pla1MoveFlg = false;
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
		if (m_player->GetPlaNum() >= 1)
		{
			m_number1Pos.y += speed;
		}
		//2�l
		if (m_player->GetPlaNum() >= 2)
		{
			m_number2Pos.y += speed;
		}
		//3�l
		if (m_player->GetPlaNum() >= 3)
		{
			m_number3Pos.y += speed;
		}
		//4�l
		if (m_player->GetPlaNum() >= 4)
		{
			m_number4Pos.y += speed;
		}
	}
	else if (m_verticalMoveTimer < (width * 2))
	{
		//1�l
		if (m_player->GetPlaNum() >= 1)
		{
			m_number1Pos.y -= speed;
		}
		//2�l
		if (m_player->GetPlaNum() >= 2)
		{
			m_number2Pos.y -= speed;
		}
		//3�l
		if (m_player->GetPlaNum() >= 3)
		{
			m_number3Pos.y -= speed;
		}
		//4�l
		if (m_player->GetPlaNum() >= 4)
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
	if (m_player->GetPlaNum() >= 1)
	{
		m_plaNum[0]->SetPosition(m_number1Pos);
	}
	//2�l
	if (m_player->GetPlaNum() >= 2)
	{
		m_plaNum[1]->SetPosition(m_number2Pos);
	}
	//3�l
	if (m_player->GetPlaNum() >= 3)
	{
		m_plaNum[2]->SetPosition(m_number3Pos);
	}
	//4�l
	if (m_player->GetPlaNum() >= 4)
	{
		m_plaNum[3]->SetPosition(m_number4Pos);
	}
}


//���ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
void ResultScene::InitRankingImage()
{
	//���ʕ��������������A�\��
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		//���ʉ摜�I�u�W�F�N�g����
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);

		switch (plaNum)
		{
		//�P�ʉ摜
		case Player1:
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/1st.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING1_POS);
			break;
		//�Q�ʉ摜
		case Player2:
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/2nd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING2_POS);
			break;
		//�R�ʉ摜
		case Player3:
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/3rd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING3_POS);
			break;
		//�S�ʉ摜
		case Player4:
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/4th.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING4_POS);
			break;
		}
	}
}


//PLAYER�摜�̏��������܂Ƃ߂Ă���֐�
void ResultScene::InitPlayerImage()
{
	for (int plaNum = Player1; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//�v���C���[�����摜�I�u�W�F�N�g����
		m_plaNum[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);
		switch (plaNum)
		{
		//�PP
		case Player1:
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
			break;
		//�QP
		case Player2:
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
			break;
		//�RP
		case Player3:
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
			break;
		//�SP
		case Player4:
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
			break;
		}
	}
}