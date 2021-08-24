///<<summary>
///ステージ選択画面のメイン処理
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Fade.h"
#include "StageSelectScenePlayer.h"

namespace nsCARBOOM
{
	namespace nsStageSelectScene
	{
		const int PLAYER1 = 0;		//プレイヤー１
		const Vector3 FLATSTAGE_MODEL_POS = { 0, 0, 90 };
		const Vector3 DONUTSTAGE_MODEL_POS = { 170, 0, 90 };
		const Vector3 ICESTAGE_MODEL_POS = { 0, 0, -90 };
		const Vector3 WINDSTAGE_MODEL_POS = { 350, 0, 90 };
		const Vector3 TILTSTAGE_MODEL_POS = { 170, 0, -90 };
		const Vector3 RANDOMSTAGE_MODEL_POS = { 350, 0, -90 };
		const Vector3 FLATSTAGE_NAME_POS = { 0, 0, 0 };
		const Vector3 DONUTSTAGE_NAME_POS = { 240, 0, 0 };
		const Vector3 ICESTAGE_NAME_POS = { 0, -250, 0 };
		const Vector3 WINDSTAGE_NAME_POS = { 490, 0, 0 };
		const Vector3 TILTSTAGE_NAME_POS = { 240, -250, 0 };
		const Vector3 RANDOMSTAGE_NAME_POS = { 490, -250, 0 };
		const Vector3 FLATSTAGE_FUKIDASI_POS = { 0, 200, 0 };
		const Vector3 DONUTSTAGE_FUKIDASI_POS = { 235, 200, 0 };
		const Vector3 ICESTAGE_FUKIDASI_POS = { 0, -50, 0 };
		const Vector3 WINDSTAGE_FUKIDASI_POS = { 490, 200, 0 };
		const Vector3 TILTSTAGE_FUKIDASI_POS = { 235, -50, 0 };
		const Vector3 RANDOMSTAGE_FUKIDASI_POS = { 490, -50, 0 };
		const Vector3 STAGE_NAME_SCALEUP = { 1.5f,1.5f,1.5f };	//ステージ名を拡大したときのサイズ
	}

	bool StageSelectScene::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//ライトオブジェクト生成
		m_light = NewGO<Light>(nsStdafx::PRIORITY_0, nsStdafx::LIGHT_NAME);
		//ディレクションライトをセット
		m_light->SetDirectionLightData();
		//半球ライトをセット
		m_light->SetHemiSphereLightData();

