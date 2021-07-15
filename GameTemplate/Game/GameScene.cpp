///<<summary>
///ゲーム画面中の処理を行うクラス
///</summary>


#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"


namespace
{
	const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//プレイヤー1の名前表示位置
	const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//プレイヤー2の名前表示位置
	const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//プレイヤー3の名前表示位置
	const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//プレイヤー4の名前表示位置

	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//制限時間フォントの位置
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//制限時間フォントの色
	const Vector4   TIMELIMIT_LAST_COL = { 1.0f,0.0f,0.0f,1.0f };	//制限時間フォントの残り5秒の色

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
	//ライトオブジェクト生成
	m_light = NewGO<Light>(PRIORITY_0, LIGHT_NAME);
	//ディレクションライトをセット
	m_light->SetDirectionLightData();
	//半球ライトをセット
	m_light->SetHemiSphereLightData();

	//フェードイン
	m_fadeIn = NewGO<Fade>(0, "fade");
	m_fadeIn->SetState(StateIn);
	m_fadeIn->SetAlphaValue(1.0f);

	//敵オブジェクト生成
	m_enemy = NewGO<Enemy>(PRIORITY_0, ENEMY_NAME);
	m_enemy->SetTotalPlaNum(m_totalPlaNum);
	m_enemy->SetStageSelectNum(m_stageSelecttNum);
	//プレイヤーオブジェクト生成
	m_player = NewGO<Player>(PRIORITY_0, PLAYER_NAME);
	m_player->SetTotalPlaNum(m_totalPlaNum);
	m_player->SetStageSelectNum(m_stageSelecttNum);
	//ステージオブジェクト生成
	m_stage = NewGO<Stage>(PRIORITY_0, STAGE_NAME);
	m_stage->SetSelectStageNum(m_stageSelecttNum);
	m_stage->SetTotalPlaNum(m_stageSelecttNum);

