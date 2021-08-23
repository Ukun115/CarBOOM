///<<summary>
///画面角に表示させるプレイヤー名表示処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;

	class PlayerName : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
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
			TotalPlaNum	//プレイヤーの最大数
		};

		FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };
		GameScene* m_gameScene = nullptr;

		int m_totalPlaNum = 0;

		bool m_isAddPlayerFlg[TotalPlaNum] = { false };		//各プレイヤーが登録されているかの判別フラグ

		bool Start()override final;
		~PlayerName()override final;
		void Update()override final;

	public:
		//プレイヤーを追加したときにカラーチェンジ（アクティブ化）する関数
		void ColorChange(const int totalPlaNum);

		//タイトルシーンで何人プレイヤーが追加されたかを持ってくる
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }

		void AddPlayerFlgOn(const int totalPlaNum);
	};
}