#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// 注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！
/// </summary>

namespace
{
	const Vector3 TITLE_POS = { -60.0f, 50.0f,0.0f };			//タイトルの表示位置
	const Vector3 TITLE_SCA = { 6.0f, 6.0f,6.0f };			//タイトルの大きさ

	const int PLAYER1   = 0;	//1P
	const int PLAYER2   = 1;	//2P
	const int PLAYER3   = 2;	//3P
	const int PLAYER4   = 3;	//4P
	const Vector3 PLAYER1_NAMEPOS = {-570.0f, 300.0f,0.0f};			//プレイヤー1の名前表示位置
	const Vector3 PLAYER2_NAMEPOS = { 570.0f, 300.0f,0.0f};			//プレイヤー2の名前表示位置
	const Vector3 PLAYER3_NAMEPOS = {-570.0f,-300.0f,0.0f};			//プレイヤー3の名前表示位置
	const Vector3 PLAYER4_NAMEPOS = { 570.0f,-300.0f,0.0f};			//プレイヤー4の名前表示位置

	const Vector3 PLAYER1_CROWNPOS = { -470.0f, 300.0f,0.0f };		//プレイヤー1の王冠表示位置
	const Vector3 PLAYER2_CROWNPOS = { 470.0f, 300.0f,0.0f };		//プレイヤー2の王冠表示位置
	const Vector3 PLAYER3_CROWNPOS = { -470.0f, -300.0f,0.0f };		//プレイヤー3の王冠表示位置
	const Vector3 PLAYER4_CROWNPOS = { 470.0f, -300.0f,0.0f };		//プレイヤー4の王冠表示位置
	const Vector3 CROWNSCA = { 0.2f, 0.2f,0.2f };					//王冠の大きさ

	const Vector3 BUTTON_POS = { 0.0f, -200.0f,0.0f };				//プッシュスタートボタンの表示位置
	const Vector3 BUTTON_SCA = { 1.2f, 1.2f,1.2f };					//プッシュスタートボタンの大きさ
	const Vector4 BUTTON_MULCOL = { 1.0f, 1.0f,1.0f ,0.0f};			//プッシュスタートボタンの乗算カラー

	const int MAXPLAYERNUM = 4;		//最大プレイ人数

	const float PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED = 0.02f;
}

bool TitleScene::Start()
{
	//タイトルロゴを表示
	m_titleSprite = NewGO<SpriteRender>(0);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 300.0f, 150.0f);
	m_titleSprite->SetPosition({ TITLE_POS });
	m_titleSprite->SetScale({ TITLE_SCA });

	//王冠を表示
	m_crownSprite = NewGO<SpriteRender>(1);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });

	//PUSH START BUTTONを表示
	m_pushStartButtonSprite = NewGO<SpriteRender>(1);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ BUTTON_POS });
	m_pushStartButtonSprite->SetScale({ BUTTON_SCA });
	m_pushStartButtonSprite->SetMulColor({ BUTTON_MULCOL });//透明

	//1Pは無条件で追加フラグを真に。
	isAddPlayer[PLAYER1] = true;
	//1Pは非アクティブ時がないため、初めからアクティブ画像を表示
	//（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_plaActiveName[PLAYER1] = NewGO<SpriteRender>(1);
	m_plaActiveName[PLAYER1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 120.0f, 120.0f);
	m_plaActiveName[PLAYER1]->SetPosition(PLAYER1_NAMEPOS);

	//2P～4Pの非アクティブ画像を表示。
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++) {
		//（一番上のレイヤーに置きたいのでプライオリティーは最高値）
		m_plaDeactiveName[i] = NewGO<SpriteRender>(1);
		//1P
		if (i == PLAYER1)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER1_NAMEPOS);
			//非アクティブ時はないため、非表示にしておく。
			m_plaDeactiveName[i]->Deactivate();
		}
		//2P
		if (i == PLAYER2)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER2_NAMEPOS);
		}
		//3P
		if (i == PLAYER3)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER3_NAMEPOS);
		}
		//4P
		if (i == PLAYER4)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER4_NAMEPOS);
		}
	}

	//Start関数のreturn文
	return true;
}

