#pragma once

//�|�C���g���C�g�̍\���̂̒�`
struct PoiLigData {
	Vector3 ptPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 ptColor;		//�J���[
	float ptRange;			//�e���͈�
};

class PointLight
{
private:
	bool Start();
	~PointLight();
	void Update();

	// �|�C���g���C�g�̃f�[�^���쐬
	PoiLigData PointLig;

public:

};