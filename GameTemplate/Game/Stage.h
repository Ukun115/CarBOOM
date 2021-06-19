#pragma once


class Stage : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	SkinModelRender* m_stage[1] = { nullptr };	//全ステージ分用意


	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクトクラスを作成

public:

	bool Start() override;
	~Stage()override;
	void Update() override;
};