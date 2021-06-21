#pragma once

class Player;
class Enemy;
class Stage;
class TitleScene;


class GameScene :public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = nullptr;
	Stage* m_normalStage = nullptr;
	SkinModelRender* m_crownModel = nullptr;
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_timeLimit = nullptr;


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isCountTimeFlg = true;


	/// <summary>
	/// タイマー
	/// </summary>


	int m_counttime = 0;
	int m_timer = 3600;	//60秒
	int m_plscore[4] = { 0 };
<<<<<<< HEAD
	unsigned int m_countDownTimer = 0;
	unsigned int m_nowNumOnePla = 0;
	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};
	unsigned int m_resultsenniTimer = 0;
	wchar_t text1[64];	//制限時間フォント
	wchar_t text2[64];	//プレイヤースコアフォント


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
=======
	int m_countDownTimer = 0;
	int m_nowNumOnePla = 0;
	Vector3 m_crownModelPos = {0.0f,0.0f,0.0f};
	int m_resultsenniTimer = 0;
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
	~GameScene()override;
	void Update()override;


<<<<<<< HEAD
	//制限時間処理関数
	void TimeLimit();
	//プレイヤーのスコア描画関数
	void PlaScoreDraw();
	//カウントダウン処理関数
	void CountDown();
=======
>>>>>>> remotes/origin/master
	//プレイヤーごとのスコアの位置を指定する関数
	Vector2 SetScoreTextPos(int t);
	//プレイヤーごとの「pt」文字の位置を指定する関数
	Vector2 GetScorePos(int x);
	//プレイヤーごとのスコアの色を指定する関数
	Vector4 ScoreColor(int c);
	/*プレイヤーの得点変動処理関数
     (ｘは落としたプレイヤー、yは自滅したプレイヤー)*/
	void GetPlayerAddScore(int x,int y);
	//１位に王冠画像と王冠モデルを渡す関数
	void NowCrown();
<<<<<<< HEAD
	//リザルト画面に遷移する関数
	void ResultSceneTransition();
=======
>>>>>>> remotes/origin/master


	/// <summary>
	/// ゲット関数
	/// </summary>
	//現在の残り制限時間を取得する関数
	int GetNowTime() { return m_counttime; }
	//ゲーム開始のカウントダウンを終了したかどうかのフラグを取得する関数
	bool GetCountDownFlg() { return m_isCountTimeFlg; }
	//プレイヤーのスコアを取得する関数
	int GetPlaScore(int x) { return m_plscore[x]; };
};