///<<summary>
///�X�e�[�W�I����ʃN���X
///</summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "Fade.h"


namespace nsStageSelectScene
{
	const int PLAYER1 = 0;		//�v���C���[�P

	const Vector3 STAGE_1_POS = { 0, 0, 90 };
	const Vector3 STAGE_2_POS = { 170, 0, 90 };
	const Vector3 STAGE_3_POS = { 0, 0, -90 };
	const Vector3 STAGE_4_POS = { 350, 0, 90 };
	const Vector3 STAGE_5_POS = { 170, 0, -90 };
	const Vector3 STAGE_RANDOM_POS = { 350, 0, -90 };

	const Vector3 STAGE_1_NAME_POS = { 0, 0, 0 };
	const Vector3 STAGE_2_NAME_POS = { 240, 0, 0 };
	const Vector3 STAGE_3_NAME_POS = { 0, -250, 0 };
	const Vector3 STAGE_4_NAME_POS = { 490, 0, 0 };
	const Vector3 STAGE_5_NAME_POS = { 240, -250, 0 };
	const Vector3 STAGE_RANDOM_NAME_POS = { 490, -250, 0 };

	const Vector3 BIG_STAGE_NAME = { 1.5f,1.5f,1.5f };	//�g�債���Ƃ��̃T�C�Y
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
	m_fade[FadeIn] = NewGO<Fade>(0, nullptr);
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

	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
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

	for (int i = Stage1; i < TotalStageNum; i++)
	{
		sprintf(m_filePath, "bg/stage_%d_Select", i);
		m_stage[i]->Init(m_filePath);
		sprintf(m_filePath, "Stage%dName", i);
		m_stageName[i]->Init(m_filePath,200,100);
	}
	//�ǂЂ傤�X�e�[�W&���O�摜�����[�h
	//����
	m_stagePos[Stage1] = nsStageSelectScene::STAGE_1_POS;
	m_stage[Stage1]->SetPosition(m_stagePos[Stage1]);
	m_stageName[Stage1]->SetPosition(nsStageSelectScene::STAGE_1_NAME_POS);

	//�h�[�i�c�X�e�[�W&���O�摜�����[�h
	//�E��
	m_stagePos[Stage2] = nsStageSelectScene::STAGE_2_POS;
	m_stage[Stage2]->SetPosition(m_stagePos[Stage2]);
	m_stageName[Stage2]->SetPosition(nsStageSelectScene::STAGE_2_NAME_POS);

	//�A�C�X�X�e�[�W&���O�摜�����[�h
	//����
	m_stagePos[Stage3] = nsStageSelectScene::STAGE_3_POS;
	m_stage[Stage3]->SetPosition(m_stagePos[Stage3]);
	m_stageName[Stage3]->SetPosition(nsStageSelectScene::STAGE_3_NAME_POS);

	//�E�B���h�X�e�[�W&���O�摜�����[�h
	//�E��
	m_stagePos[Stage4] = nsStageSelectScene::STAGE_4_POS;
	m_stage[Stage4]->SetPosition(m_stagePos[Stage4]);
	m_stageName[Stage4]->SetPosition(nsStageSelectScene::STAGE_4_NAME_POS);

	//�e�B���g�X�e�[�W&���O�摜�����[�h
	//�E�^��
	m_stagePos[Stage5] = nsStageSelectScene::STAGE_5_POS;
	m_stage[Stage5]->SetPosition(m_stagePos[Stage5]);
	m_stageName[Stage5]->SetPosition(nsStageSelectScene::STAGE_5_NAME_POS);

	//�����_���X�e�[�W&���O�摜�����[�h
	//�E��
	m_stagePos[RandomStage] = nsStageSelectScene::STAGE_RANDOM_POS;
	m_stage[RandomStage]->SetPosition(m_stagePos[RandomStage]);
	m_stageName[RandomStage]->SetPosition(nsStageSelectScene::STAGE_RANDOM_NAME_POS);

	//�v���C���[���f���I�u�W�F�N�g����
	//�����摜�̏�ɏ��悤�Ƀv���C�I���e�B�[�͂P�����摜������������
	m_pla = NewGO<SkinModelRender>(nsStdafx::PRIORITY_2, nullptr);
	m_pla->Init("LowPoly_PlayerCar_0");	//�Ԏ�
	//�����ʒu�ݒ�
	m_pla->SetPosition(Vector3::Zero);

	//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
	//m_skinModelRenderArrow = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
	//m_skinModelRenderArrow->Init("Arrow");	//���


