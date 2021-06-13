#pragma once
class PhysicsPlayer;

class Enemy : public IGameObject
{
private:
	SkinModelRender* m_enemy[6] = { nullptr };		//敵6体
	PhysicsPlayer* m_player;	//プレイヤー。
	Vector3    m_plaPos[4];		//プレイヤーの位置
	Vector3    m_enePos[6];		//エネミーの位置
	Quaternion m_rot[6];		//エネミーの回転
	Vector3    m_kyori[6];   //プレイヤーと敵の距離
	//Vector3    m_kyoriV[6];   //プレイヤーと敵の距離ベクトル
	//Vector3    m_kyoriL[6];   //プレイヤーと敵の距離の大きさ

	Vector3 m_moveSpeed[6];				//移動速度
	Vector3 m_eneDir[6];					//向き
	float m_rotAngle[6];				//回転角度
	Vector3 m_friction[6];				//摩擦
	Quaternion m_rot2[6];
	int m_cTime[6];				//攻撃のCT
	bool ctFlg[6] = { false };		//CTのフラグ


public:
	bool Start();
	~Enemy();
	void Update();

	//移動処理
	void EneMove(int x);
	//回転処理
	void EneTurn(int x);
	//距離設定
	void Kyori(int x);

};