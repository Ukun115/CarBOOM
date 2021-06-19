#include "stdafx.h"


//フォントの初期化関数
void FontRender::Init
(
	const wchar_t* text,		//テキスト
	const Vector2 position,		//位置
	Vector4 color,				//色
	float rotation,				//回転
	float scale,				//拡大率
	Vector2 pivot		)		//基点
{
	/// <summary>
	/// フォント構造体に初期化で設定したデータを代入
	/// </summary>
	swprintf_s(m_fontValue.text, text);
	m_fontValue.position = position;
	m_fontValue.color = color;
	m_fontValue.rotation = rotation;
	m_fontValue.scale = scale;
	m_fontValue.pivot = pivot;
}

//描画関数
void FontRender::Render(RenderContext& rc)
{
		m_font.Begin(rc);

		m_font.Draw
		(
			m_fontValue.text,
			m_fontValue.position,
			m_fontValue.color,
			m_fontValue.rotation,
			m_fontValue.scale,
			m_fontValue.pivot
		);

		m_font.End(rc);
}