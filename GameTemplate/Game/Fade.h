#pragma once


class Fade:public IGameObject
{
private:
	SpriteRender* m_fadeSprite = nullptr;
	//画像のα値
	float m_alphaValue = 0.0f;

	int m_nowState;  //現在のステート

	bool Start()override;
	~Fade()override;
	void Update()override;

	//列挙型
	enum enumState {
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};

public:
	//現在のα値を得る
	float GetAlphaValue() { return m_alphaValue; }
	void SetAlphaValue(float alphaValue) { m_alphaValue = alphaValue; }
	//現在の状態を得る
	int GetNowState() { return m_nowState; }
	void SetState(int newState) { m_nowState = newState; }
};