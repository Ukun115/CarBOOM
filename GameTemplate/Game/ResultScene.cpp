///<<summary>
///リザルト画面のメイン処理
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Fade.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const float RESULT_SPRITE_WIDTH = 600.0f;
		const float RESULT_SPRITE_HEIGHT = 300.0f;
		const float RESULT_SPRITE_POS_Y = 160.0f;
		const float GRAYBACK_SCA = 1500.0f;
		const Vector3 RANKING1_POS = { -150.0f,50.0f,0.0f };	//１位画像の位置
		const Vector3 RANKING2_POS = { -150.0f,-50.0f,0.0f };	//２位画像の位置
		const Vector3 RANKING3_POS = { -150.0f,-150.0f,0.0f };	//３位画像の位置
		const Vector3 RANKING4_POS = { -150.0f,-250.0f,0.0f };	//４位画像の位置
		const int JUMP_WIDTH = 10;
		const float JUMP_SPEED = 1.0f;
		const int DELAYTIMER = 100;
		const int PLUS_ONE = 1;
		const float RANKING_FONT_SCALE = 150.0f;
		const int NIBAI = 2;
		const float PLAYERNAME_SPRITE_WIDTH = 340.0f;
		const float PLAYERNAME_SPRITE_HEIGHT = 170.0f;
		const float NEXT_JUNNI_CHANGE_SPEED = 2.0f;
	}

	bool ResultScene::Start()
	{
		//インスタンスを探す。
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//リザルトジングル
		m_soundPlayBack->ResultSceneSoundPlayBack(ResultGingle);
		//ゲーム中のBGMサウンド
		m_soundPlayBack->ResultSceneSoundPlayBack(GameBGM);

		m_grayBack = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		//灰色にする画像を初期化
		m_grayBack->Init("GrayBack", nsResultScene::GRAYBACK_SCA, nsResultScene::GRAYBACK_SCA);

		//リザルト文字画像オブジェクト生成
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		m_resultSprite->Init("Result", nsResultScene:: RESULT_SPRITE_WIDTH, nsResultScene::RESULT_SPRITE_HEIGHT);
		m_resSprPos = { nsStdafx::FLOAT_ZERO,nsResultScene::RESULT_SPRITE_POS_Y,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//順位の画像の初期化をまとめている関数
			InitRankingImage(plaNum);
			//PLAYER画像の初期化をまとめている関数
			InitPlayerImage(plaNum);
		}

		//順位情報を並び替え
		RankingSort();

		return true;
	}

	ResultScene::~ResultScene()
	{
		//順位画像の削除。
		DeleteGO(m_resultSprite);

		DeleteGO(m_fadeOut);

		DeleteGO(m_grayBack);

		//プレイヤー名画像の削除。
		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++)
		{
			DeleteGO(m_plaNum[plaNum]);

			DeleteGO(m_rankingSprite[plaNum]);
		}
	}

	void ResultScene::Update()
	{
		//ディレイをかける
		if (m_delayTimerOnFlg)
		{
			m_plaMoveDelayTimer++;
			if (m_plaMoveDelayTimer > nsResultScene::DELAYTIMER)
			{
				m_plaMoveFlg[Player4] = true;
				m_delayTimerOnFlg = false;
			}
		}
		//プレイヤーが画面外（右側）からスライドしてくる処理
		PlayerNameMove();

		if (!m_plaJumpFlg)
		{
			return;
		}
		//画像がジャンプする
		VerticalMove(nsResultScene::JUMP_WIDTH, nsResultScene::JUMP_SPEED);

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

			//次の遷移先
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
				//リザルト画面で使われるサウンドを破棄
				m_soundPlayBack->ResultSceneDeleteGO();
				//ゲームシーンクラスを削除するようにフラグをオン
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			}
		}
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
			for (int nextPlaNum = plaNum + nsResultScene::PLUS_ONE; nextPlaNum < m_totalPlaNum; nextPlaNum++)
			{
				if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
				{
					SpriteRender* tmp = m_plaNum[plaNum];
					m_plaNum[plaNum] = m_plaNum[nextPlaNum];
					m_plaNum[nextPlaNum] = tmp;
				}
			}
		}

		//プレイヤーの人数に応じて横からプレイヤー名が出てくる速度が変化
		for (int plaNum = Player1; plaNum <= m_totalPlaNum; plaNum)
		{
			MoveSpeedChange(plaNum);
			PlaRankingPosSet(plaNum);
		}
	}

	//画像がジャンプする関数
	void ResultScene::VerticalMove(const int width, const float speed)
	{
		if (m_verticalMoveTimer < width)
		{
			//上にジャンプ
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, speed);
			}
		}
		else if (m_verticalMoveTimer < (width * nsResultScene::NIBAI))
		{
			//ジャンプ後の落下
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, -speed);
			}
		}
		else
		{
			m_plaJumpFlg = false;
		}

		m_verticalMoveTimer++;

		for (int plaNum = Player2; plaNum <= TotalPlaNum; plaNum)
		{
			PlaRankingPosSet(plaNum);
		}
	}

	//順位の画像の初期化をまとめている関数
	void ResultScene::InitRankingImage(const int plaNum)
	{
		//順位文字を初期化し、表示
		//順位画像オブジェクト生成
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "%dst", (plaNum + nsResultScene::PLUS_ONE));
		m_rankingSprite[plaNum]->Init(m_filePath, nsResultScene::RANKING_FONT_SCALE, nsResultScene::RANKING_FONT_SCALE);
		m_rankingSprite[plaNum]->SetPosition(WhatRankingNumPos(plaNum));
	}

	//PLAYER画像の初期化をまとめている関数
	void ResultScene::InitPlayerImage(const int plaNum)
	{
		//プレイヤー文字画像オブジェクト生成
		m_plaNum[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "Player%d_ActiveName", plaNum);
		m_plaNum[plaNum]->Init(m_filePath, nsResultScene::PLAYERNAME_SPRITE_WIDTH, nsResultScene::PLAYERNAME_SPRITE_HEIGHT);
	}

	void ResultScene::PlayerNameMove()
	{
		for (int plaNum = Player4; plaNum >= Player1; plaNum--)
		{
			if (!m_plaMoveFlg[Player4])
			{
				return;
			}
			if (m_totalPlaNum >= (plaNum + nsResultScene::PLUS_ONE))
			{
				if (m_number4Pos.x > 150.0f)
				{
					m_number4Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[plaNum - nsResultScene::PLUS_ONE] = true;
					if (plaNum != Player1)
					{
						m_plaMoveFlg[plaNum] = false;
					}
					else
					{
						m_plaJumpFlg = true;
					}
					//次登場する画像のスピードを変化させる
					m_moveSpeed /= nsResultScene::NEXT_JUNNI_CHANGE_SPEED;
				}
				m_plaNum[plaNum]->SetPosition(m_number4Pos);
			}
			else
			{
				m_plaMoveFlg[plaNum] = false;
				if (plaNum != Player1)
				{
					m_plaMoveFlg[plaNum - nsResultScene::PLUS_ONE] = true;
				}
				else
				{
					m_plaJumpFlg = true;
				}
			}
		}
	}

	void ResultScene::MoveSpeedChange(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_moveSpeed = WhatMoveSpeed(plaNum);
		}
	}

	void ResultScene::PlaRankingPosSet(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_plaNum[plaNum]->SetPosition(WhatNumberPos(plaNum));
		}
	}

	void ResultScene::PlaNameJumpState(const int plaNum, const float speed)
	{
		if (m_totalPlaNum >= plaNum)
		{
			switch (plaNum)
			{
			case Player2:
				m_number1Pos.y += speed;
				break;
			case Player3:
				m_number2Pos.y += speed;
				break;
			case Player4:
				m_number3Pos.y += speed;
				break;
			case TotalPlaNum:
				m_number4Pos.y += speed;
				break;
			}
		}
	}

	Vector3 ResultScene::WhatRankingNumPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return nsResultScene::RANKING1_POS;
			break;
		case Player2:
			return nsResultScene::RANKING2_POS;
			break;
		case Player3:
			return nsResultScene::RANKING3_POS;
			break;
		case TotalPlaNum:
			return nsResultScene::RANKING4_POS;
			break;
		}
	}

	float ResultScene::WhatMoveSpeed(const int plaNum)
	{
		switch (plaNum)
		{
		case Player2:
			return 20.0f;
			break;
		case Player3:
			return 5.0f;
			break;
		case Player4:
			return 10.0f;
			break;
		case TotalPlaNum:
			return 20.0f;
			break;
		}
	}

	Vector3 ResultScene::WhatNumberPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return m_number1Pos;
			break;
		case Player2:
			return m_number2Pos;
			break;
		case Player3:
			return m_number3Pos;
			break;
		case Player4:
			return m_number4Pos;
			break;
		}
	}
}