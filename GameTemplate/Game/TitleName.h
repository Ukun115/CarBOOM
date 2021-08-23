///<<summary>
///タイトル名のムーブ処理
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleName : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:
		enum enTitleSpriteNum
		{
			TitleSprite1,
			TotalTitleSpriteNum = 9
		};

		SpriteRender* m_titleBaraBaraSprite[TotalTitleSpriteNum] = { nullptr };

		char m_filePath[256];
		Vector3 m_titleBaraBaraSpritePos[TotalTitleSpriteNum];
		int m_waveTimer = 0;
		int m_verticalMoveTimer[TotalTitleSpriteNum] = { 0 };

		bool Start()override final;
		~TitleName()override final;
		void Update()override final;

		//画像が縦移動する関数
		void VerticalMove(const int width, const float speed, const int spriteNum);
		//タイトル名をウェーブさせる関数
		void TitleNameWave();

	public:

	};
}