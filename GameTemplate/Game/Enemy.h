#pragma once
class PhysicsPlayer;
class TitleScene;
class GameScene;

class Enemy : public IGameObject
{
private:
	BoxCollider m_boxCollider[6];		//当たり判定
	RigidBody m_rigidBody[6];			//剛体

	Vector3 m_boxColliderSize[6];				//縦横高さ
	RigidBodyInitData rbInitData[6];

	SkinModelRender* m_enemy[6] = { nullptr };		//敵6体
	PhysicsPlayer* m_player;	//プレイヤー。
	Vector3    m_plaPos[4];		//プレイヤーの位置
	Vector3    m_enePos[6];		//エネミーの位置
	Quaternion m_rot[6];		//エネミーの回転
	Vector3    m_mostShortKyori[6];   //プレイヤー1と敵の距離
	Vector3    m_newKyori[6];   //プレイヤー2と敵の距離

	Vector3 m_moveSpeed[6];				//移動速度
	Vector3 m_eneDir[6];					//向き
	float m_rotAngle[6];				//回転角度
	Vector3 m_friction[6];				//摩擦
	Quaternion m_rot2[6];
	int m_cTime[6];				//攻撃のCT
	bool ctFlg[6] = { false };		//CTのフラグ

	TitleScene* m_titlescene = nullptr;
	GameScene* m_gamescene = nullptr;
	int m_startDelayTimer = 0;		//スタートを遅らせる変数

	PhysicsPlayer* m_physicsPlayer = nullptr;

	Vector3 m_origin = { 0.0f,0.0f,0.0f };		//原点
	Vector3 m_diff;								//パトカーとステージの中心（原点）との距離

	bool m_respornFallFlg[6] = { false };	//少し上にリスポーンされるので、落下させるフラグ

public:
	bool Start()override;
	~Enemy()override;
	void Update()override;

	//移動処理
	void EneMove(int x);
	//回転処理
	void EneTurn(int x);
	//距離設定
	void Kyori(int x);

	//パトカーを初期位置に戻す関数
	void EneResporn(int x);
};