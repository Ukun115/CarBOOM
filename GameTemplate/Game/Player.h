#pragma once
class TitleScene;
class GameScene;
class Enemy;
class StageSelectScene;
class Stage;


class Player : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene{ nullptr };
	GameScene* m_gameScene{ nullptr };
	SkinModelRender* m_player[PLAYER_MAX_NUM]{ nullptr };		//プレイヤー4人分
	SpriteRender* m_DASpr1[PLAYER_MAX_NUM]{ nullptr };		//プレイヤー4人分
	SpriteRender* m_DASpr2[PLAYER_MAX_NUM]{ nullptr };		//プレイヤー4人分
	SpriteRender* m_chargeUI1_1[PLAYER_MAX_NUM];		//チャージ画像
	SpriteRender* m_chargeUI1_2[PLAYER_MAX_NUM];		//チャージ画像
	SpriteRender* m_chargeUI2_1[PLAYER_MAX_NUM];		//チャージ画像
	SpriteRender* m_chargeUI2_1_1[PLAYER_MAX_NUM];		//チャージ画像
	SpriteRender* m_chargeUI2_2[PLAYER_MAX_NUM];		//チャージ画像
	Enemy* m_enemy{ nullptr };
	StageSelectScene* m_stageSelectScene{ nullptr };
	SoundSource* m_carHorn[PLAYER_MAX_NUM]{ nullptr };	//クラクションサウンド
	SoundSource* m_shootDownSound[PLAYER_MAX_NUM]{ nullptr };	//撃墜サウンド
	SoundSource* m_FallSound[PLAYER_MAX_NUM]{ nullptr };	//落下サウンド
	SoundSource* m_ChargeSound[PLAYER_MAX_NUM]{ nullptr };	//チャージサウンド
	SoundSource* m_Dash1Sound[PLAYER_MAX_NUM]{ nullptr };	//ダッシュ１サウンド
	SoundSource* m_Dash2Sound[PLAYER_MAX_NUM]{ nullptr };	//ダッシュ２サウンド
	SoundSource* m_PlaAndPlaClashSound[PLAYER_MAX_NUM]{ nullptr };	//プレイヤーとプレイヤーがぶつかったときのサウンド
	Stage* m_stage = nullptr;

	CharacterController m_charaCon[PLAYER_MAX_NUM];		//プレイヤー4人分のキャラクタコントローラークラスを作成
	Effect m_shootDownEffect[PLAYER_MAX_NUM];		//プレイヤー4人分の落下したときの撃墜エフェクト
	Effect m_jetEffect[PLAYER_MAX_NUM];		//プレイヤー4人分のジェットエフェクト
	Effect m_landingEffect[PLAYER_MAX_NUM];		//プレイヤー4人分の着地エフェクト


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isCharge1Flg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2Flg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge1HanteiFlg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2HanteiFlg[PLAYER_MAX_NUM]{ false };
	bool m_isBPushFlg[PLAYER_MAX_NUM]{ false };		//Bボタンが押されたときのフラグ
	bool m_isAttack0Flg[PLAYER_MAX_NUM]{ false };		//Bボタンが押されたときのフラグ
	bool m_isAttack1Flg[PLAYER_MAX_NUM]{ false };		//Bボタンが押されたときのフラグ
	bool m_isAttack2Flg[PLAYER_MAX_NUM]{ false };		//Bボタンが押されたときのフラグ
	bool m_isAttack1HanteiFlg[PLAYER_MAX_NUM]{ false };		//攻撃1の判定フラグ
	bool m_isAttack2HanteiFlg[PLAYER_MAX_NUM]{ false };		//攻撃2の判定フラグ
	bool m_isCharge1EffectSoundFlg[PLAYER_MAX_NUM]{ false };
	bool m_isCharge2EffectSoundFlg[PLAYER_MAX_NUM]{ false };
	bool m_isFallSoundFlg[PLAYER_MAX_NUM]{ false };			//落下音を落下中何回もならないようにするフラグ
	bool m_isLandingOKFlg[PLAYER_MAX_NUM]{ false };


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_chargeTimer[PLAYER_MAX_NUM]{ 0 };		//押したときのタイマー
	unsigned int m_releaseTimer[PLAYER_MAX_NUM]{ 0 };		//離したときのタイマー
	unsigned int m_attackTimer[PLAYER_MAX_NUM]{ 0 };			//攻撃のタイマー
	unsigned int m_attackHanteiTimer[PLAYER_MAX_NUM]{ 0 };			//攻撃判定のタイマー
	unsigned int m_landingEffectDelayTimer[PLAYER_MAX_NUM]{ 0 };			//着地エフェクトをプレイヤーが着地したときに再生させるためのタイマー


	Vector3    m_pos[PLAYER_MAX_NUM];		//プレイヤーの位置
	Quaternion m_rot[PLAYER_MAX_NUM];		//プレイヤーの回転
	Quaternion m_charge1_1Rot[PLAYER_MAX_NUM];		//プレイヤーの回転
	Quaternion m_charge1_2Rot[PLAYER_MAX_NUM];		//プレイヤーの回転
	unsigned int m_plaNum{ 0 };	//プレイヤー数をカウントする変数
	Vector3 m_moveSpeed[PLAYER_MAX_NUM];		//移動速度
	Vector3 m_enePushSpeed;		//敵から与えられるプッシュパワー
	Vector3 m_plaDir[PLAYER_MAX_NUM];		//向き
	float m_leftStick_x[PLAYER_MAX_NUM]{ 0.0f };		//左スティックのx入力量
	float m_leftStick_y[PLAYER_MAX_NUM]{ 0.0f };		//左スティックのy入力量
	float m_rotAngle[PLAYER_MAX_NUM]{ 0.0f };		//回転角度
	Vector3 m_friction[PLAYER_MAX_NUM];		//摩擦
	Vector3 m_diff;				//プレイヤーと敵との距離
	unsigned int m_pushPlayer[5]{ 0 };
	Quaternion m_shootDownEffectRot;

	//デバッグ用
	SkinModelRender* m_skinModelRenderArrow[PLAYER_MAX_NUM]{ nullptr };
	Vector3 m_arrowPos[PLAYER_MAX_NUM];
	Quaternion m_arrowRot[PLAYER_MAX_NUM];
	Vector3 m_arrowSize;


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

	enum SoundNum
	{
		ShootDownSound,
		CarHornSound,
		FallSound,
		ChargeSound,
		Dash1Sound,
		Dash2Sound,
		PlaAndPlaClashSound,
		PlaAndEneClashSound
	};

	enum Wind
	{
		Up,		//下から上への風
		Down,	//上から下への風
		Left,	//右から左への風
		Right,	//左から右への風
		Max		//最大数
	};


	bool Start() override;
	~Player() override;
	void Update() override;


	//プレイヤーのリスポーン処理関数
	void PlaResporn(int plaNum);
	//落ちたプレイヤーの初期位置をセットさせる関数
	void PlaResPos(int plaNum);
	//プレイヤーの位置,回転の情報を更新する関数
	void PlaDataUpdate(int plaNum);
	//プレイヤーの通常移動処理関数
	void PlaMove(int plaNum);
	//プレイヤーの移動速度に補正を入れる関数
	void PlaSpeedCorrection(int plaNum);
	//プレイヤーの回転処理関数
	void PlaTurn(int plaNum);
	//プレイヤーのDA(ダッシュアタック)処理関数
	void PlaAttackBefore(int plaNum);
	//プレイヤーの現在の状態を伝える関数
	void PlaNowState(int plaNum);
	//プレイヤーと敵がぶつかったときの処理関数
	void PlaAndEneClash(int plaNum);
	//プレイヤーとプレイヤーがぶつかったときの処理関数
	void PlaAndPlaClash(int plaNum);
	//プレイヤーにかかる重力を設定する関数
	void Gravity(int plaNum);
	//ベクトルを可視化させるデバック関数
	void PlaMooveSpeedDebug(int plaNum);
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum, int plaNum);
	//プレイヤーに影響を及ぼす風力
	void WindPower(int planum);


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//プレイヤーの人数を取得する関数
	int GetPlaNum() { return m_plaNum; }
	//プレイヤーの位置を取得する関数
	Vector3 GetPlaPos(int plaNum) { return  m_pos[plaNum]; }
	//プレイヤーの速度を取得する関数
	Vector3 GetPlaSpeed(int plaNum) { return m_moveSpeed[plaNum]; }
	//プレイヤーの向きを取得する関数
	Vector3 GetPlaDir(int plaNum) { return m_plaDir[plaNum]; }
	//プレイヤーのチャージを取得する関数
	bool GetPlaisTyazi1HanteiFlg(int plaNum) { return m_isCharge1HanteiFlg[plaNum]; }
	bool GetPlaisTyazi2HanteiFlg(int plaNum) { return m_isCharge2HanteiFlg[plaNum]; }
};