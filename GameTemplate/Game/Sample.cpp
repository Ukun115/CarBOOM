#include "stdafx.h"
#include "Sample.h"


bool Sample::Start()
{
	int number = 0;
	Level2DObjectData data;
	//ƒŒƒxƒ‹‚ğ“Ç‚İ‚Ş
	m_level.Init("Assets/sprite/level.casl", [&](Level2DObjectData& objdata) {
		if (objdata.ForwardMatchName("C")) {
			number++;
			if (number == 1)
			{
				SpriteInitData data;
				data.m_width = objdata.width;
				data.m_height = objdata.height;
				data.m_ddsFilePath[0] = "Assets/Image/cr.dds";
				data.m_fxFilePath = "Assets/shader/sprite.fx";
				m_sprite[0].Init(data);
				m_position[0].x = objdata.position.x;
				m_position[0].y = objdata.position.y;
				m_position[0].z = 1.0f;
				m_scale[0].x = objdata.scale.x;
				m_scale[0].y = objdata.scale.y;
				m_scale[0].z = 1.0f;
				return true;
			}
			else {
				return false;
			}
		}
	
		return false;
	});

	//cl.Load("Assets/levela.casl");
	/*auto objList = cl.FindsNameMatch("c1");
	int a = 0;
	//Vector3 pos2;
	//Sprite sprite[2];

	//Vector3 pos[2];
	//‰æ‘œ‚Ì”‚¾‚¯“Ç‚İ‚ŞB
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
	
	auto obj = cl.FindNameMatch("c2");
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
	m_scale[2].z = 1.0f;*/

	return true;
}

void Sample::Update()
{
	m_sprite[0].Update(m_position[0], Quaternion::Identity, m_scale[0]);
	//m_sprite[1].Update(m_position[1], Quaternion::Identity, m_scale[1]);
	//m_sprite[2].Update(m_position[2], Quaternion::Identity, m_scale[2]);
	m_level.Update();
}


