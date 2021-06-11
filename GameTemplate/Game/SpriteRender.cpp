#include "stdafx.h"

namespace
{

}

bool SpriteRender::Start()
{


	//Start�֐���return��
	return true;
}

SpriteRender::~SpriteRender()
{

}

void SpriteRender::Update()
{

	//�ʒu�A��]�A�g�嗦���X�V
	m_sprite.Update(m_pos,m_rot,m_sca);
}

void SpriteRender::Init(const char* filepath, float width, float height, AlphaBlendMode mode)
{
	m_spriteInitData.m_ddsFilePath[0] = filepath;					//�t�@�C���p�X
	m_spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";		//�V�F�[�_�[�t�@�C���̃p�X���w��
	m_spriteInitData.m_width = width;								//����
	m_spriteInitData.m_height = height;								//�c��
	m_spriteInitData.m_alphaBlendMode = mode;						//����

	m_sprite.Init(m_spriteInitData);
}

//���ꂪ�Ȃ��ƕ`�悳��Ȃ�
void SpriteRender::Render(RenderContext& renderContext)
{
	//�h���[�֐�
	m_sprite.Draw(renderContext);
}