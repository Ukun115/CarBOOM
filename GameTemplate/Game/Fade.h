#pragma once


class Fade:public IGameObject	//TODO:コピー禁止ポリシーを継承する。
{
private:

	//列挙型
	enum enumState {
		StateIn,	//フェードイン
		StateOut,	//フェードアウト
		StateWait,	//待機
	};


	SpriteRender* m_fadeSprite = nullptr;


	//画像のα値
	float m_alphaValue = FLOAT_ZERO;
	int m_nowState = 0;  //現在のステート

	bool Start()override final;
	~Fade()override final;
	void Update()override final;

public:
	//現在のα値を得る
	float GetAlphaValue()const { return m_alphaValue; }
	void SetAlphaValue(const float alphaValue) { m_alphaValue = alphaValue; }
	//現在の状態を得る
	int GetNowState()const { return m_nowState; }
	void SetState(const int newState) { m_nowState = newState; }
};