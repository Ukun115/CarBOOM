#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


bool TitleScene::Start()
{
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
	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//ゲーム画面に遷移
		NewGO<GameScene>(0);
		//このクラスの削除
		DeleteGO(this);
	}
}