#pragma once
class StageSelectScene;


class TitleScene : public IGameObject
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_pushStartButtonSprite = nullptr;
	SpriteRender* m_plaActiveName[4] = { nullptr };		//プレイヤー4人分用意
	SpriteRender* m_plaDeactiveName[4] = { nullptr };		//プレイヤー4人分用意
	SpriteRender* m_pressASpeechBalloon[3] = { nullptr };
	StageSelectScene* m_stageSelectScene = nullptr;
	SoundSource* m_addPlayer = nullptr;
	SoundSource* m_gameNameGingle;	//ゲーム名ジングルサウンド
	SoundSource* m_titleCall;	//タイトルコールサウンド
	SoundSource* m_titleBGM;	//タイトルBGFMサウンド
	SoundSource* m_decideSound;	//スタートボタンが押されたときのサウンド


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isAddPlayerFlg[4] = { false };		//各プレイヤーが登録されているかの判別フラグ
	bool m_isCanStageSelectSceneFlg = true;			//trueのときはゲームスタートボタンを押せる
	bool m_isFlashingFontTimerActiveFlg = true;		//trueのとき点滅文字の表示タイミング
	bool m_isTitleCallOneShotFlg = true;		//trueのときタイトルコール再生可能


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_flashingFontTimer = 0;		//点滅文字の表示非表示の切り替えタイマー
	unsigned int m_titleCallDelayTimer = 0;


	unsigned int m_totalPlaNum = 1;			//プレイヤーの合計数を計測
	Vector3 m_pressASpeechBalloonPos = Vector3::Zero;		//プレイヤー追加吹き出しの位置


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum enumPlayer
	{
		Player1,		//1Pの配列での番号
		Player2,		//2Pの配列での番号
		Player3,		//3Pの配列での番号
		Player4,		//4Pの配列での番号
		MaxPlayerNum	//プレイヤーの最大数
	};

	enum soundNum
	{
		TitleSceneGingle,	//タイトルジングル
		TitleSceneBGM,		//タイトルシーンのBGM
		TitleCallSound,		//タイトルコール
		DecideSound,		//決定音
		EngineSound,		//エンジンサウンド
	};


	bool Start()override;
	~TitleScene()override;
	void Update()override;


	//プレイヤーを追加する関数
	void AddPlayer();
	//ゲーム画面に遷移する関数
	void StageSelectSceneTransition();
	//「PRESS START BUTTON」文字画像の点滅処理関数
	void FlashingFont();
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:

	/// <summary>
	/// ゲッター
	/// </summary>
	//プレイヤーが追加されているかどうかを取得する関数
	 bool GetPlaFlg(int planum) { return m_isAddPlayerFlg[planum]; }
	//登録されたプレイヤーの合計人数を取得する関数
	int GetTotalPlaNum(){ return m_totalPlaNum; }
};