#pragma once
class TitleScene;

class Player : public IGameObject
{
private:
	SkinModelRender* m_player[4] = { nullptr };		//最大プレイ人数4人
	TitleScene* m_getAddPlayerFlg = { nullptr };

	Vector3    m_pos[4];		//プレイヤーの位置
	Quaternion m_rot[4];		//プレイヤーの回転
	Vector3    m_sca[4];		//プレイヤーの拡大率

public:
	bool Start();
	~Player();
	void Update();
	void PlaDataUpdate();	//プレイヤーの位置回転拡大率の情報更新関数
};

