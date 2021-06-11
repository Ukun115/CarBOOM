#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	bool addPlayer[4] = { false };		//プレイヤーが登録されたかの判別フラグ
	int m_totalPlayerNum = 1;			//プレイヤーの合計数

public:
	bool Start();
	~TitleScene();
	void Update();

	//プレイヤーが追加されているかのフラグを取得するゲット関数
	bool GetPlayerFlg(int x) { return addPlayer[x]; }
};