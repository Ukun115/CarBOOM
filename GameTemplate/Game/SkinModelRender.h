#pragma once
class Model;

class SkinModelRender : public IGameObject
{
private:

	bool Start();
	~SkinModelRender();
	void Update();

	Vector3    m_pos = Vector3::Zero;					//�ʒu
	Quaternion m_rot = Quaternion::Identity;			//��]
	Vector3    m_sca = Vector3::One;					//�g�嗦

	//���f�������������邽�߂̏���ݒ�
	ModelInitData m_modelInitData;
	//m_model�̓��f���N���X
	Model m_model;
	//�f�B���N�V�������C�g�̍\���̂̒��g�������锠
	DirLigData* m_dirLigData = nullptr;

public:
	//3D���f�������[�h���邽�߂̏���ݒ肷��֐�
	void Init(const char* tkmFilePath);

	//�ʒu��ݒ肷��Z�b�g�֐�
	void SetPosition(Vector3 pos) { m_pos = pos; }
	//��]��ݒ肷��Z�b�g�֐�
	void SetRotation(Quaternion rot) { m_rot = rot; }
	//�g�嗦��ݒ肷��Z�b�g�֐�
	void SetScale(Vector3 sca) { m_sca = sca; }

	//�`��֐�
	void Render(RenderContext& rc);

	//�f�B���N�V�������C�g�N���X�̍\���̂̒��̏���m_dirLigData�ɃZ�b�g
	void SetDirLigData(DirLigData& ligData) { m_dirLigData = &ligData; }
};