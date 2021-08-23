///<<summary>
///敵の移動ベクトルを可視化処理(デバック用)
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
			//デバック用のプレイヤースピードの矢印表示
			m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
		}

		return true;
	}

	EnemyMoveSpeedArrow::~EnemyMoveSpeedArrow()
	{
		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			//デバック用のプレイヤースピードの矢印削除
			DeleteGO(m_skinModelRenderArrow[eneNum]);
		}
	}

	void EnemyMoveSpeedArrow::Update()
	{
		for (int eneNum = Enemy1; eneNum < TotalEneNum; eneNum++)
		{
			Vector3 Dir = m_enemy->GetEnemySpeed(eneNum);
			Dir.y = nsStdafx::INT_ZERO;
			Dir.Normalize();//大きさを位置にする
			float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
			Dir.z *= -1;
			float angleX = acosf(x);//アークコサイン
			if (Dir.z < 0) {
				angleX *= -1;
			}
			m_arrowRot[eneNum].SetRotationY(angleX);//ｘ度だけY軸を回す
			m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//角度を設定する
			m_arrowPos[eneNum] = m_enemy->GetEnemyPos(eneNum);
			m_arrowPos[eneNum].y += 30.0f;
			m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
			m_arrowSize[eneNum].x = m_arrowSize[eneNum].z = m_enemy->GetEnemySpeed(eneNum).Length() / 5;
			m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize[eneNum]);
		}
	}
}