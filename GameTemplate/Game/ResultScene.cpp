#include "stdafx.h"
#include "ResultScene.h"

namespace
{

}

bool ResultScene::Start()
{
	//サンプル背景画像を初期化。
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
	m_spriteRender->SetPosition(Vector3::Zero);

	//Start関数のreturn文
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_spriteRender);
}

void ResultScene::Update()
{
	//Aボタン(キーボード：J)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//exeを閉じてゲーム終了
		exit(EXIT_SUCCESS);
	}
}