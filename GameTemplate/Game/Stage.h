#pragma once
class StageSelectScene;
class GameScene;
class StageSelectcene;
class Player;
class TitleScene;
class Enemy;


class Stage : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	SkinModelRender* m_stage = nullptr;
	StageSelectScene* m_stageSelectScene= nullptr;
	GameScene* m_gameScene = nullptr;
	Player* m_player = nullptr;
	TitleScene* m_titleScene = nullptr;
	Enemy* m_enemy = nullptr;


	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクトクラスを作成
	Effect m_fallSnowEffect[2];		//アイスステージの降ってくる雪エフェクト


	bool m_isPauseFlg = false;


	/// <summary>
	/// タイマー
	/// </summary>
	int m_fallSnowTimer = 0;
	int m_windDirection = 0;	//現在の風


	Vector3 m_plaPos[4];			//プレイヤー4体分のプレイヤーの位置
	Vector3 m_LengthFromStaPivToPla[4];	//ステージの基点からプレイヤーまでの距離

	int m_stageSelectNum = 0;
	int m_nowTime = 0;
	int m_totalPlaNum = 0;

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
		Stage4,
		Stage5
	};


	bool Start() override;
	~Stage()override;
	void Update() override;


	//雪エフェクト処理関数
	void SnowFall();
	//風の影響を与える処理
	void WindStage();
	//傾かせる処理
	void Tilt();

public:
	int GetWindDirection() { return m_windDirection; }

	void SetNowTime(int nowTime) { m_nowTime = nowTime ; }
	void SetSelectStageNum(int stageSelectNum) {m_stageSelectNum = stageSelectNum ; }
	void SetTotalPlaNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	void SetPauseFlg(bool pauseFlg) { m_isPauseFlg = pauseFlg; }
};