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
<<<<<<< HEAD
	swprintf_s(m_fontValue.text, text);	//テキスト
	m_fontValue.position = position;	//位置
	m_fontValue.color = color;			//色
	m_fontValue.rotation = rotation;	//回転
	m_fontValue.scale = scale;			//拡大率
	m_fontValue.pivot = pivot;			//基点
=======
	swprintf_s(m_fontValue.text, text);
	m_fontValue.position = position;
	m_fontValue.color = color;
	m_fontValue.rotation = rotation;
	m_fontValue.scale = scale;
	m_fontValue.pivot = pivot;
>>>>>>> remotes/origin/master
}

//描画関数
void FontRender::Render(RenderContext& rc)
{
		m_font.Begin(rc);

		m_font.Draw
		(
			m_fontValue.text,		//テキスト
			m_fontValue.position,	//位置
			m_fontValue.color,		//色
			m_fontValue.rotation,	//回転
			m_fontValue.scale,		//拡大率
			m_fontValue.pivot		//基点
		);

		m_font.End(rc);
}