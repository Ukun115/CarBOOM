///<<summary>
///�G�̈ړ��x�N�g������������(�f�o�b�N�p)
///</summary>

#include "stdafx.h"
#include "EnemyMoveSpeedArrow.h"
#include "Enemy.h"

namespace nsCARBOOM
{
	namespace nsEnemyMoveSpeedArrow
	{

	}

	bool EnemyMoveSpeedArrow::Start()
	{
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);

		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
			m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
		}

		return true;
	}

	EnemyMoveSpeedArrow::~EnemyMoveSpeedArrow()
	{
		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��폜
			DeleteGO(m_skinModelRenderArrow[eneNum]);
		}
	}

	void EnemyMoveSpeedArrow::Update()
	{
		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			Vector3 Dir = m_enemy->GetEnemySpeed(eneNum);
			Dir.y = nsStdafx::INT_ZERO;
			Dir.Normalize();//�傫�����ʒu�ɂ���
			float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
			Dir.z *= -1;
			float angleX = acosf(x);//�A�[�N�R�T�C��
			if (Dir.z < 0) {
				angleX *= -1;
			}
			m_arrowRot[eneNum].SetRotationY(angleX);//���x����Y������
			m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//�p�x��ݒ肷��
			m_arrowPos[eneNum] = m_enemy->GetEnemyPos(eneNum);
			m_arrowPos[eneNum].y += 30.0f;
			m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
			m_arrowSize[eneNum].x = m_arrowSize[eneNum].z = m_enemy->GetEnemySpeed(eneNum).Length() / 5;
			m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize[eneNum]);
		}
	}
}