#include "stdafx.h"
#include "ResultScene.h"

bool ResultScene::Start()
{


	//Start�֐���return��
	return true;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//exe����ăQ�[���I��
		exit(EXIT_SUCCESS);
	}
}