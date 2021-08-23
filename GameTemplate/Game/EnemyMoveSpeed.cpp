///<<summary>
///敵の移動処理
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

	//敵の摩擦処理関数
	void EnemyMoveSpeed::EneFriction(const int eneNum)
	{
		//摩擦力を設定する
		m_friction[eneNum] = m_moveSpeed[eneNum];
		m_friction[eneNum] *= -1.5f;

		///下のif文はステージの処理なのでステージクラスに移したい。
		//アイスステージが選択されているとき、
		if (m_stageSelectNum == nsStdafx::STAGE3)
		{
			//摩擦を減らす
			m_friction[eneNum] /= 2.0f;
		}

		//摩擦力を加算する
		m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
	}

	void EnemyMoveSpeed::EneMoveSpeedZero(const int eneNum)
	{
		m_moveSpeed[eneNum] = { Vector3::Zero };
	}

	void EnemyMoveSpeed::EneNormalMove(const int eneNum)
	{
		//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
		m_moveSpeed[eneNum] = m_enemy->GetMostShortDistanceDir(0) * 5.0f;
	}

	void EnemyMoveSpeed::EneSettenMove(const int eneNum)
	{
		//接点１の方向か接点２の方向に行くかを判別
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