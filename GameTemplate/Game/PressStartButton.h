///<<summary>
///PRESS START BUTTON のムーブ処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PressStartButton : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		SpriteRender* m_pressStartButtonSprite = { nullptr };

		/// <summary>
		/// タイマー
		/// </summary>
		unsigned int m_flashingFontTimer = { nsStdafx::INT_ZERO };		//点滅文字の表示非表示の切り替えタイマー

		bool m_isFlashingFontActiveFlg = { true };		//trueのとき点滅文字の表示タイミング

		bool Start()override final;
		~PressStartButton()override final;
		void Update()override final;

	public:

	};
}