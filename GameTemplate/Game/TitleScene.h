#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender[4] = {nullptr};		//スプライトレンダー
	bool isAddPlayer[4] = { false };		//プレイヤーが登録されたかの判別フラグ
	int m_totalPlayerNum = 1;			//プレイヤーの合計数
	bool isCanGameStartFlg = true;		//trueのときはゲームスタートボタンを押せる

public:
	bool Start();
	~TitleScene();
	void Update();

	//プレイヤーが追加されているかのフラグを取得するゲット関数
	bool GetPlaFlg(int x) { return isAddPlayer[x]; }
};