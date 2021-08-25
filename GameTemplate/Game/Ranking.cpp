///<<summary>
///ランキング決定処理
///</summary>

#include "stdafx.h"
#include "Ranking.h"
#include "GameScene.h"

namespace nsCARBOOM
{
	namespace nsRanking
	{
		const Vector3 RANKING1_POS = { -150.0f,50.0f,0.0f };	//１位画像の位置
		const Vector3 RANKING2_POS = { -150.0f,-50.0f,0.0f };	//２位画像の位置
		const Vector3 RANKING3_POS = { -150.0f,-150.0f,0.0f };	//３位画像の位置
		const Vector3 RANKING4_POS = { -150.0f,-250.0f,0.0f };	//４位画像の位置
		const int JUMP_WIDTH = 10;
		const float JUMP_SPEED = 1.0f;
		const int DELAYTIMER = 100;
		const int PLUS_ONE = 1;
		const float RANKING_FONT_SCALE = 150.0f;
		const int NIBAI = 2;
		const float PLAYERNAME_SPRITE_WIDTH = 340.0f;
		const float PLAYERNAME_SPRITE_HEIGHT = 170.0f;
		const float NEXT_JUNNI_CHANGE_SPEED = 2.0f;
	}

	bool Ranking::Start()
	{
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);

		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//順位の画像の初期化をまとめている関数
			InitRankingImage(plaNum);
			//PLAYER画像の初期化をまとめている関数
			InitPlayerImage(plaNum);
		}

		//順位情報を並び替え
		RankingSort();

		return true;
	}

	Ranking::~Ranking()
	{
		//プレイヤー名画像の削除。
		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++)
		{
			DeleteGO(m_plaNum[plaNum]);

			DeleteGO(m_rankingSprite[plaNum]);
		}
	}

	void Ranking::Update()
	{
		//ディレイをかける
		if (m_delayTimerOnFlg)
		{
			m_plaMoveDelayTimer++;
			if (m_plaMoveDelayTimer > nsRanking::DELAYTIMER)
			{
				m_plaMoveFlg[Player4] = true;
				m_delayTimerOnFlg = false;
			}
		}
		//プレイヤーが画面外（右側）からスライドしてくる処理
		PlayerNameMove();

		if (!m_plaJumpFlg)
		{
			return;
		}
		//画像がジャンプする
		VerticalMove(nsRanking::JUMP_WIDTH, nsRanking::JUMP_SPEED);
	}

	//順位によってソートしプレイヤー名の画像を並び替える関数
	void Ranking::RankingSort()
	{
		//プレイヤーの人数分スコアをゲット
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			m_plaScore[plaNum] = m_gameScene->GetPlaScore(plaNum);
		}
		//ソート
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			for (int nextPlaNum = plaNum + nsRanking::PLUS_ONE; nextPlaNum < m_totalPlaNum; nextPlaNum++)
			{
				if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
				{
					SpriteRender* tmp = m_plaNum[plaNum];
					m_plaNum[plaNum] = m_plaNum[nextPlaNum];
					m_plaNum[nextPlaNum] = tmp;
				}
			}
		}

		//プレイヤーの人数に応じて横からプレイヤー名が出てくる速度が変化
		for (int plaNum = Player1; plaNum <= m_totalPlaNum; plaNum)
		{
			MoveSpeedChange(plaNum);
			PlaRankingPosSet(plaNum);
		}
	}

	//画像がジャンプする関数
	void Ranking::VerticalMove(const int width, const float speed)
	{
		if (m_verticalMoveTimer < width)
		{
			//上にジャンプ
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, speed);
			}
		}
		else if (m_verticalMoveTimer < (width * nsRanking::NIBAI))
		{
			//ジャンプ後の落下
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				PlaNameJumpState(plaNum, -speed);
			}
		}
		else
		{
			m_plaJumpFlg = false;
		}

		m_verticalMoveTimer++;

		for (int plaNum = Player2; plaNum <= TotalPlaNum; plaNum)
		{
			PlaRankingPosSet(plaNum);
		}
	}

	//順位の画像の初期化をまとめている関数
	void Ranking::InitRankingImage(const int plaNum)
	{
		//順位文字を初期化し、表示
		//順位画像オブジェクト生成
		m_rankingSprite[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "%dst", (plaNum + nsRanking::PLUS_ONE));
		m_rankingSprite[plaNum]->Init(m_filePath, nsRanking::RANKING_FONT_SCALE, nsRanking::RANKING_FONT_SCALE);
		m_rankingSprite[plaNum]->SetPosition(WhatRankingNumPos(plaNum));
	}

	//PLAYER画像の初期化をまとめている関数
	void Ranking::InitPlayerImage(const int plaNum)
	{
		//プレイヤー文字画像オブジェクト生成
		m_plaNum[plaNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_7, nullptr);
		sprintf(m_filePath, "Player%d_ActiveName",plaNum);
		m_plaNum[plaNum]->Init(m_filePath, nsRanking::PLAYERNAME_SPRITE_WIDTH, nsRanking::PLAYERNAME_SPRITE_HEIGHT);
	}

	void Ranking::PlayerNameMove()
	{
		for (int plaNum = Player4; plaNum >= Player1; plaNum--)
		{
			if (!m_plaMoveFlg[Player4])
			{
				return;
			}
			if (m_totalPlaNum >= (plaNum + nsRanking::PLUS_ONE))
			{
				if (m_number4Pos.x > 150.0f)
				{
					m_number4Pos.x -= m_moveSpeed;
				}
				else
				{
					m_plaMoveFlg[plaNum - nsRanking::PLUS_ONE] = true;
					if (plaNum != Player1)
					{
						m_plaMoveFlg[plaNum] = false;
					}
					else
					{
						m_plaJumpFlg = true;
					}
					//次登場する画像のスピードを変化させる
					m_moveSpeed /= nsRanking::NEXT_JUNNI_CHANGE_SPEED;
				}
				m_plaNum[plaNum]->SetPosition(m_number4Pos);
			}
			else
			{
				m_plaMoveFlg[plaNum] = false;
				if (plaNum != Player1)
				{
					m_plaMoveFlg[plaNum - nsRanking::PLUS_ONE] = true;
				}
				else
				{
					m_plaJumpFlg = true;
				}
			}
		}
	}

	void Ranking::MoveSpeedChange(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_moveSpeed = WhatMoveSpeed(plaNum);
		}
	}

	void Ranking::PlaRankingPosSet(const int plaNum)
	{
		if (m_totalPlaNum > plaNum)
		{
			m_plaNum[plaNum]->SetPosition(WhatNumberPos(plaNum));
		}
	}

	void Ranking::PlaNameJumpState(const int plaNum,const float speed)
	{
		if (m_totalPlaNum >= plaNum)
		{
			switch (plaNum)
			{
			case Player2:
				m_number1Pos.y += speed;
				break;
			case Player3:
				m_number2Pos.y += speed;
				break;
			case Player4:
				m_number3Pos.y += speed;
				break;
			case TotalPlaNum:
				m_number4Pos.y += speed;
				break;
			}
		}
	}

	Vector3 Ranking::WhatRankingNumPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return nsRanking::RANKING1_POS;
			break;
		case Player2:
			return nsRanking::RANKING2_POS;
			break;
		case Player3:
			return nsRanking::RANKING3_POS;
			break;
		case TotalPlaNum:
			return nsRanking::RANKING4_POS;
			break;
		}
	}

	float Ranking::WhatMoveSpeed(const int plaNum)
	{
		switch (plaNum)
		{
		case Player2:
			return 20.0f;
			break;
		case Player3:
			return 5.0f;
			break;
		case Player4:
			return 10.0f;
			break;
		case TotalPlaNum:
			return 20.0f;
			break;
		}
	}

	Vector3 Ranking::WhatNumberPos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return m_number1Pos;
			break;
		case Player2:
			return m_number2Pos;
			break;
		case Player3:
			return m_number3Pos;
			break;
		case Player4:
			return m_number4Pos;
			break;
		}
	}
}