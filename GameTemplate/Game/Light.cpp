///<<summary>
///���C�g���܂Ƃ߂Ă���N���X
///</summary>


#include "stdafx.h"


namespace
{
	//�f�B���N�V�������C�g
	const Vector3 DIRLIG_DIR = { 0.0f, -1.0f ,0.0f };	//����(�^�ォ��^���ɗ�����)
	//�X�|�b�g���C�g
	const Vector3 SPOLIG_POS = { 0.0f, 50.0f ,0.0f };	//�ʒu
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//����
	const float	  SPOLIG_RAN = 100.0f;					//�e���͈�
	const float	  SPOLIG_ANG = 75.0f;					//�ˏo�p�x
	//�������C�g
	const Vector3 HEMISPHERELIG_GROUNDCOLOR = {0.5,0.3,0.1};	//�n�ʐF
	const Vector3 HEMISPHERELIG_SKYCOLOR = {0.15,0.3,0.45};		//�V���F
	const Vector3 HEMISPHERELIG_GROUNDNORMAL = {0.0,1.0,0.0};	//�n�ʂ̖@��
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
	m_ligData.dirLigData.dirDirection = DIRLIG_DIR;
	//�f�B���N�V�������C�g�𐳋K�����đ傫��1�̃x�N�g���ɂ���
	m_ligData.dirLigData.dirDirection.Normalize();
	//�f�B���N�V�������C�g�̐F��ݒ�
	m_ligData.dirLigData.dirColor = GRAY;
}


//�|�C���g���C�g�̍��W,�F,�e���͈͂�ݒ肷��֐�
void Light::SetPointLightData(Vector3 position,Vector3 color,float range,int lignum)
{
		//�|�C���g���C�g�̍��W��ݒ�
		m_ligData.poiLigData[lignum].ptPosition = position;
		//�|�C���g���C�g�̐F��ݒ�
		m_ligData.poiLigData[lignum].ptColor = color;
		//�|�C���g���C�g�̉e���͈͂�ݒ�
		m_ligData.poiLigData[lignum].ptRange = range;
}


//�X�|�b�g���C�g�̍��W,�F,����,�ˏo�͈�,�ˏo�p�x��ݒ肷��֐�
void Light::SetSpotLightData()
{
	//�X�|�b�g���C�g�̍��W��ݒ�
	m_ligData.spotLigData.spPosition = SPOLIG_POS;
	//�X�|�b�g���C�g�̐F��ݒ�
	m_ligData.spotLigData.spColor = WHITE;
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


//�������C�g�̒n�ʐF�i�Ƃ�Ԃ��̃��C�g�j,�V���F,�n�ʂ̖@����ݒ肷��֐�
void Light::SetHemiSphereLightData()
{
	//�n�ʐF��ݒ�
	m_ligData.hemiSphereLigData.hemiGroundColor = HEMISPHERELIG_GROUNDCOLOR;
	//�V���F��ݒ�
	m_ligData.hemiSphereLigData.hemiSkyColor = HEMISPHERELIG_SKYCOLOR;
	//�n�ʂ̖@����ݒ�
	m_ligData.hemiSphereLigData.hemiGroundNormal = HEMISPHERELIG_GROUNDNORMAL;
}