#include "stdafx.h"
#include "DirectionLight.h"

bool DirectionLight::Start()
{

	//�f�B���N�V�������C�g�̕�����ݒ�
	directionLig.ligDirection.x = 1.0f;
	directionLig.ligDirection.y = -1.0f;
	directionLig.ligDirection.z = -1.0f;
	//�f�B���N�V�������C�g�𐳋K�����đ傫��1�̃x�N�g���ɂ���
	directionLig.ligDirection.Normalize();
	//�f�B���N�V�������C�g�̐F��ݒ�
	directionLig.ligColor.x = 0.5f;
	directionLig.ligColor.y = 0.5f;
	directionLig.ligColor.z = 0.5f;
	directionLig.ligColor.w = 1.0f;

	//���_�̈ʒu��ݒ肷��
	directionLig.eyePos = g_camera3D->GetPosition();

	//Start�֐���return��
	return true;
}

DirectionLight::~DirectionLight()
{

}

void DirectionLight::Update()
{

}