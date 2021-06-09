#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


bool TitleScene::Start()
{
	//�T���v���w�i�摜���������B
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/eheheNS.dds", 1300.0f, 750.0f);
	m_spriteRender->SetPosition(Vector3::Zero);

	//Start�֐���return��
	return true;
}

TitleScene::~TitleScene()
{
	DeleteGO(m_spriteRender);
}

void TitleScene::Update()
{
	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�Q�[����ʂɑJ��
		NewGO<GameScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}