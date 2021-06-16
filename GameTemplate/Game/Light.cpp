#include "stdafx.h"

namespace
{
	const Vector3 DIRLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//�f�B���N�V�������C�g�̏�������
	const Vector3 DIRLIG_COL = { 1.0f, 1.0f ,1.0f };	//�f�B���N�V�������C�g�̏����J���[

	const Vector3 SPOLIG_POS = { 0.0f, 0.0f ,0.0f };	//�X�|�b�g���C�g�̏����ʒu
	const Vector3 SPOLIG_COL = { 1.0f, 1.0f ,1.0f };	//�X�|�b�g���C�g�̏����J���[
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//�X�|�b�g���C�g�̏�������
	const float	  SPOLIG_RAN = 100.0f;					//�X�|�b�g���C�g�̏����e���͈�
	const float	  SPOLIG_ANG = 75.0f;					//�X�|�b�g���C�g�̏����ˏo�p�x
}

bool Light::Start()
{
	//���_�̈ʒu��ݒ肷��
	m_ligdata.eyePos = g_camera3D->GetPosition();

	//���C�g�N���X�̒��̃f�B���N�V�������C�g���Z�b�g
	//SetDirectionLightData();
	//���C�g�N���X�̒��̃|�C���g���C�g���Z�b�g
	//SetPointLightData();
	//���C�g�N���X�̒��̃X�|�b�g���C�g���Z�b�g
	//SetSpotLightData();

	//Start�֐���return��
	return true;
}


Light::~Light()
{

}

void Light::Update()
{
	//�X�|�b�g���C�g�𓮂����Ă݂鏈��(�R�����g�A�E�g��)
	{
	//	//�R���g���[���[�ŃX�|�b�g���C�g�𓮂����B
	//	m_ligdata.spotLigData.spPosition.x -= g_pad[0]->GetLStickXF();
	//	m_ligdata.spotLigData.spPosition.z -= g_pad[0]->GetLStickYF();
	//	if (g_pad[0]->IsPress(enButtonB))//�L�[�{�[�h�FK
	//	{
	//		m_ligdata.spotLigData.spPosition.y += 2.0f;
	//	}
	//	if (g_pad[0]->IsPress(enButtonX))//�L�[�{�[�h�FL
	//	{
	//		m_ligdata.spotLigData.spPosition.y -= 2.0f;
	//	}
	//	//Y������̉�]�N�H�[�^�j�I��
	//	static Quaternion qRotY;
	//	//Y������̉�]�N�H�[�^�j�I�����v�Z����
	//	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
	//	//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
	//	qRotY.Apply(m_ligdata.spotLigData.spDirection);
	//	//X������̉�]�N�H�[�^�j�I��
	//	static Vector3 rotAxis;
	//	static Quaternion qRotX;
	//	//X������̉�]�N�H�[�^�j�I�����v�Z����
	//	rotAxis.Cross(g_vec3AxisY, m_ligdata.spotLigData.spDirection);
	//	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
	//	//�v�Z�����N�H�[�^�j�I���Ń��C�g�̕�������
	//	qRotX.Apply(m_ligdata.spotLigData.spDirection);
	}
}

void Light::SetDirectionLightData()
{
	//�f�B���N�V�������C�g�̕�����ݒ�
	m_ligdata.dirLigData.ligDirection = DIRLIG_DIR;
	//�f�B���N�V�������C�g�𐳋K�����đ傫��1�̃x�N�g���ɂ���
	m_ligdata.dirLigData.ligDirection.Normalize();
	//�f�B���N�V�������C�g�̐F��ݒ�
	m_ligdata.dirLigData.ligColor = DIRLIG_COL;
}

void Light::SetPointLightData(Vector3 x,Vector3 y,float z)
{
	//�|�C���g���C�g�̍��W��ݒ�
	m_ligdata.poiLigData.ptPosition = x;
	//�|�C���g���C�g�̐F��ݒ�
	m_ligdata.poiLigData.ptColor = y;
	//�|�C���g���C�g�̉e���͈͂�ݒ�
	m_ligdata.poiLigData.ptRange = z;
}

void Light::SetSpotLightData()
{
	//�X�|�b�g���C�g�̍��W��ݒ�
	m_ligdata.spotLigData.spPosition = SPOLIG_POS;
		//�X�|�b�g���C�g�̐F��ݒ�
	m_ligdata.spotLigData.spColor = SPOLIG_COL;
	//�X�|�b�g���C�g�̕�����ݒ�
	m_ligdata.spotLigData.spDirection = SPOLIG_DIR;
	//�����f�[�^������傫����1�ɂ��邽�߂ɐ��K��������
	m_ligdata.spotLigData.spDirection.Normalize();
	//�X�|�b�g���C�g�̎ˏo�͈͂�ݒ�
	m_ligdata.spotLigData.spRange = SPOLIG_RAN;
	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�
	//(�f�O���[�P��(75�x)���烉�W�A���P�ʂɕϊ������l����)
	m_ligdata.spotLigData.spAngle = Math::DegToRad(SPOLIG_ANG);
}