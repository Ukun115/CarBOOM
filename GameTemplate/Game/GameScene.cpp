#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "TitleScene.h"

namespace
{
	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//制限時間フォントの位置
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//制限時間フォントの色
	const float     TIMELIMIT_ROT = 0.0f;						//制限時間フォントの傾き
	const float     TIMELIMIT_SCA = 1.5f;						//制限時間フォントの拡大率
	const Vector2   TIMELIMIT_PIV = { 0.0f,0.0f };				//制限時間フォントの基点

	const Vector2   PLA1SCORE_POS = { -460.0f, 255.0f };		//1Pスコアフォントの位置
	const Vector2   PLA2SCORE_POS = { 520.0f, 255.0f };			//2Pスコアフォントの位置
	const Vector2   PLA3SCORE_POS = { -460.0f,-205.0f };		//3Pスコアフォントの位置
	const Vector2   PLA4SCORE_POS = { 520.0f,-205.0f };			//4Pスコアフォントの位置

	const Vector2 PLAYER1_SCOREFONTPOS = { -630.0f,260.0f };	//プレイヤー1のSCROE文字表示
	const Vector2 PLAYER2_SCOREFONTPOS = { 350.0f,260.0f };		//プレイヤー2のSCROE文字表示
	const Vector2 PLAYER3_SCOREFONTPOS = { -630.0f,-200.0f };	//プレイヤー3のSCROE文字表示
	const Vector2 PLAYER4_SCOREFONTPOS = { 350.0f,-200.0f };	//プレイヤー4のSCROE文字表示

	const Vector3 PLAYER1_CROWNPOS = { -320.0f, 310.0f,0.0f };		//プレイヤー1の王冠表示位置
	const Vector3 PLAYER2_CROWNPOS = { 300.0f, 310.0f,0.0f };		//プレイヤー2の王冠表示位置
	const Vector3 PLAYER3_CROWNPOS = { -300.0f, -310.0f,0.0f };		//プレイヤー3の王冠表示位置
	const Vector3 PLAYER4_CROWNPOS = { 300.0f, -310.0f,0.0f };		//プレイヤー4の王冠表示位置
	const Vector3 CROWNSCA = { 0.2f, 0.2f,0.2f };					//王冠の大きさ
}

bool GameScene::Start()
{
	//敵クラス
	enemy = NewGO<Enemy>(0,"enemy");
	//プレイヤークラス
	physicsPlayer = NewGO<Player>(0, "physicsplayer");
	//ステージクラス
	physicsStage = NewGO<Stage>(0, nullptr);

	//インスタンスを作成
	m_titlescene = FindGO<TitleScene>("titlescene");

	//王冠を表示
	m_crownSprite = NewGO<SpriteRender>(1, nullptr);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });

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

	//現在のスコア１位を判定し、王冠画像を移動
	NowCrown();

	//制限時間が0秒になったら、
	if (counttime == 0)
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0, nullptr);
	}
}

//「Score」の表示位置判別関数
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case PLAYER1:
		return PLAYER1_SCOREFONTPOS;
		break;
	case PLAYER2:
		return PLAYER2_SCOREFONTPOS;
		break;
	case PLAYER3:
		return PLAYER3_SCOREFONTPOS;
		break;
	case PLAYER4:
		return PLAYER4_SCOREFONTPOS;
		break;
	}
}

Vector2 GameScene::SetScoreTextPos(int t) {
	switch (t)
	{
	case PLAYER1:
		return PLA1SCORE_POS;
		break;
	case PLAYER2:
		return PLA2SCORE_POS;
		break;
	case PLAYER3:
		return PLA3SCORE_POS;
		break;
	case PLAYER4:
		return  PLA4SCORE_POS;
		break;
	}
}

//ｘは落としたプレイヤー、yは自滅したプレイヤー
void GameScene::GetPlayerAddScore(int x,int y)
{
	//自滅したとき、
	if (x == 4)
	{
		//20pt減少
		m_plscore[y] -= 20;
		//点数が０以下にならないように補正
		if (m_plscore[y] < 0)
		{
			m_plscore[y] = 0;
		}
	}
	//落としたとき、
	else
	{
		//30pt増加
		m_plscore[x] += 30;
		//もし落とした敵が1位だったら、
		if (y == m_nowNumOnePla)
		{
			//落とされた１位はマイナス60pt
			//これを入れることで１位が狙われやすい仕様にしている。
			m_plscore[y] -= 60;
			//点数が０以下にならないように補正
			if (m_plscore[y] < 0)
			{
				m_plscore[y] = 0;
			}
		}
	}
}

//王冠画像の位置更新関数
void GameScene::NowCrown()
{
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		for (int u = PLAYER1; u < MAXPLAYERNUM; u++)
		{
			//番号が同じときは次のループに行く
			if (i == u)
			{
				continue;
			}
			//今のプレイヤー(i)と次のプレイヤー(u)を比較
			//次のプレイヤーのほうがスコアが高いとき、
			if (m_plscore[i] < m_plscore[u])
			{
				m_nowNumOnePla = u;
			}
		}
	}

	//王冠の位置を次のプレイヤーの位置に変更
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWNPOS });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWNPOS });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWNPOS });
	}
}