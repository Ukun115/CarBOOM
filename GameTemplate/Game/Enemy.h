#pragma once
class Player;
class TitleScene;
class GameScene;


class Enemy : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	GameScene* m_gameScene = nullptr;
	SkinModelRender* m_enemy[6] = { nullptr };		//敵6体分
	Player* m_player = nullptr;


	CharacterController m_charaCon[6];		//敵６体分のキャラクタコントローラークラスを作成


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isCtFlg[6] = { false };		//敵６体分のCTのフラグ


	/// <summary>
	/// タイマー
	/// </summary>
	int m_startDelayTimer = 0;		//スタートを遅らせるタイマー
	int m_startDelay[6];			//敵６体分のスタート遅延時間
	int m_cTime[6];					//敵６体分の攻撃CTタイマー
	int m_eneCTCount[6];			//敵６体分のCT時間


	//敵情報
	Vector3    m_enePos[6];			//敵６体分の敵の位置
	Quaternion m_rot[6];			//敵６体分の敵の回転
	float m_rotAngle[6];			//敵６体分の回転角度
	Vector3 m_moveSpeed[6];			//敵６体分の移動速度
	Vector3 m_friction[6];			//敵６体分の摩擦
	Vector3    m_plaPos[4];			//プレイヤー4体分のプレイヤーの位置
	Vector3    m_mostShortKyori[4];	 //プレイヤー4体分と敵の距離
	Vector3 m_randEneResPos[10];	//敵のリスポーン位置計10か所


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum ENEMY
	{
		ENEMY1,		 //敵１の配列での番号
		ENEMY2,		 //敵２の配列での番号
		ENEMY3,		 //敵３の配列での番号
		ENEMY4,		 //敵４の配列での番号
		ENEMY5,		 //敵５の配列での番号
		ENEMY6,		 //敵６の配列での番号
		ENEMYNUM	 //敵の総数
	};
	enum PLAYER
	{
		PLAYER1,		//1Pの配列での番号
		PLAYER2,		//2Pの配列での番号
		PLAYER3,		//3Pの配列での番号
		PLAYER4,		//4Pの配列での番号
		MAXPLAYERNUM	//プレイヤーの最大数
	};

public:

	bool Start()override;
	~Enemy()override;
	void Update()override;


	//敵の移動処理関数
	void EneMove(int x);
	//敵の回転処理関数
	void EneTurn(int x);
	//敵から最寄りのプレイヤーを検索する関数
	void Distance(int x);
	//敵のリスポーン処理関数
	void EneResporn(int x);


	/// <summary>
	/// ゲット関数
	/// </summary>
	//敵の位置を取得する関数
	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
	//敵の速度を取得する関数
	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }
};