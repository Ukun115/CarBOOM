#pragma once


class SpriteRender : public IGameObject
{
private:

	SpriteInitData m_spriteInitData;	//�X�v���C�g�C�j�b�g�f�[�^�\���̂̃f�[�^���쐬
	Sprite m_sprite;					//�X�v���C�g�N���X���쐬


	Vector3    m_pos = Vector3::Zero;			//�ʒu(�����l:���_)
	Quaternion m_rot = Quaternion::Identity;	//��](�����l:0,0,0,1)
	Vector3    m_sca = Vector3::One;			//�g�嗦(�����l:1�{)
	Vector4    m_mulColor = Vector4::White;		//��Z(Multiply)�F(��)
							//���ڂ�����Vector�N���X���݂Ă�

public:

	bool Start()override;
	~SpriteRender()override;
	void Update()override;


	//�摜������������֐�
	void Init(const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	//�`��֐�
	void Render(RenderContext& renderContext);


	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	//�摜�̈ʒu��ݒ肷��֐�
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	//�摜�̉�]��ݒ肷��֐�
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	//�摜�̊g�嗦��ݒ肷��֐�
	void SetScale(const Vector3& sca) { m_sca = sca; }
	//�摜�̐F��ݒ肷��֐�
	void SetMulColor(const Vector4& mulColor) { m_sprite.SetMulColor(mulColor); }
};