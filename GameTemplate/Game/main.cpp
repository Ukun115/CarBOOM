#include "stdafx.h"
#include "system/system.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "TitleScene.h"


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//ディレクションライトをロード
	DirectionLight* m_directionlight = NewGO<DirectionLight>(0, "directionlight");
	m_directionlight->SetDirectionLightData();

	//ポイントライトをロード
	PointLight* m_pointlight = NewGO<PointLight>(0, "pointlight");
	m_pointlight->SetPointLightData();

	//スポットライトをロード
	SpotLight* m_spotlight = NewGO<SpotLight>(0, "spotlight");
	m_spotlight->SetSpotLightData();

	//タイトルシーンクラスから開始
	TitleScene* titleScene = NewGO<TitleScene>(0);

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);


		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}