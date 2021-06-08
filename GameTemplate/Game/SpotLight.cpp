#include "stdafx.h"
#include "SpotLight.h"

bool SpotLight::Start()
{

	//Start�֐���return��
	return true;
}

SpotLight::~SpotLight()
{

}

void SpotLight::Update()
{
	//�R���g���[���[�ŃX�|�b�g���C�g�𓮂����B
	SpotLig.spPosition.x -= g_pad[0]->GetLStickXF();
	SpotLig.spPosition.z -= g_pad[0]->GetLStickYF();
	if (g_pad[0]->IsPress(enButtonB))//�L�[�{�[�h�FK
	{
		SpotLig.spPosition.y += 2.0f;
	}
	if (g_pad[0]->IsPress(enButtonX))//�L�[�{�[�h�FL
	{
		SpotLig.spPosition.y -= 2.0f;
	}
	//Y������̉�]�N�H�[�^�j�I�����v�Z����
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
	//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
	qRotY.Apply(SpotLig.spDirection);
	//X������̉�]�N�H�[�^�j�I�����v�Z����
	rotAxis.Cross(g_vec3AxisY, SpotLig.spDirection);
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
	//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
	qRotX.Apply(SpotLig.spDirection);
}

void SpotLight::SetSpotLightData()
{
	//�X�|�b�g���C�g�̍��W��ݒ�
	SpotLig.spPosition.x = 0.0f;
	SpotLig.spPosition.y = 0.0f;
	SpotLig.spPosition.z = 50.0f;
	//�X�|�b�g���C�g�̐F��ݒ�
	SpotLig.spColor.x = 10.0f;
	SpotLig.spColor.y = 10.0f;
	SpotLig.spColor.z = 10.0f;
	//�X�|�b�g���C�g�̕�����ݒ�
	SpotLig.spDirection.x = 1.0f;
	SpotLig.spDirection.y = -1.0f;
	SpotLig.spDirection.z = 1.0f;
	//�����f�[�^������傫����1�ɂ��邽�߂ɐ��K��������
	SpotLig.spDirection.Normalize();
	//�X�|�b�g���C�g�̎ˏo�͈͂�ݒ�
	SpotLig.spRange = 300.0f;
	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�
	//(�f�O���[�P��(25�x)���烉�W�A���P��(0.436332rad)�ɕϊ�)
	SpotLig.spAngle = Math::DegToRad(25.0f);
}