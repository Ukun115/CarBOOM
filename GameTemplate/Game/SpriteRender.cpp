///<<summary>
///画像表示処理
///</summary>

#include "stdafx.h"

namespace nsCARBOOM
{
	bool SpriteRender::Start()
	{
		return true;
	}

	SpriteRender::~SpriteRender()
	{

	}

	void SpriteRender::Update()
	{
		//位置、回転、拡大率を更新
		m_sprite.Update(m_pos, m_rot, m_sca);
	}

	//画像を初期化する関数
	void SpriteRender::Init(const char* filePath, float width, float height, AlphaBlendMode mode)
	{
		sprintf(m_filePath, "Assets/image/dds/%s.dds", filePath);
		m_spriteInitData.m_ddsFilePath[nsStdafx::INT_ZERO] = m_filePath;					//ファイルパス
		m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";		//シェーダーファイルのパスを指定
		m_spriteInitData.m_width = width;								//横幅
		m_spriteInitData.m_height = height;								//縦幅
		m_spriteInitData.m_alphaBlendMode = mode;						//透過

		m_sprite.Init(m_spriteInitData);
	}

	//描画関数
	void SpriteRender::Render(RenderContext& renderContext)
	{
		//ドロー関数
		m_sprite.Draw(renderContext);
	}
}