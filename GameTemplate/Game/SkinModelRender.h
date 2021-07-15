#pragma once
class Model;
class Light;


class SkinModelRender : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	Light* m_light = nullptr;


	ModelInitData m_modelInitData;		//���f���C�j�b�g�f�[�^�\���̂̃f�[�^���쐬
	Model m_model;						//���f���N���X���쐬


	Vector3    m_pos = { Vector3::Zero };			//�ʒu
	Quaternion m_rot = { Quaternion::Identity };	//��]
	Vector3    m_sca = { Vector3::One };			//�g�嗦


	bool Start()override;
	~SkinModelRender()override;



public:

	//���f��������������֐�
	void Init(const char* tkmFilePath);
	//�`��֐�
	void Render(RenderContext& rc);

	void Update()override;

	/// <summary>
	/// �Z�b�^�[
	/// </summary>
	//���f���̈ʒu��ݒ肷��֐�
	void SetPosition(Vector3 pos) { m_pos = pos; }
	//���f���̉�]��ݒ肷��֐�
	void SetRotation(Quaternion rot) { m_rot = rot; }
	//���f���̊g�嗦��ݒ肷��֐�
	void SetScale(Vector3 sca) { m_sca = sca; }


	/// <summary>
	/// �Q�b�^�[
	/// </summary>
	//���f���̈ʒu���擾����֐�
	Vector3 GetPosition() { return m_pos; }
	/// <summary>
	/// ��]�N�H�[�^�j�I�����擾�B
	/// </summary>
	/// <returns>��]�N�H�[�^�j�I��</returns>
	Quaternion GetRotation() { return m_rot; }
	//���f���̃A�h���X���擾����֐�
	Model* GetModel() { return &m_model ; }
};