	//王冠画像オブジェクト生成
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//王冠画像を初期化
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);	//王冠画像
	m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });						//位置を設定
	m_crownSprite->SetScale({ CROWN_SCA });									//拡大率を設定
	m_crownSprite->Deactivate();					//はじめは誰も一位じゃないので隠しておく。


	m_pauseSprite = NewGO<SpriteRender>(PRIORITY_6, nullptr);
	//ポーズ画像を初期化
	m_pauseSprite->Init("Assets/image/DDS/Pause.dds", 600.0f, 300.0f);
	m_pauseSprite->Deactivate();

	m_grayBack = NewGO<SpriteRender>(PRIORITY_5, nullptr);
	//ポーズ中灰色にする画像を初期化
	m_grayBack->Init("Assets/image/DDS/GrayBack.dds", 1500.0f, 1500.0f);
	m_grayBack->Deactivate();

	//制限時間フォントオブジェクト生成（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	//各プレイヤーのポイント画像の位置を設定
	m_plaScorePos[0] = { -520.0f, 255.0f };
	m_plaScorePos[1] = { 450.0f, 255.0f };
	m_plaScorePos[2] = { -520.0f,-205.0f };
	m_plaScorePos[3] = { 450.0f,-205.0f };

	for (int plaNum = 0; plaNum < 4; plaNum++) {
		//プレイヤーごとのptフォントオブジェクト生成
		m_ScoreFontRender[plaNum] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//初期化
		m_ScoreFontRender[plaNum]->Init
		(
			L"pt",				//テキスト
			GetScorePos(plaNum),		//位置
			ScoreColor(plaNum),		//色
			FONT_ROT,			//傾き
			PT_SCA,				//拡大率
			FONT_PIV			//基点
		);
		//プレイヤーごとのポイントフォントオブジェクト生成
		m_TextScoreFontRender[plaNum] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//初期化
		m_TextScoreFontRender[plaNum]->Init
		(
			L"",					//テキスト
			m_plaScorePos[plaNum],		//位置
			ScoreColor(plaNum),			//色
			FONT_ROT,				//傾き
			FONT_SCA,				//拡大率
			FONT_PIV				//基点
		);


		//文字の境界線表示
		m_ScoreFontRender[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
		//文字の境界線表示
		m_TextScoreFontRender[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
	}
	//登録されていないプレイヤーのスコアはグレー表示にする
	for (int plaNum = m_totalPlaNum; plaNum < 4; plaNum++)
	{
		m_ScoreFontRender[plaNum]->SetColor(GRAY);
		m_TextScoreFontRender[plaNum]->SetColor(GRAY);
	}
	//制限時間フォントの初期化
	m_timeLimit->Init
	(
		L"",			//テキスト
		TIMELIMIT_POS,	//位置
		TIMELIMIT_COL,	//色
		FONT_ROT,		//傾き
		FONT_SCA,		//拡大率
		FONT_PIV		//基点
	);
	//文字の境界線表示
	m_timeLimit->SetShadowParam(true, 3.0f, Vector4::Black);

	m_syutyusen = NewGO<SpriteRender>(PRIORITY_0, nullptr);
	m_syutyusen->Init("Assets/image/DDS/BackScreenImage.dds", 1600.0f, 800.0f);

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++) {
		//2P～4Pの非アクティブ画像オブジェクト生成
		m_PlaNameFont[plaNum] = NewGO<FontRender>(1);		//1P
		if (plaNum == Player1)
		{
			m_PlaNameFont[plaNum]->Init(
				L"PLAYER1",					//テキスト
				PLANAME1POS,		//位置
				GRAY,		//色
				FONT_ROT,			//傾き
				1.0f,		//拡大率
				FONT_PIV			//基点
			);
		};
		//2P
		if (plaNum == Player2)
		{
			m_PlaNameFont[plaNum]->Init(
				L"PLAYER2",					//テキスト
				PLANAME2POS,		//位置
				GRAY,		//色
				FONT_ROT,			//傾き
				1.0f,		//拡大率
				FONT_PIV			//基点
			);
		}
		//3P
		if (plaNum == Player3)
		{
			m_PlaNameFont[plaNum]->Init(
				L"PLAYER3",					//テキスト
				PLANAME3POS,		//位置
				GRAY,		//色
				FONT_ROT,			//傾き
				1.0f,		//拡大率
				FONT_PIV			//基点
			);
		}
		//4P
		if (plaNum == Player4)
		{
			m_PlaNameFont[plaNum]->Init(
				L"PLAYER4",					//テキスト
				PLANAME4POS,		//位置
				GRAY,		//色
				FONT_ROT,			//傾き
				1.0f,		//拡大率
				FONT_PIV			//基点
			);
		}
		//文字の境界線表示
		m_PlaNameFont[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);

		if (m_totalPlaNum > plaNum)
		{
			if (plaNum == Player1)
			{
				m_PlaNameFont[plaNum]->SetColor(RED);
			}
			if (plaNum == Player2)
			{
				m_PlaNameFont[plaNum]->SetColor(BLUE);
			}
			if (plaNum == Player3)
			{
				m_PlaNameFont[plaNum]->SetColor(YELLOW);
			}
			if (plaNum == Player4)
			{
				m_PlaNameFont[plaNum]->SetColor(GREEN);
			}
		}
	}

	return true;
}


GameScene::~GameScene()
{
	DeleteGO(m_light);

	DeleteGO(m_fadeIn);
	if(m_fadeOut != nullptr)
	DeleteGO(m_fadeOut);

	//ステージを削除。
	DeleteGO(m_stage);

	for (int i = 0; i < 4; i++)
	{
		//カウントダウンスプライトを削除
		DeleteGO(m_sprite[i]);
		//pt文字を削除
		DeleteGO(m_ScoreFontRender[i]);
		//
		DeleteGO(m_TextScoreFontRender[i]);

		DeleteGO(m_PlaNameFont[i]);
	}
	//プレイヤークラスを削除。
	DeleteGO(m_player);
	//敵クラスを削除。
	DeleteGO(m_enemy);
	//タイムを削除
	DeleteGO(m_timeLimit);
	//王冠画像を削除
	DeleteGO(m_crownSprite);
	//ゲーム画面背景を削除
	DeleteGO(m_syutyusen);

	//サウンドを削除
	if(m_gameStartGingle != nullptr)
	DeleteGO(m_gameStartGingle);
	if (m_gameBGM != nullptr)
	DeleteGO(m_gameBGM);
	if (m_countDown != nullptr)
	DeleteGO(m_countDown);
	if (m_whistleSound != nullptr)
	DeleteGO(m_whistleSound);
	if(m_pauseSound != nullptr)
	DeleteGO(m_pauseSound);
	if (m_decideSound != nullptr)
		DeleteGO(m_decideSound);

	DeleteGO(m_resultScene);

	DeleteGO(m_pauseSprite);
	DeleteGO(m_grayBack);
}


