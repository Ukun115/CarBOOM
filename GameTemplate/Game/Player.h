#pragma once
class TitleScene;
class GameScene;
class Enemy;

#include "../../ExEngine/physics/CharacterController.h"

class Player : public IGameObject
{
public:
	bool Start() override;
	~Player() override;
	void Update() override;

	void PlaResporn(int x);		//プレイヤーを初期位置にリスポーンさせる関数
	void PlaDataUpdate(int x);	//プレイヤーの位置回転拡大率の情報更新関数

	//移動処理
	void PlaMove(int x);
	//回転処理
	void PlaTurn(int x);
	//攻撃準備処理
	void PlaAttackBefore(int x);

	void PlaNowSpeed(int x);

	//プレイヤーポジションをゲットする関数
	Vector3 GetPlaPos(int x) { return  m_pos[x]; }


	Vector3 GetPlaSpeed(int x) { return m_moveSpeed[x]; }

private:
	CharacterController m_charaCon[4];		//キャラクタコントローラ。

	SkinModelRender* m_player[4] = { nullptr };		//最大プレイ人数4人
	TitleScene* m_titlescene = nullptr;
	GameScene* m_gamescene = nullptr;
	Enemy* m_enemy = nullptr;

	Vector3    m_pos[4];		//プレイヤーの位置
	Quaternion m_rot[4];		//プレイヤーの回転
	Vector3    m_sca[4];		//プレイヤーの拡大率

	int m_plaNum = 0;	//プレイヤー数をカウントする変数

	Vector3 m_moveSpeed[4];				//移動速度
	Vector3 m_enePushSpeed;				//エネミーから与えられるプッシュパワー
	Vector3 m_plaDir[4];					//向き
	float m_leftStick_x[4];				//左スティックのx入力量
	float m_leftStick_y[4];				//左スティックのy入力量
	int m_pressTimer[4];				//押した時のタイマー
	int m_releaseTimer[4];				//離した時のタイマー
	bool isBPushFlg[4] = { false };		//Bボタンが押された時のフラグ
	float m_rotAngle[4];				//回転角度
	Vector3 m_friction[4];				//摩擦

	Vector3 m_origin = {0.0f,0.0f,0.0f};		//原点
	Vector3 m_diff;								//プレイヤーとエネミーとの距離

	bool m_respornFallFlg[4] = {false};	//少し上にリスポーンされるので、落下させるフラグ

	bool m_isPlaLanding[4] = {false};	//プレイヤーが着地しているかしていないかを判別するフラグ

	SpriteRender* m_sprite1[4] = { nullptr };
	SpriteRender* m_sprite2[4] = { nullptr };
	bool isAtack0Flg[4] = { false };		//Bボタンが押された時のフラグ
	bool isAtack1Flg[4] = { false };		//Bボタンが押された時のフラグ
	bool isAtack2Flg[4] = { false };		//Bボタンが押された時のフラグ
	int m_atackTime[4];				    //攻撃のタイマー

	int m_pushPlayer[5];

	enum
	{
		PLAYER1,			//1P
		PLAYER2,			//2P
		PLAYER3,			//3P
		PLAYER4,			//4P
		MAXPLAYERNUM		//プレイヤーの最大人数
	};

	int m_noMooveTimer[4] = { 0 };
};