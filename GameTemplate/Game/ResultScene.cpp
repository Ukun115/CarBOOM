#include "stdafx.h"
#include "ResultScene.h"

namespace
{

}

bool ResultScene::Start()
{
	//�T���v���w�i�摜���������B
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
	m_spriteRender->SetPosition(Vector3::Zero);

	//Start�֐���return��
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_spriteRender);
}

void ResultScene::Update()
{
	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//exe����ăQ�[���I��
		exit(EXIT_SUCCESS);
	}
}