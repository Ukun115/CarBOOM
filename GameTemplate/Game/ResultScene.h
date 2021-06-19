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
	SpriteRender* m_plaNum[4] = {nullptr};
	SpriteRender* m_rankingSprite[4] = {nullptr};
	Player* m_player = nullptr;


	int m_plaScore[4];		//プレイヤーのスコアを入れる配列

public:

	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//順位によってソートしプレイヤー名の画像を並び替える関数
	void RankingSort();
};

