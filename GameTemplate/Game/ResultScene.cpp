///<<summary>
///リザルト画面のメイン処理
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"
#include "Fade.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const Vector3 RANKING1_POS = { -150.0f,50.0f,nsStdafx::FLOAT_ZERO };	//１位画像の位置
		const Vector3 RANKING2_POS = { -150.0f,-50.0f,nsStdafx::FLOAT_ZERO };	//２位画像の位置
		const Vector3 RANKING3_POS = { -150.0f,-150.0f,nsStdafx::FLOAT_ZERO };	//３位画像の位置
		const Vector3 RANKING4_POS = { -150.0f,-250.0f,nsStdafx::FLOAT_ZERO };	//４位画像の位置
	}


	bool ResultScene::Start()
	{
		//インスタンスを探す。
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//順位の画像の初期化をまとめている関数
		InitRankingImage();

		//リザルトジングル
		m_soundPlayBack->ResultSceneSoundPlayBack(ResultGingle);

		//ゲーム中のBGMサウンド
		m_soundPlayBack->ResultSceneSoundPlayBack(GameBGM);

		//リザルト文字画像オブジェクト生成
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		m_resultSprite->Init("Result", 600.0f, 300.0f);
		Vector3 m_resSprPos = { nsStdafx::FLOAT_ZERO,160.0f,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		//PLAYER画像の初期化をまとめている関数
		InitPlayerImage();

		//順位情報を並び替え
		RankingSort();

		return true;
	}


	ResultScene::~ResultScene()
	{
		//順位画像の削除。
		DeleteGO(m_resultSprite);

		//プレイヤー名画像の削除。
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			DeleteGO(m_plaNum[plaNum]);

			DeleteGO(m_rankingSprite[plaNum]);
		}

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
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			m_plaScore[plaNum] = m_gameScene->GetPlaScore(plaNum);

		}
		//ソート
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			for (int nextPlaNum = plaNum + 1; nextPlaNum < m_totalPlaNum; nextPlaNum++)
			{
				if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
				{
					SpriteRender* tmp = m_plaNum[plaNum];
					m_plaNum[plaNum] = m_plaNum[nextPlaNum];
					m_plaNum[nextPlaNum] = tmp;
				}
			}
		}

		//1P
		if (m_totalPlaNum >= 1)
		{
			m_plaNum[0]->SetPosition(m_number1Pos);
			m_moveSpeed = 20.0f;
		}
		//2P
		if (m_totalPlaNum >= 2)
		{
			m_plaNum[1]->SetPosition(m_number2Pos);
			m_moveSpeed = 5.0f;
		}
		//3P
		if (m_totalPlaNum >= 3)
		{
			m_plaNum[2]->SetPosition(m_number3Pos);
			m_moveSpeed = 10.0f;
		}
		//4P
		if (m_totalPlaNum >= 4)
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
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++) {
				//セレクトボタンが押されたら、
				if (g_pad[plaNum]->IsTrigger(enButtonSelect))
				{
					//決定サウンド
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextGameEnd;

					//フェードアウト
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
				//スタートボタンが押されたら、
				if (g_pad[plaNum]->IsTrigger(enButtonStart))
				{
					//決定サウンド
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextTitleScene;

					//フェードアウト
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
				//Yボタンが押されたら、
				if (g_pad[plaNum]->IsTrigger(enButtonY))
				{
					//決定サウンド
					m_soundPlayBack->ResultSceneSoundPlayBack(DecideSound);

					m_select = NextStageSelectScene;

					//フェードアウト
					m_fadeOut = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fadeOut->SetState(StateOut);
					m_fadeOut->SetAlphaValue(nsStdafx::FLOAT_ZERO);
				}
			}
		}
		else
		{
			if (m_fadeOut->GetNowState() != StateWait && !m_muriFlg)
			{
				return;
			}

			switch (m_select)
			{
			case NextGameEnd:
				//exeを閉じてゲーム終了
				exit(EXIT_SUCCESS);
				//メモ//
				//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
				//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
				break;
			case NextTitleScene:
				//タイトル画面に戻る
				NewGO<TitleScene>(nsStdafx::PRIORITY_0, nullptr);
				//ゲームシーンクラスを削除するようにフラグをオン
				m_gameScene->SetDeleteFlg(true);
				//リザルト画面で使われるサウンドを破棄
				m_soundPlayBack->ResultSceneDeleteGO();

				m_muriFlg = true;
				break;
			case NextStageSelectScene:
				//ステージ選択画面に戻る
				m_stageSelectScene = NewGO<StageSelectScene>(nsStdafx::PRIORITY_0, nullptr);
				m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);

				//ゲームシーンクラスを削除するようにフラグをオン
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;

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
				m_plaMoveFlg[Player4] = true;
				m_delayTimerOnFlg = false;
			}
		}
		//4P
		if (m_plaMoveFlg[Player4])
		{
			if (m_totalPlaNum >= 4)
			{
				if (m_number4Pos.x > 150.0f)
				{
					m_number4Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player3] = true;
					m_plaMoveFlg[Player4] = false;
					//次登場する画像のスピードを変化させる
					m_moveSpeed /= 2.0;
				}
				m_plaNum[3]->SetPosition(m_number4Pos);
			}
			else
			{
				m_plaMoveFlg[Player4] = false;
				m_plaMoveFlg[Player3] = true;
			}
		}
		//3P
		if (m_plaMoveFlg[Player3])
		{
			if (m_totalPlaNum >= 3)
			{
				if (m_number3Pos.x > 150.0f)
				{
					m_number3Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player2] = true;
					m_plaMoveFlg[Player3] = false;
					//次登場する画像のスピードを変化させる
					m_moveSpeed /= 2.0;
				}
				m_plaNum[2]->SetPosition(m_number3Pos);
			}
			else
			{
				m_plaMoveFlg[Player2] = true;
				m_plaMoveFlg[Player3] = false;
			}
		}
		//2P
		if (m_plaMoveFlg[Player2])
		{
			if (m_totalPlaNum >= 2)
			{
				if (m_number2Pos.x > 150.0f)
				{
					m_number2Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player1] = true;
					m_plaMoveFlg[Player2] = false;
					//次登場する画像のスピードを変化させる
					m_moveSpeed /= 2.0;
				}
				m_plaNum[1]->SetPosition(m_number2Pos);
			}
			else
			{
				m_plaMoveFlg[Player1] = true;
				m_plaMoveFlg[Player2] = false;
			}
		}
		//1P
		if (m_plaMoveFlg[Player1])
		{
			if (m_totalPlaNum >= 1)
			{
				if (m_number1Pos.x > 150.0f)
				{
					m_number1Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[Player1] = false;
					m_plaJumpFlg = true;
				}
				m_plaNum[0]->SetPosition(m_number1Pos);
			}
			else
			{
				m_plaMoveFlg[Player1] = false;
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
	void ResultScene::VerticalMove(const int width, const float speed)
	{
		if (m_verticalMoveTimer < width)
		{
			//1人
			if (m_totalPlaNum >= 1)
			{
				m_number1Pos.y += speed;
			}
			//2人
			if (m_totalPlaNum >= 2)
			{
				m_number2Pos.y += speed;
			}
			//3人
			if (m_totalPlaNum >= 3)
			{
				m_number3Pos.y += speed;
			}
			//4人
			if (m_totalPlaNum >= 4)
			{
				m_number4Pos.y += speed;
			}
		}
		else if (m_verticalMoveTimer < (width * 2))
		{
			//1人
			if (m_totalPlaNum >= 1)
			{
				m_number1Pos.y -= speed;
			}
			//2人
			if (m_totalPlaNum >= 2)
			{
				m_number2Pos.y -= speed;
			}
			//3人
			if (m_totalPlaNum >= 3)
			{
				m_number3Pos.y -= speed;
			}
			//4人
			if (m_totalPlaNum >= 4)
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
		if (m_totalPlaNum >= 1)
		{
			m_plaNum[0]->SetPosition(m_number1Pos);
		}
		//2人
		if (m_totalPlaNum >= 2)
		{
			m_plaNum[1]->SetPosition(m_number2Pos);
		}
		//3人
		if (m_totalPlaNum >= 3)
		{
			m_plaNum[2]->SetPosition(m_number3Pos);
		}
		//4人
		if (m_totalPlaNum >= 4)
		{
			m_plaNum[3]->SetPosition(m_number4Pos);
		}
	}


	//順位の画像の初期化をまとめている関数
	void ResultScene::InitRankingImage()
	{
		//順位文字を初期化し、表示
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//順位画像オブジェクト生成
			m_rankingSprite[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);

			sprintf(m_filePath, "%dst", plaNum + 1);
			m_rankingSprite[plaNum]->Init(m_filePath, 150.0f, 150.0f);
			switch (plaNum)
			{
				//１位画像
			case Player1:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING1_POS);
				break;
				//２位画像
			case Player2:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING2_POS);
				break;
				//３位画像
			case Player3:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING3_POS);
				break;
				//４位画像
			case Player4:
				m_rankingSprite[plaNum]->SetPosition(nsResultScene::RANKING4_POS);
				break;
			}
		}
	}


	//PLAYER画像の初期化をまとめている関数
	void ResultScene::InitPlayerImage()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//プレイヤー文字画像オブジェクト生成
			m_plaNum[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);

			sprintf(m_filePath, "Player%d_ActiveName", plaNum + 1);
			m_plaNum[plaNum]->Init(m_filePath, 340.0f, 170.0f);
		}
	}
}