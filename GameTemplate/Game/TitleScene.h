#pragma once


class TitleScene : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_pushStartButtonSprite = nullptr;
	SpriteRender* m_plaActiveName[4] = {nullptr};		//プレイヤー4人分用意
	SpriteRender* m_plaDeactiveName[4] = {nullptr};		//プレイヤー4人分用意


	/// <summary>
	/// フラグ
	/// </summary>
<<<<<<< HEAD
	bool m_isAddPlayerFlg[4] = { false };		//各プレイヤーが登録されているかの判別フラグ
	bool m_isCanGameStartFlg = true;			//trueのときはゲームスタートボタンを押せる
	bool m_isFlashingFontTimerActiveFlg = true;		//trueのとき点滅文字の表示タイミング


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_flashingFontTimer = 0;		//点滅文字の表示非表示の切り替えタイマー


	unsigned int m_totalPlaNum = 1;			//プレイヤーの合計数を計測
=======
	bool m_isAddPlayerFlg[4] = { false };		//プレイヤーが登録されたかの判別フラグ
	bool m_isCanGameStartFlg = true;		//trueのときはゲームスタートボタンを押せる
	bool m_isButtonTimerActiveFlg = true;


	/// <summary>
	/// タイマー
	/// </summary>
	int m_buttonTimer = 0;


	int m_totalPlayerNum = 1;			//プレイヤーの合計数を計測
>>>>>>> remotes/origin/master


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
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
	~TitleScene()override;
	void Update()override;


<<<<<<< HEAD
	//プレイヤーを追加する関数
	void AddPlayer();
	//ゲーム画面に遷移する関数
	void GameSceneTransition();
	//「PRESS START BUTTON」文字画像の点滅処理関数
	void FlashingFont();


=======
>>>>>>> remotes/origin/master
	/// <summary>
	/// ゲット関数
	/// </summary>
	//プレイヤーが追加されているかどうかを取得する関数
	bool GetPlaFlg(int x) { return m_isAddPlayerFlg[x]; }
	//登録されたプレイヤーの合計人数を取得する関数
<<<<<<< HEAD
	int GetTotalPlaNum(){ return m_totalPlaNum; }
=======
	int GetTotalPlaNum(){ return m_totalPlayerNum; }
>>>>>>> remotes/origin/master
};