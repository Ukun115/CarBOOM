#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0
}


bool Stage::Start()
{
	//�C���X�^���X��T��
	m_stageSelectScene = FindGO<StageSelectScene>("stageselectscene");

	//�ǂЂ傤�X�e�[�W���f���I�u�W�F�N�g����
	m_stage = NewGO<SkinModelRender>(PRIORITY_0,nullptr);

	//�I�����ꂽ�̂��ǂЂ傤�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage1)
	{
		//�ǂЂ傤�X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_00.tkm");
	}
	//�I�����ꂽ�̂��h�[�i�c�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage2)
	{
		//�X�e�[�W�h�[�i�c�����[�h
		m_stage->Init("Assets/modelData/bg/stage_00.tkm");
	}
	//�I�����ꂽ�̂����X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		//���X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_00.tkm");
	}

	//�����蔻���K��
	m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

	//Start�֐���return��
	return true;
}


Stage::~Stage()
{

}


void Stage::Update()
{

}