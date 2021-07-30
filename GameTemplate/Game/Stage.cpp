///<<summary>
///�X�e�[�W�\���ƃX�e�[�W���Ƃ̏����N���X
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include <random>

namespace nsCARBOOM
{
	namespace nsStage
	{
		const int SNOW1 = 0;
		const int SNOW2 = 1;

		const float ENEMY_WIND_POWER = 0.02f;
		const float PLAYER_WIND_POWER = 0.05f;
	}


	bool Stage::Start()
	{
		//�C���X�^���X��T��
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);
		m_player = FindGO<Player>(nsStdafx::PLAYER_NAME);
		m_enemy = FindGO<Enemy>(nsStdafx::ENEMY_NAME);
		//�X�e�[�W���f���I�u�W�F�N�g����
		m_stage = NewGO<SkinModelRender>(nsStdafx::PRIORITY_0, nullptr);

		sprintf(m_stageModelFilePath, "bg/stage_%d", m_stageSelectNum);
		m_stage->Init(m_stageModelFilePath);



		//�I�����ꂽ�̂��A�C�X�X�e�[�W�̂Ƃ��A
		if (m_stageSelectNum == Stage3)
		{
			for (int snowEffectNum = 0; snowEffectNum < 2; snowEffectNum++)
			{
				//�~���G�t�F�N�g�̏������B
				m_fallSnowEffect[snowEffectNum].Init(u"Snow");
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
		if (m_stageSelectNum == Stage4)
		{
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<int> windNum(0, 3);		//�ŏ��̕��̌����������_���ɂ���

			m_windDirection = windNum(mt);
		}

		////�I�����ꂽ�̂������ނ��X�e�[�W�̎�
		//if (m_stageSelectNum == Stage5) {
		//	Quaternion qRotX, qRotZ, qRot;
		//	qRotX.SetRotationDegX(10.0f);
		//	qRotZ.SetRotationDegZ(40.0f);
		//	qRot.Multiply(qRotX, qRotZ);
		//	m_stage->SetRotation(qRot);
		//}

		//�����蔻���K��
		m_physicsStaticObject.CreateFromModel(*m_stage->GetModel(), m_stage->GetModel()->GetWorldMatrix());

		return true;
	}


	Stage::~Stage()
	{
		//�X�e�[�W���폜
		DeleteGO(m_stage);
	}


	void Stage::Update()
	{
		//�|�[�Y���łȂ��Ƃ��A
		if (m_isPauseFlg)
		{
			return;
		}
		//�I�����ꂽ�X�e�[�W���A�C�X�X�e�[�W�̂Ƃ��A
		if (m_stageSelectNum == Stage3)
		{
			//��G�t�F�N�g����
			SnowFall();
		}
		if (m_stageSelectNum == Stage4)
		{
			//���̉e����^����
			WindInpact();
		}

		//if (m_stageSelectNum == Stage5)
		//{
		//	//�X������
		//	Tilt();
		//}
		//m_physicsStaticObject.Update(m_stage->GetPosition(), m_stage->GetRotation());
	}


	//��G�t�F�N�g�����֐�
	void Stage::SnowFall()
	{
		switch (m_fallSnowTimer)
		{
		case 0:
			//1�ڂ̍~���G�t�F�N�g�Đ��J�n�B
			m_fallSnowEffect[nsStage::SNOW1].Play();
			//�X�V
			m_fallSnowEffect[nsStage::SNOW1].Update();
			break;
		case 200:
			//2�ڂ̍~���G�t�F�N�g�Đ��J�n�B
			m_fallSnowEffect[nsStage::SNOW2].Play();
			//�X�V
			m_fallSnowEffect[nsStage::SNOW2].Update();
			break;
		case 400:
			//�^�C�}�[��߂�
			m_fallSnowTimer = 0;
			break;
		}

		//�^�C�}�[���Z
		m_fallSnowTimer++;
	}


	void Stage::WindInpact()
	{
		//���X�e�[�W���I������Ă���ꍇ�A���̉e����^����
		if (m_stageSelectNum != nsStdafx::STAGE4 || m_gameScene->GetCountDownFlg())
		{
			return;
		}

		//�P�O�b���Ƃɕ��̌�����ς���B
		for (int s = 1; s <= 6; s++) {
			if (m_gameScene->GetNowTime() == s * 10) {
				//�����ŁA�������g�p���āA�����_���ɕ��̌��������߂�B
				//�������񂶂ɁA�O�̕��̌����ƕς��悤�ɂ���B
				std::mt19937 mt{ std::random_device{}() };
				std::uniform_int_distribution<int> windNum(0, 3);


				int w = windNum(mt);	//�V������

				if (w == m_windDirection)
				{
					if (m_windDirection == 3)
					{
						m_windDirection = 0;		//5�Ԗڂ̕������܂�Ă��܂��̂őj�~!
					}
					else
					{

						m_windDirection += 1; //���Ȃ��悤��
					}
				}
				else
				{
					m_windDirection = w;	//����ĂȂ������炻�̂܂ܑ��v�B
				}
			}
		}
		for (int eneNum = 0; eneNum < 6; eneNum++)
		{
			//���݂̕��̌����ɉ���������
			switch (m_windDirection) {
			case UpWind://�������ւ̕�
				m_enemy->AddWindPowerZ(eneNum, nsStage::ENEMY_WIND_POWER);
				break;
			case DownWind:
				m_enemy->AddWindPowerZ(eneNum, -nsStage::ENEMY_WIND_POWER);
				break;
			case LeftWind:
				m_enemy->AddWindPowerZ(eneNum, -nsStage::ENEMY_WIND_POWER);
				break;
			case RightWind:
				m_enemy->AddWindPowerZ(eneNum, nsStage::ENEMY_WIND_POWER);
				break;
			}
		}
		for (int plaNum = 0; plaNum < m_totalPlaNum; plaNum++)
		{
			//���݂̕��̌����ɉ���������
			switch (m_windDirection) {
			case UpWind://�������ւ̕�
				m_player->AddWindPowerZ(plaNum, nsStage::PLAYER_WIND_POWER);
				break;
			case DownWind:
				m_player->AddWindPowerZ(plaNum, -nsStage::PLAYER_WIND_POWER);
				break;
			case LeftWind:
				m_player->AddWindPowerZ(plaNum, -nsStage::PLAYER_WIND_POWER);
				break;
			case RightWind:
				m_player->AddWindPowerZ(plaNum, nsStage::PLAYER_WIND_POWER);
				break;
			}
		}
	}


	void Stage::Tilt()
	{
		//�X�e�[�W���X���邽�߂ɃX�e�[�W�̒��S����v���C���[�܂ł̋����𑪂�
		for (int i = 0; i < m_totalPlaNum; i++)
		{
			m_plaPos[i] = m_player->GetPlaPos(i);
		}
	}
}