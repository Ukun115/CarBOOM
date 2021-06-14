#pragma once
class PhysicsPlayer;
class Enemy;
class Stage;

class GameScene:public IGameObject
{
private:
	SkinModelRender* m_normalStage = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };

	PhysicsPlayer* physicsPlayer = nullptr;
	Enemy* enemy = nullptr;
	Stage* physicsStage = nullptr;

	FontRender* m_timeLimit = nullptr;
	int counttime = 0;
	int m_timer = 3600;	//60•b

	int m_countDownTimer = 0;
	bool m_countTimeFlg = true;

	//FontRender* m_plaScore[4] = { nullptr };

public:
	bool Start()override;
	~GameScene()override;
	void Update()override;

	Vector2 GetScorePos(int x);

	int GetNowTime() { return counttime; }

	bool GetCountDownFlg() { return m_countTimeFlg; }
};