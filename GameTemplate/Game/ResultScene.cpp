#include "stdafx.h"
#include "ResultScene.h"

namespace
{

}

bool ResultScene::Start()
{
	//���U���g�����摜���������B
	m_resultSprite = NewGO<SpriteRender>(0);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 300.0f, 300.0f);

	//Start�֐���return��
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_resultSprite);
}

void ResultScene::Update()
{
	//1P�̃Z���N�g�{�^��(�L�[�{�[�h�F�X�y�[�X)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//exe����ăQ�[���I��
		exit(EXIT_SUCCESS);
	}
}