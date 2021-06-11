#pragma once

class GameScene:public IGameObject
{
private:
	SkinModelRender* bg_normal;
public:
	bool Start();
	~GameScene();
	void Update();
};