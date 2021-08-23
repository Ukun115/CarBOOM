/// <summary>
/// タイトル画面のメイン処理
/// (注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！)
/// </summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"
#include "TitleName.h"
#include "PressStartButton.h"
#include "PressASpeechBalloon.h"
#include "PlayerName.h"

namespace nsCARBOOM
{
	namespace nsTitleScene
	{

	}

	bool TitleScene::Start()
	{
		//フェードイン
		m_fade[FadeIn] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeIn]->SetState(StateIn);
		m_fade[FadeIn]->SetAlphaValue(1.0f);

		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		m_titleName = NewGO<TitleName>(nsStdafx::PRIORITY_0, nullptr);

		m_pressStartButton = NewGO<PressStartButton>(nsStdafx::PRIORITY_0, nullptr);

		m_pressASpeechBalloon = NewGO<PressASpeechBalloon>(nsStdafx::PRIORITY_0, nullptr);

		//タイトル名ジングルサウンド
		m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneGingle);

		//タイトルBGMサウンド
		m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneBGM);

		//タイトルロゴオブジェクト生成
		m_titleSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		m_titleSprite->Init("TitleRogo", 1600.0f, 800.0f);

		m_playerName = NewGO<PlayerName>(nsStdafx::PRIORITY_0, nullptr);

		return true;
	}

	TitleScene::~TitleScene()
	{
		DeleteGO(m_titleName);

		DeleteGO(m_titleName);

		DeleteGO(m_pressStartButton);

		DeleteGO(m_pressASpeechBalloon);

		//タイトルロゴを削除。
		DeleteGO(m_titleSprite);

		for (int fadeNum = FadeIn; fadeNum < TotalFadeNum; fadeNum++)
		{
			DeleteGO(m_fade[fadeNum]);
		}
	}

	void TitleScene::Update()
	{
		//プレイヤーを登録する
		AddPlayer();

		if (m_fade[FadeOut] == nullptr)
		{
			//登録されている誰かのスタートボタンが押されたら、
			for (unsigned int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				//スタートボタンが押されたときの処理関数
				PushStartButton(plaNum);
				//ボタンが押されたときの処理関数
				PushSelectButton(plaNum);
			}
		}
		else
		{
			//選択された次のシーンに行く処理関数
			NextScene();
		}
	}

	//プレイヤーを追加する関数
	void TitleScene::AddPlayer()
	{
		//登録されたプレイヤー数が最大数4人になるまで追加できる
		if (m_totalPlaNum == TotalPlaNum)
		{
			return;
		}
		/*登録されていないコントローラーのAボタンが押されたら、
		【注意】USBポートに繋がれた順じゃないと登録されていきません。*/
		if (!g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
		{
			return;
		}
		//エンジンサウンド
		m_soundPlayBack->TitleSceneSoundPlayBack(EngineSound);

		//新規プレイヤーの追加フラグを真に。
		m_playerName->AddPlayerFlgOn(m_totalPlaNum);

		//アクティブ化したプレイヤーの名前のカラーチェンジ
		m_playerName->ColorChange(m_totalPlaNum);

		//吹き出しのポジション変更
		m_pressASpeechBalloon->NextState(m_totalPlaNum);

		//次のプレイヤーへ
		m_totalPlaNum++;
	}

	//ステージ選択画面に遷移する関数
	void TitleScene::StageSelectSceneTransition()
	{
		//ステージ選択画面に遷移
		m_stageSelectScene = NewGO<StageSelectScene>(nsStdafx::PRIORITY_0, nullptr);
		//登録された人数データを次のクラスに渡す
		m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);
		//このクラスの削除
		DeleteGO(this);
		//タイトルシーンで使われるサウンドを破棄
		m_soundPlayBack->TitleSceneDeleteGO();
	}

	//スタートボタンが押されたときの処理関数
	void TitleScene::PushStartButton(int plaNum)
	{
		//スタートボタンが押されたら、
		if (!g_pad[plaNum]->IsTrigger(enButtonStart))
		{
			return;
		}
		//決定サウンド
		m_soundPlayBack->TitleSceneSoundPlayBack(DecideSound);

		//フェードアウト
		m_fade[FadeOut] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeOut]->SetState(StateOut);
		m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

		m_nextScene = StateSelectScene;
	}

	//ボタンが押されたときの処理関数
	void TitleScene::PushSelectButton(int plaNum)
	{
		//セレクトボタンが押されたら、、
		if (!g_pad[plaNum]->IsTrigger(enButtonSelect))
		{
			return;
		}
		//フェードアウト
		m_fade[FadeOut] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeOut]->SetState(StateOut);
		m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

		m_nextScene = GameEnd;
	}

	//選択された次のシーンに行く処理関数
	void TitleScene::NextScene()
	{
		//真っ白になったら遷移
		if (m_fade[FadeOut]->GetNowState() != StateWait)
		{
			return;
		}
		switch (m_nextScene)
		{
		case StateSelectScene:
			//ステージ選択画面に遷移
			StageSelectSceneTransition();
			break;
		case GameEnd:
			//exeを閉じてゲーム終了
			exit(EXIT_SUCCESS);
			//メモ//
			//exit(EXIT_FAILURE);は異常終了		EXIT_FAILURE = 1
			//exit(EXIT_SUCCESS);は正常終了		EXIT_SUCCESS = 0
			break;
		}
	}
}