#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[

public:
	bool Start();
	~TitleScene();
	void Update();
};