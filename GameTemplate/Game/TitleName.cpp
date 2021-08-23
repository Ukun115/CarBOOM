///<<summary>
///タイトル名のムーブ処理
///</summary>

#include "stdafx.h"
#include "TitleName.h"

namespace nsCARBOOM
{
	namespace nsTitleName
	{

	}

	bool TitleName::Start()
	{
		//タイトル名オブジェクト生成
		for (int titleSpriteNum = TitleSprite1; titleSpriteNum < TotalTitleSpriteNum; titleSpriteNum++)
		{
			m_titleBaraBaraSprite[titleSpriteNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
			sprintf(m_filePath, "TitleName_%d", titleSpriteNum);
			m_titleBaraBaraSprite[titleSpriteNum]->Init(m_filePath, 1600.0f, 800.0f);
			//初めは非表示
			m_titleBaraBaraSprite[titleSpriteNum]->Deactivate();
		}

		return true;
	}

	TitleName::~TitleName()
	{
		for (int titleSpriteNum = TitleSprite1; titleSpriteNum < TotalTitleSpriteNum; titleSpriteNum++)
		{
			DeleteGO(m_titleBaraBaraSprite[titleSpriteNum]);
		}
	}

	void TitleName::Update()
	{
		//タイトル名をウェーブさせる関数
		TitleNameWave();
	}

	//画像が縦移動する関数
	void TitleName::VerticalMove(const int width, const float speed, const int spriteNum)
	{
		if (m_verticalMoveTimer[spriteNum] < width)
		{
			m_titleBaraBaraSpritePos[spriteNum].y += speed;
		}
		else if (m_verticalMoveTimer[spriteNum] < (width * 2))
		{
			m_titleBaraBaraSpritePos[spriteNum].y -= speed;
		}
		else if (m_verticalMoveTimer[spriteNum] > (width * 2))
		{
			//初期化
			m_verticalMoveTimer[spriteNum] = 100;
			m_titleBaraBaraSprite[spriteNum]->SetPosition(Vector3::Zero);
		}

		m_verticalMoveTimer[spriteNum]++;

		m_titleBaraBaraSprite[spriteNum]->SetPosition(m_titleBaraBaraSpritePos[spriteNum]);
	}

	//タイトル名をウェーブさせる関数
	void TitleName::TitleNameWave()
	{
		for (int TitleSpriteNum = TitleSprite1; TitleSpriteNum < TotalTitleSpriteNum; TitleSpriteNum++)
		{
			//表示
			m_titleBaraBaraSprite[TitleSpriteNum]->Activate();
		}

		if (m_waveTimer < 30)
		{
			VerticalMove(10, 4.0f, 0);
		}
		if (5 < m_waveTimer && m_waveTimer < 35)
		{
			VerticalMove(10, 4.0f, 1);
		}
		if (15 < m_waveTimer && m_waveTimer < 45)
		{
			VerticalMove(10, 4.0f, 2);
		}
		if (25 < m_waveTimer && m_waveTimer < 55)
		{
			VerticalMove(10, 4.0f, 3);
		}
		if (35 < m_waveTimer && m_waveTimer < 65)
		{
			VerticalMove(10, 4.0f, 4);
		}
		if (45 < m_waveTimer && m_waveTimer < 75)
		{
			VerticalMove(10, 4.0f, 5);
		}
		if (55 < m_waveTimer && m_waveTimer < 85)
		{
			VerticalMove(10, 4.0f, 6);
		}
		if (65 < m_waveTimer && m_waveTimer < 95)
		{
			VerticalMove(10, 4.0f, 7);
		}
		if (75 < m_waveTimer && m_waveTimer < 105)
		{
			VerticalMove(10, 4.0f, 8);
		}

		//タイマーを初期化
		if (m_waveTimer > 170)
		{
			for (int titleSpriteNum = TitleSprite1; titleSpriteNum < TotalTitleSpriteNum; titleSpriteNum++)
			{
				//初期化
				m_verticalMoveTimer[titleSpriteNum] = 0;
			}
			m_waveTimer = 0;
		}

		m_waveTimer++;
	}
}