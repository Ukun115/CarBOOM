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
<<<<<<< HEAD
	swprintf_s(m_fontValue.text, text);	//�e�L�X�g
	m_fontValue.position = position;	//�ʒu
	m_fontValue.color = color;			//�F
	m_fontValue.rotation = rotation;	//��]
	m_fontValue.scale = scale;			//�g�嗦
	m_fontValue.pivot = pivot;			//��_
=======
	swprintf_s(m_fontValue.text, text);
	m_fontValue.position = position;
	m_fontValue.color = color;
	m_fontValue.rotation = rotation;
	m_fontValue.scale = scale;
	m_fontValue.pivot = pivot;
>>>>>>> remotes/origin/master
}

//�`��֐�
void FontRender::Render(RenderContext& rc)
{
		m_font.Begin(rc);

		m_font.Draw
		(
			m_fontValue.text,		//�e�L�X�g
			m_fontValue.position,	//�ʒu
			m_fontValue.color,		//�F
			m_fontValue.rotation,	//��]
			m_fontValue.scale,		//�g�嗦
			m_fontValue.pivot		//��_
		);

		m_font.End(rc);
}