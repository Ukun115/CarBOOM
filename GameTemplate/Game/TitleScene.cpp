#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"


/// <summary>
/// ���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I
/// </summary>


namespace
{
	const int PRIORITY_0 = 0;	//�D��x0
	const int PRIORITY_1 = 1;	//�D��x1

	const Vector3 TITLE_POS = { 0.0f, 0.0f,0.0f };	//�^�C�g���̕\���ʒu

	const Vector3 PLAYER1_NAME_POS = {-480.0f, 310.0f,0.0f};			//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER2_NAME_POS = { 480.0f, 310.0f,0.0f};			//�v���C���[2�̖��O�\���ʒu
	const Vector3 PLAYER3_NAME_POS = {-480.0f,-310.0f,0.0f};			//�v���C���[3�̖��O�\���ʒu
	const Vector3 PLAYER4_NAME_POS = { 480.0f,-310.0f,0.0f};			//�v���C���[4�̖��O�\���ʒu

	const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//�_�ŕ����̕\���ʒu
	const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//�_�ŕ����̑傫��
}


bool TitleScene::Start()
{
	//�^�C�g�����S�I�u�W�F�N�g����
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 1600.0f, 800.0f);
	m_titleSprite->SetPosition({ TITLE_POS });

	//PUSH START BUTTON�I�u�W�F�N�g����
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ FlashingFont_SCA });

	//1P�͖������Œǉ��t���O��^�ɁB
	m_isAddPlayerFlg[PLAYER1] = true;
	//1P�͔�A�N�e�B�u�Ƃ����Ȃ����߁A���߂���A�N�e�B�u�摜�I�u�W�F�N�g����
	m_plaActiveName[PLAYER1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_plaActiveName[PLAYER1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 300.0f, 150.0f);
	m_plaActiveName[PLAYER1]->SetPosition(PLAYER1_NAME_POS);

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++) {
		//2P�`4P�̔�A�N�e�B�u�摜�I�u�W�F�N�g����
		m_plaDeactiveName[i] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//1P
		if (i == PLAYER1)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER1_NAME_POS);
			//��A�N�e�B�u���͂Ȃ����߁A��\���ɂ��Ă����B
			m_plaDeactiveName[i]->Deactivate();
		}
		//2P
		if (i == PLAYER2)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER2_NAME_POS);
		}
		//3P
		if (i == PLAYER3)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER3_NAME_POS);
		}
		//4P
		if (i == PLAYER4)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER4_NAME_POS);
		}
	}

	//Start�֐���return��
	return true;
}


TitleScene::~TitleScene()
{
	//�o�^���ꂽ�v���C���[�̃A�N�e�B�u�摜���폜
	for (int i = PLAYER1; i < m_totalPlaNum; i++)
	{
		DeleteGO(m_plaActiveName[i]);
	}
	//�o�^����Ă��Ȃ��v���C���[�̔�A�N�e�B�u�摜���폜
	for (int i = m_totalPlaNum; i < (MAXPLAYERNUM+1); i++)
	{
		//4P�܂œo�^����Ă�����m_plaDeactiveName[4]�ƁA
		//�Y�������I�[�o�[���Ă��܂��̂ł�����for���𔲂�������
		if (m_totalPlaNum == MAXPLAYERNUM)
		{
			break;
		}
		//�΂̔g���͑��v�ł�
		DeleteGO(m_plaDeactiveName[i]);
	}
}


void TitleScene::Update()
{
	//�Q�[����ʂɑJ�ڂ���Ɣ�����t���O
	if (m_isCanGameStartFlg == true) {

		//�o�^���ꂽ�v���C���[�����ő吔4�l�ɂȂ�܂Œǉ��ł���
		if (m_totalPlaNum != MAXPLAYERNUM)
		{
			/*�o�^����Ă��Ȃ��R���g���[���[��A�{�^���������ꂽ��A
			�y���ӁzUSB�|�[�g�Ɍq���ꂽ������Ȃ��Ɠo�^����Ă����܂���B*/
			if (g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
			{
				//�v���C���[��o�^����
				AddPlayer();
			}
		}

		//�o�^����Ă���N���̃X�^�[�g�{�^���������ꂽ��A
		for (int i = PLAYER1; i < m_totalPlaNum; i++)
		{
			if (g_pad[i]->IsTrigger(enButtonStart))
			{
				//�Q�[����ʂɑJ��
				GameSceneTransition();
			}
		}

		//�uPRESS START BUTTON�v�����摜�̓_�ŏ���
		FlashingFont();
	}
}


//�v���C���[��ǉ�����֐�
void TitleScene::AddPlayer()
{
	//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	//�v���C���[�̃A�N�e�B�u�摜�I�u�W�F�N�g�����i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_plaActiveName[m_totalPlaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//2P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == PLAYER2)
	{
		m_plaActiveName[PLAYER2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[PLAYER2]->SetPosition(PLAYER2_NAME_POS);
	}
	//3P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == PLAYER3)
	{
		m_plaActiveName[PLAYER3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[PLAYER3]->SetPosition(PLAYER3_NAME_POS);
	}
	//4P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == PLAYER4)
	{
		m_plaActiveName[PLAYER4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[PLAYER4]->SetPosition(PLAYER4_NAME_POS);
	}
	//��A�N�e�B�u�摜���폜�B
	DeleteGO(m_plaDeactiveName[m_totalPlaNum]);
	//���̃v���C���[��...
	m_totalPlaNum++;
}


//�Q�[����ʂɑJ�ڂ���֐�
void TitleScene::GameSceneTransition()
{
	//�Q�[����ʂɑJ��
	NewGO<GameScene>(PRIORITY_0, "gamescene");
	////���̃N���X�̍폜
	////DeleteGO(this);

	//�^�C�g�����S���폜�B
	DeleteGO(m_titleSprite);
	//PUSHSTARTBUTTON���폜�B
	DeleteGO(m_pushStartButtonSprite);

	//�Q�[����ʂɑJ�ڌ�A�Q�[���J�n�{�^���ƃv���C���[�ǉ��{�^���������Ȃ�����t���O
	m_isCanGameStartFlg = false;
}


//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
void TitleScene::FlashingFont()
{
	if (m_isFlashingFontTimerActiveFlg)
	{
		//�^�C�}�[���Z
		m_flashingFontTimer++;
		//�uPRESS START BUTTON�v�\��
		m_pushStartButtonSprite->Activate();
	}
	else
	{
		//�^�C�}�[���Z
		m_flashingFontTimer--;
		//�uPRESS START BUTTON�v��\��
		m_pushStartButtonSprite->Deactivate();
	}
	//�^�C�}�[��60���傫���l�ɂȂ�ƁA
	if (m_flashingFontTimer > 60)
	{
		//�uPRESS START BUTTON�v���\���ɂ���t���O
		m_isFlashingFontTimerActiveFlg = false;
	}
	//�^�C�}�[��0��菬�����l�ɂȂ�ƁA
	if (m_flashingFontTimer < 10)
	{
		//�uPRESS START BUTTON�v��\������t���O
		m_isFlashingFontTimerActiveFlg = true;
	}
}