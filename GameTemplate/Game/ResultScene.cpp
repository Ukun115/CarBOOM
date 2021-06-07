#include "stdafx.h"
#include "ResultScene.h"

bool ResultScene::Start()
{


	//Start関数のreturn文
	return true;
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update()
{
	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//exeを閉じてゲーム終了
		exit(EXIT_SUCCESS);
	}
}