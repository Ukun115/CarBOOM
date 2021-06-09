#include "stdafx.h"

bool Light::Start()
{


	//Start�֐���return��
	return true;
}
Light::Light()
{
	//���_�̈ʒu��ݒ肷��
	m_ligdata.eyePos = g_camera3D->GetPosition();

	//���C�g�N���X�̒��̃f�B���N�V�������C�g���Z�b�g
	SetDirectionLightData();
	//���C�g�N���X�̒��̃|�C���g���C�g���Z�b�g
	SetPointLightData();
	//���C�g�N���X�̒��̃X�|�b�g���C�g���Z�b�g
	SetSpotLightData();
}

Light::~Light()
{

}

void Light::Update()
{

	//�X�|�b�g���C�g�𓮂����Ă݂鏈��
	{
		//�R���g���[���[�ŃX�|�b�g���C�g�𓮂����B
		m_ligdata.spotLigData.spPosition.x -= g_pad[0]->GetLStickXF();
		m_ligdata.spotLigData.spPosition.z -= g_pad[0]->GetLStickYF();
		if (g_pad[0]->IsPress(enButtonB))//�L�[�{�[�h�FK
		{
			m_ligdata.spotLigData.spPosition.y += 2.0f;
		}
		if (g_pad[0]->IsPress(enButtonX))//�L�[�{�[�h�FL
		{
			m_ligdata.spotLigData.spPosition.y -= 2.0f;
		}
		//Y������̉�]�N�H�[�^�j�I�����v�Z����
		qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
		//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
		qRotY.Apply(m_ligdata.spotLigData.spDirection);
		//X������̉�]�N�H�[�^�j�I�����v�Z����
		rotAxis.Cross(g_vec3AxisY, m_ligdata.spotLigData.spDirection);
		qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
		//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
		qRotX.Apply(m_ligdata.spotLigData.spDirection);
	}
}

void Light::SetDirectionLightData()
{
	//�f�B���N�V�������C�g�̕�����ݒ�
	m_ligdata.dirLigData.ligDirection.x = 1.0f;
	m_ligdata.dirLigData.ligDirection.y = -1.0f;
	m_ligdata.dirLigData.ligDirection.z = -1.0f;
	//�f�B���N�V�������C�g�𐳋K�����đ傫��1�̃x�N�g���ɂ���
	m_ligdata.dirLigData.ligDirection.Normalize();
	//�f�B���N�V�������C�g�̐F��ݒ�
	m_ligdata.dirLigData.ligColor.x = 1.0f;
	m_ligdata.dirLigData.ligColor.y = 1.0f;
	m_ligdata.dirLigData.ligColor.z = 1.0f;
}

void Light::SetPointLightData()
{
	//�|�C���g���C�g�̍��W��ݒ�
	m_ligdata.poiLigData.ptPosition.x = 0.0f;
	m_ligdata.poiLigData.ptPosition.y = 0.0f;
	m_ligdata.poiLigData.ptPosition.z = 0.0f;
	//�|�C���g���C�g�̐F��ݒ�
	m_ligdata.poiLigData.ptColor.x = 5.0f;
	m_ligdata.poiLigData.ptColor.y = 5.0f;
	m_ligdata.poiLigData.ptColor.z = 5.0f;
	//�|�C���g���C�g�̉e���͈͂�ݒ�
	m_ligdata.poiLigData.ptRange = 100;
}

void Light::SetSpotLightData()
{
	//�X�|�b�g���C�g�̍��W��ݒ�
	m_ligdata.spotLigData.spPosition.x = 0.0f;
	m_ligdata.spotLigData.spPosition.y = 0.0f;
	m_ligdata.spotLigData.spPosition.z = 50.0f;
	//�X�|�b�g���C�g�̐F��ݒ�
	m_ligdata.spotLigData.spColor.x = 10.0f;
	m_ligdata.spotLigData.spColor.y = 10.0f;
	m_ligdata.spotLigData.spColor.z = 10.0f;
	//�X�|�b�g���C�g�̕�����ݒ�
	m_ligdata.spotLigData.spDirection.x = 1.0f;
	m_ligdata.spotLigData.spDirection.y = -1.0f;
	m_ligdata.spotLigData.spDirection.z = 1.0f;
	//�����f�[�^������傫����1�ɂ��邽�߂ɐ��K��������
	m_ligdata.spotLigData.spDirection.Normalize();
	//�X�|�b�g���C�g�̎ˏo�͈͂�ݒ�
	m_ligdata.spotLigData.spRange = 300.0f;
	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�
	//(�f�O���[�P��(75�x)���烉�W�A���P�ʂɕϊ�)
	m_ligdata.spotLigData.spAngle = Math::DegToRad(75.0f);
}