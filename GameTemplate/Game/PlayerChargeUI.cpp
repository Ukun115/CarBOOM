///<<summary>
///プレイヤーのチャージ攻撃UI処理
///</summary>


#include "stdafx.h"
#include "PlayerChargeUI.h"
#include "Player.h"


namespace nsCARBOOM
{
	namespace nsPlayerChargeUI
	{
		const float CHARGE1_MOVESPEED = 6.0f;
		const float CHARGE2_MOVESPEED = 3.0f;
	}


	bool PlayerChargeUI::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//各プレイヤーの２段階溜め攻撃のUI
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			for (int chargeUINum = ChargeUI_1_1; chargeUINum < TotalChargeUINum; chargeUINum++)
			{
				m_chargeUI[chargeUINum][plaNum] = NewGO<SpriteRender>(ChargeUIPriorityDecide(chargeUINum), nullptr);
				sprintf(m_filePath, "ChargeUI_%d", chargeUINum + 1);
				m_chargeUI[chargeUINum][plaNum]->Init(m_filePath, 50.0f, 50.0f);
				m_chargeUI[chargeUINum][plaNum]->Deactivate();
				m_chargeUI[chargeUINum][plaNum]->SetRotation(Quaternion::Identity);
			}
		}

		return true;
	}


	PlayerChargeUI::~PlayerChargeUI()
	{
		//登録されているプレイヤー数ループ
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//チャージ攻撃の際の段階文字表示の削除。
			for (int chargeUINum = ChargeUI_1_1; chargeUINum < TotalChargeUINum; chargeUINum++)
			{
				if (m_chargeUI[chargeUINum][plaNum] != nullptr)
				{
					DeleteGO(m_chargeUI[chargeUINum][plaNum]);
				}
			}
		}
	}


	void PlayerChargeUI::Update()
	{

	}


	//チャージUI画像のそれぞれの優先度決め
	int PlayerChargeUI::ChargeUIPriorityDecide(const int chargeUINum)
	{
		switch (chargeUINum)
		{
		case ChargeUI_1_1:
			return nsStdafx::PRIORITY_2;
			break;
		case ChargeUI_1_2:
			return nsStdafx::PRIORITY_3;
			break;
		case ChargeUI_2_1:
			return nsStdafx::PRIORITY_1;
			break;
		case ChargeUI_2_1_1:
			return nsStdafx::PRIORITY_4;
			break;
		case ChargeUI_2_2:
			return nsStdafx::PRIORITY_2;
			break;
		}
	}


	//チャージUI画像を非表示にする関数
	void PlayerChargeUI::ChargeUIDeactive(const int plaNum)
	{
		for (int chargeUINum = ChargeUI_1_1; chargeUINum < TotalChargeUINum; chargeUINum++)
		{
			m_chargeUI[chargeUINum][plaNum]->Deactivate();
			m_chargeUI[chargeUINum][plaNum]->SetRotation(Quaternion::Identity);
		}
	}


	void PlayerChargeUI::ChargeUIScreenPos(const int plaNum,const Vector2 plaScreenPos)
	{
		//(Vector2をVector3に変換)
		m_plaChargeUIPos[plaNum].x = plaScreenPos.x + 50.0f;
		m_plaChargeUIPos[plaNum].y = plaScreenPos.y;
		//チャージ攻撃のUIにプレイヤーのスクリーン座標を代入
		for (int i = ChargeUI_1_1; i < TotalChargeUINum; i++)
		{
			m_chargeUI[i][plaNum]->SetPosition(m_plaChargeUIPos[plaNum]);
		}
	}


	//
	void PlayerChargeUI::ChargeRotValueInit(const int plaNum)
	{
		m_chargeRotValue1[plaNum] = nsStdafx::FLOAT_ZERO;
		m_chargeRotValue2[plaNum] = nsStdafx::FLOAT_ZERO;
	}


	//
	void PlayerChargeUI::Charge1Move(const int plaNum)
	{
		m_chargeRotValue1[plaNum] -= nsPlayerChargeUI::CHARGE1_MOVESPEED;
		m_charge1_1Rot[plaNum].SetRotationDeg(Vector3::AxisZ, m_chargeRotValue1[plaNum]);
		m_chargeUI[ChargeUI_1_1][plaNum]->SetRotation(m_charge1_1Rot[plaNum]);
	}


	//
	void PlayerChargeUI::Charge2Move(const int plaNum)
	{
		m_chargeRotValue2[plaNum] -= nsPlayerChargeUI::CHARGE2_MOVESPEED;
		m_charge1_2Rot[plaNum].SetRotationDeg(Vector3::AxisZ, m_chargeRotValue2[plaNum]);
		m_chargeUI[ChargeUI_1_2][plaNum]->SetRotation(m_charge1_2Rot[plaNum]);
	}


	//
	void PlayerChargeUI::ChargeUIActive(const int plaNum)
	{
		m_chargeUI[ChargeUI_2_1_1][plaNum]->Deactivate();
		m_chargeUI[ChargeUI_1_1][plaNum]->Activate();
		m_chargeUI[ChargeUI_1_2][plaNum]->Activate();
		m_chargeUI[ChargeUI_2_1][plaNum]->Activate();
	}


	//
	void PlayerChargeUI::SetChargeUI1(const int plaNum)
	{
		m_chargeUI[ChargeUI_1_1][plaNum]->Deactivate();
		m_chargeUI[ChargeUI_2_1][plaNum]->Deactivate();
		m_chargeUI[ChargeUI_2_1_1][plaNum]->Activate();
		m_chargeUI[ChargeUI_2_2][plaNum]->Activate();
	}


	//
	void PlayerChargeUI::SetChargeUI2(const int plaNum)
	{
		m_chargeUI[ChargeUI_1_2][plaNum]->Deactivate();
	}
}