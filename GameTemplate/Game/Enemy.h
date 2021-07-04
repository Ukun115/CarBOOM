#pragma once
class Player;
class TitleScene;
class GameScene;
class StageSelectScene;


class Enemy : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;

	Light* m_light = { nullptr };

	SkinModelRender* m_enemy[6] = { nullptr };		//敵6体分
	Player* m_player = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;
	SoundSource* m_shootDownSound[6] = {nullptr};
	SoundSource* m_FallSound[6];	//落下サウンド
	SoundSource* m_DashSound[6];	//ダッシュサウンド
	SoundSource* m_PlaAndEneClashSound[6];	//衝突サウンド


	CharacterController m_charaCon[6];		//敵６体分のキャラクタコントローラークラスを作成
	Effect m_shootDownEffect[6];		//落下したときの撃墜エフェクト


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isCtFlg[6] = { false };		//敵６体分のCTのフラグ
	bool m_stage2Flg = false;
	bool m_isFallSoundFlg[6] = { false };			//落下音を落下中何回もならないようにするフラグ
	bool m_isPlaAndEneClashSoundFlg[6] = { false };


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_startDelayTimer = 0;		//スタートを遅らせるタイマー
	unsigned int m_startDelay[6];			//敵６体分のスタート遅延時間
	unsigned int m_CTTime[6];					//敵６体分の攻撃CTタイマー
	unsigned int m_eneCTCount[6];			//敵６体分のCT時間


	//敵情報
	Vector3    m_enePos[6];			//敵６体分の敵の位置
	Quaternion m_rot[6];			//敵６体分の敵の回転
	float m_rotAngle[6];			//敵６体分の回転角度
	Vector3 m_moveSpeed[6];			//敵６体分の移動速度
	Vector3 m_samDir[6];			//敵とプレイヤーの向き
	Vector3 m_friction[6];			//敵６体分の摩擦
	Vector3    m_plaPos[4];			//プレイヤー4体分のプレイヤーの位置
	Vector3    m_mostShortKyori[4];	//プレイヤー4体分と敵の距離
	//↓特に途中で変更しない値なので、const使いたい。
	Vector3 m_ranEneResPos[10];		//敵のリスポーン位置計10か所

	float m_randEneResAngle[8];		//敵のリスポーン回転角度4か所
	Vector3 m_eneDir[6];			//向き
	Vector3 m_diff;				//プレイヤーと敵との距離
	unsigned int m_pushPlayer[6];
	unsigned int m_randomDashSoundNum;


	Vector3 m_enePoiLigPos;
	int	m_poiLigNum = 0;


	//デバッグ用
	SkinModelRender* m_skinModelRenderArrow[6] = { nullptr };
	Vector3 m_arrowPos[6];
	Quaternion m_arrowRot[6];
	Vector3 m_arrowSize = Vector3::One;


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enumEnemy
	{
		Enemy1,		 //敵１の配列での番号
		Enemy2,		 //敵２の配列での番号
		Enemy3,		 //敵３の配列での番号
		Enemy4,		 //敵４の配列での番号
		Enemy5,		 //敵５の配列での番号
		Enemy6,		 //敵６の配列での番号
		MaxEnemyNum	 //敵の総数
	};
	enum enumPlayer
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		MaxPlaNum	//プレイヤーの最大数
	};
	//敵のランダムリスポーン位置
	enum enumRanEneResPos
	{
		ResPos1,	//１つ目
		ResPos2,	//２つ目
		ResPos3,	//３つ目
		ResPos4,	//４つ目
		ResPos5,	//５つ目
		ResPos6,	//６つ目
		ResPos7,	//７つ目
		ResPos8,	//８つ目
		ResPos9,	//９つ目
		ResPos10,	//１０つ目
	};

	enum SoundNum
	{
		ShootDownSound,
		FallSound,
		DashSound,
		PlaAndEneClashSound
	};


	bool Start()override;
	~Enemy()override;
	void Update()override;


	//敵の位置,回転を更新する関数
	void EneDataUpdate(int eneNum);
	//敵のDA処理関数
	void EneDA(int eneNum);
	//敵の回転処理関数
	void EneTurn(int eneNum);
	//敵から最寄りのプレイヤーを検索する関数
	void Distance(int eneNum);
	//敵のリスポーン処理関数
	void EneResporn(int eneNum);
	//敵の摩擦処理関数
	void EneFriction(int eneNum);
	//プレイヤーと敵がぶつかったときの処理関数
	void PlaAndEneClash(int eneNum);
	//敵にかかる重力を設定する関数
	void Gravity(int eneNum);
	//敵のスピードベクトルを可視化させるデバック関数
	void EneMooveSpeedDebug(int eneNum);
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum,int eneNum);


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//敵の位置を取得する関数
	Vector3 GetEnemyPos(int eneNum) { return m_enePos[eneNum]; }
	//敵の速度を取得する関数
	Vector3 GetEnemySpeed(int eneNum) { return m_moveSpeed[eneNum]; }
};