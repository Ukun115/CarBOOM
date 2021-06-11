#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// 注意！ゲームパッドの登録する順番は、ゲームパッドがPCに接続された順番！！
/// </summary>

namespace
{
	const int PLAYER1   = 0;
	const int PLAYER2   = 1;
	const int PLAYER3   = 2;
	const int PLAYER4   = 3;
	const Vector3 PLAYER1_NAMEPOS = {-550.0f, 300.0f,0.0f};		//プレイヤー1の名前表示位置
	const Vector3 PLAYER2_NAMEPOS = { 550.0f, 300.0f,0.0f};		//プレイヤー1の名前表示位置
	const Vector3 PLAYER3_NAMEPOS = {-550.0f,-300.0f,0.0f};		//プレイヤー1の名前表示位置
	const Vector3 PLAYER4_NAMEPOS = { 550.0f,-300.0f,0.0f};		//プレイヤー1の名前表示位置
	const int MAXPLAYERNUM = 4;
}

bool TitleScene::Start()
{
	//1Pは無条件で追加フラグを真に。
	isAddPlayer[PLAYER1] = true;

	//サンプル背景画像を初期化。
	m_spriteRender[PLAYER1] = NewGO<SpriteRender>(0);
	m_spriteRender[PLAYER1]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
	m_spriteRender[PLAYER1]->SetPosition(PLAYER1_NAMEPOS);

	//Start関数のreturn文
	return true;
}

TitleScene::~TitleScene()
{
	//プレイヤーの数だけ名前表示画像を削除
	for (int i = 0; i < m_totalPlayerNum; i++)
	{
		DeleteGO(m_spriteRender[i]);
	}
}

void TitleScene::Update()
{
	if (isCanGameStartFlg == true) {
		//プレイヤーを追加する
		if (m_totalPlayerNum != MAXPLAYERNUM)
		{
			//登録されていないコントローラーのスタートボタンが押されたら、
			if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonA))
			{
				//新規プレイヤーの追加フラグを真に。
				isAddPlayer[m_totalPlayerNum] = true;

				//プレイヤーのアクティブ化
				//サンプル背景画像を初期化。
				m_spriteRender[m_totalPlayerNum] = NewGO<SpriteRender>(0);
				//2Pのアクティブ化
				if (m_totalPlayerNum == PLAYER2)
				{
					m_spriteRender[PLAYER2]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//画像のポジション指定
					m_spriteRender[PLAYER2]->SetPosition(PLAYER2_NAMEPOS);
				}
				//3Pのアクティブ化
				if (m_totalPlayerNum == PLAYER3)
				{
					m_spriteRender[PLAYER3]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//画像のポジション指定
					m_spriteRender[PLAYER3]->SetPosition(PLAYER3_NAMEPOS);
				}
				//4Pのアクティブ化
				if (m_totalPlayerNum == PLAYER4)
				{
					m_spriteRender[PLAYER4]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//画像のポジション指定
					m_spriteRender[PLAYER4]->SetPosition(PLAYER4_NAMEPOS);
				}
				//次のプレイヤーへ...
				m_totalPlayerNum++;
			}
		}
		//1Pのスタートボタンが押されたらゲーム開始
		if (g_pad[PLAYER1]->IsTrigger(enButtonStart))
		{
			//ゲーム画面に遷移
			NewGO<GameScene>(0);
			//このクラスの削除
			//DeleteGO(this);

			//一度のみゲーム開始ボタンを押せるようにする
			isCanGameStartFlg = false;
		}
	}
}