#pragma once



//�f�B���N�V�������C�g�̍\���̂̒�`
struct DirLigData {
	Vector3 ligDirection;	//����
	float pad1;				//HLSL���̒萔�o�b�t�@��float3�^(12��)�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����A���ߍ��킹�����Ă����B
	Vector3 ligColor;		//�F
	float pad2;
};

//�|�C���g���C�g�̍\���̂̒�`
struct PoiLigData {
	Vector3 ptPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 ptColor;		//�J���[
	float ptRange;			//�e���͈�
};

//�X�|�b�g���C�g�̍\���̂̒�`
struct SpotLigData {
	Vector3 spPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 spColor;		//�J���[
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x
};


//���C�g�S�̂̃f�[�^�\����
struct ligData {
	DirLigData  dirLigData;			//�f�B���N�V�������C�g�̍\���̃f�[�^
	PoiLigData  poiLigData;			//�|�C���g���C�g�̍\���̃f�[�^
	SpotLigData spotLigData;		//�X�|�b�g���C�g�̍\���̃f�[�^

	Vector3 eyePos;			//���_�̈ʒu
};


class Light : public IGameObject
{
private:



public:
	bool Start()override;
	~Light()override;
	void Update()override;

	//���C�g�̃f�[�^���쐬
	ligData m_ligdata;

	//�f�B���N�V�������C�g�̃f�[�^��ݒ肷��Z�b�g�֐�
	void SetDirectionLightData();

	//�|�C���g���C�g�̃f�[�^��ݒ肷��Z�b�g�֐�
	void SetPointLightData();

	//�X�|�b�g���C�g�̃f�[�^��ݒ肷��Z�b�g�֐�
	void SetSpotLightData();

	ligData GetLight() {return m_ligdata ; }
	ligData* GetLightAdoress() { return &m_ligdata; }
};

