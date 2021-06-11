#pragma once
class TitleScene;

class Player : public IGameObject
{
private:
	SkinModelRender* m_player[4] = { nullptr };		//最大プレイ人数4人
	TitleScene* m_getAddPlayerFlg = { nullptr };

	Vector3    m_pos[4];		//プレイヤーの位置
	Quaternion m_rot[4];		//プレイヤーの回転
	Vector3    m_sca[4];		//プレイヤーの拡大率

	int m_plaNum = 0;	//プレイヤー数をカウントする変数

	Vector3 m_moveSpeed[4];				//移動速度
	Vector3 m_plaDir[4];					//向き
	float m_leftStick_x[4];				//左スティックのx入力量
	float m_leftStick_y[4];				//左スティックのy入力量
	int m_pressTimer[4];				//押した時のタイマー
	int m_releaseTimer[4];				//離した時のタイマー
	bool isBPushFlg[4] = { false };		//Bボタンが押された時のフラグ
	float m_rotAngle[4];				//回転角度
	Vector3 m_friction[4];				//摩擦
	Quaternion m_rot2[4];

public:
	bool Start();
	~Player();
	void Update();
	void PlaResporn(int x);		//プレイヤーを初期位置にリスポーンさせる関数
	void PlaDataUpdate(int x);	//プレイヤーの位置回転拡大率の情報更新関数

	//移動処理
	void PlaMove(int x);
	//回転処理
	void PlaTurn(int x);
	//攻撃準備処理
	void PlaAttackBefore(int x);
	//攻撃処理
	void PlaAtack(int x);
	//プレイヤーの状態
	void Joutai(int x);

	void PlaNowSpeed(int x);
};

