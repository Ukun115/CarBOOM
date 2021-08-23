///<<summary>
///フェードインフェードアウト処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Fade :public IGameObject	//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		//列挙型
		enum enState {
			StateIn,	//フェードイン
			StateOut,	//フェードアウト
			StateWait,	//待機
		};

		SpriteRender* m_fadeSprite = nullptr;

		//画像のα値
		float m_alphaValue = nsStdafx::FLOAT_ZERO;
		int m_nowState = nsStdafx::INT_ZERO;  //現在のステート

		bool Start()override final;
		~Fade()override final;
		void Update()override final;

	public:
		//ゲッター
		float GetAlphaValue()const { return m_alphaValue; }
		int GetNowState()const { return m_nowState; }
		//セッター
		void SetAlphaValue(const float alphaValue) { m_alphaValue = alphaValue; }
		void SetState(const int newState) { m_nowState = newState; }
	};
}