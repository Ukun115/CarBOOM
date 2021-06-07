#include "stdafx.h"
#include "PointLight.h"

bool PointLight::Start()
{
	//�|�C���g���C�g�̍��W��ݒ�
	PointLig.ptPosition.x = 0.0f;
	PointLig.ptPosition.y = 50.0f;
	PointLig.ptPosition.z = 50.0f;
	//�|�C���g���C�g�̐F��ݒ�
	PointLig.ptColor.x = 15.0f;
	PointLig.ptColor.y = 0.0f;
	PointLig.ptColor.z = 0.0f;
	//�|�C���g���C�g�̉e���͈͂�ݒ�
	PointLig.ptRange = 100.0f;

	//Start�֐���return��
	return true;
}

PointLight::~PointLight()
{

}

void PointLight::Update()
{
	//�R���g���[���[�Ń|�C���g���C�g�𓮂����B
	PointLig.ptPosition.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB))
	{
		PointLig.ptPosition.y += g_pad[0]->GetLStickYF();
	}
	else
	{
		PointLig.ptPosition.z -= g_pad[0]->GetLStickYF();
	}
}