#pragma once
class ResultScene: public IGameObject
{
private:
	SpriteRender* m_spriteRender = { nullptr };		//�X�v���C�g�����_�[
public:
	bool Start();
	~ResultScene();
	void Update();
};

