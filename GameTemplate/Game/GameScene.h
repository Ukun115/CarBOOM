#pragma once


class TitleScene;
class StageSelectScene;
class Stage;
class Player;
class Enemy;
class Fade;
class ResultScene;


class GameScene :public IGameObject		//TODO:コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enumPlayerNum
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		TotalPlaNum	//プレイヤーの最大数
	};

	enum enumSoundNum
	{
		GameStartGingle,	//ゲームスタートジングル
		CountDownSound,		//カウントダウンサウンド
		GameBGM,			//ゲーム内BGM
		WhistleSound,		//ホイッスルサウンド
		PauseSound,			//ポーズサウンド
		DecideSound,
		TotalSoundNum
	};


	//列挙型
	enum enumState
	{
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};
	enum enumFade
	{
		FadeIn,
		FadeOut,
		TotalFade
	};


	/// <summary>
	/// クラスのポインタ
	/// </summary>
	Light* m_light = nullptr;
	Fade* m_fade[TotalFade] = { nullptr };
	TitleScene* m_titleScene = { nullptr };
	StageSelectScene* m_stageSelectScene = { nullptr };
	ResultScene* m_resultScene = { nullptr };
	Stage* m_stage = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_ScoreFontRender[TotalPlaNum] = { nullptr };
	FontRender* m_TextScoreFontRender[TotalPlaNum] = { nullptr };
	FontRender* m_timeLimit = nullptr;
	FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };
	SpriteRender* m_sprite[TotalPlaNum] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_grayBack = nullptr;
	SpriteRender* m_gameBackScreen = nullptr;
	SpriteRender* m_pauseSprite = nullptr;
	SoundPlayBack* m_soundPlayBack = nullptr;


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isFinishCountDownFlg = true;
	bool m_deleteFlg = false;
	bool m_isPauseFlg = false;
	bool m_pauseOkFlg = true;

	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_resultsenniTimer = INT_ZERO;
	unsigned int m_countDownTimer = INT_ZERO;
	int m_timer = 3600;	//3600/60 = 60秒
	int m_countTime = INT_ZERO;


	int m_plaScore[TotalPlaNum] = { INT_ZERO };
	Vector2 m_plaScorePos[TotalPlaNum];
	unsigned int m_nowNumOnePla = TotalPlaNum;
	wchar_t text1[64];	//制限時間フォント
	wchar_t text2[64];	//プレイヤースコアフォント


	int m_totalPlaNum = INT_ZERO;
	int m_stageSelecttNum = INT_ZERO;


	bool Start()override final;
	~GameScene()override final;
	void Update()override final;


	//制限時間処理関数
	void TimeLimit();
	//プレイヤーのスコア描画関数
	void PlaScoreDraw();
	//カウントダウン処理関数
	void CountDown();
	//プレイヤーごとのスコアの位置を指定する関数
	void SetScoreTextPos(const int plaNum);
	//プレイヤーごとの「pt」文字の位置を指定する関数
	Vector2 GetScorePos(const int plaNum);
	//プレイヤーごとのスコアの色を指定する関数
	Vector4 ScoreColor(const int plaNum);
	//１位に王冠画像と王冠モデルを渡す関数
	void NowCrown();
	//リザルト画面に遷移する関数
	void ResultSceneTransition();
	//PLAYERフォントの初期化をまとめている関数
	void InitPlayerFont();
	//プレイヤーのポイントフォントの初期化をまとめている関数
	void InitPlayerPtFont();
	//制限時間フォントの初期化をまとめている関数
	void InitTimeLimitFont();
	//ポーズ画面の画像の初期化をまとめている関数
	void InitPauseSceneImage();
	//ポーズ機能
	void PauseMenue();


public:

	/*プレイヤーの得点変動処理関数
	(plaNum1は落としたプレイヤー、plaNum2は自滅したプレイヤー)*/
	void GetPlayerAddScore(const int plaNum1, const int plaNum2);

	/// <summary>
	/// セッター
	/// </summary>
	//タイトルシーンで何人プレイヤーが追加されたかをステージセレクトシーンを中継にして持ってくる
	void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	//ステージなんぼが選ばれているかをゲームクラスに渡す
	void SetSelectStageNum(const int stageNum) { m_stageSelecttNum = stageNum ; }
	void SetDeleteFlg(const bool deleteFlg) { m_deleteFlg = deleteFlg; }

	/// <summary>
	/// ゲッター
	/// </summary>
	//現在の残り制限時間を取得する関数
	int GetNowTime()const { return m_countTime; }
	//ゲーム開始のカウントダウンを終了したかどうかのフラグを取得する関数
	bool GetCountDownFlg()const { return m_isFinishCountDownFlg; }
	//プレイヤーのスコアを取得する関数
	int GetPlaScore(const int x)const { return m_plaScore[x]; };
	//現在の１位のプレイヤーが誰かを取得
	int GetNumber1Player()const { return m_nowNumOnePla; }
};