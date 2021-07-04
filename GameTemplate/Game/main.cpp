#include "stdafx.h"
#include "system/system.h"
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
	//フィジクスワールドのインスタンスを作成する。
	PhysicsWorld::CreateInstance();
	//エフェクトエンジンのインスタンスを作成する。
	EffectEngine::CreateInstance();
	//サウンドエンジンのインスタンスを作成する。
	SoundEngine::CreateInstance();
	SoundEngine::GetInstance()->Init();

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	Light* m_light = nullptr;
	//ライトオブジェクト生成
	m_light = NewGO<Light>(PRIORITY_0, LIGHT_NAME);
	//ディレクションライトをセット
	m_light->SetDirectionLightData();
	//半球ライトをセット
	m_light->SetHemiSphereLightData();

	//タイトルシーンオブジェクト生成
	TitleScene* m_titleScene = NewGO<TitleScene>(PRIORITY_0, TITLESCENE_NAME);


	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////


		//ゲームオブジェクトマネージャーの更新。
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//物理ワールドの更新。
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		//エフェクトエンジンの更新。
		EffectEngine::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());

		//登録されているゲームオブジェクトの描画関数を呼び出す。
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//エフェクトのドロー。
		EffectEngine::GetInstance()->Draw();

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}