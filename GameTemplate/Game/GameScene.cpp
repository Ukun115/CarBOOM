#include "stdafx.h"
#include "GameScene.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "ResultScene.h"

bool GameScene::Start()
{
	//ディレクションライトをロード
	m_directionlight = NewGO<DirectionLight>(0);

	//ポイントライトをロード
	m_pointlight = NewGO<PointLight>(0);

	//モデルをロード
	m_skinmodelrender = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	m_skinmodelrender->Init("Assets/modelData/unityChan.tkm");
	//モデルにディレクションライトの設定
	m_skinmodelrender->SetDirLigData(directionLig);

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