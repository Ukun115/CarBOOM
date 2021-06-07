#include "stdafx.h"
#include "GameScene.h"
#include "PointLight.h"
#include "ResultScene.h"
#include "SkinModelRender.h"

bool GameScene::Start()
{
	//モデルをロード
	m_skinmodelrender = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	m_skinmodelrender->Init("Assets/modelData/unityChan.tkm");

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{
	DeleteGO(m_skinmodelrender);
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