#pragma once
class SpriteRender : public IGameObject
{
private:
	Vector3    m_pos = Vector3::Zero;				//位置(初期値:原点)
	Quaternion m_rot = Quaternion::Identity;		//回転(初期値:0,0,0,1)
	Vector3    m_sca = Vector3::One;				//拡大率(初期値:1倍)
	Vector4    m_mulColor = Vector4::White;				//乗算(Multiply)色(白)
							//↑詳しくはVectorクラスをみてね

	SpriteInitData m_spriteInitData;
	Sprite m_sprite;

public:
	bool Start();
	~SpriteRender();
	void Update();
	void Render(RenderContext& renderContext);

	void Init(const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);

	//位置のセット関数
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	//回転のセット関数
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	//拡大率のセット関数
	void SetScale(const Vector3& sca) { m_sca = sca; }
	//色のセット関数
	void SetMulColor(const Vector4& mulColor) { m_sprite.SetMulColor(mulColor); }

	//色を得る関数
	const Vector4& GetMulColor() { return m_sprite.GetMulColor(); }
};