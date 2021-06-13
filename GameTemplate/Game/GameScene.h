#pragma once
class PhysicsPlayer;
class Enemy;
class Stage;

class GameScene:public IGameObject
{
private:
	SkinModelRender* m_normalStage = nullptr;

	PhysicsPlayer* physicsPlayer = nullptr;
	Enemy* enemy = nullptr;
	Stage* physicsStage = nullptr;

	FontRender* m_timeLimit = nullptr;
	int counttime = 0;
	int m_timer = 3600;	//60•b

	//FontRender* m_plaScore[4] = { nullptr };

public:
	bool Start();
	~GameScene();
	void Update();
	Vector2 GetScorePos(int x);

	int GetNowTime() { return counttime; }
};