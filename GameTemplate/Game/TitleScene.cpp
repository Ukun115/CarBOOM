#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


bool TitleScene::Start()
{


	//Start関数のreturn文
	return true;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Update()
{
	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//ゲーム画面に遷移
		NewGO<GameScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}