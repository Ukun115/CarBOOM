#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"


namespace
{

}

bool GameScene::Start()
{
	//プレイヤークラスを追加
	m_player = NewGO<Player>(0);

	//ステージモデルをロード
	m_normalStage = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	m_normalStage->Init("Assets/modelData/bg/stage_00.tkm");

	////フォントクラス
	//m_fontRender = NewGO<FontRender>(1);

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{
	//ステージを削除。
	DeleteGO(m_normalStage);
	//プレイヤークラスを削除。
	DeleteGO(m_player);
	////タイムを削除
	//DeleteGO(m_fontRender);
}

void GameScene::Update()
{
	////ゲーム残り時間を縮めていく。
	//m_timer--;
	//int counttime = m_timer / 60;
	//wchar_t text1[64];
	//swprintf_s(text1, L"%d", counttime);
	//m_fontRender->SetText(text1);
	////0秒になったら、
	//if (counttime == 0)
	//{
	//	//リザルト画面に遷移
	//	NewGO<ResultScene>(0);
	//}

	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}