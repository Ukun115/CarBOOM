#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "tkSoundSource.h"					//サウンド

//ゲーム全体で頻繁に使うのでstdafx.hでhをインクルードする
#include "SkinModelRender.h"				//モデル
#include "SpriteRender.h"					//画像
#include "FontRender.h"						//文字
#include "Light.h"							//ライト
#include "../../ExEngine/effect/Effect.h"	//エフェクト

//色とかはここに名前空間でまとめておく。
//NewGOの際の名前等も
namespace
{
	/// <summary>
	/// 優先度
	/// </summary>
	const int PRIORITY_0 = 0;
	const int PRIORITY_1 = 1;
	const int PRIORITY_2 = 2;

	/// <summary>
	/// 色
	/// </summary>
	const Vector3 WHITE = { 1.0f, 1.0f ,1.0f };	//白色
	const Vector3 RED = { 1.0f, 0.0f ,0.0f };	//赤色
	const Vector3 BLUE = { 0.0f, 0.0f ,1.0f };	//青色
	const Vector3 YELLOW = { 0.0f, 0.0f ,1.0f };//黄色
	const Vector3 GREEN = { 1.0f, 1.0f ,0.0f };	//緑色
	const Vector3 GRAY = { 0.7f,0.7f,0.7f };	//灰色
	/// <summary>
	/// 名前
	/// </summary>
	const char* TITLESCENE_NAME = "titlescene";
	const char* STAGESELECT_NAME = "stageselectscene";
	const char* GAMESCENE_NAME = "gamescene";
	const char* LIGHT_NAME = "light";
	const char* PLAYER_NAME = "player";
	const char* ENEMY_NAME = "enemy";
	/// <summary>
	/// ステージ番号
	/// </summary>
	const int STAGE1 = 1;
	const int STAGE2 = 2;
	const int STAGE3 = 3;

	const float GRAVITY = 0.3f;		//重力
}