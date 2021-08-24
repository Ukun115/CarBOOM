#include "stdafx.h"
#include "system/system.h"
#include "TitleScene.h"
#include "StopWatch.h"

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

	//サウンド管轄クラス
	nsCARBOOM::SoundPlayBack* m_soundPlayBack = nullptr;
	m_soundPlayBack = NewGO<nsCARBOOM::SoundPlayBack>(nsStdafx::PRIORITY_0, nsStdafx::SOUNDPLAYBACK_NAME);

	//ストップウォッチを生成する
	StopWatch stopWatch;

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//タイトルシーンオブジェクト生成
	nsCARBOOM::TitleScene* m_titleScene = NewGO<nsCARBOOM::TitleScene>(nsStdafx::PRIORITY_0, nullptr);

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//ストップウォッチの計測開始
		stopWatch.Start();

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

		//スピンロックを行う。
		int restTime = 0;
		do {
			stopWatch.Stop();
			restTime = 16 - (int)stopWatch.GetElapsedMillisecond();
		} while (restTime > 0);

		//ストップウォッチの計測終了
		stopWatch.Stop();
		//デルタタイムをストップウォッチの計測時間から、計算する
		GameTime().PushFrameDeltaTime((float)stopWatch.GetElapsed());
	}

	/*GameObjectManager::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	EffectEngine::DeleteInstance();*/

	return 0;
}