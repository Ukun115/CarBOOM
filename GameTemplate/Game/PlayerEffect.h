///<<summary>
///敵のエフェクト処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PlayerTurn;
	class Player;

	class PlayerEffect : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		/// <summary>
		/// 列挙型の宣言
		/// </summary>
		enum enPlayer
		{
			Player1,		//1Pの配列での番号
			Player2,		//2Pの配列での番号
			Player3,		//3Pの配列での番号
			Player4,		//4Pの配列での番号
			TotalPlayerNum	//プレイヤーの最大数
		};

		PlayerTurn* m_playerTurn = nullptr;
		Player* m_player = nullptr;

		Effect m_shootDownEffect[TotalPlayerNum];		//プレイヤー4人分の落下したときの撃墜エフェクト
		Effect m_jetEffect[TotalPlayerNum];		//プレイヤー4人分のジェットエフェクト
		Effect m_landingEffect[TotalPlayerNum];		//プレイヤー4人分の着地エフェクト

		char m_filePath[256];
		int m_totalPlaNum = 0;
		unsigned int m_landingEffectDelayTimer[TotalPlayerNum] = { 0 };			//着地エフェクトをプレイヤーが着地したときに再生させるためのタイマー
		bool m_isLandingOKFlg[TotalPlayerNum] = { false };

		bool Start()override final;
		~PlayerEffect()override final;
		void Update()override final;

	public:
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }

		void JetEffectPlay(const int plaNum);
		void ShootDownEffectPlay(const int plaNum);
		void LandingEffectPlay(const int plaNum);

		void LandingEffectFlgOn(const int plaNum);
	};
}