#include "stdafx.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0
	const int PRIORITY_1 = 1;	//�D��x1
	const int PLAYER1 = 0;		//�v���C���[�P

	const Vector3 STAGE_1_POS = { -120, 0, 100 };
	const Vector3 STAGE_2_POS = { 120, 0, 100 };
	const Vector3 STAGE_3_POS = { -120, 0, -100 };
	const Vector3 STAGE_RANDOM_POS = { 120, 0, -100 };

	const Vector3 STAGE_1_NAME_POS = { -170, 0, 0 };
	const Vector3 STAGE_2_NAME_POS = { 170, 0, 0 };
	const Vector3 STAGE_3_NAME_POS = { -170, -280, 0 };
	const Vector3 STAGE_RANDOM_NAME_POS = { 170, -280, 0 };

	const Vector3 BIG_STAGE_NAME = { 1.5f,1.5f,1.5f };	//�g�債���Ƃ��̃T�C�Y
}


bool StageSelectScene::Start()
{
	//�C���X�^���X���쐬
	m_titleScene = FindGO<TitleScene>("titlescene");

	for (int i = Stage1; i < TotalStageNum; i++)
	{
		//�S�X�e�[�W���f���I�u�W�F�N�g����
		m_stage[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);
		//�傫������
		m_stage[i]->SetScale({ 0.3,0.3,0.3 });
		//�S�X�e�[�W�X�v���C�g�I�u�W�F�N�g����
		m_stageName[i] = NewGO<SpriteRender>(PRIORITY_0, nullptr);
	}

	//�ǂЂ傤�X�e�[�W&���O�摜�����[�h
	m_stage[Stage1]->Init("Assets/modelData/bg/stage_1.tkm");
	m_stageName[Stage1]->Init("Assets/Image/DDS/FLAT STAGE.dds", 200, 100);
	//����
	m_stagePos[Stage1] = STAGE_1_POS;
	m_stage[Stage1]->SetPosition(m_stagePos[Stage1]);
	m_stageName[Stage1]->SetPosition(STAGE_1_NAME_POS);

	//�h�[�i�c�X�e�[�W&���O�摜�����[�h
	m_stage[Stage2]->Init("Assets/modelData/bg/stage_2.tkm");
	m_stageName[Stage2]->Init("Assets/Image/DDS/DONUT STAGE.dds", 200, 100);
	//�E��
	m_stagePos[Stage2] = STAGE_2_POS;
	m_stage[Stage2]->SetPosition(m_stagePos[Stage2]);
	m_stageName[Stage2]->SetPosition(STAGE_2_NAME_POS);

	//�A�C�X�X�e�[�W&���O�摜�����[�h
	m_stage[Stage3]->Init("Assets/modelData/bg/stage_3.tkm");
	m_stageName[Stage3]->Init("Assets/Image/DDS/ICE STAGE.dds", 200, 100);
	//����
	m_stagePos[Stage3] = STAGE_3_POS;
	m_stage[Stage3]->SetPosition(m_stagePos[Stage3]);
	m_stageName[Stage3]->SetPosition(STAGE_3_NAME_POS);

	//�����_���X�e�[�W&���O�摜�����[�h
	m_stage[RandomStage]->Init("Assets/modelData/bg/stage_random.tkm");
	m_stageName[RandomStage]->Init("Assets/Image/DDS/RANDOM.dds", 200, 100);
	//�E��
	m_stagePos[RandomStage] = STAGE_RANDOM_POS;
	m_stage[RandomStage]->SetPosition(m_stagePos[RandomStage]);
	m_stageName[RandomStage]->SetPosition(STAGE_RANDOM_NAME_POS);

	//�v���C���[���f���I�u�W�F�N�g����
	//�����摜�̏�ɏ��悤�Ƀv���C�I���e�B�[�͂P�����摜������������
	m_pla = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
	m_pla->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
	//�����ʒu�ݒ�
	m_pla->SetPosition({ 0.0f,0.0f,0.0f });
	//�g��
	m_pla->SetScale({1.5f,1.5f,1.5f});


	//Start�֐���return��
	return true;
}


StageSelectScene::~StageSelectScene()
{

}


void StageSelectScene::Update()
{
	if (m_isCanGameStartFlg == true)
	{
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
		//�����_���X�e�[�W���I�΂�Ă�����A
		if (m_stageNum == RandomStage)
		{
			//�����_���֐���SEED�i��j��ݒ�
			//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
			srand((int)time(nullptr));
			//���ݑ��݂���X�e�[�W�̒����烉���_���őI��
			m_stageNum = ((rand() % 3)+Stage1);
		}

		//�Q�[����ʂɑJ��
		NewGO<GameScene>(PRIORITY_0, "gamescene");

		//�\������Ă���X�e�[�W���f���ƃX�e�[�W���摜�����ׂč폜
		for (int i = 0; i < TotalStageNum; i++)
		{
			DeleteGO(m_stage[i]);
			DeleteGO(m_stageName[i]);
		}
		//�v���C���[���폜�B
		DeleteGO(m_pla);

		//���̃N���X�̏������Q�[����ʂɈڂ����Ƃ��Ɏ��s���Ȃ��Ȃ�t���O
		m_isCanGameStartFlg = false;
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
	if (m_moveSpeed.x > 5.0f) {
		m_moveSpeed.x = 5.0f;	//�E�����̍ő呬�x
	}
	if (m_moveSpeed.x < -5.0f) {
		m_moveSpeed.x = -5.0f;	//�������̍ő呬�x
	}
	if (m_moveSpeed.z > 5.0f) {
		m_moveSpeed.z = 5.0f;	//������̍ő呬�x
	}
	if (m_moveSpeed.z < -5.0f) {
		m_moveSpeed.z = -5.0f;	//�������̍ő呬�x
	}
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
	for (int i = Stage1; i < TotalStageNum; i++)
	{
		//�ʏ�T�C�Y
		m_stageName[i]->SetScale(Vector3::One);

		//�v���C���[�Ɗe�X�e�[�W�Ƃ̋��������߂�
		m_diff = m_stagePos[i] - m_pos;
		//�X�e�[�W�̏�ɏ���Ă�����A
		if (m_diff.Length() < 70.0f)
		{
			//�X�e�[�W���摜�������g��
			m_stageName[i]->SetScale(BIG_STAGE_NAME);

			//�I������Ă���X�e�[�W�̔ԍ�������B
			m_stageNum = i;

			//�Q�[����ʑJ�ڏ���
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