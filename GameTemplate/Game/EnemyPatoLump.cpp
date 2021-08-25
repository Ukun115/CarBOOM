///<<summary>
///敵のパトランプ処理
///</summary>

#include "stdafx.h"
#include "EnemyPatoLump.h"
#include "Light.h"
#include "Enemy.h"

namespace nsCARBOOM
{
	namespace nsEnemyPatoLump
	{
		const float POILIG_RANGE = 50.0f;	//ポイントライトの影響範囲
		const float PATORAMPU_POS_SHIFT = 10.0f;
	}

	bool EnemyPatoLump::Start()
	{
		m_light = FindGO<Light>(nsStdafx::LIGHT_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);

		return true;
	}

	EnemyPatoLump::~EnemyPatoLump()
	{

	}

	//パトランプをパトカーの上にセットする関数
	void EnemyPatoLump::Update()
	{
		//ポーズ中のときアップデート処理を全て止める
		if (m_isPauseFlg)
		{
			return;
		}

		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//赤ポイントライトを設定
			m_enePoiLigPos = m_enemy->GetEnemyPos(eneNum);
			m_enePoiLigPos.x -= nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_enePoiLigPos.y += nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::RED, nsEnemyPatoLump::POILIG_RANGE, m_poiLigNum);
			m_poiLigNum++;
			//青ポイントライトを設定
			m_enePoiLigPos = m_enemy->GetEnemyPos(eneNum);
			m_enePoiLigPos.x += nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_enePoiLigPos.y += nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::BLUE, nsEnemyPatoLump::POILIG_RANGE, m_poiLigNum);
			m_poiLigNum++;
		}
	}


	void EnemyPatoLump::PoiLigNumInit()
	{
		m_poiLigNum = nsStdafx::INT_ZERO;
	}
}