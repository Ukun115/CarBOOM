#pragma once

//�f�B���N�V�������C�g�̍\���̂̒�`
struct DirLigData {
	Vector3 ligDirection;	//����
	float pad1;				//HLSL���̒萔�o�b�t�@��float3�^(12��)�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����A���ߍ��킹�����Ă����B
	Vector3 ligColor; //= { 0.5f,0.5f,0.5f };		//�F
	float pad2;

	Vector3 eyePos;			//���_�̈ʒu
};

class DirectionLight : public IGameObject
{
public:
	bool Start();
	~DirectionLight();
	void Update();

	/// <summary>
	/// �f�B���N�V�������C�g�̃f�[�^��ݒ�
	/// </summary>
	void SetDirectionData();

private:
	// �f�B���N�V�������C�g�̃f�[�^���쐬
	DirLigData directionLig;

public:
	DirLigData GetData()
	{
		return directionLig;
	}
};