#pragma once
#include "Light.h"
class Model;
class Light;

class SkinModelRender : public IGameObject
{
public:
	bool Start()override;
	~SkinModelRender()override;
	void Update()override;

private:

	Vector3    m_pos = Vector3::Zero;					//�ʒu
	Quaternion m_rot = Quaternion::Identity;			//��]
	Vector3    m_sca = Vector3::One;					//�g�嗦

	//���f�������������邽�߂̏���ݒ�
	ModelInitData m_modelInitData;
	//m_model�̓��f���N���X
	Model m_model;

	Light* m_light;

public:
	//3D���f�������[�h���邽�߂̏���ݒ肷��֐�
	void Init(const char* tkmFilePath);

	//�ʒu��ݒ肷��Z�b�g�֐�
	void SetPosition(const Vector3 pos) { m_pos = pos; }
	//�ʒu���擾����Q�b�g�֐�
	Vector3 GetPosition() { return m_pos; }
	//��]��ݒ肷��Z�b�g�֐�
	void SetRotation(const Quaternion rot) { m_rot = rot; }
	//�g�嗦��ݒ肷��Z�b�g�֐�
	void SetScale(const Vector3 sca) { m_sca = sca; }

	Model* GetModel() { return &m_model ; }

	//�`��֐�
	void Render(RenderContext& rc);
};