		//フェードイン
		m_fade[FadeIn] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeIn]->SetState(StateIn);
		m_fade[FadeIn]->SetAlphaValue(1.0f);

		m_stageSelectScenePlayer = NewGO<StageSelectScenePlayer>(nsStdafx::PRIORITY_0, nullptr);

		//ステージ説明の背景画像オブジェクト生成
		m_stageDiscription[0] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		//ステージ説明のバックスクリーン画像
		m_stageDiscription[0]->Init("Stage0Discription", 500, 600);
		Vector3 m_stageDiscriptionPos = { -400.0f,-20.0f,nsStdafx::FLOAT_ZERO };
		m_stageDiscription[0]->SetPosition(m_stageDiscriptionPos);

		//ステージセレクト文字画像オブジェクト生成
		m_stageSelectSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);

		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			//操作説明の画像オブジェクト生成
			m_operatorDiscription[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			m_operatorDiscription[stageNum]->Init("OperationDiscription", 550, 550);
			//説明文字の表示位置を指定
			m_operatorDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);

			//ステージ説明の背景画像オブジェクト生成
			m_stageDiscription[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			sprintf(m_filePath, "Stage%dDiscription", stageNum);
			m_stageDiscription[stageNum]->Init(m_filePath, 550, 550);
			//位置を指定
			m_stageDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);
			m_stageDiscription[stageNum]->Deactivate();

			//全ステージモデルオブジェクト生成
			m_stage[stageNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_1, nullptr);
			//全ステージスプライトオブジェクト生成
			m_stageName[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		}

		m_stageSelectSprite->Init("STAGESELECT", 750, 375);
		Vector3 m_stageSelectSpritePos = { nsStdafx::FLOAT_ZERO,310.0f,nsStdafx::FLOAT_ZERO };
		m_stageSelectSprite->SetPosition(m_stageSelectSpritePos);

		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			sprintf(m_filePath, "bg/stage_%d_Select", stageNum);
			m_stage[stageNum]->Init(m_filePath);
			sprintf(m_filePath, "Stage%dName", stageNum);
			m_stageName[stageNum]->Init(m_filePath, 200, 100);

			m_stage[stageNum]->SetPosition(WhatStageModelPos(stageNum));
			m_stageName[stageNum]->SetPosition(WhatStageNamePos(stageNum));
		}

		//ステージの上に表示されるA吹き出し
		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			m_Ahukidasi[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			m_Ahukidasi[stageNum]->Init("Ahukidasi", 100, 100);
			m_Ahukidasi[stageNum]->Deactivate();
			m_Ahukidasi[stageNum]->SetPosition(WhatFukidasiPos(stageNum));
		}

		//オブジェクト生成(背景画像)
		m_titleSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		m_titleSprite->Init("BackScreenImage", 1600.0f, 800.0f);

		//タイトルBGMサウンド
		m_soundPlayBack->StageSelectSceneSoundPlayBack(TitleSceneBGM);

		return true;
	}

	StageSelectScene::~StageSelectScene()
	{
		DeleteGO(m_light);

		//表示されているステージモデルとステージ名画像をすべて削除
		for (int stageNum = 0; stageNum < TotalStageNum; stageNum++)
		{
			DeleteGO(m_stage[stageNum]);
			DeleteGO(m_stageName[stageNum]);
		}
		//プレイヤーのスピード可視化矢印を削除。
		//DeleteGO(m_skinModelRenderArrow);
		//背景画像を削除
		DeleteGO(m_titleSprite);
		//A吹き出し画像を削除
		for (int plaNum = FlatStage; plaNum < TotalStageNum; plaNum++)
		{
			DeleteGO(m_Ahukidasi[plaNum]);
		}

		//ステージ選択文字画像
		DeleteGO(m_stageSelectSprite);

		for (int stageDiscriptionNum = 0; stageDiscriptionNum < 7; stageDiscriptionNum++)
		{
			//ステージ説明の画像を削除
			DeleteGO(m_stageDiscription[stageDiscriptionNum]);
			if (stageDiscriptionNum == 0)
			{
				continue;
			}
			//操作説明画像を削除
			DeleteGO(m_operatorDiscription[stageDiscriptionNum]);
		}

		if (m_fade[FadeIn] != nullptr)
			DeleteGO(m_fade[FadeIn]);
		if (m_fade[FadeOutBadk] != nullptr)
			DeleteGO(m_fade[FadeOutBadk]);
		if (m_fade[FadeOutNext] != nullptr)
			DeleteGO(m_fade[FadeOutNext]);

		DeleteGO(m_stageSelectScenePlayer);
	}

	void StageSelectScene::Update()
	{
		TouchStage();

		//セレクトボタンが押されたら、
		if (g_pad[nsStageSelectScene::PLAYER1]->IsTrigger(enButtonSelect))
		{
			//決定サウンド
			m_soundPlayBack->StageSelectSceneSoundPlayBack(DecideSound);

			//フェードアウト
			m_fade[FadeOutBadk] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
			m_fade[FadeOutBadk]->SetState(StateOut);
			m_fade[FadeOutBadk]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

			m_nextTitleSceneFlg = 1;
		}
		if (!m_nextTitleSceneFlg)
		{
			return;
		}
		if (m_fade[FadeOutBadk]->GetNowState() == StateWait)
		{
			m_titleScene = NewGO<TitleScene>(nsStdafx::PRIORITY_0, nullptr);
			DeleteGO(this);
		}
	}

	//ゲーム画面遷移処理関数
	void StageSelectScene::GameSceneTransition()
	{
		if (m_fade[FadeOutNext] == nullptr)
		{
			//Aボタンが押されたら、
			if (g_pad[nsStageSelectScene::PLAYER1]->IsTrigger(enButtonA))
			{
				//ステージ５（ティルトステージ）は未実装のため、ステージに入れないようにreturnしています
				if (m_stageNum == TiltStage)
				{
					return;
				}

				//決定サウンド
				m_soundPlayBack->StageSelectSceneSoundPlayBack(DecideSound);

				//フェードアウト
				m_fade[FadeOutNext] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
				m_fade[FadeOutNext]->SetState(StateOut);
				m_fade[FadeOutNext]->SetAlphaValue(nsStdafx::FLOAT_ZERO);
			}
		}
		else
		{
			if (m_fade[FadeOutNext]->GetNowState() != StateWait)
			{
				return;
			}
			//ランダムステージが選ばれていたら、
			if (m_stageNum == RandomStage)
			{
				//ランダム関数のSEED（種）を設定
				//（これによりランダム値を本当の意味でランダムにしている）
				srand((int)time(nullptr));
				//現在存在するステージの中からランダムで選ぶ(ランダム以外から抽選。)
				m_stageNum = ((rand() % (RandomStage - 1)) + FlatStage);
			}

			//ゲーム画面に遷移
			m_gameScene = NewGO<GameScene>(nsStdafx::PRIORITY_0, nsStdafx::GAMESCENE_NAME);
			//登録された人数データをゲームクラスに渡す
			m_gameScene->SetTotalPlaNum(m_totalPlaNum);
			//ステージなんぼが選ばれているかをゲームクラスに渡す
			m_gameScene->SetSelectStageNum(m_stageNum);
			//クラスの破棄
			DeleteGO(this);
			//ステージセレクトシーンで使われているサウンドを破棄
			m_soundPlayBack->StageSelectSceneDeleteGO();
		}
	}

	//
	Vector3 StageSelectScene::WhatStageModelPos(const int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_MODEL_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_MODEL_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_MODEL_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_MODEL_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_MODEL_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_MODEL_POS;
			break;
		}
	}

	//
	Vector3 StageSelectScene::WhatStageNamePos(int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_NAME_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_NAME_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_NAME_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_NAME_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_NAME_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_NAME_POS;
			break;
		}
	}

	//
	Vector3 StageSelectScene::WhatFukidasiPos(int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_FUKIDASI_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_FUKIDASI_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_FUKIDASI_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_FUKIDASI_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_FUKIDASI_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_FUKIDASI_POS;
			break;
		}
	}

	//ステージの上にいるときそのステージを選択できる関数
	void StageSelectScene::TouchStage()
	{
		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			//プレイヤーと各ステージとの距離を求める
			m_diff[stageNum] = WhatStageModelPos(stageNum) - m_stageSelectScenePlayer->GetPlayerPos();

			//ステージの上に乗っていなかったら
			if (m_diff[stageNum].Length() >= 70.0f)
			{
				//全ての吹き出しを非表示
				m_Ahukidasi[stageNum]->Deactivate();
				//全てのステージ説明文字を非表示
				m_stageDiscription[stageNum]->Deactivate();

				if (m_isOperatorFlg[stageNum] == true)
				{
					//操作説明文表示
					m_operatorDiscription[stageNum]->Activate();
				}
				m_isOperatorFlg[stageNum] = false;

				//通常サイズ
				m_stageName[stageNum]->SetScale(Vector3::One);

				//音を鳴らせる！っていうフラグ復活！
				m_canOnStageSoundPlayFlg[stageNum] = true;
			}
			//ステージの上に乗っていたら
			else
			{
				//A吹き出しを表示
				m_Ahukidasi[stageNum]->Activate();
				//ステージ説明文を表示
				m_stageDiscription[stageNum]->Activate();

				if (m_canOnStageSoundPlayFlg[stageNum])
				{
					//ステージを選択できるようになったら鳴らすサウンド
					m_soundPlayBack->StageSelectSceneSoundPlayBack(OnStageSound);

					m_canOnStageSoundPlayFlg[stageNum] = false;
				}

				for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
				{
					//操作説明文非表示
					m_operatorDiscription[stageNum]->Deactivate();
				}

				//ステージ名画像を強調拡大
				m_stageName[stageNum]->SetScale(nsStageSelectScene::STAGE_NAME_SCALEUP);

				m_isOperatorFlg[stageNum] = true;

				//選択されているステージの番号を決定。
				m_stageNum = stageNum;

				//ゲーム画面遷移処理関数
				GameSceneTransition();
			}
		}
	}
}