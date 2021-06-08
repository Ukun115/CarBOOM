#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー

public:
	bool Start();
	~TitleScene();
	void Update();
};