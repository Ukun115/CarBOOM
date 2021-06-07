#include "stdafx.h"
#include "SkinModelRender.h"

bool SkinModelRender::Start()
{


	//Start�֐���return
	return true;
}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Update()
{
	//���f���̈ʒu�A��]�A�g����X�V
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
}

void SkinModelRender::Init(const char* tkmFilePath)
{
	DirectionLight* m_directionlight = FindGO<DirectionLight>("directionlight");

	//�f�B���N�V�������C�g�N���X�̃I�u�W�F�N�g���������Ă��郉�C�g�̍\���̃f�[�^��
	//���̃I�u�W�F�N�g���������Ă���\���̃f�[�^�ɓn���B
	m_dirLigData = m_directionlight->GetData();

	//tkm�t�@�C���̃t�@�C���p�X��ݒ肷��B
	m_modelInitData.m_tkmFilePath = tkmFilePath;
	//modelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ肷��B
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//���f���̏���������萔�o�b�t�@�Ƃ��ăf�B�X�N���v�^�q�[�v��
	//�o�^���邽�߂Ƀ��f���̏��������Ƃ��ēn���B
	m_modelInitData.m_expandConstantBuffer = &m_dirLigData;
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_dirLigData);
	//�����������g���ă��f���\������������������
	m_model.Init(m_modelInitData);
}

void SkinModelRender::Render(RenderContext& rc)
{
	//���f���̃h���[�R�[�������s���A�\������
	m_model.Draw(rc);
}