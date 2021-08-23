///<<summary>
///PressA!!吹き出し画像のムーブ処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PressASpeechBalloon : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enNowState
		{
			Player3SidePos = 1,
			Player4SidePos,
			Delete
		};

		SpriteRender* m_pressASpeechBalloon = { nullptr };
		SpriteRender* m_pressASpeechBalloonArrow = { nullptr };

		Vector3 m_pressASpeechBalloonPos;		//プレイヤー追加吹き出しの位置
		Vector3 m_arrowSca;

		/// <summary>
		/// タイマー
		/// </summary>
		int m_sideMoveTimer = nsStdafx::INT_ZERO;

		bool Start()override final;
		~PressASpeechBalloon()override final;
		void Update()override final;

	public:
		void NextState(const int nowState);
	};
}