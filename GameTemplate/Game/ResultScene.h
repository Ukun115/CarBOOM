#pragma once
class GameScene;
class Player;

class ResultScene : public IGameObject
{
private:
	SpriteRender* m_resultSprite = nullptr;
	SpriteRender* m_plaNum[4] = {nullptr};
	GameScene* m_gamescene = nullptr;
	Player* m_player = nullptr;
	SpriteRender* m_rankingSprite[4] = {nullptr};

	int m_plaScore[4];		//プレイヤーのスコアを入れる配列
	int m_plaJunni[4];		//順位を入れる配列

	//前がプレイヤー番号
	int m_plaJunnni[4][4] = { 0,1,2,3 };

public:
	bool Start()override;
	~ResultScene()override;
	void Update()override;

	void RankingSort();		//順位によってソートしプレイヤー画像を並び替える関数
};

