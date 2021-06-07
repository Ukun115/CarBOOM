#pragma once

//�f�B���N�V�������C�g�̍\���̂̒�`
struct DirLigData {
	Vector3 ligDirection;	//����
	float pad;				//HLSL���̒萔�o�b�t�@��float3�^(12��)�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����A���ߍ��킹�����Ă����B
	Vector4 ligColor;		//�F

	//���_�̈ʒu
	Vector3 eyePos;
};

class DirectionLight
{
private:
	bool Start();
	~DirectionLight();
	void Update();

	// �f�B���N�V�������C�g�̃f�[�^���쐬
	DirLigData directionLig;
public:
};

