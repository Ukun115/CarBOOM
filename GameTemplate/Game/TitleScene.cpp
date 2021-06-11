#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{
	const int PLAYER1   = 0;
	const int MAXPLAYERNUM = 4;
}

bool TitleScene::Start()
{
	//1Pは無条件で追加フラグを真に。
	addPlayer[PLAYER1] = true;

	//サンプル背景画像を初期化。
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/eheheNS.dds", 1300.0f, 750.0f);
	m_spriteRender->SetPosition(Vector3::Zero);

	//Start関数のreturn文
	return true;
}

TitleScene::~TitleScene()
{
	DeleteGO(m_spriteRender);
}

void TitleScene::Update()
{

	//プレイヤーを追加する
	if(m_totalPlayerNum != MAXPLAYERNUM)
	{
		//登録されていないコントローラーのスタートボタンが押されたら、
		if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonStart))
		{
			//新規プレイヤーの追加フラグを真に。
			addPlayer[m_totalPlayerNum] = true;

			m_totalPlayerNum++;
		}
	}

	//1Pのスタートボタン(キーボード：J)が押されたらゲーム開始
	if (g_pad[PLAYER1]->IsTrigger(enButtonStart))
	{
		//ゲーム画面に遷移
		NewGO<GameScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}

}