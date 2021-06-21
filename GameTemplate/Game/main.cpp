#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
}


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


<<<<<<< HEAD
	//ライトオブジェクト生成
=======
	//ライトクラスをロード
>>>>>>> remotes/origin/master
	Light* m_light = NewGO<Light>(PRIORITY_0, "light");
	//ディレクションライトをセット
	m_light->SetDirectionLightData();

<<<<<<< HEAD
	//タイトルシーンオブジェクト生成
=======
	//タイトルシーンクラスからゲーム開始
>>>>>>> remotes/origin/master
	TitleScene* m_titleScene = NewGO<TitleScene>(PRIORITY_0,"titlescene");


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

		//物理ワールドの更新。
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}