void GameScene::Update()
{
	//ポーズ中でないとき、
	if (!m_isPauseFlg)
	{
		//制限時間のカウント&描画処理
		TimeLimit();
		m_stage->SetNowTime(m_countTime);

		//プレイヤーのスコア描画関数
		PlaScoreDraw();

		//現在のスコア１位を判定し、王冠画像を移動
		NowCrown();

		//制限時間が0秒になったら、
		if (m_countTime == 0)
		{
			//リザルト画面に遷移する
			ResultSceneTransition();
		}

		//ゲームシーンに遷移したら、
		if (m_isFinishCountDownFlg)
		{
			//カウントダウン処理を開始
			CountDown();
		}

		//リザルトシーンクラスが削除されたら同じくゲームシーンも削除する
		if (m_deleteFlg)
		{
			DeleteGO(this);
		}
	}
	//ポーズ機能
	for (int i = 0; i < m_totalPlaNum; i++)
	{
		//セレクトボタンでオンオフ
		if (g_pad[i]->IsTrigger(enButtonSelect))
		{
			//ポーズ画面を開く音
			SoundPlayBack(PauseSound);

			//ポーズ中じゃないとき、
			if (!m_isPauseFlg)
			{
				//ポーズにする
				m_pauseSprite->Activate();
				m_grayBack->Activate();
				if (m_gameBGM != nullptr)
				{
					m_gameBGM->SetVolume(0.0f);
				}

				m_isPauseFlg = true;
			}
			//ポーズ中の時、
			else
			{
				m_pauseSprite->Deactivate();
				m_grayBack->Deactivate();
				if (m_gameBGM != nullptr)
				{
					m_gameBGM->SetVolume(0.5f);
				}

				//ポーズを外す
				m_isPauseFlg = false;
			}
			m_player->SetPauseFlg(m_isPauseFlg);
			m_enemy->SetPauseFlg(m_isPauseFlg);
			m_stage->SetPauseFlg(m_isPauseFlg);
		}
	}

	if (m_fadeOut == nullptr && m_isPauseFlg)
	{
		//ステージ選択画面に戻る
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//スタートボタンが押されたら、
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//決定サウンド
				SoundPlayBack(DecideSound);
				//フェードアウト
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);

			}
		}
	}

	if (m_fadeOut != nullptr && m_fadeOut->GetNowState() == StateWait)
	{
		//ステージ選択画面に戻る
		m_stageSelectScene = NewGO<StageSelectScene>(0, STAGESELECT_NAME);
		m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);

		DeleteGO(this);
	}
}


