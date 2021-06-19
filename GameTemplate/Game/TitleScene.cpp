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

	const Vector3 TITLE_POS = { -60.0f, 50.0f,0.0f };		//タイトルの表示位置
	const Vector3 TITLE_SCA = { 6.0f, 6.0f,6.0f };			//タイトルの大きさ

	const Vector3 PLAYER1_NAMEPOS = {-480.0f, 310.0f,0.0f};			//プレイヤー1の名前表示位置
	const Vector3 PLAYER2_NAMEPOS = { 480.0f, 310.0f,0.0f};			//プレイヤー2の名前表示位置
	const Vector3 PLAYER3_NAMEPOS = {-480.0f,-310.0f,0.0f};			//プレイヤー3の名前表示位置
	const Vector3 PLAYER4_NAMEPOS = { 480.0f,-310.0f,0.0f};			//プレイヤー4の名前表示位置

	const Vector3 BUTTON_POS = { 0.0f, -200.0f,0.0f };				//プッシュスタートボタンの表示位置
	const Vector3 BUTTON_SCA = { 1.2f, 1.2f,1.2f };					//プッシュスタートボタンの大きさ
}


bool TitleScene::Start()
{
	//タイトルロゴを表示
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 300.0f, 150.0f);
	m_titleSprite->SetPosition({ TITLE_POS });
	m_titleSprite->SetScale({ TITLE_SCA });

	//PUSH START BUTTONを表示
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ BUTTON_POS });
	m_pushStartButtonSprite->SetScale({ BUTTON_SCA });

	//1Pは無条件で追加フラグを真に。
	m_isAddPlayerFlg[PLAYER1] = true;
	//1Pは非アクティブときがないため、初めからアクティブ画像を表示
	m_plaActiveName[PLAYER1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_plaActiveName[PLAYER1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 300.0f, 150.0f);
	m_plaActiveName[PLAYER1]->SetPosition(PLAYER1_NAMEPOS);

	//2P～4Pの非アクティブ画像を表示。
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++) {
		m_plaDeactiveName[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//1P
		if (i == PLAYER1)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER1_NAMEPOS);
			//非アクティブ時はないため、非表示にしておく。
			m_plaDeactiveName[i]->Deactivate();
		}
		//2P
		if (i == PLAYER2)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER2_NAMEPOS);
		}
		//3P
		if (i == PLAYER3)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER3_NAMEPOS);
		}
		//4P
		if (i == PLAYER4)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER4_NAMEPOS);
		}
	}

	//Start関数のreturn文
	return true;
}


TitleScene::~TitleScene()
{
	//登録されたプレイヤーのアクティブ画像を削除
	for (int i = PLAYER1; i < m_totalPlayerNum; i++)
	{
		DeleteGO(m_plaActiveName[i]);
	}
	//登録されていないプレイヤーの非アクティブ画像を削除
	for (int i = m_totalPlayerNum; i < (MAXPLAYERNUM+1); i++)
	{
		//4Pまで登録されていたらm_plaDeactiveName[4]と、
		//添え字がオーバーしてしまうのでここでfor文を抜けさせる
		if (m_totalPlayerNum == MAXPLAYERNUM)
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
		//プレイヤーを追加する
		if (m_totalPlayerNum != MAXPLAYERNUM)
		{
			/*登録されていないコントローラーのAボタンが押されたら、
			【注意】USBポートに繋がれた順じゃないと登録されていきません。*/
			if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonA))
			{
				//新規プレイヤーの追加フラグを真に。
				m_isAddPlayerFlg[m_totalPlayerNum] = true;

				//プレイヤーのアクティブ化（一番上のレイヤーに置きたいのでプライオリティーは最高値）
				m_plaActiveName[m_totalPlayerNum] = NewGO<SpriteRender>(PRIORITY_1,nullptr);
				//2Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER2)
				{
					m_plaActiveName[PLAYER2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 300.0f, 150.0f);
					//画像の位置指定
					m_plaActiveName[PLAYER2]->SetPosition(PLAYER2_NAMEPOS);
				}
				//3Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER3)
				{
					m_plaActiveName[PLAYER3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 300.0f, 150.0f);
					//画像の位置指定
					m_plaActiveName[PLAYER3]->SetPosition(PLAYER3_NAMEPOS);
				}
				//4Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER4)
				{
					m_plaActiveName[PLAYER4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 300.0f, 150.0f);
					//画像の位置指定
					m_plaActiveName[PLAYER4]->SetPosition(PLAYER4_NAMEPOS);
				}
				//非アクティブ画像を削除。
				DeleteGO(m_plaDeactiveName[m_totalPlayerNum]);
				//次のプレイヤーへ...
				m_totalPlayerNum++;
			}
		}

		//登録されている誰かのスタートボタンが押されたら、
		for (int i = PLAYER1; i < m_totalPlayerNum; i++)
		{
			if (g_pad[i]->IsTrigger(enButtonStart))
			{
				//ゲーム画面に遷移
				NewGO<GameScene>(PRIORITY_0,"gamescene");
				////このクラスの削除
				////DeleteGO(this);

				//タイトルロゴを削除。
				DeleteGO(m_titleSprite);
				//PUSHSTARTBUTTONを削除。
				DeleteGO(m_pushStartButtonSprite);

				//ゲーム画面に遷移後、ゲーム開始ボタンとプレイヤー追加ボタンを押せなくするフラグ
				m_isCanGameStartFlg = false;
			}
		}

		//「PRESS START BUTTON」の点滅処理
		if (m_isButtonTimerActiveFlg)
		{
			//タイマー加算
			m_buttonTimer++;
			//「PRESS START BUTTON」表示
			m_pushStartButtonSprite->Activate();
		}
		else
		{
			//タイマー減算
			m_buttonTimer--;
			//「PRESS START BUTTON」非表示
			m_pushStartButtonSprite->Deactivate();
		}
		//タイマーが60より大きい値になると、
		if (m_buttonTimer > 60)
		{
			//「PRESS START BUTTON」を非表示にするフラグ
			m_isButtonTimerActiveFlg = false;
		}
		//タイマーが0より小さい値になると、
		if (m_buttonTimer < 0)
		{
			//「PRESS START BUTTON」を表示するフラグ
			m_isButtonTimerActiveFlg = true;
		}
	}
}