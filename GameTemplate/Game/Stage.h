#pragma once
class StageSelectScene;


class Stage : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	SkinModelRender* m_stage = { nullptr };
	StageSelectScene* m_stageSelectScene;


	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクトクラスを作成
	Effect m_fallSnowEffect[2];		//アイスステージの降ってくる雪エフェクト


	/// <summary>
	/// タイマー
	/// </summary>
	int m_fallSnowTimer = 0;


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	//ステージ番号
	enum StageNum
	{
		ehehe,	//Stage1を１番にするためにeheheを入れて調整
		Stage1,
		Stage2,
		Stage3,
	};


	bool Start() override;
	~Stage()override;
	void Update() override;


public:

};