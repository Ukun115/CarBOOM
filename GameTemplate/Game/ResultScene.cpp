#include "stdafx.h"
#include "ResultScene.h"

namespace
{
	const Vector3 NUMBER1_POS = { 150.0f,50.0f,0.0f };
	const Vector3 NUMBER2_POS = { 150.0f,-50.0f,0.0f };
	const Vector3 NUMBER3_POS = { 150.0f,-150.0f,0.0f };
	const Vector3 NUMBER4_POS = { 150.0f,-250.0f,0.0f };
}

bool ResultScene::Start()
{
	//���U���g�����摜���������B
	m_resultSprite = NewGO<SpriteRender>(2, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);

	//�v���C���[�����摜���������B
	for (int i = 0; i < 4; i++)
	{
		m_plaNum[i] = NewGO<SpriteRender>(2, nullptr);
		if (i == 0)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER1_POS);
		}
		if (i == 1)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER2_POS);
		}
		if (i == 2)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER3_POS);
		}
		if (i == 3)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER4_POS);
		}
	}

	//Start�֐���return��
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_resultSprite);

	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_plaNum[i]);
	}
}

void ResultScene::Update()
{
	//�Z���N�g�{�^��(�L�[�{�[�h�F�X�y�[�X)�������ꂽ��A
	for (int i = 0; i < 4; i++) {
		if (g_pad[i]->IsTrigger(enButtonSelect))
		{
			//exe����ăQ�[���I��
			exit(EXIT_SUCCESS);
		}
	}
}