#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "Background.h"
#include "HelloFont.h"
#include "Hello2D.h"
#include "HelloLevel2D.h"
#include "PhysicsBall.h"
#include "Seesaw.h"

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
	
	//プレイヤーを生成。
	//NewGO<Player>(0);
	//背景を生成。
	NewGO<Background>(0);
	////フォント表示のサンプルを生成
	/*NewGO<HelloFont>(0);
	////2D表示のサンプルを生成。
	NewGO<Hello2D>(0);
	////レベル2Dのサンプルを生成。
	NewGO<HelloLevel2D>(0);*/
	NewGO< PhysicsBall>(0);
	NewGO<Seesaw>(0);
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		//登録されているゲームオブジェクトの更新関数を呼び出す。
		GameObjectManager::GetInstance()->ExecuteUpdate();

		//物理ワールドの更新。
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		//登録されているゲームオブジェクトの描画関数を呼び出す。
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		

		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

