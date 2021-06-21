#include "stdafx.h"
#include "Stage.h"


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0

	const int STAGE_1 = 0;		//�X�e�[�W�P�̔z��ԍ�
}


bool Stage::Start()
{
	//�X�e�[�W�P���f���I�u�W�F�N�g����
	m_stage[STAGE_1] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
	//�X�e�[�W�P�����[�h
	m_stage[STAGE_1]->Init("Assets/modelData/bg/stage_00.tkm");

	//�����蔻���K��
	m_physicsStaticObject.CreateFromModel(*m_stage[STAGE_1]->GetModel(), m_stage[STAGE_1]->GetModel()->GetWorldMatrix());

	//Start�֐���return��
	return true;
}


Stage::~Stage()
{

}


void Stage::Update()
{
	//�����I�ȓ����͂��Ȃ�����Update�֐����͂Ȃɂ��Ȃ��B
}