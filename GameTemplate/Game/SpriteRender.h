#pragma once
class SpriteRender : public IGameObject
{
private:
	bool Start();
	~SpriteRender();
	void Update();

	Vector3    m_pos      = Vector3::Zero;				//�ʒu(�����l:���_)
	Quaternion m_rot      = Quaternion::Identity;		//��](�����l:0,0,0,1)
	Vector3    m_sca      = Vector3::One;				//�g�嗦(�����l:1�{)
	Vector4    m_mulColor = Vector4::White;				//��Z(Multiply)�F(��)
							//���ڂ�����Vector�N���X���݂Ă�

public:
};

