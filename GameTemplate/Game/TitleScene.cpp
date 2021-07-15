/// <summary>
/// タイトル画面クラス
/// (注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！)
/// </summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"


namespace
{
	const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//プレイヤー1の名前表示位置
	const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//プレイヤー2の名前表示位置
	const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//プレイヤー3の名前表示位置
	const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//プレイヤー4の名前表示位置

	const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//点滅文字の表示位置
	const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//点滅文字の大きさ

	const Vector3 PLAYER2_NAME_POS;
	const Vector3 PLAYER3_NAME_POS;
	const Vector3 PLAYER4_NAME_POS;

	const Vector3 PressASpeechBalloonPos2 = { 300.0f,280.0f,0 };
	const Vector3 PressASpeechBalloonPos3 = { -270.0f,-315,0 };
	const Vector3 PressASpeechBalloonPos4 = { 300.0f,-315.0f,0 };

	const Vector4 PLANAME1COL = { 1.0f,0.0f,0.0f,1.0f };		//プレイヤー1の表示は常にあるので赤て固定
	const Vector4 PLANAME234COL = { 0.7f,0.7f,0.7f,1.0f };	//プレイヤー2からはアクティブする前は灰色

	const float PLA1234_SCA = { 1.0f, };					//拡大率

	const Vector4 PLANAME2COL = { 0.0f,0.0f,1.0f,1.0f };			//アクティブ時、青
	const Vector4 PLANAME3COL = { 1.0f,1.0f,0.0f,1.0f };			//アクティブ時、黄色
	const Vector4 PLANAME4COL = { 0.0f,1.0f,0.0f,1.0f };			//アクティブ時、緑


	const float     FONT_ROT = 0.0f;			//フォントの傾き
	const Vector2   FONT_PIV = { 1.0f,1.0f };	//フォントの基点
	const float     FONT_SCA = 1.4f;			//フォントの拡大率

	const float PLA_SCA = 0.85f;
}


