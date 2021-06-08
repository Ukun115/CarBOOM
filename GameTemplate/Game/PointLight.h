#pragma once

//�|�C���g���C�g�̍\���̂̒�`
struct PoiLigData {
	Vector3 ptPosition;		//�ʒu
	float pad;				//�p�f�B���O
	Vector3 ptColor;		//�J���[
	float ptRange;			//�e���͈�
};

class PointLight : public IGameObject
{
private:

	// �|�C���g���C�g�̃f�[�^���쐬
	PoiLigData PointLig;

public:
	bool Start();
	~PointLight();
	void Update();

	void SetPointLightData();

	PoiLigData& GetData()
	{
		return PointLig;
	}
};