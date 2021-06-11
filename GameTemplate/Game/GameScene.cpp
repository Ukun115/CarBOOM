#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"


namespace
{
	const Vector2 TIMEFONT_POS = {-40.0f,300.0f};			//制限時間フォントの位置
	const Vector4 TIMEFONT_COL = {1.0f,1.0f,1.0f,1.0f};		//制限時間フォントの色
	const float   TIMEFONT_ROT = 0.0f;						//制限時間フォントの傾き
	const float   TIMEFONT_SCA = 1.5f;						//制限時間フォントの拡大率
	const Vector2   TIMEFONT_PIV = { 0.0f,0.0f };			//制限時間フォントの基点
}

bool GameScene::Start()
{
	//プレイヤークラス
	m_player = NewGO<Player>(0);

	//ステージモデル
	m_normalStage = NewGO<SkinModelRender>(0);
	//モデルのファイルパスを設定。
	m_normalStage->Init("Assets/modelData/bg/stage_00.tkm");

	//フォントクラス（一番上のレイヤーに置きたいのでプライオリティーは最高値）
	m_fontRender = NewGO<FontRender>(1);
	//初期設定。
	m_fontRender->Init
	(
		L"",
		TIMEFONT_POS,	//位置
		TIMEFONT_COL,	//カラー
		TIMEFONT_ROT,	//傾き
		TIMEFONT_SCA,	//拡大率
		TIMEFONT_PIV	//基点
	);
	//文字の境界線表示
	m_fontRender->SetShadowParam(true, 1.0f, Vector4::Black);

	//Start関数のreturn
	return true;
}

GameScene::~GameScene()
{
	//ステージを削除。
	DeleteGO(m_normalStage);
	//プレイヤークラスを削除。
	DeleteGO(m_player);
	//タイムを削除
	DeleteGO(m_fontRender);
}

void GameScene::Update()
{
	//制限時間を縮めていく。
	m_timer--;
	int counttime = m_timer / 60;
	wchar_t text1[64];
	swprintf_s(text1, L"%d", counttime);
	//画面表示
	m_fontRender->SetText(text1);

	//制限時間が0秒になったら、
	if (counttime == 0)
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
	}

	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//リザルト画面に遷移
		NewGO<ResultScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}