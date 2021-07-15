///<<summary>
///リザルト画面時の処理クラス
///</summary>


#include "stdafx.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "Player.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"


namespace
{
	Vector3 NUMBER1_END_POS = { 150.0f,50.0f,0.0f };		//１位プレイヤーの表示位置
	Vector3 NUMBER2_END_POS = { 150.0f,-50.0f,0.0f };		//２位プレイヤーの表示位置
	Vector3 NUMBER3_END_POS = { 150.0f,-150.0f,0.0f };	//３位プレイヤーの表示位置
	Vector3 NUMBER4_END_POS = { 150.0f,-250.0f,0.0f };	//４位プレイヤーの表示位置

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
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		//順位画像オブジェクト生成
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);

		//１位画像
		if (plaNum == 0)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/1st.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING1_POS);
		}
		//2位画像
		if (plaNum == 1)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/2nd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING2_POS);
		}
		//3位画像
		if (plaNum == 2)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/3rd.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING3_POS);
		}
		//4位画像
		if (plaNum == 3)
		{
			m_rankingSprite[plaNum]->Init("Assets/image/DDS/4th.dds", 150.0f, 150.0f);
			m_rankingSprite[plaNum]->SetPosition(RANKING4_POS);
		}
	}
	//リザルトジングル
	SoundPlayBack(ResultGingle);

	//ゲーム中のBGMサウンド
	SoundPlayBack(GameBGM);

	//リザルト文字画像オブジェクト生成
	m_resultSprite = NewGO<SpriteRender>(PRIORITY_6, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);


	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//プレイヤー文字画像オブジェクト生成
		m_plaNum[plaNum] = NewGO<SpriteRender>(PRIORITY_6, nullptr);
		//1P
		if (plaNum == 0)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
		}
		//2P
		if (plaNum == 1)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
		}
		//3P
		if (plaNum == 2)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
		}
		//4P
		if (plaNum == 3)
		{
			m_plaNum[plaNum]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
		}
	}

	//順位情報を並び替え
	RankingSort();

	return true;
}


ResultScene::~ResultScene()
{
	//順位画像の削除。
	DeleteGO(m_resultSprite);

	//プレイヤー名画像の削除。
	for (int plaNum = 0; plaNum < 4; plaNum++)
	{
		DeleteGO(m_plaNum[plaNum]);

		DeleteGO(m_rankingSprite[plaNum]);
	}

	//サウンドを削除
	if(m_resultGingle != nullptr)
	DeleteGO(m_resultGingle);
	if (m_gameBGM != nullptr)
	DeleteGO(m_gameBGM);
	if (m_decideSound != nullptr)
	DeleteGO(m_decideSound);

	DeleteGO(m_fadeOut);
}


void ResultScene::Update()
{
	//プレイヤーが画面外（右側）からスライドしてくる処理
	SlidePlayerName();

	//ゲーム終了処理
	SelectScene();
}


//順位によってソートしプレイヤー名の画像を並び替える関数
void ResultScene::RankingSort()
{
	//プレイヤーの人数分スコアをゲット
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		m_plaScore[plaNum] = m_gameScene->GetPlaScore(plaNum);

	}
	//ソート
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_player->GetPlaNum(); nextPlaNum++)
		{
			if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
			{
				SpriteRender *tmp = m_plaNum[plaNum];
				m_plaNum[plaNum] = m_plaNum[nextPlaNum];
				m_plaNum[nextPlaNum] = tmp;
			}
		}
	}

	//1P
	if (m_player->GetPlaNum() >= 1)
	{
		m_plaNum[0]->SetPosition(m_number1Pos);
		m_moveSpeed = 20.0f;
	}
	//2P
	if (m_player->GetPlaNum() >= 2)
	{
		m_plaNum[1]->SetPosition(m_number2Pos);
		m_moveSpeed = 5.0f;
	}
	//3P
	if (m_player->GetPlaNum() >= 3)
	{
		m_plaNum[2]->SetPosition(m_number3Pos);
		m_moveSpeed = 10.0f;
	}
	//4P
	if (m_player->GetPlaNum() >= 4)
	{
		m_plaNum[3]->SetPosition(m_number4Pos);
		m_moveSpeed = 20.0f;
	}
}


//次どのシーンに行くか切り替える関数
void ResultScene::SelectScene()
{
	if (m_fadeOut == nullptr)
	{
		//プレイヤーの内、誰かのセレクトボタンが押されたら、
		for (int plaNum = 0; plaNum < 4; plaNum++) {
			//セレクトボタンが押されたら、
			if (g_pad[plaNum]->IsTrigger(enButtonSelect))
			{
				//決定サウンド
				SoundPlayBack(DecideSound);

				m_select = 0;

				//フェードアウト
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
			//スタートボタンが押されたら、
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//決定サウンド
				SoundPlayBack(DecideSound);

				m_select = 1;

				//フェードアウト
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
			//Yボタンが押されたら、
			if (g_pad[plaNum]->IsTrigger(enButtonY))
			{
				//決定サウンド
				SoundPlayBack(DecideSound);

				m_select = 2;

				//フェードアウト
				m_fadeOut = NewGO<Fade>(0, "fade");
				m_fadeOut->SetState(StateOut);
				m_fadeOut->SetAlphaValue(0.0f);
			}
		}
	}
	else
	{
		if (m_fadeOut->GetNowState() == StateWait&& !m_muriFlg)
		{
			switch (m_select)
			{
			case 0:
				//exeを閉じてゲーム終了
				exit(EXIT_SUCCESS);
				//メモ//
				//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
				//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
				break;
			case 1:
				//タイトル画面に戻る
				NewGO<TitleScene>(0, TITLESCENE_NAME);
				//ゲームシーンクラスを削除するようにフラグをオン！
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			case 2:
				//ステージ選択画面に戻る
				m_stageSelectScene = NewGO<StageSelectScene>(0, STAGESELECT_NAME);
				m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);

				//ゲームシーンクラスを削除するようにフラグをオン！
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;

			}
		}
	}
}


