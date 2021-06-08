#pragma once
#include "DirectionLight.h"
#include "PointLight.h"
class Model;

//���C�g�S�̂̃f�[�^�\����
struct ligData
{
	DirLigData dirLigData;		//�f�B���N�V�������C�g�̍\���̃f�[�^
	PoiLigData poiLigData;				//�|�C���g���C�g�̍\���̃f�[�^
};

class SkinModelRender : public IGameObject
{
public:
	bool Start();
	~SkinModelRender();
	void Update();

private:

	Vector3    m_pos = Vector3::Zero;					//�ʒu
	Quaternion m_rot = Quaternion::Identity;			//��]
	Vector3    m_sca = Vector3::One;					//�g�嗦

	//���f�������������邽�߂̏���ݒ�
	ModelInitData m_modelInitData;
	//m_model�̓��f���N���X
	Model m_model;

	ligData m_ligData;

	DirectionLight* m_directionLight = nullptr;
	PointLight* m_pointLight = nullptr;


public:
	//3D���f�������[�h���邽�߂̏���ݒ肷��֐�
	void Init(const char* tkmFilePath);

	//�ʒu��ݒ肷��Z�b�g�֐�
	void SetPosition(const Vector3 pos) { m_pos = pos; }

	Vector3 GetPosition() { return m_pos; }
	//��]��ݒ肷��Z�b�g�֐�
	void SetRotation(const Quaternion rot) { m_rot = rot; }
	//�g�嗦��ݒ肷��Z�b�g�֐�
	void SetScale(const Vector3 sca) { m_sca = sca; }

	//�`��֐�
	void Render(RenderContext& rc);

	////�f�B���N�V�������C�g�N���X�̍\���̂̒��̏���dirLigData�ɃZ�b�g
	//void SetDirLigData(const DirLigData ligData) { dirLigData = ligData; }

	////�|�C���g���C�g�N���X�̍\���̂̒��̏���poiLigData�ɃZ�b�g
	//void SetPoiLigData(const PoiLigData ligData) { poiLigData = ligData; }
};