///<<summary>
///PressA!!吹き出し画像のムーブ処理
///</summary>

#include "stdafx.h"
#include "PressASpeechBalloon.h"

namespace nsCARBOOM
{
	namespace nsPressASpeechBalloon
	{
		const Vector3 PRESSASPEECHBALLOON_PLAYER2_POS = { 300.0f,280.0f,0 };
		const Vector3 PRESSASPEECHBALLOON_PLAYER3_POS = { -270.0f,-315,0 };
		const Vector3 PRESSASPEECHBALLOON_PLAYER4_POS = { 300.0f,-315.0f,0 };
	}

	bool PressASpeechBalloon::Start()
	{
		//PRESS A !! 吹き出し画像オブジェクト生成
		m_pressASpeechBalloon = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressASpeechBalloonArrow = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressASpeechBalloon->Init("PRESS A !!", 400.0f, 200.0f);
		m_pressASpeechBalloonArrow->Init("PRESS A !!Arrow", 200.0f, 100.0f);

		//初期位置設定
		//2Pの左側
		m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER2_POS;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x += 75.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
		//大きさ調整
		m_pressASpeechBalloon->SetScale({ 0.5f,0.5f,0.5f });

		return true;
	}

	PressASpeechBalloon::~PressASpeechBalloon()
	{
		//吹き出しを削除。
		if(m_pressASpeechBalloon != nullptr)
		DeleteGO(m_pressASpeechBalloon);
		if (m_pressASpeechBalloonArrow != nullptr)
		DeleteGO(m_pressASpeechBalloonArrow);
	}

	void PressASpeechBalloon::Update()
	{
		//吹き出しの矢印画像が横移動する関数

		if (m_sideMoveTimer < 60)
		{
			m_pressASpeechBalloonPos.x += 0.2f;
		}
		else if (m_sideMoveTimer < 60 * 2)
		{
			m_pressASpeechBalloonPos.x -= 0.2f;
		}
		else
		{
			//初期化
			m_sideMoveTimer = 0;
		}

		m_sideMoveTimer++;

		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
	}

	void PressASpeechBalloon::NextState(const int nowState)
	{
		switch (nowState)
		{
		case Player3SidePos:
			//3Pの右側
			m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER3_POS;
			m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos.x -= 105.0f;
			m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
			//反転させる
			m_arrowSca = { -1.0f,-1.0f,-1.0f };
			m_pressASpeechBalloonArrow->SetScale(m_arrowSca);
			break;

		case Player4SidePos:
			//4Pの左側
			m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER4_POS;
			m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos.x += 80.0f;
			m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
			//元に戻す
			m_pressASpeechBalloonArrow->SetScale(Vector3::One);
			break;

		case Delete:
			//吹き出しを削除。
			DeleteGO(m_pressASpeechBalloon);
			DeleteGO(m_pressASpeechBalloonArrow);
			break;
		}
	}
}