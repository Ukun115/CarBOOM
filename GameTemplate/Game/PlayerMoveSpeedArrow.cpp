///<<summary>
///プレイヤーの移動ベクトルを可視化処理(デバック用)
///</summary>


#include "stdafx.h"
#include "PlayerMoveSpeedArrow.h"
#include "Player.h"


namespace nsCARBOOM
{
	bool PlayerMoveSpeedArrow::Start()
	{
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);

		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			//デバック用のプレイヤースピードの矢印表示
			m_skinModelRenderArrow[i] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);
		}

		return true;
	}


	PlayerMoveSpeedArrow::~PlayerMoveSpeedArrow()
	{
		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			//デバック用のプレイヤースピードの矢印削除
			DeleteGO(m_skinModelRenderArrow[i]);
		}
	}


	void PlayerMoveSpeedArrow::Update()
	{
		for (int i = Player1; i < m_totalPlaNum; i++)
		{
			Vector3 Dir = m_player->GetPlaSpeed(i);
			Dir.y = nsStdafx::INT_ZERO;
			Dir.Normalize();//大きさを位置にする
			float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
			Dir.z *= -1;
			float angleX = acosf(x);//アークコサイン
			if (Dir.z < 0) {
				angleX *= -1;
			}
			//angleX -= 0.5 * PAI;
			m_arrowRot[i].SetRotationY(angleX);//ｘ度だけY軸を回す
			m_skinModelRenderArrow[i]->SetRotation(m_arrowRot[i]);//角度を設定する
			m_arrowPos[i] = m_player->GetPlaPos(i);
			m_arrowPos[i].y += 30.0f;
			m_skinModelRenderArrow[i]->SetPosition(m_arrowPos[i]);
			m_arrowSize[i].x = m_arrowSize[i].z = m_player->GetPlaSpeed(i).Length() / 5;
			m_skinModelRenderArrow[i]->SetScale(m_arrowSize[i]);
		}
	}
}