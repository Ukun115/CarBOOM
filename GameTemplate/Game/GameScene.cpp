#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "TitleScene.h"


namespace
{
<<<<<<< HEAD
	//優先度
	const int PRIORITY_0 = 0;
	const int PRIORITY_1 = 1;
=======
	const int PRIORITY_0 = 0;	//優先度0
	const int PRIORITY_1 = 1;	//優先度1
>>>>>>> remotes/origin/master

	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//制限時間フォントの位置
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//制限時間フォントの色

	const Vector2   PLA1SCORE_POS = { -520.0f, 255.0f };	//1Pスコアフォントの位置
	const Vector2   PLA2SCORE_POS = { 450.0f, 255.0f };		//2Pスコアフォントの位置
	const Vector2   PLA3SCORE_POS = { -520.0f,-205.0f };	//3Pスコアフォントの位置
	const Vector2   PLA4SCORE_POS = { 450.0f,-205.0f };		//4Pスコアフォントの位置

	const Vector4	PLAYER1_COL_RED = { 1.0f,0.0f,0.0f,1.0f };		//プレイヤー１のスコアの色
	const Vector4	PLAYER2_COL_BLUE = { 0.0f,0.0f,1.0f,1.0f };		//プレイヤー２のスコアの色
	const Vector4	PLAYER3_COL_YELLOW = { 1.0f,1.0f,0.0f,1.0f };		//プレイヤー３のスコアの色
	const Vector4	PLAYER4_COL_GREEN = { 0.0f,1.0f,0.0f,1.0f };		//プレイヤー４のスコアの色
	const Vector4	PLAYER_COL_GRAY = { 0.7f,0.7f,0.7f,1.0f };		//全プレイヤーの非アクティブのスコアの色

	const float     FONT_ROT = 0.0f;			//フォントの傾き
	const Vector2   FONT_PIV = { 1.0f,1.0f };	//フォントの基点
	const float     FONT_SCA = 1.5f;			//フォントの拡大率

	const Vector2 PLAYER1_PT_POS = { -420.0f,235.0f };	//プレイヤー1のpt文字表示
	const Vector2 PLAYER2_PT_POS = { 550.0f,235.0f };	//プレイヤー2のpt文字表示
	const Vector2 PLAYER3_PT_POS = { -420.0f,-230.0f };	//プレイヤー3のpt文字表示
	const Vector2 PLAYER4_PT_POS = { 550.0f,-230.0f };	//プレイヤー4のpt文字表示
	const float PT_SCA = 0.85f;		//pt文字の大きさ

	const Vector3 PLAYER1_CROWN_POS = { -320.0f, 310.0f,0.0f };		//プレイヤー1の王冠画像表示位置
	const Vector3 PLAYER2_CROWN_POS = { 300.0f, 310.0f,0.0f };		//プレイヤー2の王冠画像表示位置
	const Vector3 PLAYER3_CROWN_POS = { -300.0f, -310.0f,0.0f };	//プレイヤー3の王冠画像表示位置
	const Vector3 PLAYER4_CROWN_POS = { 300.0f, -310.0f,0.0f };		//プレイヤー4の王冠画像表示位置
	const Vector3 CROWN_SCA = { 0.2f, 0.2f,0.2f };					//王冠画像の拡大率

	const Vector3 CROWN_MODEL_SCA = {0.5f,0.5f,0.5f};	//王冠モデルの拡大率
	//配列番号
	const int ARRAY_NUM_0 = 0;
	const int ARRAY_NUM_1 = 1;
	const int ARRAY_NUM_2 = 2;
	const int ARRAY_NUM_3 = 3;
}


bool GameScene::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>("titlescene");

