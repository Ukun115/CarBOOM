#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = {1.5f,1.5f,1.5f};			//プレイヤーの初期サイズ
	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int PLAYER3 = 2;
	const int PLAYER4 = 3;
	const int MAXPLAYERNUM = 4;			//プレイヤーの最大人数
	const Vector3 PLAYER1_RESPOS = { -20.0f,0.0f,-20.0f };		//リスポーン座標(左上)
	const Vector3 PLAYER2_RESPOS = { 20.0f,0.0f,-20.0f };		//リスポーン座標(右上)
	const Vector3 PLAYER3_RESPOS = { -20.0f,0.0f,20.0f };		//リスポーン座標(左下)
	const Vector3 PLAYER4_RESPOS = { 20.0f,0.0f,20.0f };		//リスポーン座標(右下)
}

bool Player::Start()
{

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{

		//登録されたプレイヤーの車をロード
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//プレイヤーの車をロード
			m_player[i] = NewGO<SkinModelRender>(0);
			//モデルのファイルパスを設定＆初期座標(リスポーン座標)の設定。
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
				m_player[i]->SetPosition(PLAYER1_RESPOS);		//左上
			}
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//青車
				m_player[i]->SetPosition(PLAYER2_RESPOS);		//右上
			}
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//黄車
				m_player[i]->SetPosition(PLAYER3_RESPOS);		//左下
			}
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//緑車
				m_player[i]->SetPosition(PLAYER4_RESPOS);		//右下
			}
			//大きさ調整。モデルの大きさを1.5倍。
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
		}
	}


	//Start関数のreturn文
	return true;
}

Player::~Player()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//追加されていたら追加されたプレイヤーの車をロード
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//プレイヤーを削除
			DeleteGO(m_player[i]);
		}
	}
}

void Player::Update()
{
	//登録されているプレイヤー数ループ
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//コントローラー左スティックでプレイヤーを動かす。
			m_pos[i].x -= g_pad[i]->GetLStickXF() * 2.0f;
			m_pos[i].z -= g_pad[i]->GetLStickYF() * 2.0f;
		}
	}

	//登録されているプレイヤーの情報を更新
	DataUpdate();
}

//プレイヤーの情報を更新する関数
void Player::DataUpdate()
{
	//参加しているプレイヤー数ループ
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//位置をセット
		m_player[i]->SetPosition(m_pos[i]);
		//回転をセット
		m_player[i]->SetRotation(m_rot[i]);
		//拡大率をセット
		m_player[i]->SetScale(m_sca[i]);
	}
}