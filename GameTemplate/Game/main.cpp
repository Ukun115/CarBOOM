#include "stdafx.h"
#include "system/system.h"
#include "../../ExEngine/level2D/CaslFile.h"
#include "Sample.h"

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
	
	Sample* sample = NewGO<Sample>(0);
	/*for (int i = 0; i < objList.size(); i++)
	{
		auto obj = objList[i];
		SpriteInitData data;
		data.m_width = obj->width;
		data.m_height = obj->height;
		data.m_ddsFilePath[0] = "Assets/Image/sample.dds";
		//data.m_ddsFilePath[0] = "Assets/Image/a.dds";

		data.m_fxFilePath = "Assets/shader/sprite.fx";
		sprite[i].Init(data);
		pos[i].x = obj->position.x;
		pos[i].y = obj->position.y;
	}*/
	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////
		
		//sprite[1].Update(pos[1], Quaternion::Identity, Vector3::One);
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

