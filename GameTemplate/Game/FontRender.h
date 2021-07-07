#pragma once
#include "stdafx.h"

//フォントの構造体の定義
struct FontValue {

	wchar_t text[256];	//テキスト
	Vector2 position;	//位置
	Vector4 color;		//色
	float rotation;		//回転
	float scale;		//拡大率
	Vector2 pivot;		//基点
};


class FontRender : public IGameObject
{
private:

	Font m_font;				//フォントクラスを作成
	FontValue m_fontValue;		//フォント構造体のデータを作成

public:

	//フォントの初期化関数
	void Init(
		const wchar_t* text,						//テキスト
		const Vector2 position = Vector2::Zero,		//位置
		Vector4 color = Vector4::Black,				//色
		float rotation = 0.0f,						//回転
		float scale = 1.0f,							//拡大率
		Vector2 pivot = { 0.5f,0.5f }				//基点
	);
	//描画関数
	void Render(RenderContext& rc)override	final;


	/// <summary>
	/// セッター
	/// </summary>
	//テキストを設定する関数
	void SetText(const wchar_t* text){swprintf_s(m_fontValue.text, text);}
	//テキストの位置を設定する関数
	void SetPosition(const Vector2& pos) {m_fontValue.position = pos;}
	//テキストの拡大率を設定する関数
	void SetScale(float sca) {m_fontValue.scale = sca;}
	//テキストの色を設定する関数
	void SetColor(const Vector4& col) {m_fontValue.color = col;}
	//テキストの基点を設定する関数
	void SetPivot(const Vector2& piv) {m_fontValue.pivot = piv;}
	//テキストの枠の影を設定する関数
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
	{m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);}
};