bool TitleScene::Start()
{
	//フェードイン
	m_fadeIn = NewGO<Fade>(0, "fade");
	m_fadeIn->SetState(StateIn);
	m_fadeIn->SetAlphaValue(1.0f);

	//タイトル名ジングルサウンド
	SoundPlayBack(TitleSceneGingle);

	//タイトルBGMサウンド
	SoundPlayBack(TitleSceneBGM);

	//タイトルロゴオブジェクト生成
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 1600.0f, 800.0f);
	//タイトル名オブジェクト生成
	m_titleNameSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_titleNameSprite->Init("Assets/image/DDS/TitleName.dds", 1600.0f, 800.0f);
	m_titleNameSca.x = 0.0f;
	m_titleNameSprite->SetScale(m_titleNameSca);
	for (int i = 0; i < 9; i++)
	{
		m_titleBaraBaraSprite[i] = NewGO<SpriteRender>(PRIORITY_0, nullptr);
		switch (i)
		{
		case 0:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_1.dds", 1600.0f, 800.0f);
			break;
		case 1:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_2.dds", 1600.0f, 800.0f);
			break;
		case 2:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_3.dds", 1600.0f, 800.0f);
			break;
		case 3:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_4.dds", 1600.0f, 800.0f);
			break;
		case 4:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_5.dds", 1600.0f, 800.0f);
			break;
		case 5:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_6.dds", 1600.0f, 800.0f);
			break;
		case 6:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_7.dds", 1600.0f, 800.0f);
			break;
		case 7:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_8.dds", 1600.0f, 800.0f);
			break;
		case 8:
			m_titleBaraBaraSprite[i]->Init("Assets/image/DDS/TitleName_9.dds", 1600.0f, 800.0f);
			break;
		}
		//初めは非表示
		m_titleBaraBaraSprite[i]->Deactivate();
	}

	//PUSH START BUTTONオブジェクト生成
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ FlashingFont_SCA });

	//PRESS A !! 吹き出し画像オブジェクト生成
	m_pressASpeechBalloon = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pressASpeechBalloonArrow = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pressASpeechBalloon->Init("Assets/image/DDS/PRESS A !!.dds", 400.0f, 200.0f);
	m_pressASpeechBalloonArrow->Init("Assets/image/DDS/PRESS A !!Arrow.dds", 200.0f, 100.0f);
	//初期位置設定
	//2Pの左側
	m_pressASpeechBalloonPos = PressASpeechBalloonPos2;
	m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
	m_pressASpeechBalloonPos.x += 75.0f;
	m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);

	//大きさ調整
	m_pressASpeechBalloon->SetScale({0.5f,0.5f,0.5f});

	//１Pの追加フラグを真に。
	m_isAddPlayerFlg[Player1] = true;

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++) {
		//2P～4Pの非アクティブ画像オブジェクト生成
		m_PlaNameFont[plaNum] = NewGO<FontRender>(1);		//1P
		if (plaNum == Player1)
		{
			m_PlaNameFont[0]->Init(
				L"PLAYER1",					//テキスト
				PLANAME1POS,		//位置
				PLANAME1COL,		//色
				FONT_ROT,			//傾き
				PLA1234_SCA,		//拡大率
				FONT_PIV			//基点
			);
		};
		//2P
		if (plaNum == Player2)
		{
			m_PlaNameFont[1]->Init(
				L"PLAYER2",					//テキスト
				PLANAME2POS,		//位置
				PLANAME234COL,		//色
				FONT_ROT,			//傾き
				PLA1234_SCA,		//拡大率
				FONT_PIV			//基点
			);
		}
		//3P
		if (plaNum == Player3)
		{
			m_PlaNameFont[2]->Init(
				L"PLAYER3",					//テキスト
				PLANAME3POS,		//位置
				PLANAME234COL,		//色
				FONT_ROT,			//傾き
				PLA1234_SCA,		//拡大率
				FONT_PIV			//基点
			);
		}
		//4P
		if (plaNum == Player4)
		{
			m_PlaNameFont[3]->Init(
				L"PLAYER4",					//テキスト
				PLANAME4POS,		//位置
				PLANAME234COL,		//色
				FONT_ROT,			//傾き
				PLA1234_SCA,		//拡大率
				FONT_PIV			//基点
			);
		}
		//文字の境界線表示
		m_PlaNameFont[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
	}

	return true;
}


TitleScene::~TitleScene()
{
	//タイトルロゴを削除。
	DeleteGO(m_titleSprite);
	DeleteGO(m_titleNameSprite);
	for (int i = 0; i < 9; i++)
	{
		DeleteGO(m_titleBaraBaraSprite[i]);
	}
	//PUSHSTARTBUTTONを削除。
	DeleteGO(m_pushStartButtonSprite);
	//吹き出しを削除。
	DeleteGO(m_pressASpeechBalloon);
	DeleteGO(m_pressASpeechBalloonArrow);

	//サウンドを削除
	if(m_titleBGM != nullptr)
	//タイトルBGMを削除
	DeleteGO(m_titleBGM);
	if (m_addPlayer != nullptr)
	//エンジン音を削除
	DeleteGO(m_addPlayer);
	if (m_gameNameGingle != nullptr)
	//タイトルジングルを削除
	DeleteGO(m_gameNameGingle);
	if (m_decideSound != nullptr)
	DeleteGO(m_decideSound);

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++) {
		DeleteGO(m_PlaNameFont[plaNum]);
	}

	DeleteGO(m_fadeOut);
	DeleteGO(m_fadeIn);
}