//プレイヤーが画面外（右側）からスライドしてくる処理関数
void ResultScene::SlidePlayerName()
{
	//ディレイをかける
	if (m_delayTimerOnFlg)
	{
		m_plaMoveDelayTimer++;
		if (m_plaMoveDelayTimer > 100)
		{
			m_pla4MoveFlg = true;
			m_delayTimerOnFlg = false;
		}
	}
	//4P
	if (m_pla4MoveFlg)
	{
		if (m_player->GetPlaNum() >= 4)
		{
			if (m_number4Pos.x > 150.0f)
			{
				m_number4Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla3MoveFlg = true;
				m_pla4MoveFlg = false;
				//次登場する画像のスピードを変化させる
				m_moveSpeed /= 2.0;
			}
			m_plaNum[3]->SetPosition(m_number4Pos);
		}
		else
		{
			m_pla4MoveFlg = false;
			m_pla3MoveFlg = true;
		}
	}
	//3P
	if (m_pla3MoveFlg)
	{
		if (m_player->GetPlaNum() >= 3)
		{
			if (m_number3Pos.x > 150.0f)
			{
				m_number3Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla2MoveFlg = true;
				m_pla3MoveFlg = false;
				//次登場する画像のスピードを変化させる
				m_moveSpeed /= 2.0;
			}
			m_plaNum[2]->SetPosition(m_number3Pos);
		}
		else
		{
			m_pla2MoveFlg = true;
			m_pla3MoveFlg = false;
		}
	}
	//2P
	if (m_pla2MoveFlg)
	{
		if (m_player->GetPlaNum() >= 2)
		{
			if (m_number2Pos.x > 150.0f)
			{
				m_number2Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla1MoveFlg = true;
				m_pla2MoveFlg = false;
				//次登場する画像のスピードを変化させる
				m_moveSpeed /= 2.0;
			}
			m_plaNum[1]->SetPosition(m_number2Pos);
		}
		else
		{
			m_pla1MoveFlg = true;
			m_pla2MoveFlg = false;
		}
	}
	//1P
	if (m_pla1MoveFlg)
	{
		if (m_player->GetPlaNum() >= 1)
		{
			if (m_number1Pos.x > 150.0f)
			{
				m_number1Pos.x -= m_moveSpeed;
			}
			else
			{
				m_pla1MoveFlg = false;
				m_plaJumpFlg = true;
			}
			m_plaNum[0]->SetPosition(m_number1Pos);
		}
		else
		{
			m_pla1MoveFlg = false;
			m_plaJumpFlg = true;
		}
	}
	if (m_plaJumpFlg)
	{
		//画像がジャンプする
		VerticalMove(10, 1.0f);
	}
}


//画像がジャンプする関数
void ResultScene::VerticalMove(int width, float speed)
{
	if (m_verticalMoveTimer < width)
	{
		//1人
		if (m_player->GetPlaNum() >= 1)
		{
			m_number1Pos.y += speed;
		}
		//2人
		if (m_player->GetPlaNum() >= 2)
		{
			m_number2Pos.y += speed;
		}
		//3人
		if (m_player->GetPlaNum() >= 3)
		{
			m_number3Pos.y += speed;
		}
		//4人
		if (m_player->GetPlaNum() >= 4)
		{
			m_number4Pos.y += speed;
		}
	}
	else if (m_verticalMoveTimer < (width * 2))
	{
		//1人
		if (m_player->GetPlaNum() >= 1)
		{
			m_number1Pos.y -= speed;
		}
		//2人
		if (m_player->GetPlaNum() >= 2)
		{
			m_number2Pos.y -= speed;
		}
		//3人
		if (m_player->GetPlaNum() >= 3)
		{
			m_number3Pos.y -= speed;
		}
		//4人
		if (m_player->GetPlaNum() >= 4)
		{
			m_number4Pos.y -= speed;
		}
	}
	else
	{
		m_plaJumpFlg = false;
	}

	m_verticalMoveTimer++;

	//1人
	if (m_player->GetPlaNum() >= 1)
	{
		m_plaNum[0]->SetPosition(m_number1Pos);
	}
	//2人
	if (m_player->GetPlaNum() >= 2)
	{
		m_plaNum[1]->SetPosition(m_number2Pos);
	}
	//3人
	if (m_player->GetPlaNum() >= 3)
	{
		m_plaNum[2]->SetPosition(m_number3Pos);
	}
	//4人
	if (m_player->GetPlaNum() >= 4)
	{
		m_plaNum[3]->SetPosition(m_number4Pos);
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