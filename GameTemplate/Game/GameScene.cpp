#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"


namespace
{

}

bool GameScene::Start()
{
	//プレイヤークラスを追加
	NewGO<Player>(0);

	//ステージモデルをロード
	bg_normal = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	bg_normal->Init("Assets/modelData/bg/stage_00.tkm");

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{

}

void GameScene::Update()
{


	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}