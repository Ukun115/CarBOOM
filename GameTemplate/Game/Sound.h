#pragma once

class Sound : public IGameObject
{
private:

public:
	bool Start()override;
	~Sound()override;
	void Update()override;
};