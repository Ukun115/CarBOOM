///<<summary>
///�X�e�[�W�\���ƃX�e�[�W���Ƃ̏����N���X
///</summary>


#include "stdafx.h"
#include "Stage.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Player.h"
#include "Enemy.h"
#include <random>


namespace
{
	const int SNOW1 = 0;
	const int SNOW2 = 1;
}


bool Stage::Start()
{
	//�C���X�^���X��T��
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);
	m_gameScene = FindGO<GameScene>(GAMESCENE_NAME);
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_player = FindGO<Player>(PLAYER_NAME);
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

		for (int snowEffectNum = 0; snowEffectNum < 2; snowEffectNum++)
		{
			//�~���G�t�F�N�g�̏������B
			m_fallSnowEffect[snowEffectNum].Init(u"Assets/effect/efk/Snow.efk");
			//�G�t�F�N�g�̑傫������
			m_fallSnowEffect[snowEffectNum].SetScale({ 10.0f,10.0f,10.0f });
			//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
			Quaternion m_shootDownEffectRot = m_fallSnowEffect[snowEffectNum].GetRotation();
			//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
			m_shootDownEffectRot.AddRotationX(-0);	//X������_�ɁA-1.5708rad(-90��)��]
			m_fallSnowEffect[snowEffectNum].SetRotation(m_shootDownEffectRot);
			//�~���G�t�F�N�g�̈ʒu���v�J�����̏�ʂ̈ʒu�ɐݒ�
			m_fallSnowEffect[snowEffectNum].SetPosition({ 0,500,0 });
		}
	}

	//�I�����ꂽ�̂����X�e�[�W�̎�
	if (m_stageSelectScene->GetStageNum() == Stage4)
	{
		//���X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_4.tkm");

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<int> windNum(0, 3);		//�ŏ��̕��̌����������_���ɂ���

		m_windDirection = windNum(mt);
	}

	//�I�����ꂽ�̂������ނ��X�e�[�W�̎�
	if (m_stageSelectScene->GetStageNum() == Stage5) {

		//�����ނ��X�e�[�W�����[�h
		m_stage->Init("Assets/modelData/bg/stage_5.tkm");
	}

	//�����蔻���K��
	m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

	//Start�֐���return��
	return true;
}


Stage::~Stage()
{
	//�X�e�[�W���폜
	DeleteGO(m_stage);
}


void Stage::Update()
{
	//�I�����ꂽ�X�e�[�W���A�C�X�X�e�[�W�̂Ƃ��A
	if (m_stageSelectScene->GetStageNum() == Stage3)
	{
		//��G�t�F�N�g����
		SnowFall();
	}
	if (m_stageSelectScene->GetStageNum() == Stage4)
	{
		//���̉e����^����
		WindStage();
	}

	if (m_stageSelectScene->GetStageNum() == Stage5)
	{
		//�X������
		Tilt();
	}
}


//��G�t�F�N�g�����֐�
void Stage::SnowFall()
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


void Stage::WindStage()
{
	//���X�e�[�W���I������Ă���ꍇ�A���̉e����^����
	if (m_stageSelectScene->GetStageNum() == STAGE4)
	{
		//10�b���Ƀv���C���[�ɕ��̉e����^����p�x�����߂�(�����_��)
		//while (m_game_Scene->GetNowTime() == 0) {
		//	for(int i = 3600; i)
		//}

		//�P�O�b���Ƃɕ��̌�����ς���B
		for (int s = 1; s <= 6; s++) {
			if (m_gameScene->GetNowTime() == s * 10) {
				//�����ŁA�������g�p���āA�����_���ɕ��̌��������߂�B
				//�������񂶂ɁA�O�̕��̌����ƕς��悤�ɂ���B
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<int> windNum(0, 3);


				int w = windNum(mt);	//�V������

				if (w == m_windDirection) {
					if (m_windDirection == 3) {
						m_windDirection = 0;		//5�Ԗڂ̕������܂�Ă��܂��̂őj�~!
					}
					else {

						m_windDirection += 1; //���Ȃ��悤��
					}
				}
				else {
					m_windDirection = w;	//����ĂȂ������炻�̂܂ܑ��v�B
				}
			}
		}
	}
}

void Stage::Tilt()
{
	//�X�e�[�W���X���邽�߂ɃX�e�[�W�̒��S����v���C���[�܂ł̋����𑪂�
	for (int i = 0; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		m_plaPos[i] = m_player->GetPlaPos(i);
	}
}