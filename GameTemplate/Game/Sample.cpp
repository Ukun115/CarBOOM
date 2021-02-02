#include "stdafx.h"
#include "Sample.h"
#include "../../ExEngine/level2D/CaslFile.h"

bool Sample::Start()
{
	CaslFile cl;
	cl.Load("Assets/level.casl");
	auto objList = cl.Finds("c1");
	int a = 0;
	//Vector3 pos2;
	//Sprite sprite[2];

	//Vector3 pos[2];
	for (int i = 0; i < objList.size(); i++)
	{
		auto obj = objList[i];
		SpriteInitData data;
		data.m_width = obj->width;
		data.m_height = obj->height;
		data.m_ddsFilePath[0] = "Assets/Image/cr.dds";
		data.m_fxFilePath = "Assets/shader/sprite.fx";
		m_sprite[i].Init(data);
		m_position[i].x = obj->position.x;
		m_position[i].y = obj->position.y;
		m_position[i].z = 1.0f;
		m_scale[i].x = obj->scale.x;
		m_scale[i].y = obj->scale.y;
		m_scale[i].z = 1.0f;
	}
	
	auto obj = cl.Find("c2");
	SpriteInitData data;
	data.m_width = obj->width;
	data.m_height = obj->height;
	data.m_ddsFilePath[0] = "Assets/Image/cr.dds";
	data.m_fxFilePath = "Assets/shader/sprite.fx";
	m_sprite[2].Init(data);
	m_position[2].x = obj->position.x;
	m_position[2].y = obj->position.y;
	m_position[2].z = 1.0f;
	m_scale[2].x = obj->scale.x;
	m_scale[2].y = obj->scale.y;
	m_scale[2].z = 1.0f;

	return true;
}

void Sample::Update()
{
	m_sprite[0].Update(m_position[0], Quaternion::Identity, m_scale[0]);
	m_sprite[1].Update(m_position[1], Quaternion::Identity, m_scale[1]);
	m_sprite[2].Update(m_position[2], Quaternion::Identity, m_scale[2]);
}


