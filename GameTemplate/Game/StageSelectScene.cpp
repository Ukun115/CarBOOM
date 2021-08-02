///<<summary>
///�X�e�[�W�I����ʂ̃��C������
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Fade.h"


namespace nsCARBOOM
{
	namespace nsStageSelectScene
	{
		const int PLAYER1 = 0;		//�v���C���[�P

		const Vector3 FLATSTAGE_MODEL_POS = { 0, 0, 90 };
		const Vector3 DONUTSTAGE_MODEL_POS = { 170, 0, 90 };
		const Vector3 ICESTAGE_MODEL_POS = { 0, 0, -90 };
		const Vector3 WINDSTAGE_MODEL_POS = { 350, 0, 90 };
		const Vector3 TILTSTAGE_MODEL_POS = { 170, 0, -90 };
		const Vector3 RANDOMSTAGE_MODEL_POS = { 350, 0, -90 };

		const Vector3 FLATSTAGE_NAME_POS = { 0, 0, 0 };
		const Vector3 DONUTSTAGE_NAME_POS = { 240, 0, 0 };
		const Vector3 ICESTAGE_NAME_POS = { 0, -250, 0 };
		const Vector3 WINDSTAGE_NAME_POS = { 490, 0, 0 };
		const Vector3 TILTSTAGE_NAME_POS = { 240, -250, 0 };
		const Vector3 RANDOMSTAGE_NAME_POS = { 490, -250, 0 };

		const Vector3 FLATSTAGE_FUKIDASI_POS = { 0, 200, 0 };
		const Vector3 DONUTSTAGE_FUKIDASI_POS = { 235, 200, 0 };
		const Vector3 ICESTAGE_FUKIDASI_POS = { 0, -50, 0 };
		const Vector3 WINDSTAGE_FUKIDASI_POS = { 490, 200, 0 };
		const Vector3 TILTSTAGE_FUKIDASI_POS = { 235, -50, 0 };
		const Vector3 RANDOMSTAGE_FUKIDASI_POS = { 490, -50, 0 };

		const Vector3 STAGE_NAME_SCALEUP = { 1.5f,1.5f,1.5f };	//�X�e�[�W�����g�債���Ƃ��̃T�C�Y

		const float MAX_MOOVESPEED = 5.0f;

		const float VERTICAL_WIDTH = 230.0f;
		const float BESIDE_WIDTH = 420.0f;
	}


	bool StageSelectScene::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//���C�g�I�u�W�F�N�g����
		m_light = NewGO<Light>(nsStdafx::PRIORITY_0, nsStdafx::LIGHT_NAME);
		//�f�B���N�V�������C�g���Z�b�g
		m_light->SetDirectionLightData();
		//�������C�g���Z�b�g
		m_light->SetHemiSphereLightData();

