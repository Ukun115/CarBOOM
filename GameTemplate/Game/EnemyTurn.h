///<<summary>
///�G�̉�]����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class EnemyMoveSpeed;

	class EnemyTurn : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		enum enEnemyNum
		{
			Enemy1,
			TotalEneNum = 6
		};

		//�G�̃��X�|�[�����̃����_������
		enum enRandomEneRespornRot
		{
			ResRot1,
			ResRot2,
			ResRot3,
			ResRot4,
			ResRot5,
			ResRot6,
			ResRot7,
			ResRot8,
			TotalResRot
		};

		EnemyMoveSpeed* m_enemyMoveSpeed = nullptr;

		bool Start()override final;
		void Update()override final;
		~EnemyTurn()override final;

		//
		float WhatEneRandomResRot(const int eneNum);

		Quaternion m_rot[TotalEneNum];			//�G�U�̕��̓G�̉�]
		float m_rotAngle[TotalEneNum] = { nsStdafx::FLOAT_ZERO };			//�G�U�̕��̉�]�p�x
		Vector3 m_eneDir[TotalEneNum];			//����
		float m_randEneResAngle[TotalResRot] = { nsStdafx::FLOAT_ZERO };		//�G�̃��X�|�[����]�p�x4����

	public:
		//�G�̉�]�����֐�
		void EneTurn(const int eneNum);
		//���X�|�[�����̌����������_���ɂ��鏈��
		void EneRespornAngleDecide(const int eneNum);
		Quaternion GetEneRot(const int eneNum)const { return m_rot[eneNum]; }
		Vector3 GetEneDir(const int eneNum)const { return m_eneDir[eneNum]; }
	};
}