#pragma once
class Player;

class GameScene:public IGameObject
{
private:
	Player* m_player;
	SkinModelRender* m_normalStage;

	FontRender* m_fontRender = nullptr;
	int m_timer = 3600;	//60•b

public:
	bool Start();
	~GameScene();
	void Update();
};