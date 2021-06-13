#pragma once
class ResultScene: public IGameObject
{
private:
	SpriteRender* m_resultSprite = nullptr;

public:
	bool Start();
	~ResultScene();
	void Update();
};

