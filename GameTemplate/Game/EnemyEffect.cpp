///<<summary>
///敵のエフェクト処理
///</summary>

#include "stdafx.h"
#include "EnemyEffect.h"

namespace nsCARBOOM
{
	namespace nsEnemyEffect
	{
		const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };
		const float SHOOTDOWNEFFECT_ROT_RADIAN_VALUE = -1.5708f;	//-９０度
	}

	bool EnemyEffect::Start()
	{
		//敵の最大数繰り返す
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//落下したときの撃墜エフェクトの初期化。
			m_shootDownEffect[eneNum].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
			//大きさ調整
			m_shootDownEffect[eneNum].SetScale(nsEnemyEffect::SHOOTDOWNEFFECT_SCALE);
			//エフェクトが横倒しになっているのでこちらで調整
			Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(nsEnemyEffect::SHOOTDOWNEFFECT_ROT_RADIAN_VALUE);	//X軸を基点に、-1.5708rad(-90°)回転
			m_shootDownEffect[eneNum].SetRotation(m_shootDownEffectRot);
		}

		return true;
	}

	EnemyEffect::~EnemyEffect()
	{

	}

	void EnemyEffect::Update()
	{

	}

	void EnemyEffect::ShootDownEffectPlay(int eneNum)
	{
		//撃墜エフェクト再生開始。
		m_shootDownEffect[eneNum].Play();
		//撃墜エフェクトの位置を敵が落ちた位置に設定
		m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
		//更新
		m_shootDownEffect[eneNum].Update();
	}
}