void TitleScene::Update()
{
	//「PRESS START BUTTON」文字画像の点滅処理
	FlashingFont();
	//吹き出しの矢印画像が横移動する関数
	SideMove(60, 0.2f);

	if (m_titleNameSca.x != 1.0f)
	{
		//タイトル名を拡大する関数
		TitleNameScaUp();
	}
	else
	{
		//タイトル名をウェーブさせる関数
		TitleNameWave();
	}

	//登録されたプレイヤー数が最大数4人になるまで追加できる
	if (m_totalPlaNum != MaxPlayerNum)
	{
		/*登録されていないコントローラーのAボタンが押されたら、
		【注意】USBポートに繋がれた順じゃないと登録されていきません。*/
		if (g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
		{
			//プレイヤーを登録する
			AddPlayer();
		}
	}

	if (m_fadeOut == nullptr)
	{
		//登録されている誰かのスタートボタンが押されたら、
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

				m_nextScene = StateSelectScene;
			}
			//セレクトボタンが押されたら、、
			if (g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				//フェードアウト
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);

				m_nextScene = GameEnd;
			}
		}
	}
	else
	{
		//真っ白になったら遷移
		if (m_fadeOut->GetNowState() == StateWait) {

			if (m_nextScene == StateSelectScene)
			{
				//ステージ選択画面に遷移
				StageSelectSceneTransition();
			}
			if (m_nextScene == GameEnd)
			{
				//exeを閉じてゲーム終了
				exit(EXIT_SUCCESS);
				//メモ//
				//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
				//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
			}
		}
	}
}


//プレイヤーを追加する関数
void TitleScene::AddPlayer()
{
	//エンジンサウンド
	SoundPlayBack(EngineSound);

	//新規プレイヤーの追加フラグを真に。
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	//2Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player2)
	{
		m_PlaNameFont[1]->SetColor(PLANAME2COL);

		//3Pの右側
		m_pressASpeechBalloonPos = PressASpeechBalloonPos3;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x -= 105.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);

		//反転させる
		m_arrowSca = { -1.0f,-1.0f,-1.0f };
		m_pressASpeechBalloonArrow->SetScale(m_arrowSca);
	}
	//3Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player3)
	{
		m_PlaNameFont[2]->SetColor(PLANAME3COL);

		//4Pの左側
		m_pressASpeechBalloonPos = PressASpeechBalloonPos4;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x += 80.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);

		//元に戻す
		m_pressASpeechBalloonArrow->SetScale(Vector3::One);
	}
	//4Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player4)
	{
		m_PlaNameFont[3]->SetColor(PLANAME4COL);

		//非表示
		m_pressASpeechBalloon->Deactivate();
		m_pressASpeechBalloonArrow->Deactivate();
	}
	//次のプレイヤーへ...
	m_totalPlaNum++;
}


//ステージ選択画面に遷移する関数
void TitleScene::StageSelectSceneTransition()
{
	//ステージ選択画面に遷移
	m_stageSelectScene = NewGO<StageSelectScene>(PRIORITY_0, STAGESELECT_NAME);
	//登録された人数データを次のクラスに渡す
	m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);
	//このクラスの削除
	DeleteGO(this);
}


//「PRESS START BUTTON」文字画像の点滅処理関数
void TitleScene::FlashingFont()
{
	if (m_isFlashingFontActiveFlg)
	{
		//タイマー加算
		m_flashingFontTimer++;
		//「PRESS START BUTTON」表示
		m_pushStartButtonSprite->Activate();
	}
	else
	{
		//タイマー減算
		m_flashingFontTimer--;
		//「PRESS START BUTTON」非表示
		m_pushStartButtonSprite->Deactivate();
	}
	//タイマーが60より大きい値になると、
	if (m_flashingFontTimer > 60)
	{
		//「PRESS START BUTTON」を非表示にするフラグ
		m_isFlashingFontActiveFlg = false;
	}
	//タイマーが0より小さい値になると、
	if (m_flashingFontTimer < 10)
	{
		//「PRESS START BUTTON」を表示するフラグ
		m_isFlashingFontActiveFlg = true;
	}
}


//画像が横移動する関数
void TitleScene::SideMove(int width,float speed)
{
	if (m_sideMoveTimer < width)
	{
		m_pressASpeechBalloonPos.x += speed;
	}
	else if(m_sideMoveTimer < width*2)
	{
		m_pressASpeechBalloonPos.x -= speed;
	}
	else
	{
		//初期化
		m_sideMoveTimer = 0;
	}

	m_sideMoveTimer++;

	m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
}


