#include "stdafx.h"
#include "ResultScene.h"

namespace
{

}

bool ResultScene::Start()
{
	//リザルト文字画像を初期化。
	m_resultSprite = NewGO<SpriteRender>(0);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 300.0f, 300.0f);

	//Start関数のreturn文
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_resultSprite);
}

void ResultScene::Update()
{
	//1Pのセレクトボタン(キーボード：スペース)が押されたら、
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//exeを閉じてゲーム終了
		exit(EXIT_SUCCESS);
	}
}