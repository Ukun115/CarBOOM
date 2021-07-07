#pragma once
#include "stdafx.h"

//�t�H���g�̍\���̂̒�`
struct FontValue {

	wchar_t text[256];	//�e�L�X�g
	Vector2 position;	//�ʒu
	Vector4 color;		//�F
	float rotation;		//��]
	float scale;		//�g�嗦
	Vector2 pivot;		//��_
};


class FontRender : public IGameObject
{
private:

	Font m_font;				//�t�H���g�N���X���쐬
	FontValue m_fontValue;		//�t�H���g�\���̂̃f�[�^���쐬

public:

	//�t�H���g�̏������֐�
	void Init(
		const wchar_t* text,						//�e�L�X�g
		const Vector2 position = Vector2::Zero,		//�ʒu
		Vector4 color = Vector4::Black,				//�F
		float rotation = 0.0f,						//��]
		float scale = 1.0f,							//�g�嗦
		Vector2 pivot = { 0.5f,0.5f }				//��_
	);
	//�`��֐�
	void Render(RenderContext& rc)override	final;


	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	//�e�L�X�g��ݒ肷��֐�
	void SetText(const wchar_t* text){swprintf_s(m_fontValue.text, text);}
	//�e�L�X�g�̈ʒu��ݒ肷��֐�
	void SetPosition(const Vector2& pos) {m_fontValue.position = pos;}
	//�e�L�X�g�̊g�嗦��ݒ肷��֐�
	void SetScale(float sca) {m_fontValue.scale = sca;}
	//�e�L�X�g�̐F��ݒ肷��֐�
	void SetColor(const Vector4& col) {m_fontValue.color = col;}
	//�e�L�X�g�̊�_��ݒ肷��֐�
	void SetPivot(const Vector2& piv) {m_fontValue.pivot = piv;}
	//�e�L�X�g�̘g�̉e��ݒ肷��֐�
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
	{m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);}
};