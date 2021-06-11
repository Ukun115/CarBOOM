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
	m_player = NewGO<Player>(0);

	//ステージモデルをロード
	m_normalStage = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	m_normalStage->Init("Assets/modelData/bg/stage_00.tkm");

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{
	//ステージを削除。
	DeleteGO(m_normalStage);
	//プレイヤークラスを削除。
	DeleteGO(m_player);
}

void GameScene::Update()
{
	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}