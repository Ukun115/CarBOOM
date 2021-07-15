#pragma once
class GameScene;
class Player;
class StageSelectScene;
class TitleScene;
class Fade;


class ResultScene : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	/// <summary>
	/// クラスのポインタ
	/// </summary>
	GameScene* m_gameScene = nullptr;
	Fade* m_fadeOut = nullptr;
	StageSelectScene* m_stageSelectScene = nullptr;
	Player* m_player = nullptr;
	TitleScene* m_titleScene = nullptr;
	SpriteRender* m_resultSprite = nullptr;
	SpriteRender* m_plaNum[4] = { nullptr };			//プレイヤー4人分用意
	SpriteRender* m_rankingSprite[4] = { nullptr };	//プレイヤー4人分用意
	SoundSource* m_resultGingle = nullptr;
	SoundSource* m_gameBGM = nullptr;	//ゲーム中のBGMサウンド
	SoundSource* m_decideSound = nullptr;	//決定サウンド


	/// <summary>
	/// フラグ
	/// </summary>
	bool m_enableTimerCountFlg = false;
	bool m_pla4MoveFlg = false;
	bool m_pla3MoveFlg = false;
	bool m_pla2MoveFlg = false;
	bool m_pla1MoveFlg = false;
	bool m_delayTimerOnFlg = true;
	bool m_plaJumpFlg = false;
	bool m_muriFlg = false;


	/// <summary>
	/// タイマー
	/// </summary>
	unsigned int m_exitTimer = 0;
	int m_plaMoveDelayTimer = 0;
	int m_verticalMoveTimer = 0;


	unsigned int m_plaScore[4] = { 0 };		//プレイヤー4人分のスコアを入れる配列
	int m_totalPlaNum = 0;

	unsigned int m_select = 0;
	float m_moveSpeed = 0.0f;

	Vector3 m_number1Pos = { 900.0f,50.0f,0.0f };		//１位プレイヤーの表示位置
	Vector3 m_number2Pos = { 900.0f,-50.0f,0.0f };		//２位プレイヤーの表示位置
	Vector3 m_number3Pos = { 900.0f,-150.0f,0.0f };	//３位プレイヤーの表示位置
	Vector3 m_number4Pos = { 900.0f,-250.0f,0.0f };	//４位プレイヤーの表示位置


	/// <summary>
	/// 列挙型の宣言
	/// </summary>
	enum SoundNum
	{
		ResultGingle,
		GameBGM,
		DecideSound,
	};

	//列挙型
	enum enumState
	{
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};


	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//順位によってソートしプレイヤー名の画像を並び替える関数
	void RankingSort();
	//次どのシーンに行くか切り替える関数
	void SelectScene();
	//プレイヤーが画面外（右側）からスライドしてくる処理関数
	void SlidePlayerName();
	//画像が縦移動する関数
	void VerticalMove(int width, float speed);
	//サウンドを一括にまとめる関数
	void SoundPlayBack(int soundNum);


public:
	void SetTotalPlayerNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
};

