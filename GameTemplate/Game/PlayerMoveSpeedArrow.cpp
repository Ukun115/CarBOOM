///<<summary>
///�v���C���[�̈ړ��x�N�g������������(�f�o�b�N�p)
///</summary>


#include "stdafx.h"
#include "PlayerMoveSpeedArrow.h"
#include "Player.h"


namespace nsCARBOOM
{
	bool PlayerMoveSpeedArrow::Start()
	{
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);

		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
			m_skinModelRenderArrow[i] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
		}

		return true;
	}


	PlayerMoveSpeedArrow::~PlayerMoveSpeedArrow()
	{
		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��폜
			DeleteGO(m_skinModelRenderArrow[i]);
		}
	}


	void PlayerMoveSpeedArrow::Update()
	{
		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			Vector3 Dir = m_player->GetPlaSpeed(i);
			Dir.y = nsStdafx::INT_ZERO;
			Dir.Normalize();//�傫�����ʒu�ɂ���
			float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
			Dir.z *= -1;
			float angleX = acosf(x);//�A�[�N�R�T�C��
			if (Dir.z < 0) {
				angleX *= -1;
			}
			//angleX -= 0.5 * PAI;
			m_arrowRot[i].SetRotationY(angleX);//���x����Y������
			m_skinModelRenderArrow[i]->SetRotation(m_arrowRot[i]);//�p�x��ݒ肷��
			m_arrowPos[i] = m_player->GetPlaPos(i);
			m_arrowPos[i].y += 30.0f;
			m_skinModelRenderArrow[i]->SetPosition(m_arrowPos[i]);
			m_arrowSize[i].x = m_arrowSize[i].z = m_player->GetPlaSpeed(i).Length() / 5;
			m_skinModelRenderArrow[i]->SetScale(m_arrowSize[i]);
		}
	}
}