	m_AhukidasiPos[0] = { 0, 200, 0 };//�t���b�g
	m_AhukidasiPos[1] = { 235, 200, 0 };//�h�[�i�c
	m_AhukidasiPos[2] = { 0, -50, 0 };//�A�C�X
	m_AhukidasiPos[3] = { 490, 200, 0 };//�E�B���h
	m_AhukidasiPos[4] = { 235, -50, 0 };//�e�B���g
	m_AhukidasiPos[5] = { 490, -50, 0 };//�����_��
	//�v���C���[�̏�ɕ\�������A�����o��
	for (int stageNum = 0; stageNum < 6; stageNum++)
	{
		m_Ahukidasi[stageNum] = NewGO<SpriteRender>(nsStdafx::PRIORITY_2, nullptr);
		m_Ahukidasi[stageNum]->Init("Ahukidasi", 100, 100);
		m_Ahukidasi[stageNum]->Deactivate();
		m_Ahukidasi[stageNum]->SetPosition(m_AhukidasiPos[stageNum]);
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

	if(m_fade[FadeIn] != nullptr)
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
	m_fade[FadeOutBadk] = NewGO<Fade>(0, nullptr);
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
			if (m_stageNum == Stage5)
			{
				return;
			}

			//����T�E���h
			m_soundPlayBack->StageSelectSceneSoundPlayBack(DecideSound);

			//�t�F�[�h�A�E�g
			m_fade[FadeOutNext] = NewGO<Fade>(0, nullptr);
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
			//���ݑ��݂���X�e�[�W�̒����烉���_���őI��
			m_stageNum = ((rand() % 4) + Stage1);
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
	m_moveSpeed.x = min(m_moveSpeed.x, 5.0f);//�E�����̍ő呬�x
	m_moveSpeed.x = max(m_moveSpeed.x, -5.0f);//�������̍ő呬�x

	m_moveSpeed.z = min(m_moveSpeed.z, 5.0f);//������̍ő呬�x
	m_moveSpeed.z = max(m_moveSpeed.z, -5.0f);//�������̍ő呬�x
}


//�v���C���[�̉�]�����֐�
void StageSelectScene::PlaTurn()
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x = g_pad[0]->GetLStickXF();
	m_leftStick_y = g_pad[0]->GetLStickYF();

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
	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
	{
		//�v���C���[�Ɗe�X�e�[�W�Ƃ̋��������߂�
		m_diff[stageNum] = m_stagePos[stageNum] - m_pos;

		//�X�e�[�W�̏�ɏ���Ă��Ȃ�������
		if (m_diff[stageNum].Length() >= 70.0f)
		{
			//�S�Ă̐����o�����\��
			m_Ahukidasi[stageNum-1]->Deactivate();
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
			switch (stageNum)
			{
			case nsStdafx::STAGE1:
				//A�����o����\��
				m_Ahukidasi[0]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[Stage1]->Activate();
				break;
			case nsStdafx::STAGE2:
				//A�����o����\��
				m_Ahukidasi[1]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[Stage2]->Activate();
				break;
			case nsStdafx::STAGE3:
				//A�����o����\��
				m_Ahukidasi[2]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[Stage3]->Activate();
				break;
			case nsStdafx::STAGE4:
				//A�����o����\��
				m_Ahukidasi[3]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[Stage4]->Activate();
				break;
			case nsStdafx::STAGE5:
				//A�����o����\��
				m_Ahukidasi[4]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[Stage5]->Activate();
				break;
			case nsStdafx::STAGE6:
				//A�����o����\��
				m_Ahukidasi[5]->Activate();
				//�X�e�[�W��������\��
				m_stageDiscription[RandomStage]->Activate();
				break;
			}

			if (m_canOnStageSoundPlayFlg[stageNum])
			{
				//�X�e�[�W��I���ł���悤�ɂȂ�����炷�T�E���h
				m_soundPlayBack->StageSelectSceneSoundPlayBack(OnStageSound);

				m_canOnStageSoundPlayFlg[stageNum] = false;
			}

			for (int i = Stage1; i < TotalStageNum; i++)
			{
				//�����������\��
				m_operatorDiscription[i]->Deactivate();
			}

			//�X�e�[�W���摜�������g��
			m_stageName[stageNum]->SetScale(nsStageSelectScene::BIG_STAGE_NAME);

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
	m_pos.x = min(m_pos.x, 420.0f);
	//�����̕␳
	m_pos.x = max(m_pos.x, -420.0f);
	//�㑤�̕␳
	m_pos.z = min(m_pos.z, 230.0f);
	//�����̕␳
	m_pos.z = max(m_pos.z, -230.0f);
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