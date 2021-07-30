#pragma once
class StageSelectScene;
class Fade;


class TitleScene : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
{
private:
	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enPlayer
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		TotalPlaNum	//プレイヤーの最大数
	};

	enum enSoundNum
	{
		TitleSceneGingle,	//タイトルジングル
		TitleSceneBGM,		//タイトルシーンのBGM
		DecideSound,		//決定音
		EngineSound,		//エンジンサウンド
		TotalSoundNum
	};

	enum enFadeState
	{
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};
	enum enFadeNum
	{
		FadeIn,
		FadeOut,
		TotalFadeNum
	};

	enum enNextScene
	{
		StateSelectScene,
		GameEnd
	};


	/// <summary>
	/// クラスのポインタ
	/// </summary>
	Fade* m_fade[TotalFadeNum] = { nullptr };
	SoundPlayBack* m_soundPlayBack = nullptr;
	StageSelectScene* m_stageSelectScene = { nullptr };
	SpriteRender* m_titleSprite = { nullptr };
	SpriteRender* m_titleBaraBaraSprite[9] = { nullptr };
	SpriteRender* m_titleNameSprite = { nullptr };
	SpriteRender* m_pushStartButtonSprite = { nullptr };
	SpriteRender* m_plaActiveName[TotalPlaNum] = { nullptr };		//プレイヤー4人分用意
	SpriteRender* m_plaDeactiveName[TotalPlaNum] = { nullptr };		//プレイヤー4人分用意
	SpriteRender* m_pressASpeechBalloon = { nullptr };
	SpriteRender* m_pressASpeechBalloonArrow = { nullptr };
	FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isAddPlayerFlg[TotalPlaNum] = { false };		//各プレイヤーが登録されているかの判別フラグ
	bool m_enableUpdateFlg = { true };			//trueのときはゲームスタートボタンを押せる
	bool m_isFlashingFontActiveFlg = { true };		//trueのとき点滅文字の表示タイミング


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_flashingFontTimer = { nsStdafx::INT_ZERO };		//点滅文字の表示非表示の切り替えタイマー
	int m_sideMoveTimer = nsStdafx::INT_ZERO;
	int m_waveTimer = nsStdafx::INT_ZERO;
	int m_verticalMoveTimer[9] = { nsStdafx::INT_ZERO };


	float m_scaUpValue = 0.0f;
	Vector3 m_titleNameSca;
	unsigned int m_totalPlaNum = { 1 };			//プレイヤーの合計数を計測
	Vector3 m_pressASpeechBalloonPos;		//プレイヤー追加吹き出しの位置
	Vector3 m_arrowSca;
	Vector3 m_titleBaraBaraSpritePos[9];

	int m_nextScene = nsStdafx::INT_ZERO;

	char m_filePath[256];


	bool Start()override final;
	~TitleScene()override final;
	void Update()override final;


	//プレイヤーを追加する関数
	void AddPlayer();
	//ゲーム画面に遷移する関数
	void StageSelectSceneTransition();
	//「PRESS START BUTTON」文字画像の点滅処理関数
	void FlashingFont();
	//画像が横移動する関数
	void SideMove(const int width, const float speed);
	//画像が縦移動する関数
	void VerticalMove(const int width, const float speed, const int spriteNum);
	//タイトル名を拡大する関数
	void TitleNameScaUp();
	//タイトル名をウェーブさせる関数
	void TitleNameWave();
	//スタートボタンが押されたときの処理関数
	void PushStartButton(int plaNum);
	//ボタンが押されたときの処理関数
	void PushSelectButton(int plaNum);
	//選択された次のシーンに行く処理関数
	void NextScene();
	//PLAYERフォントの初期化をまとめている関数
	void InitPlayerFont();
	//タイトル画面の画像の初期化をまとめている関数
	void InitTitleSceneImage();


public:
};