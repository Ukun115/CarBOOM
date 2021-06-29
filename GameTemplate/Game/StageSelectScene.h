#pragma once
class TitleScene;


class StageSelectScene : public IGameObject
{
private:

	SkinModelRender* m_stage[5] = { nullptr };	//全ステージ分用意
	SpriteRender* m_stageName[5] = { nullptr };	//全ステージ分用意
	SkinModelRender* m_pla = nullptr;	//プレイヤー
	TitleScene* m_titleScene = nullptr;
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_Ahukidasi[4] = { nullptr };


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isCanGameStartFlg = true;


	int m_stageNum = 1;				//どのステージを選択しているかを格納
	Vector3 m_stagePos[5];			//ステージの位置
	Vector3    m_pos;				//プレイヤーの位置
	Quaternion m_rot;				//プレイヤーの回転
	Vector3 m_moveSpeed;			//移動速度
	float m_leftStick_x;			//左スティックのx入力量
	float m_leftStick_y;			//左スティックのy入力量
	float m_rotAngle;				//回転角度
	Vector3 m_friction;				//摩擦
	Vector3 m_diff = { 0,0,0 };		//ステージとプレイヤーとの距離
	Vector3 m_AhukidasiPos[4];


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
		RandomStage,
		TotalStageNum
	};


	bool Start()override;
	~StageSelectScene()override;
	void Update()override;


	//ゲーム画面遷移処理関数
	void GameSceneTransition();
	//プレイヤーの通常移動処理関数
	void PlaMove();
	//プレイヤーの移動速度に補正を入れる関数
	void PlaSpeedCorrection();
	//プレイヤーの回転処理関数
	void PlaTurn();
	//プレイヤーの位置,回転の情報を更新する関数
	void PlaDataUpdate();
	//ステージの上にいるときそのステージを選択できる関数
	void TouchStage();
	//プレイヤーが画面外に行かないようにする関数
	void AvoidScreenOutSide();


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//選択されたステージ番号を得る関数
	int GetStageNum() { return m_stageNum; };
};