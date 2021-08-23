///<<summary>
///�G�̈ړ�����
///</summary>

#include "stdafx.h"
#include "EnemyMoveSpeed.h"
#include "Enemy.h"
#include "StageSelectScene.h"
#include "Player.h"
#include "EnemyTurn.h"

namespace nsCARBOOM
{
	bool EnemyMoveSpeed::Start()
	{
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_enemyTurn = FindGO<EnemyTurn>(nsStdafx::ENEMYTURN_NAME);

		return true;
	}

	EnemyMoveSpeed::~EnemyMoveSpeed()
	{

	}

	void EnemyMoveSpeed::Update()
	{

	}

	//�G�̖��C�����֐�
	void EnemyMoveSpeed::EneFriction(const int eneNum)
	{
		//���C�͂�ݒ肷��
		m_friction[eneNum] = m_moveSpeed[eneNum];
		m_friction[eneNum] *= -1.5f;

		///����if���̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�Ɉڂ������B
		//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
		if (m_stageSelectNum == nsStdafx::STAGE3)
		{
			//���C�����炷
			m_friction[eneNum] /= 2.0f;
		}

		//���C�͂����Z����
		m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
	}

	void EnemyMoveSpeed::EneMoveSpeedZero(const int eneNum)
	{
		m_moveSpeed[eneNum] = { Vector3::Zero };
	}

	void EnemyMoveSpeed::EneNormalMove(const int eneNum)
	{
		//����������m_mostShortKyori[0]��5.0f���|���đ��x�ɂ���
		m_moveSpeed[eneNum] = m_enemy->GetMostShortDistanceDir(0) * 5.0f;
	}

	void EnemyMoveSpeed::EneSettenMove(const int eneNum)
	{
		//�ړ_�P�̕������ړ_�Q�̕����ɍs�����𔻕�
		m_moveSpeed[eneNum] = (m_enemy->GetPlayerToSetten1Angle(eneNum) > m_enemy->GetPlayerToSetten2Angle(eneNum)) ? m_enemy->GetEneToSetten1Dir(eneNum) : m_enemy->GetEneToSetten2Dir(eneNum);
		m_moveSpeed[eneNum] *= 5.0f;
	}

	void EnemyMoveSpeed::EneCharge1Move(const int eneNum)
	{
		for (int plaNum = nsStdafx::INT_ZERO; plaNum < m_player->GetPlaNum(); plaNum++)
		{
			m_samDir[eneNum] = m_enemyTurn->GetEneDir(plaNum) * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 20.0f;
		}
	}

	void EnemyMoveSpeed::EneCharge2Move(const int eneNum)
	{
		for (int plaNum = nsStdafx::INT_ZERO; plaNum < m_player->GetPlaNum(); plaNum++)
		{
			m_samDir[eneNum] = m_enemyTurn->GetEneDir(plaNum) * -1.0f + m_player->GetPlaDir(plaNum);
			m_samDir[eneNum].Normalize();
			m_moveSpeed[eneNum] = m_samDir[eneNum] * 30.0f;
		}
	}
}