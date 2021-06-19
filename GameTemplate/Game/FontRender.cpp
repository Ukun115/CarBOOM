#include "stdafx.h"


//�t�H���g�̏������֐�
void FontRender::Init
(
	const wchar_t* text,		//�e�L�X�g
	const Vector2 position,		//�ʒu
	Vector4 color,				//�F
	float rotation,				//��]
	float scale,				//�g�嗦
	Vector2 pivot		)		//��_
{
	/// <summary>
	/// �t�H���g�\���̂ɏ������Őݒ肵���f�[�^����
	/// </summary>
	swprintf_s(m_fontValue.text, text);
	m_fontValue.position = position;
	m_fontValue.color = color;
	m_fontValue.rotation = rotation;
	m_fontValue.scale = scale;
	m_fontValue.pivot = pivot;
}

//�`��֐�
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