//画像が縦移動する関数
void TitleScene::VerticalMove(int width, float speed,int spriteNum)
{
	if (m_verticalMoveTimer[spriteNum] < width)
	{
		m_titleBaraBaraSpritePos[spriteNum].y += speed;
	}
	else if (m_verticalMoveTimer[spriteNum] < (width * 2))
	{
		m_titleBaraBaraSpritePos[spriteNum].y -= speed;
	}
	else if(m_verticalMoveTimer[spriteNum] > (width * 2))
	{
		//初期化
		m_verticalMoveTimer[spriteNum] = 100;
		m_titleBaraBaraSprite[spriteNum]->SetPosition(Vector3::Zero);
	}

	m_verticalMoveTimer[spriteNum]++;

	m_titleBaraBaraSprite[spriteNum]->SetPosition(m_titleBaraBaraSpritePos[spriteNum]);
}


//タイトル名を拡大する関数
void TitleScene::TitleNameScaUp()
{
	if (m_titleNameSca.x < 1.0f)
	{
		m_scaUpValue += 0.001;
		if (m_titleNameSca.x > 0.5f)
		{
			m_scaUpValue += 0.005;
		}
		m_titleNameSca.x += m_scaUpValue;

		//1.0fで終わるように補正
		if (m_titleNameSca.x > 1.0f)
		{
			m_titleNameSca.x = 1.0f;
		}

		m_titleNameSprite->SetScale(m_titleNameSca);

		if (m_titleNameSca.x == 1.0f)
		{
			//タイトル拡大用のタイトル名画像を削除。
			DeleteGO(m_titleNameSprite);
		}
	}
}


//タイトル名をウェーブさせる関数
void TitleScene::TitleNameWave()
{
	for (int i = 0; i < 9; i++)
	{
		//表示
		m_titleBaraBaraSprite[i]->Activate();
	}

	if (m_waveTimer < 30)
	{
		VerticalMove(10, 4.0f, 0);
	}
	if (5 < m_waveTimer && m_waveTimer < 35)
	{
		VerticalMove(10, 4.0f, 1);
	}
	if (15 < m_waveTimer && m_waveTimer < 45)
	{
		VerticalMove(10, 4.0f, 2);
	}
	if (25 < m_waveTimer && m_waveTimer < 55)
	{
		VerticalMove(10, 4.0f, 3);
	}
	if (35 < m_waveTimer && m_waveTimer < 65)
	{
		VerticalMove(10, 4.0f, 4);
	}
	if (45 < m_waveTimer && m_waveTimer < 75)
	{
		VerticalMove(10, 4.0f, 5);
	}
	if (55 < m_waveTimer && m_waveTimer < 85)
	{
		VerticalMove(10, 4.0f, 6);
	}
	if (65 < m_waveTimer && m_waveTimer < 95)
	{
		VerticalMove(10, 4.0f, 7);
	}
	if (75 < m_waveTimer && m_waveTimer < 105)
	{
		VerticalMove(10, 4.0f, 8);
	}

	//タイマーを初期化
	if (m_waveTimer > 170)
	{
		for (int spriteNum = 0; spriteNum < 9; spriteNum++)
		{
			//初期化
			m_verticalMoveTimer[spriteNum] = 0;
		}
		m_waveTimer = 0;
	}

	m_waveTimer++;
}


//サウンドを一括にまとめる関数
void TitleScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case TitleSceneGingle:
		//タイトル名ジングルサウンドの初期化
		m_gameNameGingle = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameNameGingle->Init(L"Assets/sound/TitleSceneGingle.wav");
		m_gameNameGingle->SetVolume(0.5f);
		m_gameNameGingle->Play(false);	//偽でワンショット再生

		break;

	case TitleSceneBGM:
		//タイトルBGMサウンドの初期化
		m_titleBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_titleBGM->Init(L"Assets/sound/TitleSceneBGM.wav");
		m_titleBGM->SetVolume(0.01f);
		m_titleBGM->Play(true);	//真でループ再生

		break;

	case DecideSound:
		//決定サウンド
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//偽でワンショット再生

		break;

	case EngineSound:

		//エンジンサウンド
		m_addPlayer = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_addPlayer->Init(L"Assets/sound/AddPlayer.wav");
		m_addPlayer->SetVolume(0.5f);
		m_addPlayer->Play(false);	//偽でワンショット再生

		break;
	}
}