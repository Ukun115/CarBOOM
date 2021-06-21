#pragma once


//�f�B���N�V�������C�g�̍\���̂̐錾
struct DirLigData {

	Vector3 ligDirection;	//����
	float pad1;				//HLSL���̒萔�o�b�t�@��float3�^(12��)�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����A���ߍ��킹�����Ă����B
	Vector3 ligColor;		//�F
	float pad2;				//�p�f�B���O
};


//�|�C���g���C�g�̍\���̂̐錾
struct PoiLigData {

	Vector3 ptPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 ptColor;		//�F
	float ptRange;			//�e���͈�
};


//�X�|�b�g���C�g�̍\���̂̐錾
struct SpotLigData {

	Vector3 spPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 spColor;		//�F
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x
};


//���C�g�S�̂̃f�[�^�\���̂̐錾
struct ligData {

	DirLigData  dirLigData;		//�f�B���N�V�������C�g�̍\���̃f�[�^
	PoiLigData  poiLigData;		//�|�C���g���C�g�̍\���̃f�[�^
	SpotLigData spotLigData;	//�X�|�b�g���C�g�̍\���̃f�[�^

	Vector3 eyePos;				//���_�̈ʒu
};


class Light : public IGameObject
{
private:

	ligData m_ligData;		//���C�g�\���̂̃f�[�^���쐬

public:

	bool Start()override;
	~Light()override;
	void Update()override;


	/// <summary>
	/// �Z�b�g�֐�
	/// </summary>
	//�f�B���N�V�������C�g�̕���,�F��ݒ肷��֐�
	void SetDirectionLightData();
	//�|�C���g���C�g�̍��W,�F,�e���͈͂�ݒ肷��֐�
	void SetPointLightData(Vector3 x, Vector3 y, float z);
	//�X�|�b�g���C�g�̍��W,�F,����,�ˏo�͈�,�ˏo�p�x��ݒ肷��֐�
	void SetSpotLightData();


	/// <summary>
	/// �Q�b�g�֐�
	/// </summary>
	//���C�g�̃f�[�^���擾����֐�
	ligData GetLight() {return m_ligData ; }
	//���C�g�̃f�[�^�̃A�h���X���擾����֐�
	ligData* GetLightAdoress() { return &m_ligData; }
};