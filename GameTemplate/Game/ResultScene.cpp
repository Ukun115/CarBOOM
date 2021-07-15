///<<summary>
///���U���g��ʎ��̏����N���X
///</summary>


#include "stdafx.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"


namespace
{
	Vector3 NUMBER1_END_POS = { 150.0f,50.0f,0.0f };		//�P�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER2_END_POS = { 150.0f,-50.0f,0.0f };		//�Q�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER3_END_POS = { 150.0f,-150.0f,0.0f };	//�R�ʃv���C���[�̕\���ʒu
	Vector3 NUMBER4_END_POS = { 150.0f,-250.0f,0.0f };	//�S�ʃv���C���[�̕\���ʒu

	const Vector3 RANKING1_POS = { -150.0f,50.0f,0.0f };	//�P�ʉ摜�̈ʒu
	const Vector3 RANKING2_POS = { -150.0f,-50.0f,0.0f };	//�Q�ʉ摜�̈ʒu
	const Vector3 RANKING3_POS = { -150.0f,-150.0f,0.0f };	//�R�ʉ摜�̈ʒu
	const Vector3 RANKING4_POS = { -150.0f,-250.0f,0.0f };	//�S�ʉ摜�̈ʒu
}


bool ResultScene::Start()
{
	//�C���X�^���X��T���B
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_player = FindGO<Player>(PLAYER_NAME);

	//���ʕ��������������A�\��
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		//���ʉ摜�I�u�W�F�N�g����
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);

		//�P�ʉ摜
		if (plaNum == 0)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/1st.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING1_POS);
		}
		//2�ʉ摜
		if (plaNum == 1)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/2nd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING2_POS);
		}
		//3�ʉ摜
		if (plaNum == 2)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/3rd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING3_POS);
		}
		//4�ʉ摜
		if (plaNum == 3)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/4th.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING4_POS);
		}
	}
	//���U���g�W���O��
	SoundPlayBack(ResultGingle);

	//�Q�[������BGM�T�E���h
	SoundPlayBack(GameBGM);

	//���U���g�����摜�I�u�W�F�N�g����
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_6, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);


	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//�v���C���[�����摜�I�u�W�F�N�g����
		m_plaNum[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);
		//1P
		if (plaNum == 0)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
		}
		//2P
		if (plaNum == 1)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
		}
		//3P
		if (plaNum == 2)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
		}
		//4P
		if (plaNum == 3)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
		}
	}

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

	//�T�E���h���폜
	if(m_resultGingle != nullptr)
	DeleteGO(m_resultGingle);
	if (m_gameBGM != nullptr)
	DeleteGO(m_gameBGM);
	if (m_decideSound != nullptr)
	DeleteGO(m_decideSound);

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
		for (int plaNum = 0; plaNum < 4; plaNum++) {
			//�Z���N�g�{�^���������ꂽ��A
			if (g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				//����T�E���h
				SoundPlayBack(DecideSound);

				m_select = 0;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
			//�X�^�[�g�{�^���������ꂽ��A
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//����T�E���h
				SoundPlayBack(DecideSound);

				m_select = 1;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
			//Y�{�^���������ꂽ��A
			if (g_pad[plaNum]->IsTrigger(enButtonY))
			{
				//����T�E���h
				SoundPlayBack(DecideSound);

				m_select = 2;

				//�t�F�[�h�A�E�g
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
		}
	}
	else
	{
		if (m_fadeOut->GetNowState() == StateWait&& !m_muriFlg)
		{
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
				NewGO<TitleScene>(0, TITLESCENE_NAME);
				//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I���I
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			case 2:
				//�X�e�[�W�I����ʂɖ߂�
				m_stageSelectScene = NewGO<StageSelectScene>(0, STAGESELECT_NAME);
				m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);

				//�Q�[���V�[���N���X���폜����悤�Ƀt���O���I���I
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;

			}
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
void ResultScene::VerticalMove(int width, float speed)
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


//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void ResultScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case ResultGingle:
		//���U���g�W���O���̏�����
		m_resultGingle = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_resultGingle->Init(L"Assets/sound/ResultGingle.wav");
		m_resultGingle->SetVolume(0.5f);
		m_resultGingle->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case GameBGM:
		//�Q�[������BGM�T�E���h�̏�����
		m_gameBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameBGM->Init(L"Assets/sound/GameBGM.wav");
		m_gameBGM->SetVolume(0.01f);
		m_gameBGM->Play(true);	//�^�Ń��[�v�Đ�

		break;

	case DecideSound:
		//����T�E���h
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}