		//�t�F�[�h�C��
		m_fade[FadeIn] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeIn]->SetState(StateIn);
		m_fade[FadeIn]->SetAlphaValue(1.0f);

		//�X�e�[�W�����̔w�i�摜�I�u�W�F�N�g����
		m_stageDiscription[0] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		//�X�e�[�W�����̃o�b�N�X�N���[���摜
		m_stageDiscription[0]->Init("Stage0Discription", 500, 600);
		Vector3 m_stageDiscriptionPos = { -400.0f,-20.0f,nsStdafx::FLOAT_ZERO };
		m_stageDiscription[0]->SetPosition(m_stageDiscriptionPos);

		//�X�e�[�W�Z���N�g�����摜�I�u�W�F�N�g����
		m_stageSelectSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);

		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			//��������̉摜�I�u�W�F�N�g����
			m_operatorDiscription[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			m_operatorDiscription[stageNum]->Init("OperationDiscription", 550, 550);
			//���������̕\���ʒu���w��
			m_operatorDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);

			//�X�e�[�W�����̔w�i�摜�I�u�W�F�N�g����
			m_stageDiscription[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			sprintf(m_filePath, "Stage%dDiscription", stageNum);
			m_stageDiscription[stageNum]->Init(m_filePath, 550, 550);
			//�ʒu���w��
			m_stageDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);
			m_stageDiscription[stageNum]->Deactivate();

			//�S�X�e�[�W���f���I�u�W�F�N�g����
			m_stage[stageNum] = NewGO<SkinModelRender>(nsStdafx::PRIORITY_1, nullptr);
			//�S�X�e�[�W�X�v���C�g�I�u�W�F�N�g����
			m_stageName[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		}


		m_stageSelectSprite->Init("STAGESELECT", 750, 375);
		Vector3 m_stageSelectSpritePos = { nsStdafx::FLOAT_ZERO,310.0f,nsStdafx::FLOAT_ZERO };
		m_stageSelectSprite->SetPosition(m_stageSelectSpritePos);

		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			sprintf(m_filePath, "bg/stage_%d_Select", stageNum);
			m_stage[stageNum]->Init(m_filePath);
			sprintf(m_filePath, "Stage%dName", stageNum);
			m_stageName[stageNum]->Init(m_filePath, 200, 100);

			m_stage[stageNum]->SetPosition(WhatStageModelPos(stageNum));
			m_stageName[stageNum]->SetPosition(WhatStageNamePos(stageNum));
		}

		//�v���C���[���f���I�u�W�F�N�g����
		//�����摜�̏�ɏ��悤�Ƀv���C�I���e�B�[�͂P�����摜������������
		m_pla = NewGO<SkinModelRender>(nsStdafx::PRIORITY_2, nullptr);
		m_pla->Init("LowPoly_PlayerCar_0");	//�v���C���[�P�̎ԃ��f��
		//�����ʒu�ݒ�
		m_pla->SetPosition(Vector3::Zero);

		//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
		//m_skinModelRenderArrow = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
		//m_skinModelRenderArrow->Init("Arrow");	//���


		//�v���C���[�̏�ɕ\�������A�����o��
		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			m_Ahukidasi[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
			m_Ahukidasi[stageNum]->Init("Ahukidasi", 100, 100);
			m_Ahukidasi[stageNum]->Deactivate();
			m_Ahukidasi[stageNum]->SetPosition(WhatFukidasiPos(stageNum));
		}

		//�I�u�W�F�N�g����(�w�i�摜)
		m_titleSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		m_titleSprite->Init("BackScreenImage", 1600.0f, 800.0f);

		//�^�C�g��BGM�T�E���h
		m_soundPlayBack->StageSelectSceneSoundPlayBack(TitleSceneBGM);

		return true;
	}


	StageSelectScene::~StageSelectScene()
	{
		DeleteGO(m_light);

		//�\������Ă���X�e�[�W���f���ƃX�e�[�W���摜�����ׂč폜
		for (int stageNum = 0; stageNum < TotalStageNum; stageNum++)
		{
			DeleteGO(m_stage[stageNum]);
			DeleteGO(m_stageName[stageNum]);
		}
		//�v���C���[���폜�B
		DeleteGO(m_pla);
		//�v���C���[�̃X�s�[�h���������폜�B
		//DeleteGO(m_skinModelRenderArrow);
		//�w�i�摜���폜
		DeleteGO(m_titleSprite);
		//A�����o���摜���폜
		for (int plaNum = 0; plaNum < 6; plaNum++)
		{
			DeleteGO(m_Ahukidasi[plaNum]);
		}

		//�X�e�[�W�I�𕶎��摜
		DeleteGO(m_stageSelectSprite);

		for (int i = 0; i < 7; i++)
		{
			//�X�e�[�W�����̉摜���폜
			DeleteGO(m_stageDiscription[i]);
			if (i == 0)
			{
				continue;
			}
			//����������������폜
			DeleteGO(m_operatorDiscription[i]);
		}

		if (m_fade[FadeIn] != nullptr)
			DeleteGO(m_fade[FadeIn]);
		if (m_fade[FadeOutBadk] != nullptr)
			DeleteGO(m_fade[FadeOutBadk]);
		if (m_fade[FadeOutNext] != nullptr)
			DeleteGO(m_fade[FadeOutNext]);
	}


	void StageSelectScene::Update()
	{
		//�v���C���[������܂Ƃ߂Ă���֐�
		PlayerInformation();

		//�Z���N�g�{�^���������ꂽ��A
		if (!g_pad[nsStageSelectScene::PLAYER1]->IsTrigger(enButtonSelect))
		{
			return;
		}
		//����T�E���h
		m_soundPlayBack->StageSelectSceneSoundPlayBack(DecideSound);

		//�t�F�[�h�A�E�g
		m_fade[FadeOutBadk] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeOutBadk]->SetState(StateOut);
		m_fade[FadeOutBadk]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

		m_nextTitleSceneFlg = 1;

		if (!m_nextTitleSceneFlg)
		{
			return;
		}
		if (m_fade[FadeOutBadk]->GetNowState() != StateWait)
		{
			return;
		}
		m_titleScene = NewGO<TitleScene>(nsStdafx::PRIORITY_0, nullptr);
		DeleteGO(this);
	}


	//�Q�[����ʑJ�ڏ����֐�
	void StageSelectScene::GameSceneTransition()
	{
		if (m_fade[FadeOutNext] == nullptr)
		{
			//A�{�^���������ꂽ��A
			if (g_pad[nsStageSelectScene::PLAYER1]->IsTrigger(enButtonA))
			{
				//�X�e�[�W�T�i�e�B���g�X�e�[�W�j�͖������̂��߁A�X�e�[�W�ɓ���Ȃ��悤��return���Ă��܂�
				if (m_stageNum == TiltStage)
				{
					return;
				}

				//����T�E���h
				m_soundPlayBack->StageSelectSceneSoundPlayBack(DecideSound);

				//�t�F�[�h�A�E�g
				m_fade[FadeOutNext] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
				m_fade[FadeOutNext]->SetState(StateOut);
				m_fade[FadeOutNext]->SetAlphaValue(nsStdafx::FLOAT_ZERO);
			}
		}
		else
		{
			if (m_fade[FadeOutNext]->GetNowState() != StateWait)
			{
				return;
			}
			//�����_���X�e�[�W���I�΂�Ă�����A
			if (m_stageNum == RandomStage)
			{
				//�����_���֐���SEED�i��j��ݒ�
				//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
				srand((int)time(nullptr));
				//���ݑ��݂���X�e�[�W�̒����烉���_���őI��(�����_���ȊO���璊�I�B)
				m_stageNum = ((rand() % (RandomStage - 1)) + FlatStage);
			}

			//�Q�[����ʂɑJ��
			m_gameScene = NewGO<GameScene>(nsStdafx::PRIORITY_0, nsStdafx::GAMESCENE_NAME);
			//�o�^���ꂽ�l���f�[�^���Q�[���N���X�ɓn��
			m_gameScene->SetTotalPlaNum(m_totalPlaNum);
			//�X�e�[�W�Ȃ�ڂ��I�΂�Ă��邩���Q�[���N���X�ɓn��
			m_gameScene->SetSelectStageNum(m_stageNum);
			//�N���X�̔j��
			DeleteGO(this);
			//�X�e�[�W�Z���N�g�V�[���Ŏg���Ă���T�E���h��j��
			m_soundPlayBack->StageSelectSceneDeleteGO();
		}
	}


	//�v���C���[�̒ʏ�ړ������֐�
	void StageSelectScene::PlaMove()
	{
		//���X�e�B�b�N�̓��͗ʂ����Z����
		m_moveSpeed.x += m_leftStick_x * 10.0f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_leftStick_y * 10.0f * g_gameTime->GetFrameDeltaTime();

		//���C�͂�ݒ肷��
		m_friction = m_moveSpeed;
		m_friction *= -2.0f;

		//���C�͂����Z����
		m_moveSpeed.x += m_friction.x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed.z += m_friction.z * g_gameTime->GetFrameDeltaTime();

		m_pos += m_moveSpeed;
	}


	//�v���C���[�̈ړ����x�ɕ␳������֐�
	void StageSelectScene::PlaSpeedCorrection()
	{
		//�X�s�[�h�̕␳
		m_moveSpeed.x = min(m_moveSpeed.x, nsStageSelectScene::MAX_MOOVESPEED);//�E�����̍ő呬�x
		m_moveSpeed.x = max(m_moveSpeed.x, -nsStageSelectScene::MAX_MOOVESPEED);//�������̍ő呬�x

		m_moveSpeed.z = min(m_moveSpeed.z, nsStageSelectScene::MAX_MOOVESPEED);//������̍ő呬�x
		m_moveSpeed.z = max(m_moveSpeed.z, -nsStageSelectScene::MAX_MOOVESPEED);//�������̍ő呬�x
	}


	//�v���C���[�̉�]�����֐�
	void StageSelectScene::PlaTurn()
	{
		//���X�e�B�b�N�̓��͗ʂ��󂯎��
		m_leftStick_x = g_pad[nsStageSelectScene::PLAYER1]->GetLStickXF();
		m_leftStick_y = g_pad[nsStageSelectScene::PLAYER1]->GetLStickYF();

		//�ړ����ĂȂ��Ƃ��͉�]���Ȃ�
		if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
			return;
		}
		//��]�p�x
		m_rotAngle = atan2(m_moveSpeed.x, m_moveSpeed.z);

		m_rot.SetRotation(Vector3::AxisY, m_rotAngle);
	}


	//�X�e�[�W�̏�ɂ���Ƃ����̃X�e�[�W��I���ł���֐�
	void StageSelectScene::TouchStage()
	{
		for (int stageNum = FlatStage; stageNum < TotalStageNum; stageNum++)
		{
			//�v���C���[�Ɗe�X�e�[�W�Ƃ̋��������߂�
			m_diff[stageNum] = WhatStageNamePos(stageNum) - m_pos;

			//�X�e�[�W�̏�ɏ���Ă��Ȃ�������
			if (m_diff[stageNum].Length() >= 70.0f)
			{
				//�S�Ă̐����o�����\��
				m_Ahukidasi[stageNum]->Deactivate();
				//�S�ẴX�e�[�W�����������\��
				m_stageDiscription[stageNum]->Deactivate();

				if (m_isOperatorFlg[stageNum] == true)
				{
					//����������\��
					m_operatorDiscription[stageNum]->Activate();
				}
				m_isOperatorFlg[stageNum] = false;

				//�ʏ�T�C�Y
				m_stageName[stageNum]->SetScale(Vector3::One);

				//����点��I���Ă����t���O�����I
				m_canOnStageSoundPlayFlg[stageNum] = true;
			}
			//�X�e�[�W�̏�ɏ���Ă�����
			else
			{
				//A�����o����\��
				m_Ahukidasi[stageNum]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[stageNum]->Activate();

				if (m_canOnStageSoundPlayFlg[stageNum])
				{
					//�X�e�[�W��I���ł���悤�ɂȂ�����炷�T�E���h
					m_soundPlayBack->StageSelectSceneSoundPlayBack(OnStageSound);

					m_canOnStageSoundPlayFlg[stageNum] = false;
				}

				for (int i = FlatStage; i < TotalStageNum; i++)
				{
					//�����������\��
					m_operatorDiscription[i]->Deactivate();
				}

				//�X�e�[�W���摜�������g��
				m_stageName[stageNum]->SetScale(nsStageSelectScene::STAGE_NAME_SCALEUP);

				m_isOperatorFlg[stageNum] = true;

				//�I������Ă���X�e�[�W�̔ԍ�������B
				m_stageNum = stageNum;

				//�Q�[����ʑJ�ڏ����֐�
				GameSceneTransition();
			}
		}
	}


	//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���֐�
	void StageSelectScene::AvoidScreenOutSide()
	{
		//�E���̕␳
		m_pos.x = min(m_pos.x, nsStageSelectScene::BESIDE_WIDTH);
		//�����̕␳
		m_pos.x = max(m_pos.x, -nsStageSelectScene::BESIDE_WIDTH);
		//�㑤�̕␳
		m_pos.z = min(m_pos.z, nsStageSelectScene::VERTICAL_WIDTH);
		//�����̕␳
		m_pos.z = max(m_pos.z, -nsStageSelectScene::VERTICAL_WIDTH);
	}


	//�x�N�g��������������f�o�b�N�֐�
	void StageSelectScene::PlaMooveSpeedDebug()
	{
		Vector3 Dir = m_moveSpeed;
		Dir.y = 0;
		Dir.Normalize();//�傫�����ʒu�ɂ���
		float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
		Dir.z *= -1;
		float angleX = acosf(x);//�A�[�N�R�T�C��
		if (Dir.z < 0) {
			angleX *= -1;
		}
		//angleX -= 0.5 * PAI;
		m_arrowRot.SetRotationY(angleX);//���x����Y������
		m_skinModelRenderArrow->SetRotation(m_arrowRot);//�p�x��ݒ肷��
		m_arrowPos = m_pos;
		m_arrowPos.y += 30.0f;
		m_skinModelRenderArrow->SetPosition(m_arrowPos);
		m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 5;
		m_skinModelRenderArrow->SetScale(m_arrowSize);
	}


	//�N���N�V������炷�֐�
	void StageSelectScene::CarHorn()
	{
		//X�{�^���������ꂽ�Ƃ��Đ�
		if (!g_pad[nsStageSelectScene::PLAYER1]->IsTrigger(enButtonX))
		{
			return;
		}
		//�N���N�V�����T�E���h
		m_soundPlayBack->StageSelectSceneSoundPlayBack(CarHornSound);
	}


	//�v���C���[������܂Ƃ߂Ă���֐�
	void StageSelectScene::PlayerInformation()
	{
		//�x�N�g��������������f�o�b�N�֐�
		//PlaMooveSpeedDebug();
		//�N���N�V������炷�֐�
		CarHorn();
		//�v���C���[�̉�]����
		PlaTurn();
		//�v���C���[�̒ʏ�ړ�����
		PlaMove();
		//�v���C���[�̈ړ����x�ɕ␳������
		PlaSpeedCorrection();
		//�v���C���[����ʊO�ɍs���Ȃ��悤�ɂ���
		AvoidScreenOutSide();
		//�v���C���[�̈ʒu,��]�̏����X�V����
		PlaDataUpdate();
		//�X�e�[�W�̏�ɂ���Ƃ����̃X�e�[�W��I���ł���֐�
		TouchStage();
	}


	//
	Vector3 StageSelectScene::WhatStageModelPos(const int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_MODEL_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_MODEL_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_MODEL_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_MODEL_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_MODEL_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_MODEL_POS;
			break;
		}
	}


	//
	Vector3 StageSelectScene::WhatStageNamePos(int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_NAME_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_NAME_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_NAME_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_NAME_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_NAME_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_NAME_POS;
			break;
		}
	}


	//
	Vector3 StageSelectScene::WhatFukidasiPos(int stageNum)
	{
		switch (stageNum)
		{
		case FlatStage:
			return nsStageSelectScene::FLATSTAGE_FUKIDASI_POS;
			break;
		case DonutStage:
			return nsStageSelectScene::DONUTSTAGE_FUKIDASI_POS;
			break;
		case IceStage:
			return nsStageSelectScene::ICESTAGE_FUKIDASI_POS;
			break;
		case WindStage:
			return nsStageSelectScene::WINDSTAGE_FUKIDASI_POS;
			break;
		case TiltStage:
			return nsStageSelectScene::TILTSTAGE_FUKIDASI_POS;
			break;
		case RandomStage:
			return nsStageSelectScene::RANDOMSTAGE_FUKIDASI_POS;
			break;
		}
	}
}