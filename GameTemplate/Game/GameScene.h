#pragma once
#include "FontRender.h"

class Player;
class Enemy;
class Stage;
class TitleScene;

class GameScene :public IGameObject
{
private:
	TitleScene* m_titlescene = nullptr;

	SkinModelRender* m_normalStage = nullptr;
	SkinModelRender* m_crownModel = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;

	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Stage* physicsStage = nullptr;

	FontRender* m_timeLimit = nullptr;
	int counttime = 0;
	int m_timer = 3600;	//60秒
	int m_plscore[4] = { 0 };

	int m_countDownTimer = 0;
	bool m_countTimeFlg = true;

	enum
	{
		PLAYER1,		//1P
		PLAYER2,		//2P
		PLAYER3,		//3P
		PLAYER4,		//4P
		MAXPLAYERNUM	//プレイヤーの最大人数
	};

	int m_nowNumOnePla = 0;

	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};

	int m_resultsenniTimer = 0;

public:
	bool Start()override;
	~GameScene()override;
	void Update()override;

	Vector2 GetScorePos(int x);
	Vector2 SetScoreTextPos(int t);
	Vector4 ScoreColor(int c);

	int GetNowTime() { return counttime; }

	bool GetCountDownFlg() { return m_countTimeFlg; }

	void GetPlayerAddScore(int x,int y);

	int GetPlaScore(int x) { return m_plscore[x]; };		//各プレイヤーのスコアを取得する関数

	//現在の１位に王冠を渡す関数
	void NowCrown();
};