<<<<<<< HEAD
	//敵オブジェクト生成
	m_enemy = NewGO<Enemy>(PRIORITY_0,"enemy");
	//プレイヤーオブジェクト生成
	m_player = NewGO<Player>(PRIORITY_0, "player");
	//ステージオブジェクト生成
	m_normalStage = NewGO<Stage>(PRIORITY_0, nullptr);

	//王冠画像オブジェクト生成
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//王冠画像を初期化
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);	//王冠画像
	m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });						//位置を設定
	m_crownSprite->SetScale({ CROWN_SCA });									//拡大率を設定
	m_crownSprite->Deactivate();					//はじめは誰も一位じゃないので隠しておく。
=======
	//敵クラス
	m_enemy = NewGO<Enemy>(PRIORITY_0,"enemy");
	//プレイヤークラス
	m_player = NewGO<Player>(PRIORITY_0, "player");
	//ステージクラス
	m_normalStage = NewGO<Stage>(PRIORITY_0, nullptr);

	//王冠画像を初期化
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });
	//はじめは誰も一位じゃないので隠しておく。
	m_crownSprite->Deactivate();
>>>>>>> remotes/origin/master

	//王冠モデルオブジェクト生成
	m_crownModel = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
	//王冠モデルを初期化
<<<<<<< HEAD
	m_crownModel->Init("Assets/modelData/Crown.tkm");
	m_crownModel->SetScale({ Vector3::Zero });	//はじめは誰も１位じゃないので大きさを0にして隠しておく

	//制限時間フォントオブジェクト生成（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	for (int i = 0; i < 4; i++) {
		//プレイヤーごとのptフォントオブジェクト生成
		m_ScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//初期化
		m_ScoreFontRender[i]->Init
		(
			L"pt",				//テキスト
			GetScorePos(i),		//位置
			ScoreColor(i),		//色
			FONT_ROT,			//傾き
			PT_SCA,				//拡大率
			FONT_PIV			//基点
		);
		//プレイヤーごとのポイントフォントオブジェクト生成
		m_TextScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//初期化
		m_TextScoreFontRender[i]->Init
		(
			L"",					//テキスト
			SetScoreTextPos(i),		//位置
			ScoreColor(i),			//色
			FONT_ROT,				//傾き
			FONT_SCA,				//拡大率
			FONT_PIV				//基点
=======
	m_crownModel = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
	m_crownModel->Init("Assets/modelData/Crown.tkm");
	m_crownModel->SetScale({ Vector3::Zero });	//はじめは誰も１位じゃないので大きさを0にして隠しておく

	//フォントクラス（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	for (int i = 0; i < 4; i++) {
		m_ScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		m_ScoreFontRender[i]->Init
		(
			L"pt",
			GetScorePos(i),
			ScoreColor(i),	//色
			TIMELIMIT_ROT,	//傾き
			SCORESCA,	//拡大率
			TIMELIMIT_PIV	//基点
		);

		m_TextScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		m_TextScoreFontRender[i]->Init
		(
			L"",
			SetScoreTextPos(i),
			ScoreColor(i),	//色
			TIMELIMIT_ROT,	//傾き
			TIMELIMIT_SCA,	//拡大率
			TIMELIMIT_PIV	//基点
>>>>>>> remotes/origin/master
		);


		//文字の境界線表示
		m_ScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
		//文字の境界線表示
		m_TextScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
	//登録されていないプレイヤーのスコアはグレー表示にする
	for (int i = m_titleScene->GetTotalPlaNum() ; i < 4; i++)
	{
		m_ScoreFontRender[i]->SetColor(PLAYER_COL_GRAY);
		m_TextScoreFontRender[i]->SetColor(PLAYER_COL_GRAY);
	}
	//制限時間フォントの初期化
	m_timeLimit->Init
	(
		L"",			//テキスト
		TIMELIMIT_POS,	//位置
		TIMELIMIT_COL,	//色
<<<<<<< HEAD
		FONT_ROT,		//傾き
		FONT_SCA,		//拡大率
		FONT_PIV		//基点
=======
		TIMELIMIT_ROT,	//傾き
		TIMELIMIT_SCA,	//拡大率
		TIMELIMIT_PIV	//基点
>>>>>>> remotes/origin/master
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
	DeleteGO(m_player);
	//敵クラスを削除。
	DeleteGO(m_enemy);
	//タイムを削除
	DeleteGO(m_timeLimit);
}


void GameScene::Update()
{
	//ゲームシーンに遷移したら、
	if (m_isCountTimeFlg)
	{
		//カウントダウン処理を開始
		CountDown();
	}

<<<<<<< HEAD
	//制限時間のカウント&描画処理
	TimeLimit();
=======
		switch (m_countDownTimer) {
		case 0:
			//「3」表示
			m_sprite[0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

	//プレイヤーのスコア描画関数
	PlaScoreDraw();

	//現在のスコア１位を判定し、王冠画像を移動
	NowCrown();

<<<<<<< HEAD
	//制限時間が0秒になったら、
	if (m_counttime == 0)
	{
		//リザルト画面に遷移する
		ResultSceneTransition();
	}
}
=======
			//「2」表示
			m_sprite[1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

//カウントダウン処理関数
void GameScene::CountDown()
{
	//スタートまでのカウントダウンを開始

	switch (m_countDownTimer) {
	//カウントダウンタイマーが0のとき、
	case 0:
		//「３」画像オブジェクト生成
		m_sprite[ARRAY_NUM_0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_0]->SetPosition({ 0.0f,0.0f,0.0f });
		//初期化
		m_sprite[ARRAY_NUM_0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

		break;

	//カウントダウンタイマーが60のとき、
	case 60:
		//「3」削除。
		DeleteGO(m_sprite[ARRAY_NUM_0]);

<<<<<<< HEAD
		//「２」画像オブジェクト生成
		m_sprite[ARRAY_NUM_1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_1]->SetPosition({ 0.0f,0.0f,0.0f });
		//初期化
		m_sprite[ARRAY_NUM_1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);
=======
			//「1」表示
			m_sprite[2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

		break;

	//カウントダウンタイマーが120のとき、
	case 120:
		//「2」削除。
		DeleteGO(m_sprite[ARRAY_NUM_1]);

<<<<<<< HEAD
		//「１」画像オブジェクト生成
		m_sprite[ARRAY_NUM_2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_2]->SetPosition({ 0.0f,0.0f,0.0f });
		//初期化
		m_sprite[ARRAY_NUM_2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);
=======
			//「GO!!」表示
			m_sprite[3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);
>>>>>>> remotes/origin/master

		break;

		//カウントダウンタイマーが180のとき、
	case 180:
		//「1」削除。
		DeleteGO(m_sprite[ARRAY_NUM_2]);

<<<<<<< HEAD
		//「START」画像オブジェクト生成
		m_sprite[ARRAY_NUM_3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_3]->SetPosition({ 0.0f,0.0f,0.0f });
		//初期化
		m_sprite[ARRAY_NUM_3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);
=======
			//カウントダウンの処理を抜ける。
			m_isCountTimeFlg = false;
>>>>>>> remotes/origin/master

		break;

		//カウントダウンタイマーが300のとき、
		//「START」表示は特別少し長くする
	case 300:
		//「START」削除。
		DeleteGO(m_sprite[ARRAY_NUM_3]);

		//カウントダウンの処理を抜ける。
		m_isCountTimeFlg = false;

		break;
	}
	//カウントダウンのタイマーを加算
	m_countDownTimer++;
}


//制限時間処理関数
void GameScene::TimeLimit()
{
	//カウントダウンが終わってから制限時間を刻んでいく。
	if(m_isCountTimeFlg == false)
	{
		//制限時間を縮めていく。
		m_timer--;
	}
<<<<<<< HEAD

	m_counttime = m_timer / 60;

=======
	m_counttime = m_timer / 60;
>>>>>>> remotes/origin/master
	//０秒になってからのカウントがマイナスに行かないように補正
	if (m_counttime < 0)
	{
		m_counttime = 0;
	}

<<<<<<< HEAD
	//制限時間の描画
=======
	//残り時間の描画
	wchar_t text1[64];
>>>>>>> remotes/origin/master
	swprintf_s(text1, L"%d", m_counttime);
	//画面表示
	m_timeLimit->SetText(text1);
}


//プレイヤーのスコア描画関数
void GameScene::PlaScoreDraw()
{
	for (int i = 0; i < 4; i++) {
		//プレイヤーごとのスコアの描画
<<<<<<< HEAD
		swprintf_s(text2, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text2);
=======
		swprintf_s(text1, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text1);
	}

	//現在のスコア１位を判定し、王冠画像を移動
	NowCrown();

	//制限時間が0秒になったら、
	if (m_counttime == 0)
	{
		m_resultsenniTimer++;
		if(m_resultsenniTimer > 120)
		{
			//リザルト画面に遷移
			NewGO<ResultScene>(PRIORITY_0, nullptr);
		}
>>>>>>> remotes/origin/master
	}
}


//プレイヤーごとの「pt」文字の位置を指定する関数
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case PLAYER1:
		return PLAYER1_PT_POS;
		break;
	case PLAYER2:
		return PLAYER2_PT_POS;
		break;
	case PLAYER3:
		return PLAYER3_PT_POS;
		break;
	case PLAYER4:
		return PLAYER4_PT_POS;
		break;
	}
}

<<<<<<< HEAD

=======
>>>>>>> remotes/origin/master
//プレイヤーごとのスコアの位置を指定する関数
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

<<<<<<< HEAD

=======
>>>>>>> remotes/origin/master
//プレイヤーごとのスコアの色を指定する関数
Vector4 GameScene::ScoreColor(int c)
{
	switch (c)
	{
	case PLAYER1:
		return PLAYER1_COL_RED;
		break;
	case PLAYER2:
		return PLAYER2_COL_BLUE;
		break;
	case PLAYER3:
		return PLAYER3_COL_YELLOW;
		break;
	case PLAYER4:
		return PLAYER4_COL_GREEN;
		break;
	}
}


/*プレイヤーの得点変動処理関数
  (ｘは落としたプレイヤー、yは自滅したプレイヤー)*/
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


//１位に王冠画像と王冠モデルを渡す関数
void GameScene::NowCrown()
{
	for (int i = PLAYER1; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		for (int u = PLAYER1; u < m_titleScene->GetTotalPlaNum(); u++)
		{
			//今のプレイヤー(i)と次のプレイヤー(u)を比較
			//次のプレイヤーのほうがスコアが高いとき、
			if (m_plscore[i] < m_plscore[u])
			{
				//王冠スプライトを表示させる
				m_crownSprite->Activate();
				//王冠モデルを表示させる
				m_crownModel->SetScale(CROWN_MODEL_SCA);

				m_nowNumOnePla = u;
			}
		}
	}

	//王冠の位置を次のプレイヤーの位置に変更
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });
		//王冠モデルをそのプレイヤーの頭上に置く
		m_crownModelPos = m_player->GetPlaPos(0);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWN_POS });
		//王冠モデルをそのプレイヤーの頭上に置く
		m_crownModelPos = m_player->GetPlaPos(1);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWN_POS });
		//王冠モデルをそのプレイヤーの頭上に置く
		m_crownModelPos = m_player->GetPlaPos(2);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWN_POS });
		//王冠モデルをそのプレイヤーの頭上に置く
		m_crownModelPos = m_player->GetPlaPos(3);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
}


//リザルト画面に遷移する関数
void GameScene::ResultSceneTransition()
{

		//タイマーを加算
		m_resultsenniTimer++;
		//タイマーが120を超えてからリザルト画面に遷移
		if (m_resultsenniTimer > 120)
		{
			//リザルト画面オブジェクト生成
			NewGO<ResultScene>(PRIORITY_0, nullptr);
		}
}