#pragma once
class PhysicsPlayer;
class TitleScene;
class GameScene;

#include "../../ExEngine/physics/CharacterController.h"

class Enemy : public IGameObject
{
private:

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
	Vector3 m_diff;								//パトカーとプレイヤーとの距離
	Vector3 m_plaPushSpeed;

	bool m_respornFallFlg[6] = { false };	//少し上にリスポーンされるので、落下させるフラグ

	CharacterController m_charaCon[6];		//キャラクタコントローラ。

	float distance = 10000.0f;
	int a = 0;

	enum ENEMY
	{
		ENEMY1,		//エネミー１
		ENEMY2,		//エネミー２
		ENEMY3,		//エネミー３
		ENEMY4,		//エネミー４
		ENEMY5,		//エネミー５
		ENEMY6,		//エネミー６
		ENEMYNUM	//敵の総数
	};

	enum PLAYER
	{
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		MAXPLAYERNUM
	};

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

	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }

	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
};