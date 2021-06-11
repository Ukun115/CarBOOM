#include "stdafx.h"

namespace
{

}

bool SpriteRender::Start()
{


	//Start関数のreturn文
	return true;
}

SpriteRender::~SpriteRender()
{

}

void SpriteRender::Update()
{

	//位置、回転、拡大率を更新
	m_sprite.Update(m_pos,m_rot,m_sca);
}

void SpriteRender::Init(const char* filepath, float width, float height, AlphaBlendMode mode)
{
	m_spriteInitData.m_ddsFilePath[0] = filepath;					//ファイルパス
	m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";		//シェーダーファイルのパスを指定
	m_spriteInitData.m_width = width;								//横幅
	m_spriteInitData.m_height = height;								//縦幅
	m_spriteInitData.m_alphaBlendMode = mode;						//透過

	m_sprite.Init(m_spriteInitData);
}

//これがないと描画されない
void SpriteRender::Render(RenderContext& renderContext)
{
	//ドロー関数
	m_sprite.Draw(renderContext);
}