#pragma once
class TitleScene;
class GameScene;
class Enemy;
class StageSelectScene;


class Player : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SkinModelRender* m_player[4] = { nullptr };		//プレイヤー4人分
	SpriteRender* m_DASpr1[4] = { nullptr };		//プレイヤー4人分
	SpriteRender* m_DASpr2[4] = { nullptr };		//プレイヤー4人分
	Enemy* m_enemy = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;


	CharacterController m_charaCon[4];		//プレイヤー4人分のキャラクタコントローラークラスを作成
	Effect m_shootDownEffect[4];		//プレイヤー4人分の落下したときの撃墜エフェクト
	Effect m_jetEffect[4];		//プレイヤー4人分のジェットエフェクト


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isTyazi1Flg[4] = { false };
	bool m_isTyazi2Flg[4] = { false };
	bool m_isBPushFlg[4] = { false };		//Bボタンが押されたときのフラグ
	bool m_isAtack0Flg[4] = { false };		//Bボタンが押されたときのフラグ
	bool m_isAtack1Flg[4] = { false };		//Bボタンが押されたときのフラグ
	bool m_isAtack2Flg[4] = { false };		//Bボタンが押されたときのフラグ
	bool m_isTyaziEffectFlg[4] = { false };


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_tyaziTimer[4];		//押したときのタイマー
	unsigned int m_releaseTimer[4];		//離したときのタイマー
	unsigned int m_atackTimer[4];			//攻撃のタイマー
	unsigned int m_atackHanteiTimer[4] = { 0 };			//攻撃判定のタイマー


	Vector3    m_pos[4];		//プレイヤーの位置
	Quaternion m_rot[4];		//プレイヤーの回転
	unsigned int m_plaNum = 0;	//プレイヤー数をカウントする変数
	Vector3 m_moveSpeed[4];		//移動速度
	Vector3 m_enePushSpeed;		//敵から与えられるプッシュパワー
	Vector3 m_plaDir[4];		//向き
	float m_leftStick_x[4];		//左スティックのx入力量
	float m_leftStick_y[4];		//左スティックのy入力量
	float m_rotAngle[4];		//回転角度
	Vector3 m_friction[4];		//摩擦
	Vector3 m_diff;				//プレイヤーと敵との距離
	unsigned int m_pushPlayer[5];
	Quaternion m_shootDownEffectRot;


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enumPlayer
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		MaxPlayerNum	//プレイヤーの最大数
	};


	bool Start() override;
	~Player() override;
	void Update() override;


	//プレイヤーのリスポーン処理関数
	void PlaResporn(int planum);
	//落ちたプレイヤーの初期位置をセットさせる関数
	void PlaResPos(int planum);
	//プレイヤーの位置,回転の情報を更新する関数
	void PlaDataUpdate(int planum);
	//プレイヤーの通常移動処理関数
	void PlaMove(int planum);
	//プレイヤーの移動速度に補正を入れる関数
	void PlaSpeedCorrection(int planum);
	//プレイヤーの回転処理関数
	void PlaTurn(int planum);
	//プレイヤーのDA(ダッシュアタック)処理関数
	void PlaAttackBefore(int planum);
	//プレイヤーのDAの溜め状態の判別処理関数
	void PlaDAState(int planum);
	//プレイヤーの現在の状態を伝える関数
	void PlaNowState(int planum);
	//プレイヤーと敵がぶつかったときの処理関数
	void PlaAndEneClash(int planum);
	//プレイヤーとプレイヤーがぶつかったときの処理関数
	void PlaAndPlaClash(int planum);
	//プレイヤーにかかる重力を設定する関数
	void Gravity(int planum);


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//プレイヤーの人数を取得する関数
	int GetPlaNum() { return m_plaNum; }
	//プレイヤーの位置を取得する関数
	Vector3 GetPlaPos(int planum) { return  m_pos[planum]; }
	//プレイヤーの速度を取得する関数
	Vector3 GetPlaSpeed(int planum) { return m_moveSpeed[planum]; }
	//プレイヤーの向きを取得する関数
	Vector3 GetPlaDir(int planum) { return m_plaDir[planum]; }
	//プレイヤーのチャージを取得する関数
	bool GetPlaisTyazi1Flg(int planum) { return m_isTyazi1Flg[planum]; }
	bool GetPlaisTyazi2Flg(int planum) { return m_isTyazi2Flg[planum]; }
};