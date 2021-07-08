/// <summary>
/// タイトル画面クラス
/// (注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！)
/// </summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"


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
	const Vector3 PressASpeechBalloonPos3 = { -300.0f,-315,0 };
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
	//タイトル名ジングルサウンド
	SoundPlayBack(TitleSceneGingle);

	//タイトルBGMサウンド
	SoundPlayBack(TitleSceneBGM);

	//タイトルロゴオブジェクト生成
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 1600.0f, 800.0f);

	//PUSH START BUTTONオブジェクト生成
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ FlashingFont_SCA });

	//PRESS A !! 吹き出し画像オブジェクト生成
	for (int speechBalloonNum = 0; speechBalloonNum < 3; speechBalloonNum++)
	{
		m_pressASpeechBalloon[speechBalloonNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//PLAYER３のみ吹き出しの左側にいるので他とは違う吹き出しを使う
		if (speechBalloonNum == 1)
		{
			m_pressASpeechBalloon[speechBalloonNum]->Init("Assets/image/DDS/PRESS A !!_L.dds", 400.0f, 200.0f);
		}
		else
		{
			m_pressASpeechBalloon[speechBalloonNum]->Init("Assets/image/DDS/PRESS A !!_R.dds", 400.0f, 200.0f);
		}
		//PLAYER2以外は初期は非アクティブ
		if (speechBalloonNum != 0)
		{
			m_pressASpeechBalloon[speechBalloonNum]->Deactivate();
		}
		//位置設定
		switch (speechBalloonNum)
		{
		//2Pの左側
		case 0:
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos = PressASpeechBalloonPos2;
			break;
		//3Pの右側
		case 1:
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos = PressASpeechBalloonPos3;
			break;
		//4Pの左側
		case 2:
			//4Pの名前画像の位置を代入
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos = PressASpeechBalloonPos4;
			break;
		}
		//大きさ調整
		m_pressASpeechBalloon[speechBalloonNum]->SetScale({0.5f,0.5f,0.5f});

		//位置設定
		m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
	}

	////1Pは非アクティブときがないため、初めからアクティブ画像オブジェクト生成
	//m_plaActiveName[Player1] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
	//m_plaActiveName[Player1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 300.0f, 150.0f);
	//m_plaActiveName[Player1]->SetPosition(PLAYER1_NAME_POS);

	//１Pの追加フラグを真に。
	m_isAddPlayerFlg[Player1] = true;

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++) {
		//2P～4Pの非アクティブ画像オブジェクト生成
		m_plaDeactiveName[plaNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		m_PlaNameFont[plaNum] = NewGO<FontRender>(1);		//1P
		if (plaNum == Player1)
		{
			m_PlaNameFont[0]->Init(
				/*m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 300.0f, 150.0f);
				m_plaDeactiveName[i]->SetPosition(PLAYER1_NAME_POS);
				//非アクティブ時はないため、非表示にしておく。
				m_plaDeactiveName[i]->Deactivate();*/

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
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER2_NAME_POS);

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
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER3_NAME_POS);

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
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER4_NAME_POS);

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
		m_PlaNameFont[plaNum]->SetShadowParam(true, 2.0f, Vector4::Black);
	}

	//Start関数のreturn文
	return true;
}


TitleScene::~TitleScene()
{
	//登録されたプレイヤーのアクティブ画像を削除
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		DeleteGO(m_plaActiveName[plaNum]);
	}
	//登録されていないプレイヤーの非アクティブ画像を削除
	for (int plaNum = m_totalPlaNum; plaNum < (MaxPlayerNum+1); plaNum++)
	{
		//4Pまで登録されていたらm_plaDeactiveName[4]と、
		//添え字がオーバーしてしまうのでここでfor文を抜けさせる
		if (m_totalPlaNum == MaxPlayerNum)
		{
			break;
		}
		//緑の波線は大丈夫です
		//DeleteGO(m_plaDeactiveName[i]);
	}
}


void TitleScene::Update()
{
	//ステージ選択画面に遷移すると抜けるフラグ
	if (m_enableUpdateFlg == true) {

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

		//登録されている誰かのスタートボタンが押されたら、
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//スタートボタンが押されたら、
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//決定サウンド
				SoundPlayBack(DecideSound);

				//ステージ選択画面に遷移
				StageSelectSceneTransition();
			}
			//セレクトボタンが押されたら、、
			if (g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				//exeを閉じてゲーム終了
				exit(EXIT_SUCCESS);
				//メモ//
				//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
				//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
			}
		}
		//「PRESS START BUTTON」文字画像の点滅処理
		FlashingFont();
	}
}


//プレイヤーを追加する関数
void TitleScene::AddPlayer()
{
	//エンジンサウンド
	SoundPlayBack(EngineSound);

	//新規プレイヤーの追加フラグを真に。
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	//プレイヤーのアクティブ画像オブジェクト生成（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_plaActiveName[m_totalPlaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//2Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player2)
	{
		m_PlaNameFont[1]->SetColor(PLANAME2COL);

		//2Pの吹き出しを非表示
		m_pressASpeechBalloon[0]->Deactivate();
		//吹き出しを3Pの位置に表示
		m_pressASpeechBalloon[1]->Activate();
	}
	//3Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player3)
	{
		m_PlaNameFont[2]->SetColor(PLANAME3COL);

		//3Pの吹き出しを非表示
		m_pressASpeechBalloon[1]->Deactivate();
		//吹き出しを4Pの位置に表示
		m_pressASpeechBalloon[2]->Activate();
	}
	//4Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == Player4)
	{
		m_PlaNameFont[3]->SetColor(PLANAME4COL);

		//4Pの吹き出しを非表示
		m_pressASpeechBalloon[2]->Deactivate();
	}
	//非アクティブ画像を削除。
	DeleteGO(m_plaDeactiveName[m_totalPlaNum]);
	//次のプレイヤーへ...
	m_totalPlaNum++;
}


//ステージ選択画面に遷移する関数
void TitleScene::StageSelectSceneTransition()
{
	//ステージ選択画面に遷移
	m_stageSelectScene = NewGO<StageSelectScene>(PRIORITY_0, STAGESELECT_NAME);
	////このクラスの削除
	////DeleteGO(this);

	//タイトルロゴを削除。
	DeleteGO(m_titleSprite);
	//PUSHSTARTBUTTONを削除。
	DeleteGO(m_pushStartButtonSprite);
	//吹き出しを削除。
	for (int speechBalloonNum = 0; speechBalloonNum < 3; speechBalloonNum++)
	{
		DeleteGO(m_pressASpeechBalloon[speechBalloonNum]);
	}
	//タイトルBGMを削除
	DeleteGO(m_titleBGM);
	//エンジン音を削除
	DeleteGO(m_addPlayer);
	//タイトルジングルを削除
	DeleteGO(m_gameNameGingle);

	//ステージ選択画面に遷移後、ボタンとプレイヤー追加ボタンを押せなくするフラグ
	m_enableUpdateFlg = false;
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