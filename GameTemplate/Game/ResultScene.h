#pragma once
class GameScene;
class Player;


class ResultScene : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	GameScene* m_gameScene{ nullptr };
	SpriteRender* m_resultSprite{ nullptr };
	SpriteRender* m_plaNum[4]{ nullptr };			//プレイヤー4人分用意
	SpriteRender* m_rankingSprite[4]{ nullptr };	//プレイヤー4人分用意
	Player* m_player{ nullptr };
	SoundSource* m_resultGingle{ nullptr };
	SoundSource* m_gameBGM{ nullptr };	//ゲーム中のBGMサウンド
	SoundSource* m_decideSound{ nullptr };	//決定サウンド


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_enableTimerCountFlg{ false };


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_exitTimer{ 0 };


	unsigned int m_plaScore[4]{ 0 };		//プレイヤー4人分のスコアを入れる配列


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum SoundNum
	{
		ResultGingle,
		GameBGM,
		DecideSound,
	};


	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//順位によってソートしプレイヤー名の画像を並び替える関数
	void RankingSort();
	//ゲーム終了関数
	void GameEnd();
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:

};

