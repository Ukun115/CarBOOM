#pragma once
class Player;

class GameScene:public IGameObject
{
private:
	Player* m_player;
	SkinModelRender* m_normalStage;
public:
	bool Start();
	~GameScene();
	void Update();
};