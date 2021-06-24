#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0
	const int SNOW1 = 0;
	const int SNOW2 = 1;
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

		for (int i = 0; i < 2; i++)
		{
			//�~���G�t�F�N�g�̏������B
			m_fallSnowEffect[i].Init(u"Assets/effect/efk/Snow.efk");
			//�G�t�F�N�g�̑傫������
			m_fallSnowEffect[i].SetScale({ 10.0f,10.0f,10.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			Quaternion m_shootDownEffectRot = m_fallSnowEffect[i].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-0);	//X������_�ɁA-1.5708rad(-90��)��]
			m_fallSnowEffect[i].SetRotation(m_shootDownEffectRot);
			//�~���G�t�F�N�g�̈ʒu���v�J�����̏�ʂ̈ʒu�ɐݒ�
			m_fallSnowEffect[i].SetPosition({ 0,500,0 });
		}
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
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		if (m_fallSnowTimer == 0)
		{
			//1�ڂ̍~���G�t�F�N�g�Đ��J�n�B
			m_fallSnowEffect[SNOW1].Play();
			//�X�V
			m_fallSnowEffect[SNOW1].Update();
		}
		if (m_fallSnowTimer == 200)
		{
			//2�ڂ̍~���G�t�F�N�g�Đ��J�n�B
			m_fallSnowEffect[SNOW2].Play();
			//�X�V
			m_fallSnowEffect[SNOW2].Update();
		}
		if (m_fallSnowTimer == 400)
		{
			//�^�C�}�[��߂�
			m_fallSnowTimer = 0;
		}

		//�^�C�}�[���Z
		m_fallSnowTimer++;
	}
}

//���U���g��ʂɑJ�ڎ��~��Ⴊ�d��