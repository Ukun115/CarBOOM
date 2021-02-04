#include "stdafx.h"
#include "MapChipRender2D.h"
#include "CaslFile.h"

void MapChipRender2D::Init(CaslData* caslData)
{
	SpriteInitData data;
	data.m_width = caslData->width;
	data.m_height = caslData->height;
	data.m_ddsFilePath[0] =  caslData->ddsFileName.get();
	data.m_fxFilePath = "Assets/shader/sprite.fx";
	m_sprite.Init(data);
	m_position.x = caslData->position.x;
	m_position.y = caslData->position.y;
	m_scale.x = caslData->scale.x;
	m_scale.y = caslData->scale.y;
}


