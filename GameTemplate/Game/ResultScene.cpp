#include "stdafx.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Player.h"


namespace
{
	const Vector3 NUMBER1_POS = { 150.0f,50.0f,0.0f };		//�P�ʃv���C���[�̕\���ʒu
	const Vector3 NUMBER2_POS = { 150.0f,-50.0f,0.0f };		//�Q�ʃv���C���[�̕\���ʒu
	const Vector3 NUMBER3_POS = { 150.0f,-150.0f,0.0f };	//�R�ʃv���C���[�̕\���ʒu
	const Vector3 NUMBER4_POS = { 150.0f,-250.0f,0.0f };	//�S�ʃv���C���[�̕\���ʒu

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
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);

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
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);


	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//�v���C���[�����摜�I�u�W�F�N�g����
		m_plaNum[plaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
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

	//Start�֐���return��
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
	}
}


void ResultScene::Update()
{
	//�Q�[���I������
	GameEnd();
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

	//1P�̃v���C���[���̈ʒu��ݒ�
	if (m_player->GetPlaNum() == 1)
	{
		m_plaNum[0]->SetPosition(NUMBER1_POS);
	}
	//2P
	if (m_player->GetPlaNum() == 2)
	{
		m_plaNum[1]->SetPosition(NUMBER2_POS);
	}
	//3P
	if (m_player->GetPlaNum() == 3)
	{
		m_plaNum[2]->SetPosition(NUMBER3_POS);
	}
	//4P
	if (m_player->GetPlaNum() == 4)
	{
		m_plaNum[3]->SetPosition(NUMBER4_POS);
	}
}


//�Q�[���I���֐�
void ResultScene::GameEnd()
{
	//�v���C���[�̓��A�N���̃Z���N�g�{�^���������ꂽ��A
	for (int plaNum = 0; plaNum < 4; plaNum++) {
		if (g_pad[plaNum]->IsTrigger(enButtonSelect))
		{
			//����T�E���h
			SoundPlayBack(DecideSound);

			m_timerOnFlg = true;
		}
	}
	if (m_timerOnFlg)
	{
		m_exitTimer++;

		if (m_exitTimer > 60)
		{
			//exe����ăQ�[���I��
			exit(EXIT_SUCCESS);
			//����//
			//exit(EXIT_FAILURE);�ُ͈�I��		EXIT_FAILURE = 1
			//exit(EXIT_SUCCESS);�͐���I��		EXIT_SUCCESS = 0
		}
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