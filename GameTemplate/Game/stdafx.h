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
#include "SoundPlayBack.h"		//サウンド

//色とかはここに名前空間でまとめておく。
//NewGOの際の名前等も
namespace nsStdafx
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
	const int PRIORITY_7 = 7;
	const int PRIORITY_10 = 10;
	/// <summary>
	/// 色
	/// </summary>
	const Vector3 WHITE = { 1.0f, 1.0f ,1.0f };	//白色
	const Vector3 RED = { 1.0f, 0.0f ,0.0f };	//赤色
	const Vector3 GREEN = { 0.0f, 1.0f ,0.0f };	//緑色
	const Vector3 BLUE = { 0.0f, 0.0f ,1.0f };	//青色
	const Vector3 YELLOW = { 1.0f, 1.0f ,0.0f };//黄色
	const Vector3 GRAY = { 0.8f,0.8f,0.8f };	//灰色
	const Vector3 BLACK = { 0.0f,0.0f,0.0f };	//黒色
	/// <summary>
	/// 名前
	/// </summary>
	const char* const LIGHT_NAME = { "light" };
	const char* const GAMESCENE_NAME = { "gamescene" };
	const char* const STAGE_NAME = { "stage" };
	const char* const PLAYER_NAME = { "player" };
	const char* const ENEMY_NAME = { "enemy" };
	const char* const SOUNDPLAYBACK_NAME = { "soundplayback" };
	const char* const PLAYERTURN_NAME = { "playerturn" };
	const char* const ENEMYTURN_NAME = { "enemyturn" };
	const char* const ENEMYMOVESPEED_NAME = { "enemymovespeed" };
	const char* const ENEMYPATOLUMP_NAME = { "enemypatolump" };
	const char* const PAUSE_NAME = { "pause" };
	/// <summary>
	/// ステージ番号
	/// </summary>
	const int STAGE1 = 1;
	const int STAGE2 = 2;
	const int STAGE3 = 3;
	const int STAGE4 = 4;
	const int STAGE5 = 5;
	const int STAGE6 = 6;

	const int INT_ZERO = 0;
	const float FLOAT_ZERO = 0.0f;

	const float GRAVITY = 0.3f;		//重力
}