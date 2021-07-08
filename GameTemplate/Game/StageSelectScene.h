#pragma once
class TitleScene;


class StageSelectScene : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	SkinModelRender* m_stage[7]{ nullptr };	//全ステージ分用意
	SpriteRender* m_stageName[7]{ nullptr };	//全ステージ分用意
	SkinModelRender* m_pla{ nullptr };	//プレイヤー
	TitleScene* m_titleScene{ nullptr };
	SpriteRender* m_titleSprite{ nullptr };
	SpriteRender* m_Ahukidasi[6]{ nullptr };
	SoundSource* m_carHorn{ nullptr };	//クラクションサウンド
	SoundSource* m_decideSound{ nullptr };	//決定サウンド
	SoundSource* m_onStageSound{ nullptr };	//ステージに乗ったときのサウンド
	SoundSource* m_titleBGM{ nullptr };	//タイトルBGMサウンド


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_enableUpdateFlg{ true };
	bool m_canOnStageSoundPlayFlg[4]{ false };


	int m_stageNum{ 1 };				//どのステージを選択しているかを格納
	Vector3 m_stagePos[7];			//ステージの位置
	Vector3    m_pos;				//プレイヤーの位置
	Quaternion m_rot;				//プレイヤーの回転
	Vector3 m_moveSpeed;			//移動速度
	float m_leftStick_x{ 0.0f };			//左スティックのx入力量
	float m_leftStick_y{ 0.0f };			//左スティックのy入力量
	float m_rotAngle{ 0.0f };				//回転角度
	Vector3 m_friction;				//摩擦
	Vector3 m_diff[4];		//ステージとプレイヤーとの距離
	Vector3 m_AhukidasiPos[6];


	//デバッグ用
	SkinModelRender* m_skinModelRenderArrow{ nullptr };
	Vector3 m_arrowPos;
	Quaternion m_arrowRot;
	Vector3 m_arrowSize;


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
		Stage5,
		RandomStage,
		TotalStageNum
	};

	enum SoundNum
	{
		TitleSceneBGM,
		DecideSound,
		OnStageSound,
		CarHornSound
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
	//ベクトルを可視化させるデバック関数
	void PlaMooveSpeedDebug();
	//クラクションを鳴らす関数
	void CarHorn();
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//選択されたステージ番号を得る関数
	 int GetStageNum() { return m_stageNum; };
};