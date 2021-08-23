///<<summary>
///PRESS START BUTTON のムーブ処理
///</summary>

#include "stdafx.h"
#include "PressStartButton.h"

namespace nsCARBOOM
{
	namespace nsPressStartButton
	{
		const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//点滅文字の表示位置
		const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//点滅文字の大きさ
	}

	bool PressStartButton::Start()
	{
		//PUSH START BUTTONオブジェクト生成
		m_pressStartButtonSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressStartButtonSprite->Init("PRESSSTARTBUTTON", 400.0f, 200.0f);
		m_pressStartButtonSprite->SetPosition({ nsPressStartButton::FlashingFont_POS });
		m_pressStartButtonSprite->SetScale({ nsPressStartButton::FlashingFont_SCA });

		return true;
	}

	PressStartButton::~PressStartButton()
	{
		//PUSHSTARTBUTTONを削除。
		DeleteGO(m_pressStartButtonSprite);
	}

	void PressStartButton::Update()
	{
		if (m_isFlashingFontActiveFlg)
		{
			//タイマー加算
			m_flashingFontTimer++;
			//「PRESS START BUTTON」表示
			m_pressStartButtonSprite->Activate();
		}
		else
		{
			//タイマー減算
			m_flashingFontTimer--;
			//「PRESS START BUTTON」非表示
			m_pressStartButtonSprite->Deactivate();
		}
		//タイマーが60より大きい値になると、
		if (m_flashingFontTimer > 60)
		{
			//「PRESS START BUTTON」を非表示にするフラグ
			m_isFlashingFontActiveFlg = false;
		}
		//タイマーが0より小さい値になると、
		if (m_flashingFontTimer < 10)
		{
			//「PRESS START BUTTON」を表示するフラグ
			m_isFlashingFontActiveFlg = true;
		}
	}
}