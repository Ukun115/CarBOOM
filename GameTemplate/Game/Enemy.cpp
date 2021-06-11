#include "stdafx.h"
#include "Enemy.h"

namespace
{
	const int ENEMY1 = 0;
	const int ENEMY2 = 0;
	const int ENEMY3 = 0;
	const int ENEMY4 = 0;
	const int ENEMY5 = 0;
	const int ENEMY6 = 0;
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
			m_enemy[i]->SetPosition(ENEMY1_RESPOS);		//場所
		}
		else if(i == ENEMY2)
		{
			m_enemy[i]->SetPosition(ENEMY2_RESPOS);		//場所
		}
		else if (i == ENEMY3)
		{
			m_enemy[i]->SetPosition(ENEMY3_RESPOS);		//場所
		}
		else if (i == ENEMY4)
		{
			m_enemy[i]->SetPosition(ENEMY4_RESPOS);		//場所
		}
		else if (i == ENEMY5)
		{
			m_enemy[i]->SetPosition(ENEMY5_RESPOS);		//場所
		}
		else if (i == ENEMY6)
		{
			m_enemy[i]->SetPosition(ENEMY6_RESPOS);		//場所
		}
	}

	//Start関数のreturn文
	return true;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}