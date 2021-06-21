#include "stdafx.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Player.h"


namespace
{
	const int PRIORITY_1 = 1;	//�D��x1

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
	m_gameScene = FindGO<GameScene>("gamescene");
	m_player = FindGO<Player>("player");

	//���ʕ��������������A�\��
	for (int i = 0; i < 4; i++)
	{
		//���ʉ摜�I�u�W�F�N�g����
		m_rankingSprite[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);

		//�P�ʉ摜
		if (i == 0)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/1st.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING1_POS);
		}
		//2�ʉ摜
		if (i == 1)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/2nd.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING2_POS);
		}
		//3�ʉ摜
		if (i == 2)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/3rd.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING3_POS);
		}
		//4�ʉ摜
		if (i == 3)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/4th.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING4_POS);
		}
	}


	//���U���g�����摜�I�u�W�F�N�g����
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);

	//�S���̃X�R�A�����_�̏ꍇDraw�����摜����ԏ�ɕ\��
	


	for (int i = 0; i < m_player->GetPlaNum(); i++)
	{
		//�v���C���[�����摜�I�u�W�F�N�g����
		m_plaNum[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//1P
		if (i == 0)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
		}
		//2P
		if (i == 1)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
		}
		//3P
		if (i == 2)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
		}
		//4P
		if (i == 3)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
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
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_plaNum[i]);
	}
}


void ResultScene::Update()
{
	//�v���C���[�̓��A�N���̃Z���N�g�{�^���������ꂽ��A
	for (int i = 0; i < 4; i++) {
		if (g_pad[i]->IsTrigger(enButtonSelect))
		{
			//exe����ăQ�[���I��
			exit(EXIT_SUCCESS);
		}
	}
}


//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
void ResultScene::RankingSort()
{
	//�v���C���[�̐l�����X�R�A���Q�b�g
	for (int i = 0; i < m_player->GetPlaNum(); i++)
	{
		m_plaScore[i] = m_gameScene->GetPlaScore(i);

	}
	//�\�[�g
	for (int k = 0; k < m_player->GetPlaNum(); k++)
	{
		for (int u = k + 1; u < m_player->GetPlaNum(); u++)
		{
			if (m_plaScore[k] < m_plaScore[u])
			{
				SpriteRender *tmp = m_plaNum[k];
				m_plaNum[k] = m_plaNum[u];
				m_plaNum[u] = tmp;
			}
		}
	}

	for (int i = 0; i < m_player->GetPlaNum(); i++)
	{
		if (i == 0)
			m_plaNum[0]->SetPosition(NUMBER1_POS);
		if (i == 1)
			m_plaNum[1]->SetPosition(NUMBER2_POS);
		if (i == 2)
			m_plaNum[2]->SetPosition(NUMBER3_POS);
		if (i == 3)
			m_plaNum[3]->SetPosition(NUMBER4_POS);
	}
}