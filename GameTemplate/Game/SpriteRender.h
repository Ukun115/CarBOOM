#pragma once
class SpriteRender : public IGameObject
{
private:
	Vector3    m_pos = Vector3::Zero;				//�ʒu(�����l:���_)
	Quaternion m_rot = Quaternion::Identity;		//��](�����l:0,0,0,1)
	Vector3    m_sca = Vector3::One;				//�g�嗦(�����l:1�{)
	Vector4    m_mulColor = Vector4::White;				//��Z(Multiply)�F(��)
							//���ڂ�����Vector�N���X���݂Ă�

	SpriteInitData m_spriteInitData;
	Sprite m_sprite;

public:
	bool Start();
	~SpriteRender();
	void Update();
	void Render(RenderContext& renderContext);

	void Init(const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);

	//�ʒu�̃Z�b�g�֐�
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	//��]�̃Z�b�g�֐�
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	//�g�嗦�̃Z�b�g�֐�
	void SetScale(const Vector3& sca) { m_sca = sca; }
	//�F�̃Z�b�g�֐�
	void SetMulColor(const Vector4& mulColor) { m_sprite.SetMulColor(mulColor); }

	//�F�𓾂�֐�
	const Vector4& GetMulColor() { return m_sprite.GetMulColor(); }
};