//カウントダウン処理関数
void GameScene::CountDown()
{
	//スタートまでのカウントダウンを開始

	switch (m_countDownTimer) {
	//カウントダウンタイマーが0のとき、
	case 0:

		//ゲームスタートジングルサウンド
		SoundPlayBack(GameStartGingle);

		break;

	case 300:
		//カウントダウンサウンド
		SoundPlayBack(CountDownSound);

		//「３」画像オブジェクト生成
		m_sprite[ARRAY_NUM_0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_0]->SetPosition(Vector3::Zero);
		//初期化
		m_sprite[ARRAY_NUM_0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

		break;

	//カウントダウンタイマーが60のとき、
	case 360:
		//「3」削除。
		DeleteGO(m_sprite[ARRAY_NUM_0]);

		//「２」画像オブジェクト生成
		m_sprite[ARRAY_NUM_1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_1]->SetPosition(Vector3::Zero);
		//初期化
		m_sprite[ARRAY_NUM_1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);

		break;

	//カウントダウンタイマーが120のとき、
	case 420:
		//「2」削除。
		DeleteGO(m_sprite[ARRAY_NUM_1]);

		//「１」画像オブジェクト生成
		m_sprite[ARRAY_NUM_2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_2]->SetPosition(Vector3::Zero);
		//初期化
		m_sprite[ARRAY_NUM_2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);

		break;

		//カウントダウンタイマーが180のとき、
	case 480:
		//「1」削除。
		DeleteGO(m_sprite[ARRAY_NUM_2]);

		//「START」画像オブジェクト生成
		m_sprite[ARRAY_NUM_3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_3]->SetPosition(Vector3::Zero);
		//初期化
		m_sprite[ARRAY_NUM_3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);

		break;

		//カウントダウンタイマーが300のとき、
		//「START」表示は特別少し長くする
	case 600:
		//「START」削除。
		DeleteGO(m_sprite[ARRAY_NUM_3]);

		//ゲーム中のBGMサウンド
		SoundPlayBack(GameBGM);

		//カウントダウンの処理を抜ける。
		m_isFinishCountDownFlg = false;

		break;
	}
	//カウントダウンのタイマーを加算
	m_countDownTimer++;
}


//制限時間処理関数
void GameScene::TimeLimit()
{
	//カウントダウンが終わってから制限時間を刻んでいく。
	if(!m_isFinishCountDownFlg)
	{
		//制限時間を縮めていく。
		m_timer--;
	}

	m_countTime = m_timer / 60;

	//０秒になってからのカウントがマイナスに行かないように補正
	m_countTime = max(0,m_countTime);

	//10秒以下のとき、制限時間を赤く表示
	if(m_countTime <= 10)
	{
		m_timeLimit->SetColor(TIMELIMIT_LAST_COL);
	}

	//制限時間の描画
	swprintf_s(text1, L"%d", m_countTime);
	//画面表示
	m_timeLimit->SetText(text1);
}


//プレイヤーのスコア描画関数
void GameScene::PlaScoreDraw()
{
	for (int plaNum = 0; plaNum < 4; plaNum++) {

		//表示位置更新
		SetScoreTextPos(plaNum);

		//プレイヤーごとのスコアの描画
		swprintf_s(text2, L"%d", m_plaScore[plaNum]);
		m_TextScoreFontRender[plaNum]->SetText(text2);
	}
}


//プレイヤーごとの「pt」文字の位置を指定する関数
Vector2 GameScene::GetScorePos(int plaNum)
{
	switch (plaNum)
	{
	case Player1:
		return PLAYER1_PT_POS;
		break;
	case Player2:
		return PLAYER2_PT_POS;
		break;
	case Player3:
		return PLAYER3_PT_POS;
		break;
	case Player4:
		return PLAYER4_PT_POS;
		break;
	}
}


//プレイヤーごとのスコアの位置を指定する関数
void GameScene::SetScoreTextPos(int plaNum)
{
	//スコアが1桁のとき、
	m_plaScorePos[0] = { -520.0f, 255.0f };
	m_plaScorePos[1] = { 450.0f, 255.0f };
	m_plaScorePos[2] = { -520.0f,-205.0f };
	m_plaScorePos[3] = { 450.0f,-205.0f };

	//スコアが2桁のとき、
	if (10 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 100)
	{
		//少し左(xを-40)にずらして表示位置を合わせる
		switch (plaNum)
		{
		case Player1:
			m_plaScorePos[0].x = -560.0f;
			break;
		case Player2:
			m_plaScorePos[1].x = 410.0f;
			break;
		case Player3:
			m_plaScorePos[2].x = -560.0f;
			break;
		case Player4:
			m_plaScorePos[3].x = 410.0f;
			break;
		}
	}
	//スコアが3桁のとき、
	if (100 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 1000)
	{
		//少し左(xを-20)にずらして表示位置を合わせる
		switch (plaNum)
		{
		case Player1:
			m_plaScorePos[0].x = -580.0f;
			break;
		case Player2:
			m_plaScorePos[1].x = 390.0f;
			break;
		case Player3:
			m_plaScorePos[2].x = -580.0f;
			break;
		case Player4:
			m_plaScorePos[3].x = 390.0f;
			break;
		}
	}
	//スコアが4桁のとき、
	if (1000 <= m_plaScore[plaNum])
	{
		//少し左(xを-20)にずらして表示位置を合わせる
		switch (plaNum)
		{
		case Player1:
			m_plaScorePos[0].x = -600.0f;
			break;
		case Player2:
			m_plaScorePos[1].x = 370.0f;
			break;
		case Player3:
			m_plaScorePos[2].x = -600.0f;
			break;
		case Player4:
			m_plaScorePos[3].x = 370.0f;
			break;
		}
	}

	//位置をセット
	m_TextScoreFontRender[plaNum]->SetPosition(m_plaScorePos[plaNum]);
}


//プレイヤーごとのスコアの色を指定する関数
Vector4 GameScene::ScoreColor(int plaNum)
{
	switch (plaNum)
	{
	case Player1:
		return RED;
		break;
	case Player2:
		return BLUE;
		break;
	case Player3:
		return YELLOW;
		break;
	case Player4:
		return GREEN;
		break;
	}
}


/*プレイヤーの得点変動処理関数
  (plaNum1は落としたプレイヤー、plaNum2は落とされたプレイヤー)*/
void GameScene::GetPlayerAddScore(int plaNum1,int plaNum2)
{
	//4のとき何もしない
	if (plaNum1 == 4)
	{
		return;
	}
	//落としたとき、
	//30pt増加
	m_plaScore[plaNum1] += 30;
	//もし落としたプレイヤーが1位だったら、
	if (plaNum2 == m_nowNumOnePla)
	{
		//落とされた１位はマイナス20pt。落としたプレイヤーはプラスで20pt
		//これを入れることで１位が狙われやすい仕様にしている。
		m_plaScore[plaNum2] -= 20;
		m_plaScore[plaNum1] += 20;
		//点数が0以下にならないように補正
		if (m_plaScore[plaNum2] < 0)
		{
			m_plaScore[plaNum2] = 0;
		}
	}
	//敵を落としたとき、
	if (plaNum2 == 5)
	{
		//敵を落としたときptを10ptだけ取るように調整
		//すでに+30ptしているからマイナス20している。
		m_plaScore[plaNum1] -= 20;
	}
}


//１位に王冠画像と王冠モデルを渡す関数
void GameScene::NowCrown()
{
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		for (int nextPlaNum = Player1; nextPlaNum < m_totalPlaNum; nextPlaNum++)
		{
			//今のプレイヤー(i)と次のプレイヤー(u)を比較
			//次のプレイヤーのほうがスコアが高いとき、
			if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
			{
				//王冠スプライトを表示させる
				m_crownSprite->Activate();

				m_nowNumOnePla = nextPlaNum;
			}
		}
	}

	//王冠の位置を次のプレイヤーの位置に変更
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWN_POS });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWN_POS });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWN_POS });
	}
}


