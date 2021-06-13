#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// ���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I
/// </summary>

namespace
{
	const Vector3 TITLE_POS = { -60.0f, 50.0f,0.0f };			//�^�C�g���̕\���ʒu
	const Vector3 TITLE_SCA = { 6.0f, 6.0f,6.0f };			//�^�C�g���̑傫��

	const int PLAYER1   = 0;	//1P
	const int PLAYER2   = 1;	//2P
	const int PLAYER3   = 2;	//3P
	const int PLAYER4   = 3;	//4P
	const Vector3 PLAYER1_NAMEPOS = {-570.0f, 300.0f,0.0f};			//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER2_NAMEPOS = { 570.0f, 300.0f,0.0f};			//�v���C���[2�̖��O�\���ʒu
	const Vector3 PLAYER3_NAMEPOS = {-570.0f,-300.0f,0.0f};			//�v���C���[3�̖��O�\���ʒu
	const Vector3 PLAYER4_NAMEPOS = { 570.0f,-300.0f,0.0f};			//�v���C���[4�̖��O�\���ʒu

	const Vector3 PLAYER1_CROWNPOS = { -470.0f, 300.0f,0.0f };		//�v���C���[1�̉����\���ʒu
	const Vector3 PLAYER2_CROWNPOS = { 470.0f, 300.0f,0.0f };		//�v���C���[2�̉����\���ʒu
	const Vector3 PLAYER3_CROWNPOS = { -470.0f, -300.0f,0.0f };		//�v���C���[3�̉����\���ʒu
	const Vector3 PLAYER4_CROWNPOS = { 470.0f, -300.0f,0.0f };		//�v���C���[4�̉����\���ʒu
	const Vector3 CROWNSCA = { 0.2f, 0.2f,0.2f };					//�����̑傫��

	const Vector3 BUTTON_POS = { 0.0f, -200.0f,0.0f };				//�v�b�V���X�^�[�g�{�^���̕\���ʒu
	const Vector3 BUTTON_SCA = { 1.2f, 1.2f,1.2f };					//�v�b�V���X�^�[�g�{�^���̑傫��
	const Vector4 BUTTON_MULCOL = { 1.0f, 1.0f,1.0f ,0.0f};			//�v�b�V���X�^�[�g�{�^���̏�Z�J���[

	const int MAXPLAYERNUM = 4;		//�ő�v���C�l��

	const float PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED = 0.02f;
}

bool TitleScene::Start()
{
	//�^�C�g�����S��\��
	m_titleSprite = NewGO<SpriteRender>(0);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 300.0f, 150.0f);
	m_titleSprite->SetPosition({ TITLE_POS });
	m_titleSprite->SetScale({ TITLE_SCA });

	//������\��
	m_crownSprite = NewGO<SpriteRender>(1);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });

	//PUSH START BUTTON��\��
	m_pushStartButtonSprite = NewGO<SpriteRender>(1);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ BUTTON_POS });
	m_pushStartButtonSprite->SetScale({ BUTTON_SCA });
	m_pushStartButtonSprite->SetMulColor({ BUTTON_MULCOL });//����

	//1P�͖������Œǉ��t���O��^�ɁB
	isAddPlayer[PLAYER1] = true;
	//1P�͔�A�N�e�B�u�����Ȃ����߁A���߂���A�N�e�B�u�摜��\��
	//�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_plaActiveName[PLAYER1] = NewGO<SpriteRender>(1);
	m_plaActiveName[PLAYER1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 120.0f, 120.0f);
	m_plaActiveName[PLAYER1]->SetPosition(PLAYER1_NAMEPOS);

	//2P�`4P�̔�A�N�e�B�u�摜��\���B
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++) {
		//�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
		m_plaDeactiveName[i] = NewGO<SpriteRender>(1);
		//1P
		if (i == PLAYER1)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER1_NAMEPOS);
			//��A�N�e�B�u���͂Ȃ����߁A��\���ɂ��Ă����B
			m_plaDeactiveName[i]->Deactivate();
		}
		//2P
		if (i == PLAYER2)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER2_NAMEPOS);
		}
		//3P
		if (i == PLAYER3)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER3_NAMEPOS);
		}
		//4P
		if (i == PLAYER4)
		{
			m_plaDeactiveName[i]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 120.0f, 120.0f);
			m_plaDeactiveName[i]->SetPosition(PLAYER4_NAMEPOS);
		}
	}

	//Start�֐���return��
	return true;
}

