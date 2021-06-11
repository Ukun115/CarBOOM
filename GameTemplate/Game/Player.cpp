#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"
#include "TitleScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = {1.5f,1.5f,1.5f};			//プレイヤーの初期サイズ
	const int PLAYER1 = 0;			//1P
	const int PLAYER2 = 1;			//2P
	const int PLAYER3 = 2;			//3P
	const int PLAYER4 = 3;			//4P
	const int MAXPLAYERNUM = 4;		//プレイヤーの最大人数
	const Vector3 PLAYER1_RESPOS = { -100.0f,0.0f,100.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = { 100.0f,0.0f,100.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -100.0f,0.0f,-100.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = { 100.0f,0.0f,-100.0f };		//リスポーン座標(右下)
	const float PLANAME_WIDTHSIZE = 230.0f;		//プレイヤーの画面角に置かれている名前の画像の「横の」大きさ
	const float PLANAME_HEIGHTSIZE = 120.0f;		//プレイヤーの画面角に置かれている名前の画像の「縦の」大きさ
}

bool Player::Start()
{
	m_getAddPlayerFlg = FindGO<TitleScene>("titlescene");

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//登録されていたら実行
		if (m_getAddPlayerFlg->GetPlaFlg(i) == true)
		{
			m_player[i] = NewGO<SkinModelRender>(0);

			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			//追加されたプレイヤーの名前画像の表示と位置決め
			//１P
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車

				//プレイヤー数を+1
				m_plaNum++;
			}
			//大きさ調整。元のモデルが小さかったため、モデルの大きさを1.5倍。
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//プレイヤーを初期位置に持っていく。
			PlaResporn(i);
		}
	}


	//Start関数のreturn文
	return true;
}

Player::~Player()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
			//プレイヤーを削除
			DeleteGO(m_player[i]);
	}
}

void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//コントローラー左スティックでプレイヤーを動かす。
		m_pos[i].x += g_pad[i]->GetLStickXF() * 2.0f;
		m_pos[i].z += g_pad[i]->GetLStickYF() * 2.0f;
	}

	//登録されているプレイヤーの情報を更新
	PlaDataUpdate();
}

//選択されたプレイヤーをリスポーン位置まで戻す関数
void Player::PlaResporn(int x)
{
	//1P
	if (x == PLAYER1)
	{
		m_pos[PLAYER1] = PLAYER1_RESPOS;		//リスポーン座標(左上)
	}
	//2P
	else if (x == PLAYER2)
	{
		m_pos[PLAYER2] = PLAYER2_RESPOS;		//リスポーン座標(右上)
	}
	//3P
	else if (x == PLAYER3)
	{
		m_pos[PLAYER3] = PLAYER3_RESPOS;		//リスポーン座標(左下)
	}
	//4P
	else if (x == PLAYER4)
	{
		m_pos[PLAYER4] = PLAYER4_RESPOS;		//リスポーン座標(右下)
	}
}


//プレイヤーの情報を更新する関数
void Player::PlaDataUpdate()
{
	//参加しているプレイヤー数ループ
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//位置をセット
		m_player[i]->SetPosition(m_pos[i]);
		//回転をセット
		m_player[i]->SetRotation(m_rot[i]);
	}
}