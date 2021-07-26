#pragma once


class GameScene;
class TitleScene;
class StageSelectScene;
class Player;
class Enemy;


class Stage : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
{
private:

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


	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	StageSelectScene* m_stageSelectScene= nullptr;
	GameScene* m_gameScene = nullptr;
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	SkinModelRender* m_stage = nullptr;


	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクトクラスを作成
	Effect m_fallSnowEffect[2];		//アイスステージの降ってくる雪エフェクト


	bool m_isPauseFlg = false;


	/// <summary>
	/// タイマー
	/// </summary>
	int m_fallSnowTimer = INT_ZERO;
	int m_windDirection = INT_ZERO;	//現在の風


	Vector3 m_plaPos[4];			//プレイヤー4体分のプレイヤーの位置
	Vector3 m_LengthFromStaPivToPla[4];	//ステージの基点からプレイヤーまでの距離

	int m_stageSelectNum = INT_ZERO;
	int m_nowTime = INT_ZERO;
	int m_totalPlaNum = INT_ZERO;


	bool Start() override final;
	~Stage()override final;
	void Update() override final;


	//雪エフェクト処理関数
	void SnowFall();
	//風の影響を与える処理
	void WindStage();
	//傾かせる処理
	void Tilt();

public:
	int GetWindDirection()const { return m_windDirection; }

	void SetNowTime(const int nowTime) { m_nowTime = nowTime ; }
	void SetSelectStageNum(const int stageSelectNum) {m_stageSelectNum = stageSelectNum ; }
	void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	void SetPauseFlg(const bool pauseFlg) { m_isPauseFlg = pauseFlg; }
};