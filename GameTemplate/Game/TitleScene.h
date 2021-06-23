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
	SpriteRender* m_plaActiveName[4] = {nullptr};		//プレイヤー4人分用意
	SpriteRender* m_plaDeactiveName[4] = {nullptr};		//プレイヤー4人分用意
	StageSelectScene* m_stageSelectScene = nullptr;


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_isAddPlayerFlg[4] = { false };		//各プレイヤーが登録されているかの判別フラグ
	bool m_isCanStageSelectSceneFlg = true;			//trueのときはゲームスタートボタンを押せる
	bool m_isFlashingFontTimerActiveFlg = true;		//trueのとき点滅文字の表示タイミング


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_flashingFontTimer = 0;		//点滅文字の表示非表示の切り替えタイマー


	unsigned int m_totalPlaNum = 1;			//プレイヤーの合計数を計測


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

public:

	bool Start()override;
	~TitleScene()override;
	void Update()override;


	//プレイヤーを追加する関数
	void AddPlayer();
	//ゲーム画面に遷移する関数
	void StageSelectSceneTransition();
	//「PRESS START BUTTON」文字画像の点滅処理関数
	void FlashingFont();


	/// <summary>
	/// ゲッター
	/// </summary>
	//プレイヤーが追加されているかどうかを取得する関数
	bool GetPlaFlg(int x) { return m_isAddPlayerFlg[x]; }
	//登録されたプレイヤーの合計人数を取得する関数
	int GetTotalPlaNum(){ return m_totalPlaNum; }
};