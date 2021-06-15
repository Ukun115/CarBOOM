#pragma once
#include "FontRender.h"

class PhysicsPlayer;
class Enemy;
class Stage;

class GameScene :public IGameObject
{
private:
	SkinModelRender* m_normalStage = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };

	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };

	PhysicsPlayer* physicsPlayer = nullptr;
	Enemy* enemy = nullptr;
	Stage* physicsStage = nullptr;

	FontRender* m_timeLimit = nullptr;
	int counttime = 0;
	int m_timer = 3600;	//60•b
	int m_plscore[4] = { 0 };

	int m_countDownTimer = 0;
	bool m_countTimeFlg = true;

	//FontRender* m_plaScore[4] = { nullptr };

public:
	bool Start()override;
	~GameScene()override;
	void Update()override;

	Vector2 GetScorePos(int x);
	Vector2 SetScoreTextPos(int t);

	int GetNowTime() { return counttime; }

	bool GetCountDownFlg() { return m_countTimeFlg; }
};