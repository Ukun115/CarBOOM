#pragma once

class Player;
class Enemy;
class Stage;
class TitleScene;
class ResultScene;
class Fade;
class StageSelectScene;


class GameScene :public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	Light* m_light = nullptr;
	Fade* m_fadeIn = nullptr;
	Fade* m_fadeOut = nullptr;
	TitleScene* m_titleScene = { nullptr };
	StageSelectScene* m_stageSelectScene = { nullptr };
	ResultScene* m_resultScene = { nullptr };
	Stage* m_stage = { nullptr };
	SpriteRender* m_sprite[4] = { nullptr };
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_grayBack = nullptr;
	FontRender* m_ScoreFontRender[4] = { nullptr };
	FontRender* m_TextScoreFontRender[4] = { nullptr };
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
	FontRender* m_timeLimit = nullptr;
	SoundSource* m_gameStartGingle = nullptr;	//クラクションサウンド
	SoundSource* m_gameBGM = nullptr;	//ゲーム中のBGMサウンド
	SoundSource* m_countDown = nullptr;	//カウントダウンサウンド
	SpriteRender* m_syutyusen = nullptr;
	SpriteRender* m_pauseSprite = nullptr;
	SoundSource* m_whistleSound = nullptr;
	SoundSource* m_pauseSound = nullptr;
	SoundSource* m_decideSound = nullptr;
	FontRender* m_PlaNameFont[4] = { nullptr };


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
	unsigned int m_resultsenniTimer = 0;
	unsigned int m_countDownTimer = 0;
	int m_timer = 360;	//3600/60 = 60秒
	int m_countTime = 0;


	int m_plaScore[4] = { 0 };
	Vector2 m_plaScorePos[4];
	unsigned int m_nowNumOnePla = 4;
	wchar_t text1[64];	//制限時間フォント
	wchar_t text2[64];	//プレイヤースコアフォント


	int m_totalPlaNum = 0;
	int m_stageSelecttNum = 0;


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enumPlayerNum
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		MaxPlayerNum	//プレイヤーの最大数
	};

	enum enumSoundNum
	{
		GameStartGingle,	//ゲームスタートジングル
		CountDownSound,		//カウントダウンサウンド
		GameBGM,			//ゲーム内BGM
		WhistleSound,		//ホイッスルサウンド
		PauseSound,			//ポーズサウンド
		DecideSound
	};


	//列挙型
	enum enumState
	{
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};


	bool Start()override;
	~GameScene()override;
	void Update()override;


	//制限時間処理関数
	void TimeLimit();
	//プレイヤーのスコア描画関数
	void PlaScoreDraw();
	//カウントダウン処理関数
	void CountDown();
	//プレイヤーごとのスコアの位置を指定する関数
	void SetScoreTextPos(int plaNum);
	//プレイヤーごとの「pt」文字の位置を指定する関数
	Vector2 GetScorePos(int plaNum);
	//プレイヤーごとのスコアの色を指定する関数
	Vector4 ScoreColor(int plaNum);
	//１位に王冠画像と王冠モデルを渡す関数
	void NowCrown();
	//リザルト画面に遷移する関数
	void ResultSceneTransition();
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:

	/*プレイヤーの得点変動処理関数
	(plaNum1は落としたプレイヤー、plaNum2は自滅したプレイヤー)*/
	void GetPlayerAddScore(int plaNum1, int plaNum2);

	/// <summary>
	/// セッター
	/// </summary>
	//タイトルシーンで何人プレイヤーが追加されたかをステージセレクトシーンを中継にして持ってくる
	void SetTotalPlaNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	//ステージなんぼが選ばれているかをゲームクラスに渡す
	void SetSelectStageNum(int stageNum) { m_stageSelecttNum = stageNum ; }
	void SetDeleteFlg(bool deleteFlg) { m_deleteFlg = deleteFlg; }

	/// <summary>
	/// ゲッター
	/// </summary>
	//現在の残り制限時間を取得する関数
	int GetNowTime() { return m_countTime; }
	//ゲーム開始のカウントダウンを終了したかどうかのフラグを取得する関数
	bool GetCountDownFlg() { return m_isFinishCountDownFlg; }
	//プレイヤーのスコアを取得する関数
	int GetPlaScore(int x) { return m_plaScore[x]; };
	//現在の１位のプレイヤーが誰かを取得
	int GetNumber1Player() { return m_nowNumOnePla; }
};