///<<summary>
///�X�e�[�W�I����ʃN���X
///</summary>


#include "stdafx.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"


namespace
{
	const int PLAYER1 = 0;		//�v���C���[�P

	const Vector3 STAGE_1_POS = { -120, 0, 100 };
	const Vector3 STAGE_2_POS = { 120, 0, 100 };
	const Vector3 STAGE_3_POS = { -120, 0, -100 };
	const Vector3 STAGE_4_POS = { 300, 0, -100 };
	const Vector3 STAGE_5_POS = { 300, 0, 100 };
	const Vector3 STAGE_RANDOM_POS = { 120, 0, -100 };

	const Vector3 STAGE_1_NAME_POS = { -170, 0, 0 };
	const Vector3 STAGE_2_NAME_POS = { 170, 0, 0 };
	const Vector3 STAGE_3_NAME_POS = { -170, -280, 0 };
	const Vector3 STAGE_4_NAME_POS = { 420, -280, 0 };
	const Vector3 STAGE_5_NAME_POS = { 420, 0, 0 };
	const Vector3 STAGE_RANDOM_NAME_POS = { 170, -280, 0 };

	const Vector3 BIG_STAGE_NAME = { 1.5f,1.5f,1.5f };	//�g�債���Ƃ��̃T�C�Y
}


bool StageSelectScene::Start()
{
	//�C���X�^���X���쐬
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);

	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
	{
		//�S�X�e�[�W���f���I�u�W�F�N�g����
		m_stage[stageNum] = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
		//�S�X�e�[�W�X�v���C�g�I�u�W�F�N�g����
		m_stageName[stageNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	}

	//�ǂЂ傤�X�e�[�W&���O�摜�����[�h
	m_stage[Stage1]->Init("Assets/modelData/bg/stage_1_Select.tkm");
	m_stageName[Stage1]->Init("Assets/Image/DDS/FLAT STAGE.dds", 200, 100);
	//����
	m_stagePos[Stage1] = STAGE_1_POS;
	m_stage[Stage1]->SetPosition(m_stagePos[Stage1]);
	m_stageName[Stage1]->SetPosition(STAGE_1_NAME_POS);

	//�h�[�i�c�X�e�[�W&���O�摜�����[�h
	m_stage[Stage2]->Init("Assets/modelData/bg/stage_2_Select.tkm");
	m_stageName[Stage2]->Init("Assets/Image/DDS/DONUT STAGE.dds", 200, 100);
	//�E��
	m_stagePos[Stage2] = STAGE_2_POS;
	m_stage[Stage2]->SetPosition(m_stagePos[Stage2]);
	m_stageName[Stage2]->SetPosition(STAGE_2_NAME_POS);

	//�A�C�X�X�e�[�W&���O�摜�����[�h
	m_stage[Stage3]->Init("Assets/modelData/bg/stage_3_Select.tkm");
	m_stageName[Stage3]->Init("Assets/Image/DDS/ICE STAGE.dds", 200, 100);
	//����
	m_stagePos[Stage3] = STAGE_3_POS;
	m_stage[Stage3]->SetPosition(m_stagePos[Stage3]);
	m_stageName[Stage3]->SetPosition(STAGE_3_NAME_POS);

	//���X�e�[�W&���O�摜�����[�h
	m_stage[Stage4]->Init("Assets/modelData/bg/stage_4_Select.tkm");
	m_stageName[Stage4]->Init("Assets/Image/DDS/RANDOM.dds", 200, 100);
	//�E��
	m_stagePos[Stage4] = STAGE_4_POS;
	m_stage[Stage4]->SetPosition(m_stagePos[Stage4]);
	m_stageName[Stage4]->SetPosition(STAGE_4_NAME_POS);

	//�����ނ��X�e�[�W&���O�摜�����[�h
	m_stage[Stage5]->Init("Assets/modelData/bg/stage_5_Select.tkm");
	m_stageName[Stage5]->Init("Assets/Image/DDS/RANDOM.dds", 200, 100);
	//�E�^��
	m_stagePos[Stage5] = STAGE_5_POS;
	m_stage[Stage5]->SetPosition(m_stagePos[Stage5]);
	m_stageName[Stage5]->SetPosition(STAGE_5_NAME_POS);

	//�����_���X�e�[�W&���O�摜�����[�h
	m_stage[RandomStage]->Init("Assets/modelData/bg/stage_random.tkm");
	m_stageName[RandomStage]->Init("Assets/Image/DDS/RANDOM.dds", 200, 100);
	//�E��
	m_stagePos[RandomStage] = STAGE_RANDOM_POS;
	m_stage[RandomStage]->SetPosition(m_stagePos[RandomStage]);
	m_stageName[RandomStage]->SetPosition(STAGE_RANDOM_NAME_POS);

	//�v���C���[���f���I�u�W�F�N�g����
	//�����摜�̏�ɏ��悤�Ƀv���C�I���e�B�[�͂P�����摜������������
	m_pla = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
	m_pla->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
	//�����ʒu�ݒ�
	m_pla->SetPosition(Vector3::Zero);

	//�f�o�b�N�p�̃v���C���[�X�s�[�h�̖��\��
	//m_skinModelRenderArrow = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
	//m_skinModelRenderArrow->Init("Assets/modelData/Arrow.tkm");	//���


	//�v���C���[�̏�ɕ\�������A�����o��
	for (int plaNum = 0; plaNum < 6; plaNum++)
	{
		m_Ahukidasi[plaNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		m_Ahukidasi[plaNum]->Init("Assets/Image/DDS/Ahukidasi.dds", 100, 100);
		m_Ahukidasi[plaNum]->Deactivate();
	}
	m_AhukidasiPos[0] = { -140, 170, 0 };
	m_AhukidasiPos[1] = { 140, 170, 0 };
	m_AhukidasiPos[2] = { -160, -50, 0 };
	m_AhukidasiPos[3] = { 160, -50, 0 };
	//m_AhukidasiPos[4] = { -140, -60, 0 };
	//m_AhukidasiPos[5] = { 0, 0, 0 };

	//�I�u�W�F�N�g����(�w�i�摜)
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0, nullptr);
	m_titleSprite->Init("Assets/image/DDS/BackScreenImage.dds", 1600.0f, 800.0f);

	//�^�C�g��BGM�T�E���h
	SoundPlayBack(TitleSceneBGM);

	//Start�֐���return��
	return true;
}


