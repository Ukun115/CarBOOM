#include "stdafx.h"
#include "Fade.h"

namespace nsCARBOOM
{
	namespace nsFade
	{
		const float FADE_IMAGE_SIZE = 1500.0f;

		const float FADE_SPEED = 0.03f;

		const float ALL_WHITE = 1.0f;
	}


	//フェードイン用かフェードアウト用かのステートはNewGOしたときに自分で設定しましょう
	bool Fade::Start()
	{
		m_fadeSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_10, nullptr);
		m_fadeSprite->Init("White", nsFade::FADE_IMAGE_SIZE, nsFade::FADE_IMAGE_SIZE);
		m_fadeSprite->SetMulColor(nsStdafx::FLOAT_ZERO, nsStdafx::FLOAT_ZERO, nsStdafx::FLOAT_ZERO, m_alphaValue);

		return true;
	}


	Fade::~Fade()
	{
		DeleteGO(m_fadeSprite);
	}


	void Fade::Update()
	{
		switch (m_nowState)
		{
		case StateIn:
			m_alphaValue -= nsFade::FADE_SPEED;
			//完全にフェードインしたら削除
			if (m_alphaValue <= nsStdafx::FLOAT_ZERO) {
				DeleteGO(this);
			}
			break;
		case StateOut:
			m_alphaValue += nsFade::FADE_SPEED;
			//完全に真っ白になったら待機させる
			if (m_alphaValue >= nsFade::ALL_WHITE) {
				m_nowState = StateWait;
			}
			break;
		}

		m_fadeSprite->SetMulColor(1.0f, 1.0f, 1.0f, m_alphaValue);
	}
}