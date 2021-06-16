#pragma once
#include "FontRender.h"

class PhysicsPlayer;
class Enemy;
class Stage;
class TitleScene;

class GameScene :public IGameObject
{
private:
	TitleScene* m_titlescene = nullptr;

	SkinModelRender* m_normalStage = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;

	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };

	PhysicsPlayer* physicsPlayer = nullptr;
	Enemy* enemy = nullptr;
	Stage* physicsStage = nullptr;

	FontRender* m_timeLimit = nullptr;
	int counttime = 0;
	int m_timer = 3600;	//60ïb
	int m_plscore[4] = { 0 };

	int m_countDownTimer = 0;
	bool m_countTimeFlg = true;

	enum
	{
		PLAYER1,		//1P
		PLAYER2,		//2P
		PLAYER3,		//3P
		PLAYER4,		//4P
		MAXPLAYERNUM	//ÉvÉåÉCÉÑÅ[ÇÃç≈ëÂêlêî
	};

	int ehehe = 0;

public:
	bool Start()override;
	~GameScene()override;
	void Update()override;

	Vector2 GetScorePos(int x);
	Vector2 SetScoreTextPos(int t);

	int GetNowTime() { return counttime; }

	bool GetCountDownFlg() { return m_countTimeFlg; }

	void GetPlayerAddScore(int x,int y);

	//åªç›ÇÃÇPà Ç…â§ä•ÇìnÇ∑ä÷êî
	void NowCrown();
};