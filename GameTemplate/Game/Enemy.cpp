#include "stdafx.h"
#include "Enemy.h"

namespace
{
	const int ENEMY1 = 0;		//エネミー１
	const int ENEMY2 = 1;		//エネミー２
	const int ENEMY3 = 2;		//エネミー３
	const int ENEMY4 = 3;		//エネミー４
	const int ENEMY5 = 4;		//エネミー５
	const int ENEMY6 = 5;		//エネミー６
	const int ENEMYNUM = 6;		//敵の総数
	const Vector3 ENEMY1_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY2_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY3_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY4_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY5_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
	const Vector3 ENEMY6_RESPOS={ 0.0f,0.0f,0.0f };		//初期座標(リスポーン座標)
}

bool Enemy::Start()
{
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		//パトカー(敵)をロード
		m_enemy[i] = NewGO<SkinModelRender>(0);
		//モデルのファイルパスを設定
		m_enemy[i]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//パトカー
		//初期座標(リスポーン座標)の設定。
		if (i == ENEMY1)
		{
			m_enemy[i]->SetPosition(ENEMY1_RESPOS);		//エネミー１の場所
		}
		else if(i == ENEMY2)
		{
			m_enemy[i]->SetPosition(ENEMY2_RESPOS);		//エネミー２の場所
		}
		else if (i == ENEMY3)
		{
			m_enemy[i]->SetPosition(ENEMY3_RESPOS);		//エネミー３の場所
		}
		else if (i == ENEMY4)
		{
			m_enemy[i]->SetPosition(ENEMY4_RESPOS);		//エネミー４の場所
		}
		else if (i == ENEMY5)
		{
			m_enemy[i]->SetPosition(ENEMY5_RESPOS);		//エネミー５の場所
		}
		else if (i == ENEMY6)
		{
			m_enemy[i]->SetPosition(ENEMY6_RESPOS);		//エネミー６の場所
		}
	}

	//Start関数のreturn文
	return true;
}

Enemy::~Enemy()
{
	//全エネミーを削除。
	for (int i = ENEMY1; i < ENEMYNUM; i++)
	{
		DeleteGO(m_enemy[i]);
	}
}

void Enemy::Update()
{
	//残り30秒になったらポイントライトでパトランプを光らせるようにする
}