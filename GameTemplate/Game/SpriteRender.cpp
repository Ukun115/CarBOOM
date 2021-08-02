///<<summary>
///�摜�\������
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
		//�ʒu�A��]�A�g�嗦���X�V
		m_sprite.Update(m_pos, m_rot, m_sca);
	}


	//�摜������������֐�
	void SpriteRender::Init(const char* filePath, float width, float height, AlphaBlendMode mode)
	{
		sprintf(m_filePath, "Assets/image/dds/%s.dds", filePath);
		m_spriteInitData.m_ddsFilePath[0] = m_filePath;					//�t�@�C���p�X
		m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";		//�V�F�[�_�[�t�@�C���̃p�X���w��
		m_spriteInitData.m_width = width;								//����
		m_spriteInitData.m_height = height;								//�c��
		m_spriteInitData.m_alphaBlendMode = mode;						//����

		m_sprite.Init(m_spriteInitData);
	}


	//�`��֐�
	void SpriteRender::Render(RenderContext& renderContext)
	{
		//�h���[�֐�
		m_sprite.Draw(renderContext);
	}
}