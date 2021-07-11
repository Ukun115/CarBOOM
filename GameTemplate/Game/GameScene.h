#pragma once

class Player;
class Enemy;
class Stage;
class TitleScene;


class GameScene :public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	TitleScene* m_titleScene = { nullptr };
	Stage* m_normalStage = { nullptr };
	SpriteRender* m_sprite[4]{ nullptr };
	SpriteRender* m_crownSprite{ nullptr };
	FontRender* m_ScoreFontRender[4]{ nullptr };
	FontRender* m_TextScoreFontRender[4]{ nullptr };
	Player* m_player{ nullptr };
	Enemy* m_enemy{ nullptr };
	FontRender* m_timeLimit{ nullptr };
	SoundSource* m_gameStartGingle{ nullptr };	//クラクションサウンド
	SoundSource* m_gameBGM{ nullptr };	//ゲーム中のBGMサウンド
	SoundSource* m_countDown{ nullptr };	//カウントダウンサウンド
	SpriteRender* m_syutyusen{ nullptr };
	SoundSource* m_whistleSound{ nullptr };


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isFinishCountDownFlg{ true };


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_resultsenniTimer{ 0 };
	unsigned int m_countDownTimer{ 0 };
	int m_timer{ 360 };	//3600/60 = 60秒
	int m_countTime{ 0 };


	int m_plaScore[4] = { 0 };
	Vector2 m_plaScorePos[4];
	unsigned int m_nowNumOnePla{ 0 };
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

	enum soundNum
	{
		GameStartGingle,	//ゲームスタートジングル
		CountDownSound,		//カウントダウンサウンド
		GameBGM,			//ゲーム内BGM
		WhistleSound,		//ホイッスルサウンド
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
	/// ゲッター
	/// </summary>
	//現在の残り制限時間を取得する関数
	int GetNowTime() { return m_countTime; }
	//ゲーム開始のカウントダウンを終了したかどうかのフラグを取得する関数
	bool GetCountDownFlg() { return m_isFinishCountDownFlg; }
	//プレイヤーのスコアを取得する関数
	int GetPlaScore(int x) { return m_plaScore[x]; };
};