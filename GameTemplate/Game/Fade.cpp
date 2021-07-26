#include "stdafx.h"
#include "Fade.h"

//初めにフェードインするかフェードアウトするかはNewGOしたときに自分で設定しましょう
bool Fade::Start()
{
	m_fadeSprite = NewGO<SpriteRender>(PRIORITY_10,nullptr);
	m_fadeSprite->Init("Assets/image/DDS/White.dds", 1500.0f, 1500.0f);
	m_fadeSprite->SetMulColor(FLOAT_ZERO, FLOAT_ZERO, FLOAT_ZERO,m_alphaValue);

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
		m_alphaValue -= 0.03f;
		//完全にフェードインしたら削除
		if (m_alphaValue <= FLOAT_ZERO) {
			DeleteGO(this);
		}
		break;
	case StateOut:
		m_alphaValue += 0.03f;
		//完全に真っ白になったら待機させる
		if (m_alphaValue >= 1.0f) {
			m_nowState = StateWait;
		}
		break;
	}

	m_fadeSprite->SetMulColor(1.0f, 1.0f, 1.0f, m_alphaValue);
}