///<<summary>
///�G�̃G�t�F�N�g����
///</summary>

#include "stdafx.h"
#include "EnemyEffect.h"

namespace nsCARBOOM
{
	namespace nsEnemyEffect
	{
		const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };
		const float SHOOTDOWNEFFECT_ROT_RADIAN_VALUE = -1.5708f;	//-�X�O�x
	}

	bool EnemyEffect::Start()
	{
		//�G�̍ő吔�J��Ԃ�
		for (int eneNum = Enemy1; eneNum < TotalEnemyNum; eneNum++)
		{
			//���������Ƃ��̌��ăG�t�F�N�g�̏������B
			m_shootDownEffect[eneNum].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
			//�傫������
			m_shootDownEffect[eneNum].SetScale(nsEnemyEffect::SHOOTDOWNEFFECT_SCALE);
			//�G�t�F�N�g�����|���ɂȂ��Ă���̂ł�����Œ���
			Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(nsEnemyEffect::SHOOTDOWNEFFECT_ROT_RADIAN_VALUE);	//X������_�ɁA-1.5708rad(-90��)��]
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
		//���ăG�t�F�N�g�Đ��J�n�B
		m_shootDownEffect[eneNum].Play();
		//���ăG�t�F�N�g�̈ʒu��G���������ʒu�ɐݒ�
		m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
		//�X�V
		m_shootDownEffect[eneNum].Update();
	}
}