StageSelectScene::~StageSelectScene()
{

}


void StageSelectScene::Update()
{
	if (m_enableUpdateFlg == true)
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
}


//�Q�[����ʑJ�ڏ����֐�
void StageSelectScene::GameSceneTransition()
{
	//A�{�^���������ꂽ��A
	if (g_pad[PLAYER1]->IsPress(enButtonA))
	{
		//����T�E���h
		SoundPlayBack(DecideSound);

		//�����_���X�e�[�W���I�΂�Ă�����A
		if (m_stageNum == RandomStage)
		{
			//�����_���֐���SEED�i��j��ݒ�
			//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
			srand((int)time(nullptr));
			//���ݑ��݂���X�e�[�W�̒����烉���_���őI��
			m_stageNum = ((rand() % 5)+Stage1);
		}

		//�Q�[����ʂɑJ��
		NewGO<GameScene>(PRIORITY_0, GAMESCENE_NAME);

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
		//�^�C�g��BGM���폜
		DeleteGO(m_titleBGM);

		//���̃N���X�̏������Q�[����ʂɈڂ����Ƃ��Ɏ��s���Ȃ��Ȃ�t���O
		m_enableUpdateFlg = false;
	}
}


//�v���C���[�̈ʒu,��]�̏����X�V����֐�
void StageSelectScene::PlaDataUpdate()
{
	//�ʒu���Z�b�g
	m_pla->SetPosition(m_pos);
	//��]���Z�b�g
	m_pla->SetRotation(m_rot);
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
		m_Ahukidasi[stageNum-1]->Deactivate();

		//�ʏ�T�C�Y
		m_stageName[stageNum]->SetScale(Vector3::One);

		//�v���C���[�Ɗe�X�e�[�W�Ƃ̋��������߂�
		m_diff[stageNum] = m_stagePos[stageNum] - m_pos;

		//�X�e�[�W�̏�ɏ���Ă��Ȃ�������
		if (m_diff[stageNum].Length() >= 70.0f)
		{
			//����点��I���Ă����t���O�����I
			m_canOnStageSoundPlayFlg[stageNum] = true;
		}

		//�X�e�[�W�̏�ɏ���Ă�����
		if (m_diff[stageNum].Length() < 70.0f)
		{
			//A�����o����\��
			if (stageNum == 1)
			{
				m_Ahukidasi[0]->SetPosition(m_AhukidasiPos[0]);
				m_Ahukidasi[0]->Activate();
			}
			if (stageNum == 2)
			{
				m_Ahukidasi[1]->SetPosition(m_AhukidasiPos[1]);
				m_Ahukidasi[1]->Activate();
			}
			if (stageNum == 3)
			{
				m_Ahukidasi[2]->SetPosition(m_AhukidasiPos[2]);
				m_Ahukidasi[2]->Activate();
			}
			if (stageNum == 4)
			{
				m_Ahukidasi[3]->SetPosition(m_AhukidasiPos[3]);
				m_Ahukidasi[3]->Activate();
			}
			if (stageNum == 5)
			{
				m_Ahukidasi[4]->SetPosition(m_AhukidasiPos[4]);
				m_Ahukidasi[4]->Activate();
			}
			if (stageNum == 6)
			{
				m_Ahukidasi[5]->SetPosition(m_AhukidasiPos[5]);
				m_Ahukidasi[5]->Activate();
			}

			if (m_canOnStageSoundPlayFlg[stageNum])
			{
				//�X�e�[�W��I���ł���悤�ɂȂ�����炷�T�E���h
				SoundPlayBack(OnStageSound);

				m_canOnStageSoundPlayFlg[stageNum] = false;
			}

			//�X�e�[�W���摜�������g��
			m_stageName[stageNum]->SetScale(BIG_STAGE_NAME);

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
	if (m_pos.x > 420.0f)
	{
		m_pos.x = 420.0f;
	}
	//�����̕␳
	if (m_pos.x < -420.0f)
	{
		m_pos.x = -420.0f;
	}
	//�㑤�̕␳
	if (m_pos.z > 230.0f )
	{
		m_pos.z = 230.0f;
	}
	//�����̕␳
	if (m_pos.z < -230.0f)
	{
		m_pos.z = -230.0f;
	}
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
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		//�N���N�V�����T�E���h
		SoundPlayBack(CarHornSound);
	}
}


//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void StageSelectScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case TitleSceneBGM:
		//�^�C�g��BGM�T�E���h�̏�����
		m_titleBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_titleBGM->Init(L"Assets/sound/TitleSceneBGM.wav");
		m_titleBGM->SetVolume(0.1f);
		m_titleBGM->Play(true);	//�^�Ń��[�v�Đ�

		break;

	case DecideSound:
		//����T�E���h
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case OnStageSound:
		//�X�e�[�W��I���ł���悤�ɂȂ�����炷�T�E���h�̏�����
		m_onStageSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_onStageSound->Init(L"Assets/sound/OnStage.wav");
		m_onStageSound->SetVolume(0.5f);
		m_onStageSound->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case CarHornSound:
		//�N���N�V�����T�E���h�̏�����
		m_carHorn = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_carHorn->Init(L"Assets/sound/CarHorn.wav");
		m_carHorn->SetVolume(0.5f);
		m_carHorn->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}