#include "stdafx.h"


namespace
{
	const Vector3 DIRLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//�f�B���N�V�������C�g�̏�������
	const Vector3 DIRLIG_COL = { 1.0f, 1.0f ,1.0f };	//�f�B���N�V�������C�g�̏����F

	const Vector3 SPOLIG_POS = { 0.0f, 0.0f ,0.0f };	//�X�|�b�g���C�g�̏����ʒu
	const Vector3 SPOLIG_COL = { 1.0f, 1.0f ,1.0f };	//�X�|�b�g���C�g�̏����F
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//�X�|�b�g���C�g�̏�������
	const float	  SPOLIG_RAN = 100.0f;					//�X�|�b�g���C�g�̏����e���͈�
	const float	  SPOLIG_ANG = 75.0f;					//�X�|�b�g���C�g�̏����ˏo�p�x
}


bool Light::Start()
{
	//���_�̈ʒu��ݒ肷��
	m_ligData.eyePos = g_camera3D->GetPosition();

	//Start�֐���return��
	return true;
}


Light::~Light()
{

}


void Light::Update()
{

}


//�f�B���N�V�������C�g�̕���,�F��ݒ肷��֐�
void Light::SetDirectionLightData()
{
	//�f�B���N�V�������C�g�̕�����ݒ�
	m_ligData.dirLigData.ligDirection = DIRLIG_DIR;
	//�f�B���N�V�������C�g�𐳋K�����đ傫��1�̃x�N�g���ɂ���
	m_ligData.dirLigData.ligDirection.Normalize();
	//�f�B���N�V�������C�g�̐F��ݒ�
	m_ligData.dirLigData.ligColor = DIRLIG_COL;
}

//�|�C���g���C�g�̍��W,�F,�e���͈͂�ݒ肷��֐�
void Light::SetPointLightData(Vector3 x,Vector3 y,float z)
{
	//�|�C���g���C�g�̍��W��ݒ�
	m_ligData.poiLigData.ptPosition = x;
	//�|�C���g���C�g�̐F��ݒ�
	m_ligData.poiLigData.ptColor = y;
	//�|�C���g���C�g�̉e���͈͂�ݒ�
	m_ligData.poiLigData.ptRange = z;
}

//�X�|�b�g���C�g�̍��W,�F,����,�ˏo�͈�,�ˏo�p�x��ݒ肷��֐�
void Light::SetSpotLightData()
{
	//�X�|�b�g���C�g�̍��W��ݒ�
	m_ligData.spotLigData.spPosition = SPOLIG_POS;
	//�X�|�b�g���C�g�̐F��ݒ�
	m_ligData.spotLigData.spColor = SPOLIG_COL;
	//�X�|�b�g���C�g�̕�����ݒ�
	m_ligData.spotLigData.spDirection = SPOLIG_DIR;
	//�����f�[�^������傫����1�ɂ��邽�߂ɐ��K��������
	m_ligData.spotLigData.spDirection.Normalize();
	//�X�|�b�g���C�g�̎ˏo�͈͂�ݒ�
	m_ligData.spotLigData.spRange = SPOLIG_RAN;
	//�X�|�b�g���C�g�̎ˏo�p�x��ݒ�
	//(�f�O���[�P��(75�x)���烉�W�A���P�ʂɕϊ������l����)
	m_ligData.spotLigData.spAngle = Math::DegToRad(SPOLIG_ANG);
}