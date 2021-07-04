#include "stdafx.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Player.h"


namespace
{
	const Vector3 NUMBER1_POS = { 150.0f,50.0f,0.0f };		//１位プレイヤーの表示位置
	const Vector3 NUMBER2_POS = { 150.0f,-50.0f,0.0f };		//２位プレイヤーの表示位置
	const Vector3 NUMBER3_POS = { 150.0f,-150.0f,0.0f };	//３位プレイヤーの表示位置
	const Vector3 NUMBER4_POS = { 150.0f,-250.0f,0.0f };	//４位プレイヤーの表示位置

	const Vector3 RANKING1_POS = { -150.0f,50.0f,0.0f };	//１位画像の位置
	const Vector3 RANKING2_POS = { -150.0f,-50.0f,0.0f };	//２位画像の位置
	const Vector3 RANKING3_POS = { -150.0f,-150.0f,0.0f };	//３位画像の位置
	const Vector3 RANKING4_POS = { -150.0f,-250.0f,0.0f };	//４位画像の位置
}


bool ResultScene::Start()
{
	//インスタンスを探す。
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_player = FindGO<Player>(PLAYER_NAME);

	//順位文字を初期化し、表示
	for (int i = 0; i < 4; i++)
	{
		//順位画像オブジェクト生成
		m_rankingSprite[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);

		//１位画像
		if (i == 0)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/1st.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING1_POS);
		}
		//2位画像
		if (i == 1)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/2nd.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING2_POS);
		}
		//3位画像
		if (i == 2)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/3rd.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING3_POS);
		}
		//4位画像
		if (i == 3)
		{
			m_rankingSprite[i]->Init("Assets/image/DDS/4th.dds", 150.0f, 150.0f);
			m_rankingSprite[i]->SetPosition(RANKING4_POS);
		}
	}
	//リザルトジングル
	SoundPlayBack(ResultGingle);

	//ゲーム中のBGMサウンド
	SoundPlayBack(GameBGM);

	//リザルト文字画像オブジェクト生成
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);


	for (int i = 0; i < m_player->GetPlaNum(); i++)
	{
		//プレイヤー文字画像オブジェクト生成
		m_plaNum[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//1P
		if (i == 0)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
		}
		//2P
		if (i == 1)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
		}
		//3P
		if (i == 2)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
		}
		//4P
		if (i == 3)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
		}
	}

	//順位情報を並び替え
	RankingSort();

	//Start関数のreturn文
	return true;
}


ResultScene::~ResultScene()
{
	//順位画像の削除。
	DeleteGO(m_resultSprite);

	//プレイヤー名画像の削除。
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_plaNum[i]);
	}
}


void ResultScene::Update()
{
	//ゲーム終了処理
	GameEnd();
}


//順位によってソートしプレイヤー名の画像を並び替える関数
void ResultScene::RankingSort()
{
	//プレイヤーの人数分スコアをゲット
	for (int i = 0; i < m_player->GetPlaNum(); i++)
	{
		m_plaScore[i] = m_gameScene->GetPlaScore(i);

	}
	//ソート
	for (int k = 0; k < m_player->GetPlaNum(); k++)
	{
		for (int u = k + 1; u < m_player->GetPlaNum(); u++)
		{
			if (m_plaScore[k] < m_plaScore[u])
			{
				SpriteRender *tmp = m_plaNum[k];
				m_plaNum[k] = m_plaNum[u];
				m_plaNum[u] = tmp;
			}
		}
	}

	//1Pのプレイヤー名の位置を設定
	if (m_player->GetPlaNum() == 1)
	{
		m_plaNum[0]->SetPosition(NUMBER1_POS);
	}
	//2P
	if (m_player->GetPlaNum() == 2)
	{
		m_plaNum[1]->SetPosition(NUMBER2_POS);
	}
	//3P
	if (m_player->GetPlaNum() == 3)
	{
		m_plaNum[2]->SetPosition(NUMBER3_POS);
	}
	//4P
	if (m_player->GetPlaNum() == 4)
	{
		m_plaNum[3]->SetPosition(NUMBER4_POS);
	}
}


//ゲーム終了関数
void ResultScene::GameEnd()
{
	//プレイヤーの内、誰かのセレクトボタンが押されたら、
	for (int i = 0; i < 4; i++) {
		if (g_pad[i]->IsTrigger(enButtonSelect))
		{
			//決定サウンド
			SoundPlayBack(DecideSound);

			m_timerOnFlg = true;
		}
	}
	if (m_timerOnFlg)
	{
		m_exitTimer++;

		if (m_exitTimer > 60)
		{
			//exeを閉じてゲーム終了
			exit(EXIT_SUCCESS);
			//メモ//
			//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
			//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
		}
	}
}


//サウンドを一括にまとめる関数
void ResultScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case ResultGingle:
		//リザルトジングルの初期化
		m_resultGingle = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_resultGingle->Init(L"Assets/sound/ResultGingle.wav");
		m_resultGingle->SetVolume(0.5f);
		m_resultGingle->Play(false);	//偽でワンショット再生

		break;

	case GameBGM:
		//ゲーム中のBGMサウンドの初期化
		m_gameBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameBGM->Init(L"Assets/sound/GameBGM.wav");
		m_gameBGM->SetVolume(0.01f);
		m_gameBGM->Play(true);	//真でループ再生

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