//リザルト画面に遷移する関数
void GameScene::ResultSceneTransition()
{
	//タイマーを加算
	m_resultsenniTimer++;

	if (m_resultsenniTimer == 1)
	{
		//ホイッスルサウンド
		SoundPlayBack(WhistleSound);

		m_pauseOkFlg = false;
	}
	//タイマーが120を超えてからリザルト画面に遷移
	if (m_resultsenniTimer == 180)
	{
		//リザルト画面オブジェクト生成
		m_resultScene = NewGO<ResultScene>(PRIORITY_0, nullptr);
		m_resultScene->SetTotalPlayerNum(m_totalPlaNum);
		m_grayBack->Activate();
		//ゲームBGMをけす
		m_gameBGM->SetVolume(0.0f);
	}
}


//サウンドを一括にまとめる関数
void GameScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case GameStartGingle:
		//ゲームスタートジングルサウンドの初期化
		m_gameStartGingle = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameStartGingle->Init(L"Assets/sound/GameStartGingle.wav");
		m_gameStartGingle->SetVolume(1.0f);
		m_gameStartGingle->Play(false);	//偽でワンショット再生

		break;

	case CountDownSound:
		//カウントダウンサウンドの初期化
		m_countDown = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_countDown->Init(L"Assets/sound/CountDown.wav");
		m_countDown->SetVolume(1.0f);
		m_countDown->Play(false);	//真でワンショット再生

		break;

	case GameBGM:
		//ゲーム中のBGMサウンドの初期化
		m_gameBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameBGM->Init(L"Assets/sound/GameBGM.wav");
		m_gameBGM->SetVolume(0.5f);
		m_gameBGM->Play(true);	//真でループ再生

		break;

	case WhistleSound:
		//ホイッスルサウンドの初期化
		m_whistleSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_whistleSound->Init(L"Assets/sound/Whistle.wav");
		m_whistleSound->SetVolume(0.5f);
		m_whistleSound->Play(false);	//偽でワンショット再生

		break;

	case PauseSound:
		//ポーズサウンドの初期化
		m_pauseSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_pauseSound->Init(L"Assets/sound/PauseSound.wav");
		m_pauseSound->SetVolume(0.5f);
		m_pauseSound->Play(false);	//偽でワンショット再生

		break;

	case DecideSound:
		//決定サウンド
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//偽でワンショット再生

		break;
	}
}