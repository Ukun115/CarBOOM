///<<summary>
///�G�̃p�g�����v����
///</summary>

#include "stdafx.h"
#include "EnemyPatoLump.h"
#include "Light.h"
#include "Enemy.h"

namespace nsCARBOOM
{
	namespace nsEnemyPatoLump
	{
		const float POILIG_RANGE = 50.0f;	//�|�C���g���C�g�̉e���͈�
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

	//�p�g�����v���p�g�J�[�̏�ɃZ�b�g����֐�
	void EnemyPatoLump::Update()
	{
		//�|�[�Y���̂Ƃ��A�b�v�f�[�g������S�Ď~�߂�
		if (m_isPauseFlg)
		{
			return;
		}

		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//�ԃ|�C���g���C�g��ݒ�
			m_enePoiLigPos = m_enemy->GetEnemyPos(eneNum);
			m_enePoiLigPos.x -= nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_enePoiLigPos.y += nsEnemyPatoLump::PATORAMPU_POS_SHIFT;
			m_light->SetPointLightData(m_enePoiLigPos, nsStdafx::RED, nsEnemyPatoLump::POILIG_RANGE, m_poiLigNum);
			m_poiLigNum++;
			//�|�C���g���C�g��ݒ�
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