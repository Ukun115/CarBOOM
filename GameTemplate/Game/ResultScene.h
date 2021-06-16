#pragma once
class ResultScene : public IGameObject
{
private:
	SpriteRender* m_resultSprite = nullptr;
	SpriteRender* m_plaNum[4] = {nullptr};

public:
	bool Start()override;
	~ResultScene()override;
	void Update()override;
};

