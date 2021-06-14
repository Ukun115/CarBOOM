#include "stdafx.h"
#include "Stage.h"

bool Stage::Start()
{
	m_stage[0] = NewGO<SkinModelRender>(0);
	//�X�e�[�W�P�����[�h
	m_stage[0]->Init("Assets/modelData/bg/stage_00.tkm");

	//���b�V���R���C�_�[���������B
	m_meshCollider.CreateFromModel(m_stage[0]->GetModel(), m_stage[0]->GetModel().GetWorldMatrix());

	//���̂��������B
	RigidBodyInitData rbInitData;
	rbInitData.collider = &m_meshCollider;
	m_rigidBody.Init(rbInitData);
	//���`�ړ�����v�f��ݒ肷��B0���w�肵�����͈ړ����Ȃ��B
	//�܂�A������(����)����Œ�
	m_rigidBody.SetLinearFactor(0.0f, 0.0f, 0.0f);

	return true;
}

Stage::~Stage()
{

}

void Stage::Update()
{
	//�����I�ȓ����͂��Ȃ�����Update�֐����͂Ȃɂ��Ȃ��B
}