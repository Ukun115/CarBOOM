#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


/// <summary>
/// 注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！
/// </summary>


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
	const int PRIORITY_1 = 1;	//優先度1

	const Vector3 TITLE_POS = { 0.0f, 0.0f,0.0f };	//タイトルの表示位置

	const Vector3 PLAYER1_NAME_POS = {-480.0f, 310.0f,0.0f};			//プレイヤー1の名前表示位置
	const Vector3 PLAYER2_NAME_POS = { 480.0f, 310.0f,0.0f};			//プレイヤー2の名前表示位置
	const Vector3 PLAYER3_NAME_POS = {-480.0f,-310.0f,0.0f};			//プレイヤー3の名前表示位置
	const Vector3 PLAYER4_NAME_POS = { 480.0f,-310.0f,0.0f};			//プレイヤー4の名前表示位置

	const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//点滅文字の表示位置
	const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//点滅文字の大きさ
}


bool TitleScene::Start()
{
	//タイトルロゴオブジェクト生成
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 1600.0f, 800.0f);
	m_titleSprite->SetPosition({ TITLE_POS });

	//PUSH START BUTTONオブジェクト生成
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ FlashingFont_SCA });

	//1Pは無条件で追加フラグを真に。
	m_isAddPlayerFlg[PLAYER1] = true;
	//1Pは非アクティブときがないため、初めからアクティブ画像オブジェクト生成
	m_plaActiveName[PLAYER1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_plaActiveName[PLAYER1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 300.0f, 150.0f);
	m_plaActiveName[PLAYER1]->SetPosition(PLAYER1_NAME_POS);

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++) {
		//2P～4Pの非アクティブ画像オブジェクト生成
		m_plaDeactiveName[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//1P
		if (i == PLAYER1)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER1_NAME_POS);
			//非アクティブ時はないため、非表示にしておく。
			m_plaDeactiveName[i]->Deactivate();
		}
		//2P
		if (i == PLAYER2)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER2_NAME_POS);
		}
		//3P
		if (i == PLAYER3)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER3_NAME_POS);
		}
		//4P
		if (i == PLAYER4)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER4_NAME_POS);
		}
	}

	//Start関数のreturn文
	return true;
}


TitleScene::~TitleScene()
{
	//登録されたプレイヤーのアクティブ画像を削除
	for (int i = PLAYER1; i < m_totalPlaNum; i++)
	{
		DeleteGO(m_plaActiveName[i]);
	}
	//登録されていないプレイヤーの非アクティブ画像を削除
	for (int i = m_totalPlaNum; i < (MAXPLAYERNUM+1); i++)
	{
		//4Pまで登録されていたらm_plaDeactiveName[4]と、
		//添え字がオーバーしてしまうのでここでfor文を抜けさせる
		if (m_totalPlaNum == MAXPLAYERNUM)
		{
			break;
		}
		//緑の波線は大丈夫です
		DeleteGO(m_plaDeactiveName[i]);
	}
}


void TitleScene::Update()
{
	//ゲーム画面に遷移すると抜けるフラグ
	if (m_isCanGameStartFlg == true) {

		//登録されたプレイヤー数が最大数4人になるまで追加できる
		if (m_totalPlaNum != MAXPLAYERNUM)
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
		for (int i = PLAYER1; i < m_totalPlaNum; i++)
		{
			if (g_pad[i]->IsTrigger(enButtonStart))
			{
				//ゲーム画面に遷移
				GameSceneTransition();
			}
		}

		//「PRESS START BUTTON」文字画像の点滅処理
		FlashingFont();
	}
}


//プレイヤーを追加する関数
void TitleScene::AddPlayer()
{
	//新規プレイヤーの追加フラグを真に。
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	//プレイヤーのアクティブ画像オブジェクト生成（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_plaActiveName[m_totalPlaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//2Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == PLAYER2)
	{
		m_plaActiveName[PLAYER2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 300.0f, 150.0f);
		//画像の位置指定
		m_plaActiveName[PLAYER2]->SetPosition(PLAYER2_NAME_POS);
	}
	//3Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == PLAYER3)
	{
		m_plaActiveName[PLAYER3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 300.0f, 150.0f);
		//画像の位置指定
		m_plaActiveName[PLAYER3]->SetPosition(PLAYER3_NAME_POS);
	}
	//4Pのアクティブ化+アクティブ画像表示
	if (m_totalPlaNum == PLAYER4)
	{
		m_plaActiveName[PLAYER4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 300.0f, 150.0f);
		//画像の位置指定
		m_plaActiveName[PLAYER4]->SetPosition(PLAYER4_NAME_POS);
	}
	//非アクティブ画像を削除。
	DeleteGO(m_plaDeactiveName[m_totalPlaNum]);
	//次のプレイヤーへ...
	m_totalPlaNum++;
}


//ゲーム画面に遷移する関数
void TitleScene::GameSceneTransition()
{
	//ゲーム画面に遷移
	NewGO<GameScene>(PRIORITY_0, "gamescene");
	////このクラスの削除
	////DeleteGO(this);

	//タイトルロゴを削除。
	DeleteGO(m_titleSprite);
	//PUSHSTARTBUTTONを削除。
	DeleteGO(m_pushStartButtonSprite);

	//ゲーム画面に遷移後、ゲーム開始ボタンとプレイヤー追加ボタンを押せなくするフラグ
	m_isCanGameStartFlg = false;
}


//「PRESS START BUTTON」文字画像の点滅処理関数
void TitleScene::FlashingFont()
{
	if (m_isFlashingFontTimerActiveFlg)
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
		m_isFlashingFontTimerActiveFlg = false;
	}
	//タイマーが0より小さい値になると、
	if (m_flashingFontTimer < 10)
	{
		//「PRESS START BUTTON」を表示するフラグ
		m_isFlashingFontTimerActiveFlg = true;
	}
}