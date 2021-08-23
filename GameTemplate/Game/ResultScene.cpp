///<<summary>
///リザルト画面のメイン処理
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "Ranking.h"

namespace nsCARBOOM
{
	namespace nsResultScene
	{
		const float RESULT_SPRITE_WIDTH = 600.0f;
		const float RESULT_SPRITE_HEIGHT = 300.0f;
		const float RESULT_SPRITE_POS_Y = 160.0f;
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

		m_ranking = NewGO<Ranking>(nsStdafx::PRIORITY_0, nullptr);
		m_ranking->SetTotalPlaNum(m_totalPlaNum);

		//リザルト文字画像オブジェクト生成
		m_resultSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_6, nullptr);
		m_resultSprite->Init("Result", nsResultScene:: RESULT_SPRITE_WIDTH, nsResultScene::RESULT_SPRITE_HEIGHT);
		Vector3 m_resSprPos = { nsStdafx::FLOAT_ZERO,nsResultScene::RESULT_SPRITE_POS_Y,nsStdafx::FLOAT_ZERO };
		m_resultSprite->SetPosition(m_resSprPos);

		return true;
	}

	ResultScene::~ResultScene()
	{
		//順位画像の削除。
		DeleteGO(m_resultSprite);

		DeleteGO(m_fadeOut);

		DeleteGO(m_ranking);
	}

	void ResultScene::Update()
	{
		//ゲーム終了処理
		SelectScene();
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

				//ゲームシーンクラスを削除するようにフラグをオン
				m_gameScene->SetDeleteFlg(true);

				m_muriFlg = true;
				break;
			}
		}
	}
}