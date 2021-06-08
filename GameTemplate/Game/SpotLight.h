#pragma once

//�X�|�b�g���C�g�̍\���̂̒�`
struct SpotLigData {
	Vector3 spPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 spColor;		//�J���[
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x
};

class SpotLight : public IGameObject
{
private:
	//Y������̉�]�N�H�[�^�j�I��
	Quaternion qRotY;
	//X������̉�]�N�H�[�^�j�I��
	Vector3 rotAxis;
	Quaternion qRotX;

	//�X�|�b�g���C�g�̃f�[�^���쐬
	SpotLigData SpotLig;

public:
	bool Start();
	~SpotLight();
	void Update();


	void SetSpotLightData();

	SpotLigData& GetData()
	{
		return SpotLig;
	}
};

