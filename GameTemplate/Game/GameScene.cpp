#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "PhysicsPlayer.h"
#include "Stage.h"

namespace
{
	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//制限時間フォントの位置
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//制限時間フォントの色
	const float     TIMELIMIT_ROT = 0.0f;						//制限時間フォントの傾き
	const float     TIMELIMIT_SCA = 1.5f;						//制限時間フォントの拡大率
	const Vector2   TIMELIMIT_PIV = { 0.0f,0.0f };				//制限時間フォントの基点

	const Vector2   PLA1SCORE_POS = { -460.0f, 255.0f };			//1Pスコアフォントの位置
	const Vector2   PLA2SCORE_POS = { 520.0f, 255.0f };			//2Pスコアフォントの位置
	const Vector2   PLA3SCORE_POS = { -460.0f,-205.0f };			//3Pスコアフォントの位置
	const Vector2   PLA4SCORE_POS = { 520.0f,-205.0f };			//4Pスコアフォントの位置

	const Vector2 PLAYER1_SCOREFONTPOS = { -630.0f,260.0f };	//プレイヤー1のSCROE文字表示
	const Vector2 PLAYER2_SCOREFONTPOS = { 350.0f,260.0f };		//プレイヤー2のSCROE文字表示
	const Vector2 PLAYER3_SCOREFONTPOS = { -630.0f,-200.0f };	//プレイヤー3のSCROE文字表示
	const Vector2 PLAYER4_SCOREFONTPOS = { 350.0f,-200.0f };	//プレイヤー4のSCROE文字表示

	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int PLAYER3 = 2;
	const int PLAYER4 = 3;
	const int MAXPLAYERNUM = 4;		//プレイヤーの最大人数

	const int SWITCH_PLA1 = 0;
	const int SWITCH_PLA2 = 1;
	const int SWITCH_PLA3 = 2;
	const int SWITCH_PLA4 = 3;
}

bool GameScene::Start()
{
	//敵クラス
	enemy = NewGO<Enemy>(0,"enemy");
	//プレイヤークラス
	physicsPlayer = NewGO<PhysicsPlayer>(0, "physicsplayer");
	//ステージクラス
	physicsStage = NewGO<Stage>(0, nullptr);

	//フォントクラス（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_timeLimit = NewGO<FontRender>(1);
	for (int i = 0; i < 4; i++) {
		m_ScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_ScoreFontRender[i]->Init
		(
			L"Score",
			GetScorePos(i),
			TIMELIMIT_COL,	//カラー
			TIMELIMIT_ROT,	//傾き
			TIMELIMIT_SCA,	//拡大率
			TIMELIMIT_PIV	//基点
		);

		m_TextScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_TextScoreFontRender[i]->Init
		(
			L"",
			SetScoreTextPos(i),
			TIMELIMIT_COL,	//カラー
			TIMELIMIT_ROT,	//傾き
			TIMELIMIT_SCA,	//拡大率
			TIMELIMIT_PIV	//基点
		);


		//文字の境界線表示
		m_ScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
	//初期設定。
	m_timeLimit->Init
	(
		L"",
		TIMELIMIT_POS,	//位置
		TIMELIMIT_COL,	//カラー
		TIMELIMIT_ROT,	//傾き
		TIMELIMIT_SCA,	//拡大率
		TIMELIMIT_PIV	//基点
	);
	//文字の境界線表示
	m_timeLimit->SetShadowParam(true, 1.0f, Vector4::Black);

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{
	//ステージを削除。
	DeleteGO(m_normalStage);
	//プレイヤークラスを削除。
	DeleteGO(physicsPlayer);
	//タイムを削除
	DeleteGO(m_timeLimit);
}

void GameScene::Update()
{
	//ゲームシーンに遷移したら、
	if (m_countTimeFlg)
	{
		//スタートまでのカウントダウンを開始

		switch (m_countDownTimer) {
		case 0:
			//「3」表示
			m_sprite[0] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

			break;

		case 60:
			//「3」削除。
			DeleteGO(m_sprite[0]);

			//「2」表示
			m_sprite[1] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);

			break;

		case 120:
			//「2」削除。
			DeleteGO(m_sprite[1]);

			//「1」表示
			m_sprite[2] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);

			break;

		case 180:
			//「1」削除。
			DeleteGO(m_sprite[2]);

			//「GO!!」表示
			m_sprite[3] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);

			break;

		case 300:
			//「GO!!」削除。
			DeleteGO(m_sprite[3]);

			//カウントダウンの処理を抜ける。
			m_countTimeFlg = false;

			break;
		}
		m_countDownTimer++;
	}
	//カウントダウンが終わってから制限時間を刻んでいく。
	else
	{
		//制限時間を縮めていく。
		m_timer--;
	}
	counttime = m_timer / 60;
	//０秒になってからのカウントがマイナスに行かないように補正
	if (counttime < 0)
	{
		counttime = 0;
	}

	//残り時間の描画
	wchar_t text1[64];
	swprintf_s(text1, L"%d", counttime);
	//画面表示
	m_timeLimit->SetText(text1);

	wchar_t text2[64];
	swprintf_s(text2, L"%d", m_plscore);


	for (int i = 0; i < 4; i++) {
		//プレイヤーごとのスコアの描画
		swprintf_s(text1, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text1);
	}

	//制限時間が0秒になったら、
	if (counttime == 0)
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0, nullptr);
	}

	//1Pのセレクトボタン(キーボード：スペース)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0, nullptr);
		//このクラスの削除
		DeleteGO(this);
	}
}

//「Score : 」の表示位置判別関数
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case SWITCH_PLA1:
		return PLAYER1_SCOREFONTPOS;
		break;
	case SWITCH_PLA2:
		return PLAYER2_SCOREFONTPOS;
		break;
	case SWITCH_PLA3:
		return PLAYER3_SCOREFONTPOS;
		break;
	case SWITCH_PLA4:
		return PLAYER4_SCOREFONTPOS;
		break;
	}
}

Vector2 GameScene::SetScoreTextPos(int t) {
	switch (t)
	{
	case SWITCH_PLA1:
		return PLA1SCORE_POS;
		break;
	case SWITCH_PLA2:
		return PLA2SCORE_POS;
		break;
	case SWITCH_PLA3:
		return PLA3SCORE_POS;
		break;
	case SWITCH_PLA4:
		return  PLA4SCORE_POS;
		break;
	}
}