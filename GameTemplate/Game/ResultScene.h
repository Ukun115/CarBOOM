#pragma once
class GameScene;
class Player;


class ResultScene : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	GameScene* m_gameScene = nullptr;
	SpriteRender* m_resultSprite = nullptr;
	SpriteRender* m_plaNum[4] = {nullptr};			//プレイヤー4人分用意
	SpriteRender* m_rankingSprite[4] = {nullptr};	//プレイヤー4人分用意
	Player* m_player = nullptr;
	SoundSource* m_resultGingle = nullptr;
	SoundSource* m_gameBGM;	//ゲーム中のBGMサウンド
	SoundSource* m_decideSound;	//決定サウンド


	bool m_timerOnFlg = false;


	unsigned int m_plaScore[4];		//プレイヤー4人分のスコアを入れる配列
	unsigned int m_exitTimer;


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

