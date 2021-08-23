///<<summary>
///ランキング決定処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;

	class Ranking : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enPlayer
		{
			Player1,
			Player2,
			Player3,
			Player4,
			TotalPlaNum
		};

		GameScene* m_gameScene = nullptr;
		SpriteRender* m_plaNum[TotalPlaNum] = { nullptr };			//プレイヤー4人分用意
		SpriteRender* m_rankingSprite[TotalPlaNum] = { nullptr };	//プレイヤー4人分用意
		unsigned int m_plaScore[TotalPlaNum] = { nsStdafx::INT_ZERO };		//プレイヤー4人分のスコアを入れる配列

		Vector3 m_number1Pos = { 900.0f,50.0f,0.0f };		//１位プレイヤーの表示位置
		Vector3 m_number2Pos = { 900.0f,-50.0f,0.0f };		//２位プレイヤーの表示位置
		Vector3 m_number3Pos = { 900.0f,-150.0f,0.0f };	//３位プレイヤーの表示位置
		Vector3 m_number4Pos = { 900.0f,-250.0f,0.0f };	//４位プレイヤーの表示位置
		float m_moveSpeed = nsStdafx::FLOAT_ZERO;
		int m_totalPlaNum = nsStdafx::INT_ZERO;

		int m_plaMoveDelayTimer = nsStdafx::INT_ZERO;
		int m_verticalMoveTimer = nsStdafx::INT_ZERO;

		bool m_delayTimerOnFlg = true;
		bool m_plaJumpFlg = false;
		bool m_plaMoveFlg[TotalPlaNum] = { false };

		char m_filePath[256];

		bool Start() override final;
		~Ranking()override final;
		void Update() override final;

		//順位によってソートしプレイヤー名の画像を並び替える関数
		void RankingSort();
		//画像が縦移動する関数
		void VerticalMove(const int width, const float speed);
		//順位の画像の初期化をまとめている関数
		void InitRankingImage(const int plaNum);
		//PLAYER画像の初期化をまとめている関数
		void InitPlayerImage(const int plaNum);

		void PlayerNameMove();
		void PlaRankingPosSet(const int plaNum);
		void MoveSpeedChange(const int plaNum);
		void PlaNameJumpState(const int plaNum, const float speed);
		Vector3 WhatNumberPos(const int plaNum);
		Vector3 WhatRankingNumPos(const int plaNum);
		float WhatMoveSpeed(const int plaNum);

	public:
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	};
}