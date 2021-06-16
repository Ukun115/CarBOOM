#include "stdafx.h"
#include "ResultScene.h"

namespace
{
	const Vector3 NUMBER1_POS = { 150.0f,50.0f,0.0f };
	const Vector3 NUMBER2_POS = { 150.0f,-50.0f,0.0f };
	const Vector3 NUMBER3_POS = { 150.0f,-150.0f,0.0f };
	const Vector3 NUMBER4_POS = { 150.0f,-250.0f,0.0f };
}

bool ResultScene::Start()
{
	//リザルト文字画像を初期化。
	m_resultSprite = NewGO<SpriteRender>(2, nullptr);
	m_resultSprite->Init("Assets/image/DDS/Result.dds", 600.0f, 300.0f);
	Vector3 m_resSprPos = { 0.0f,160.0f,0.0f };
	m_resultSprite->SetPosition(m_resSprPos);

	//プレイヤー文字画像を初期化。
	for (int i = 0; i < 4; i++)
	{
		m_plaNum[i] = NewGO<SpriteRender>(2, nullptr);
		if (i == 0)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player1_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER1_POS);
		}
		if (i == 1)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player2_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER2_POS);
		}
		if (i == 2)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player3_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER3_POS);
		}
		if (i == 3)
		{
			m_plaNum[i]->Init("Assets/image/DDS/Player4_ActiveName.dds", 340.0f, 170.0f);
			m_plaNum[i]->SetPosition(NUMBER4_POS);
		}
	}

	//Start関数のreturn文
	return true;
}

ResultScene::~ResultScene()
{
	DeleteGO(m_resultSprite);

	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_plaNum[i]);
	}
}

void ResultScene::Update()
{
	//セレクトボタン(キーボード：スペース)が押されたら、
	for (int i = 0; i < 4; i++) {
		if (g_pad[i]->IsTrigger(enButtonSelect))
		{
			//exeを閉じてゲーム終了
			exit(EXIT_SUCCESS);
		}
	}
}