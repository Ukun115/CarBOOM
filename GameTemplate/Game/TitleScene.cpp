#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


bool TitleScene::Start()
{


	//Start�֐���return��
	return true;
}

TitleScene::~TitleScene()
{

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