TitleScene::~TitleScene()
{
	//�o�^���ꂽ�v���C���[�̐������A�N�e�B�u�摜���폜
	for (int i = PLAYER1; i < m_totalPlayerNum; i++)
	{
		DeleteGO(m_plaActiveName[i]);
	}
	//�o�^����Ă��Ȃ��v���C���[�̔�A�N�e�B�u�摜���폜
	for (int i = m_totalPlayerNum; i < (MAXPLAYERNUM+1); i++)
	{
		//4P�܂œo�^����Ă�����m_plaDeactiveName[4]�ƁA
		//�Y�������I�[�o�[���Ă��܂��̂ł�����for���𔲂�������B
		if (m_totalPlayerNum == MAXPLAYERNUM)
		{
			break;
		}
		//�΂̔g���͑��v�ł��B
		DeleteGO(m_plaDeactiveName[i]);
	}
}

void TitleScene::Update()
{
	if (isCanGameStartFlg == true) {
		//�v���C���[��ǉ�����
		if (m_totalPlayerNum != MAXPLAYERNUM)
		{
			//�o�^����Ă��Ȃ��R���g���[���[�̃X�^�[�g�{�^���������ꂽ��A
			if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonA))
			{
				//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
				isAddPlayer[m_totalPlayerNum] = true;

				//�v���C���[�̃A�N�e�B�u���i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
				m_plaActiveName[m_totalPlayerNum] = NewGO<SpriteRender>(1);
				//2P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
				if (m_totalPlayerNum == PLAYER2)
				{
					m_plaActiveName[PLAYER2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 120.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_plaActiveName[PLAYER2]->SetPosition(PLAYER2_NAMEPOS);
				}
				//3P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
				if (m_totalPlayerNum == PLAYER3)
				{
					m_plaActiveName[PLAYER3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 120.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_plaActiveName[PLAYER3]->SetPosition(PLAYER3_NAMEPOS);
				}
				//4P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
				if (m_totalPlayerNum == PLAYER4)
				{
					m_plaActiveName[PLAYER4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 120.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_plaActiveName[PLAYER4]->SetPosition(PLAYER4_NAMEPOS);
				}
				//��A�N�e�B�u�摜���폜�B
				DeleteGO(m_plaDeactiveName[m_totalPlayerNum]);
				//���̃v���C���[��...
				m_totalPlayerNum++;
			}
		}

		//�N���̃X�^�[�g�{�^���������ꂽ��Q�[���J�n
		for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
		{
			if (g_pad[i]->IsTrigger(enButtonStart))
			{
				//�Q�[����ʂɑJ��
				NewGO<GameScene>(0,"gamescene");
				//���̃N���X�̍폜
				//DeleteGO(this);

				//�^�C�g�����S���폜�B
				DeleteGO(m_titleSprite);
				//PUSHSTARTBUTTON���폜�B
				DeleteGO(m_pushStartButtonSprite);


				//�Q�[���J�n��A�Q�[���J�n�{�^���ƃv���C���[�ǉ��{�^���������Ȃ��Ȃ�t���O
				isCanGameStartFlg = false;
			}
		}

		//PRESSSTARTBUTTON�̓_�ŏ���
		//�t���O�������Ă���ƁA
		if (isButtonFlg == true)
		{
			//���񂾂�Ɠ����ɂ���
			m_pushStartButtonSprite->SetMulColor({ 1.0f,1.0f,1.0f,m_pushStartButtonSprite->GetMulColor().w - PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED });

			//���S�ɓ����ɂȂ�����A
			if (m_pushStartButtonSprite->GetMulColor().w <= 0.0f)
			{
				//�t���O��܂�
				isButtonFlg = false;
			}
		}
		//�t���O���܂ꂽ��A
		else
		{
			//���񂾂�ƕs�����ɂ���
			m_pushStartButtonSprite->SetMulColor({ 1.0f,1.0f,1.0f,m_pushStartButtonSprite->GetMulColor().w + PRESSSTARTBUTTON_CHANGE_ALPHA_SPEED });

			//�s�����ɂȂ�����
			if (m_pushStartButtonSprite->GetMulColor().w >= 0.8f)
			{
				//�t���O�𗧂Ă�
				isButtonFlg = true;
			}
		}
	}
}