TitleScene::~TitleScene()
{
	//登録されたプレイヤーの数だけアクティブ画像を削除
	for (int i = PLAYER1; i < m_totalPlayerNum; i++)
	{
		DeleteGO(m_plaActiveName[i]);
	}
	//登録されていないプレイヤーの非アクティブ画像を削除
	for (int i = m_totalPlayerNum; i < (MAXPLAYERNUM+1); i++)
	{
		//4Pまで登録されていたらm_plaDeactiveName[4]と、
		//添え字がオーバーしてしまうのでここでfor文を抜けさせる。
		if (m_totalPlayerNum == MAXPLAYERNUM)
		{
			break;
		}
		//緑の波線は大丈夫です。
		DeleteGO(m_plaDeactiveName[i]);
	}
}

void TitleScene::Update()
{
	if (isCanGameStartFlg == true) {
		//プレイヤーを追加する
		if (m_totalPlayerNum != MAXPLAYERNUM)
		{
			//登録されていないコントローラーのスタートボタンが押されたら、
			if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonA))
			{
				//新規プレイヤーの追加フラグを真に。
				isAddPlayer[m_totalPlayerNum] = true;

				//プレイヤーのアクティブ化（一番上のレイヤーに置きたいのでプライオリティーは最高値）
				m_plaActiveName[m_totalPlayerNum] = NewGO<SpriteRender>(1);
				//2Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER2)
				{
					m_plaActiveName[PLAYER2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 120.0f, 120.0f);
					//画像のポジション指定
					m_plaActiveName[PLAYER2]->SetPosition(PLAYER2_NAMEPOS);
				}
				//3Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER3)
				{
					m_plaActiveName[PLAYER3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 120.0f, 120.0f);
					//画像のポジション指定
					m_plaActiveName[PLAYER3]->SetPosition(PLAYER3_NAMEPOS);
				}
				//4Pのアクティブ化+アクティブ画像表示
				if (m_totalPlayerNum == PLAYER4)
				{
					m_plaActiveName[PLAYER4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 120.0f, 120.0f);
					//画像のポジション指定
					m_plaActiveName[PLAYER4]->SetPosition(PLAYER4_NAMEPOS);
				}
				//非アクティブ画像を削除。
				DeleteGO(m_plaDeactiveName[m_totalPlayerNum]);
				//次のプレイヤーへ...
				m_totalPlayerNum++;
			}
		}

		//誰かのスタートボタンが押されたらゲーム開始
		for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
		{
			if (g_pad[i]->IsTrigger(enButtonStart))
			{
				//ゲーム画面に遷移
				NewGO<GameScene>(0,"gamescene");
				//このクラスの削除
				//DeleteGO(this);

				//タイトルロゴを削除。
				DeleteGO(m_titleSprite);
				//PUSHSTARTBUTTONを削除。
				DeleteGO(m_pushStartButtonSprite);


				//ゲーム開始後、ゲーム開始ボタンとプレイヤー追加ボタンを押せなくなるフラグ
				isCanGameStartFlg = false;
			}
		}

		//PRESSSTARTBUTTONの点滅処理
		//フラグが立っていると、
		if (isButtonFlg == true)
		{
			//だんだんと透明にする
			m_pushStartButtonSprite->SetMulColor({ 1.0f,1.0f,1.0f,m_pushStartButtonSprite->GetMulColor().w - PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED });

			//完全に透明になったら、
			if (m_pushStartButtonSprite->GetMulColor().w <= 0.0f)
			{
				//フラグを折る
				isButtonFlg = false;
			}
		}
		//フラグが折れたら、
		else
		{
			//だんだんと不透明にする
			m_pushStartButtonSprite->SetMulColor({ 1.0f,1.0f,1.0f,m_pushStartButtonSprite->GetMulColor().w + PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED });

			//不透明になったら
			if (m_pushStartButtonSprite->GetMulColor().w >= 0.8f)
			{
				//フラグを立てる
				isButtonFlg = true;
			}
		}
	}
}