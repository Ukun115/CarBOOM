#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_pushStartButtonSprite = nullptr;

	SpriteRender* m_plaDeactiveName[4] = {nullptr};		//スプライトレンダー
	SpriteRender* m_plaActiveName[4] = {nullptr};		//スプライトレンダー
	bool isAddPlayer[4] = { false };		//プレイヤーが登録されたかの判別フラグ
	int m_totalPlayerNum = 1;			//プレイヤーの合計数
	bool isCanGameStartFlg = true;		//trueのときはゲームスタートボタンを押せる

	int m_buttonTimer = 0;
	bool m_buttonTimerFlg = true;

public:
	bool Start()override;
	~TitleScene()override;
	void Update()override;

	//プレイヤーが追加されているかのフラグを取得する関数
	bool GetPlaFlg(int x) { return isAddPlayer[x]; }
};