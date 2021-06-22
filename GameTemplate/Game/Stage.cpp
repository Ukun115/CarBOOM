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

	//�X�e�[�W���f���I�u�W�F�N�g����
	m_stage = NewGO<SkinModelRender>(PRIORITY_0,nullptr);

	//�I�����ꂽ�̂��ǂЂ傤�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage1)
	{
		//�ǂЂ傤�X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_1.tkm");
	}
	//�I�����ꂽ�̂��h�[�i�c�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage2)
	{
		//�h�[�i�c�X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_2.tkm");
	}
	//�I�����ꂽ�̂��A�C�X�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		//�A�C�X�X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_3.tkm");
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