#pragma once
class ResultScene: public IGameObject
{
private:
	SpriteRender* m_resultSprite = nullptr;

public:
	bool Start()override;
	~ResultScene()override;
	void Update()override;
};

