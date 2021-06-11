#pragma once
class Enemy : public IGameObject
{
private:
	SkinModelRender* m_enemy[6] = { nullptr };		//“G6‘Ì

public:
	bool Start();
	~Enemy();
	void Update();
};