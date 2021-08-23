///<<summary>
///敵のエフェクト処理
///</summary>

#include "stdafx.h"
#include "PlayerEffect.h"
#include "PlayerTurn.h"
#include "Player.h"

namespace nsCARBOOM
{
	namespace nsPlayerEffect
	{

	}

	bool PlayerEffect::Start()
	{
		m_playerTurn = FindGO<PlayerTurn>(nsStdafx::PLAYERTURN_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			switch (plaNum)
			{
			case Player1:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown0.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet0.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing0.efk");
				break;
			case Player2:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown1.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet1.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing1.efk");
				break;
			case Player3:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown2.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet2.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing2.efk");
				break;
			case Player4:
				m_shootDownEffect[plaNum].Init(u"Assets/effect/efk/ShootDown3.efk");
				m_jetEffect[plaNum].Init(u"Assets/effect/efk/Jet3.efk");
				m_landingEffect[plaNum].Init(u"Assets/effect/efk/Landing3.efk");
				break;
			}

			//sprintf(m_filePath, "ShootDown%d", plaNum);
			//m_shootDownEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//型変換
			//sprintf(m_filePath, "Jet%d", plaNum);
			//m_jetEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//型変換
			//sprintf(m_filePath, "Landing%d", plaNum);
			//m_landingEffect[plaNum].Init(reinterpret_cast<const char16_t*>(m_filePath));	//型変換

			//エフェクトの大きさ調整
			m_shootDownEffect[plaNum].SetScale({ 70.0f,70.0f,70.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			Quaternion m_shootDownEffectRot = m_shootDownEffect[plaNum].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708f);	//X軸を基点に、-1.5708rad(-90°)回転
			m_shootDownEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//エフェクトの大きさ調整
			m_jetEffect[plaNum].SetScale({ 3.0f,3.0f,3.0f });
			//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
			m_shootDownEffectRot = m_jetEffect[plaNum].GetRotation();
			//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
			m_shootDownEffectRot.AddRotationX(-1.5708f);	//X軸を基点に、-1.5708rad(-90°)回転
			m_jetEffect[plaNum].SetRotation(m_shootDownEffectRot);

			//着地エフェクトの大きさ調整
			m_landingEffect[plaNum].SetScale({ 20.0f,20.0f,20.0f });
		}

		return true;
	}

	PlayerEffect::~PlayerEffect()
	{

	}

	void PlayerEffect::Update()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//ブーストエフェクト位置をプレイヤー位置に設定
			m_jetEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
			m_jetEffect[plaNum].SetRotation(m_playerTurn->GetPlaRot(plaNum));
			//更新
			m_jetEffect[plaNum].Update();
		}
	}

	void PlayerEffect::JetEffectPlay(const int plaNum)
	{
		//ジェットエフェクト再生
		m_jetEffect[plaNum].Play();
	}

	void PlayerEffect::ShootDownEffectPlay(const int plaNum)
	{
		//撃墜エフェクト再生開始。
		m_shootDownEffect[plaNum].Play();
		//撃墜エフェクトの位置をプレイヤーが落ちた位置に設定
		m_shootDownEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
		//更新
		m_shootDownEffect[plaNum].Update();
	}

	//プレイヤーの着地エフェクトを再生させる関数
	void PlayerEffect::LandingEffectPlay(const int plaNum)
	{
		if (!m_isLandingOKFlg[plaNum])
		{
			return;
		}
		m_landingEffectDelayTimer[plaNum]++;

		if (m_landingEffectDelayTimer[plaNum] != 40)
		{
			return;
		}
		//着地エフェクト再生
		m_landingEffect[plaNum].Play();
		//着地エフェクトの位置をプレイヤーが着地した位置に設定
		m_landingEffect[plaNum].SetPosition(m_player->GetPlaPos(plaNum));
		//更新
		m_landingEffect[plaNum].Update();
		//フラグをおる
		m_isLandingOKFlg[plaNum] = false;

		m_landingEffectDelayTimer[plaNum] = nsStdafx::INT_ZERO;
	}

	void PlayerEffect::LandingEffectFlgOn(const int plaNum)
	{
		m_isLandingOKFlg[plaNum] = true;
	}
}