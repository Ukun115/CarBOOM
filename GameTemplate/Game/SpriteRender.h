#pragma once
class SpriteRender : public IGameObject
{
private:
	bool Start();
	~SpriteRender();
	void Update();

	Vector3    m_pos      = Vector3::Zero;				//位置(初期値:原点)
	Quaternion m_rot      = Quaternion::Identity;		//回転(初期値:0,0,0,1)
	Vector3    m_sca      = Vector3::One;				//拡大率(初期値:1倍)
	Vector4    m_mulColor = Vector4::White;				//乗算(Multiply)色(白)
							//↑詳しくはVectorクラスをみてね

public:
};

