///<<summary>
///PressA!!�����o���摜�̃��[�u����
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
		//PRESS A !! �����o���摜�I�u�W�F�N�g����
		m_pressASpeechBalloon = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressASpeechBalloonArrow = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		m_pressASpeechBalloon->Init("PRESS A !!", 400.0f, 200.0f);
		m_pressASpeechBalloonArrow->Init("PRESS A !!Arrow", 200.0f, 100.0f);

		//�����ʒu�ݒ�
		//2P�̍���
		m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER2_POS;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x += 75.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
		//�傫������
		m_pressASpeechBalloon->SetScale({ 0.5f,0.5f,0.5f });

		return true;
	}

	PressASpeechBalloon::~PressASpeechBalloon()
	{
		//�����o�����폜�B
		if(m_pressASpeechBalloon != nullptr)
		DeleteGO(m_pressASpeechBalloon);
		if (m_pressASpeechBalloonArrow != nullptr)
		DeleteGO(m_pressASpeechBalloonArrow);
	}

	void PressASpeechBalloon::Update()
	{
		//�����o���̖��摜�����ړ�����֐�

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
			//������
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
			//3P�̉E��
			m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER3_POS;
			m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos.x -= 105.0f;
			m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
			//���]������
			m_arrowSca = { -1.0f,-1.0f,-1.0f };
			m_pressASpeechBalloonArrow->SetScale(m_arrowSca);
			break;

		case Player4SidePos:
			//4P�̍���
			m_pressASpeechBalloonPos = nsPressASpeechBalloon::PRESSASPEECHBALLOON_PLAYER4_POS;
			m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
			m_pressASpeechBalloonPos.x += 80.0f;
			m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
			//���ɖ߂�
			m_pressASpeechBalloonArrow->SetScale(Vector3::One);
			break;

		case Delete:
			//�����o�����폜�B
			DeleteGO(m_pressASpeechBalloon);
			DeleteGO(m_pressASpeechBalloonArrow);
			break;
		}
	}
}