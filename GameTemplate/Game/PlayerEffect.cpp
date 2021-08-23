///<<summary>
///�G�̃G�t�F�N�g����
///</summary>

#include "stdafx.h"
#include "PlayerEffect.h"
#include "PlayerTurn.h"
#include "Player.h"

namespace nsCARBOOM
{
	namespace nsPlayerEffect
	{

	}

	bool PlayerEffect::Start()
	{
		m_playerTurn = FindGO<PlayerTurn>(nsStdafx::PLAYERTURN_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			switch (plaNum)
			{
			case Player1:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown0.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet0.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing0.efk");
				break;
			case Player2:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown1.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet1.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing1.efk");
				break;
			case Player3:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown2.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet2.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing2.efk");
				break;
			case Player4:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown3.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet3.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing3.efk");
				break;
			}

			//sprintf(m_filePath, "ShootDown%d", plaNum);
			//m_shootDownEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�
			//sprintf(m_filePath, "Jet%d", plaNum);
			//m_jetEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�
			//sprintf(m_filePath, "Landing%d", plaNum);
			//m_landingEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//�^�ϊ�

			//�G�t�F�N�g�̑傫������
			m_shootDownEffect[plaNum].SetScale({ 70.0f,70.0f,70.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			Quaternion m_shootDownEffectRot = m_shootDownEffect[plaNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708f);	//X������_�ɁA-1.5708rad(-90��)��]
			m_shootDownEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//�G�t�F�N�g�̑傫������
			m_jetEffect[plaNum].SetScale({ 3.0f,3.0f,3.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			m_shootDownEffectRot = m_jetEffect[plaNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-1.5708f);	//X������_�ɁA-1.5708rad(-90��)��]
			m_jetEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//���n�G�t�F�N�g�̑傫������
			m_landingEffect[plaNum].SetScale({ 20.0f,20.0f,20.0f });
		}

		return true;
	}

	PlayerEffect::~PlayerEffect()
	{

	}

	void PlayerEffect::Update()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//�u�[�X�g�G�t�F�N�g�ʒu���v���C���[�ʒu�ɐݒ�
			m_jetEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
			m_jetEffect[plaNum].SetRotation(m_playerTurn->GetPlaRot(plaNum));
			//�X�V
			m_jetEffect[plaNum].Update();
		}
	}

	void PlayerEffect::JetEffectPlay(const int plaNum)
	{
		//�W�F�b�g�G�t�F�N�g�Đ�
		m_jetEffect[plaNum].Play();
	}

	void PlayerEffect::ShootDownEffectPlay(const int plaNum)
	{
		//���ăG�t�F�N�g�Đ��J�n�B
		m_shootDownEffect[plaNum].Play();
		//���ăG�t�F�N�g�̈ʒu���v���C���[���������ʒu�ɐݒ�
		m_shootDownEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
		//�X�V
		m_shootDownEffect[plaNum].Update();
	}

	//�v���C���[�̒��n�G�t�F�N�g���Đ�������֐�
	void PlayerEffect::LandingEffectPlay(const int plaNum)
	{
		if (!m_isLandingOKFlg[plaNum])
		{
			return;
		}
		m_landingEffectDelayTimer[plaNum]++;

		if (m_landingEffectDelayTimer[plaNum] != 40)
		{
			return;
		}
		//���n�G�t�F�N�g�Đ�
		m_landingEffect[plaNum].Play();
		//���n�G�t�F�N�g�̈ʒu���v���C���[�����n�����ʒu�ɐݒ�
		m_landingEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
		//�X�V
		m_landingEffect[plaNum].Update();
		//�t���O������
		m_isLandingOKFlg[plaNum] = false;

		m_landingEffectDelayTimer[plaNum] = nsStdafx::INT_ZERO;
	}

	void PlayerEffect::LandingEffectFlgOn(const int plaNum)
	{
		m_isLandingOKFlg[plaNum] = true;
	}
}