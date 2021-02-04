#pragma once

struct CaslData;
//マップチップレンダラー2D。
class MapChipRender2D : public IGameObject
{
public:
	void Init(CaslData* caslData);

	void Update()
	{
		m_sprite.Update(m_position, m_rotation, m_scale);
	}

	void Render(RenderContext& renderContext)
	{
		m_sprite.Draw(renderContext);
	}
private:
	Vector3 m_position = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_scale = Vector3::One;
	Sprite m_sprite;
};

