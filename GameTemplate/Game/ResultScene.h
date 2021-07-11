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

	unsigned int m_select = 0;


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
	//次どのシーンに行くか切り替える関数
	void SelectScene();
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:

};

