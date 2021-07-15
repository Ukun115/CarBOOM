#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "ExEngine.h"
#include "tkSoundSource.h"					//サウンド


//ゲーム全体で頻繁に使うのでstdafx.hでhをインクルードする
#include "Noncopyable.h"					// コピー禁止ポリシーを提供するためのクラス。
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
	const int PRIORITY_3 = 3;
	const int PRIORITY_4 = 4;
	const int PRIORITY_5 = 5;
	const int PRIORITY_6 = 6;
	const int PRIORITY_10 = 10;

	/// <summary>
	/// 色
	/// </summary>
	const Vector3 WHITE = { 1.0f, 1.0f ,1.0f };	//白色
	const Vector3 RED = { 1.0f, 0.0f ,0.0f };	//赤色
	const Vector3 BLUE = { 0.0f, 0.0f ,1.0f };	//青色
	const Vector3 YELLOW = { 1.0f, 1.0f ,0.0f };//黄色
	const Vector3 GREEN = { 0.0f, 1.0f ,0.0f };	//緑色
	const Vector3 GRAY = { 0.8f,0.8f,0.8f };	//灰色
	const Vector3 BLACK = { 0.0f,0.0f,0.0f };	//黒色
	/// <summary>
	/// 名前
	/// </summary>
	const char* const LIGHT_NAME = { "light" };
	const char* const TITLESCENE_NAME = { "titlescene" };
	const char* const STAGESELECT_NAME = { "stageselectscene" };
	const char* const GAMESCENE_NAME = { "gamescene" };
	const char* const STAGE_NAME = { "stage" };
	const char* const PLAYER_NAME = { "player" };
	const char* const ENEMY_NAME = { "enemy" };

	/// <summary>
	/// ステージ番号
	/// </summary>
	const int STAGE1 = 1;
	const int STAGE2 = 2;
	const int STAGE3 = 3;
	const int STAGE4 = 4;

	const float GRAVITY = 0.3f;		//重力
	const int PLAYER_MAX_NUM = 4;
	const int ENEMY_MAX_NUM = 6;
}