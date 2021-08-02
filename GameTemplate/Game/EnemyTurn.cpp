///<<summary>
///敵の回転処理
///</summary>


#include "stdafx.h"
#include "EnemyTurn.h"
#include "Enemy.h"


namespace nsCARBOOM
{
	namespace nsEnemyTurn
	{
		//敵の各リスポーン回転
		const float ENE_RES_ROT_1 = 1.0f;
		const float ENE_RES_ROT_2 = 2.5f;
		const float ENE_RES_ROT_3 = 3.7f;
		const float ENE_RES_ROT_4 = 5.5f;
		const float ENE_RES_ROT_5 = 0.5f;
		const float ENE_RES_ROT_6 = 1.25f;
		const float ENE_RES_ROT_7 = 1.85f;
		const float ENE_RES_ROT_8 = 2.85f;
	}

	bool EnemyTurn::Start()
	{
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);

		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//敵のリスポーン回転
			for (int i = ResRot1; i < TotalResRot; i++)
			{
				m_randEneResAngle[i] = WhatEneRandomResRot(i);
			}

			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			m_rotAngle[eneNum] = m_randEneResAngle[rand() % TotalResRot]; //敵の向き
			m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		}

		return true;
	}


	EnemyTurn::~EnemyTurn()
	{

	}


	void EnemyTurn::Update()
	{

	}


	//敵の回転処理関数
	void EnemyTurn::EneTurn(const int eneNum)
	{
		//fabsf()は浮動小数点の絶対値を返す関数
		if (fabsf(m_enemy->GetEnemySpeed(eneNum).x) < 0.001f && fabsf(m_enemy->GetEnemySpeed(eneNum).z) < 0.001f)
		{
			return;
		}
		//回転角度
		m_rotAngle[eneNum] = atan2(m_enemy->GetEnemySpeed(eneNum).x, m_enemy->GetEnemySpeed(eneNum).z);

		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);

		m_eneDir[eneNum] = m_enemy->GetEnemySpeed(eneNum);
		m_eneDir[eneNum].Normalize();
	}


	//
	float EnemyTurn::WhatEneRandomResRot(const int eneResRotNum)
	{
		switch (eneResRotNum)
		{
		case ResRot1:
			return nsEnemyTurn::ENE_RES_ROT_1;
			break;
		case ResRot2:
			return nsEnemyTurn::ENE_RES_ROT_2;
			break;
		case ResRot3:
			return nsEnemyTurn::ENE_RES_ROT_3;
			break;
		case ResRot4:
			return nsEnemyTurn::ENE_RES_ROT_4;
			break;
		case ResRot5:
			return nsEnemyTurn::ENE_RES_ROT_5;
			break;
		case ResRot6:
			return nsEnemyTurn::ENE_RES_ROT_6;
			break;
		case ResRot7:
			return nsEnemyTurn::ENE_RES_ROT_7;
			break;
		case ResRot8:
			return nsEnemyTurn::ENE_RES_ROT_8;
			break;
		}
	}


	//リスポーン時の向きをランダムにする処理
	void EnemyTurn::EneRespornAngleDecide(const int eneNum)
	{
		//ランダムでリスポーン回転を入れる
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8];
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
	}
}