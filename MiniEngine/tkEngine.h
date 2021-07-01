#pragma once

#include "HID/GamePad.h"
#include "../GameTemplate/Game/GameTime.h"

class GraphicsEngine;

class TkEngine {
public:
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~TkEngine();
	/// <summary>
	/// フレームの開始時に呼ばれる処理。
	/// </summary>
	void BeginFrame();
	/// <summary>
	/// フレームの終了時に呼ばれる処理。
	/// </summary>
	void EndFrame();
	/// <summary>
	/// ゲームエンジンの初期化。
	/// </summary>
	void Init(HWND hwnd, UINT frameBufferWidth, UINT frameBufferHeight);

private:
	GraphicsEngine* m_graphicsEngine = nullptr;		//グラフィックエンジン。
	GamePad m_pad[GamePad::CONNECT_PAD_MAX];		//ゲームパッド。
	GameTime m_gameTime;							//ゲームタイム。

};

extern TkEngine* g_engine;	//TKエンジン。
extern GameTime* g_gameTime;

//デバッグ機能を簡易的にアクセスするための名前空間
namespace dbg {

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
	/*!
	* @brief	コリジョンのデバッグ表示を有効にする。
	*@param[in]	colliObj	コリジョンオブジェクト。
	*/
	static inline void SetDrawPhysicsCollisionEnable()
	{
		PhysicsWorld().SetDebugDrawMode(1);
	}
	/*!
	* @brief	コリジョンのデバッグ表示を有効にする。
	*@param[in]	colliObj	コリジョンオブジェクト。
	*/
	static inline void SetDrawPhysicsCollisionDisable()
	{
		PhysicsWorld().SetDebugDrawMode(0);
	}
	/*!
	* @brief	ベクトルのデバッグ出力。
	*/
	static inline void DrawVector(Vector3 vector, Vector3 origin, const char* name = "no name")
	{
		prefab::CVectorRender::SRenderData renderData = { name, vector, origin };
		Engine().GetVectorRender()->AddVector(renderData);
	}
	/*!
	* @brief	ベクトルのデバッグ描画を有効にする。
	*/
	static inline void SetDrawVectorEnable()
	{
		Engine().GetVectorRender()->SetRenderFlag(true);
	}
	/*!
	* @brief	ベクトルのデバッグ描画を無効にする。
	*/
	static inline void SetDrawVectorDisable()
	{
		Engine().GetVectorRender()->SetRenderFlag(false);
	}
	static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
	{
		Engine().GetVectorRender()->SetRenderVectorNameList(list);
	}
#else

	static inline void SetDrawPhysicsCollisionEnable()
	{
	}

	static inline void SetDrawPhysicsCollisionDisable()
	{
	}

	static inline void DrawVector(Vector3 vector, Vector3 origin, const char* name = "no name")
	{
	}

	static inline void SetDrawVectorEnable()
	{
	}

	static inline void SetDrawVectorDisable()
	{
	}
	static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
	{
	}
#endif

}
