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
	m_skinmodelrender->Init("Assets/modelData/LowPoly_PlayerCar_Bule.tkm");
	m_skinmodelrender->SetScale({2,2,2});

	m_bgModel = NewGO<SkinModelRender>(0);
	m_bgModel->Init("Assets/modelData/bg/bg.tkm");

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{

	DeleteGO(m_skinmodelrender);
}

void GameScene::Update()
{
	//ユニティーちゃんが動くかどうかのテスト/////////////////////////////
	if (g_pad[0]->IsPress(enButtonRight)) {
		m_unityPos.x += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_unityPos.x -= 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonUp)) {
		m_unityPos.z += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		m_unityPos.z -= 1.0f;
	}
	m_skinmodelrender->SetPosition(m_unityPos);	//位置情報更新
	//////////////////////////////////////////////////////////////////////

	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}