///<<summary>
///PRESS START BUTTON �̃��[�u����
///</summary>

#include "stdafx.h"
#include "PressStartButton.h"

namespace nsCARBOOM
{
	namespace nsPressStartButton
	{
		const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//�_�ŕ����̕\���ʒu
		const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//�_�ŕ����̑傫��
	}

	bool PressStartButton::Start()
	{
		//PUSH START BUTTON�I�u�W�F�N�g����
		m_pressStartButtonSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressStartButtonSprite->Init("PRESSSTARTBUTTON", 400.0f, 200.0f);
		m_pressStartButtonSprite->SetPosition({ nsPressStartButton::FlashingFont_POS });
		m_pressStartButtonSprite->SetScale({ nsPressStartButton::FlashingFont_SCA });

		return true;
	}

	PressStartButton::~PressStartButton()
	{
		//PUSHSTARTBUTTON���폜�B
		DeleteGO(m_pressStartButtonSprite);
	}

	void PressStartButton::Update()
	{
		if (m_isFlashingFontActiveFlg)
		{
			//�^�C�}�[���Z
			m_flashingFontTimer++;
			//�uPRESS START BUTTON�v�\��
			m_pressStartButtonSprite->Activate();
		}
		else
		{
			//�^�C�}�[���Z
			m_flashingFontTimer--;
			//�uPRESS START BUTTON�v��\��
			m_pressStartButtonSprite->Deactivate();
		}
		//�^�C�}�[��60���傫���l�ɂȂ�ƁA
		if (m_flashingFontTimer > 60)
		{
			//�uPRESS START BUTTON�v���\���ɂ���t���O
			m_isFlashingFontActiveFlg = false;
		}
		//�^�C�}�[��0��菬�����l�ɂȂ�ƁA
		if (m_flashingFontTimer < 10)
		{
			//�uPRESS START BUTTON�v��\������t���O
			m_isFlashingFontActiveFlg = true;
		}
	}
}