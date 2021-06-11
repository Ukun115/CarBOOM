#pragma once
class ResultScene: public IGameObject
{
private:
	SpriteRender* m_spriteRender = { nullptr };		//スプライトレンダー
public:
	bool Start();
	~ResultScene();
	void Update();
};

