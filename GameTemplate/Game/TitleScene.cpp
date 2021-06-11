#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

/// <summary>
/// ���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I
/// </summary>

namespace
{
	const int PLAYER1   = 0;
	const int PLAYER2   = 1;
	const int PLAYER3   = 2;
	const int PLAYER4   = 3;
	const Vector3 PLAYER1_NAMEPOS = {-550.0f, 300.0f,0.0f};		//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER2_NAMEPOS = { 550.0f, 300.0f,0.0f};		//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER3_NAMEPOS = {-550.0f,-300.0f,0.0f};		//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER4_NAMEPOS = { 550.0f,-300.0f,0.0f};		//�v���C���[1�̖��O�\���ʒu
	const int MAXPLAYERNUM = 4;
}

bool TitleScene::Start()
{
	//1P�͖������Œǉ��t���O��^�ɁB
	isAddPlayer[PLAYER1] = true;

	//�T���v���w�i�摜���������B
	m_spriteRender[PLAYER1] = NewGO<SpriteRender>(0);
	m_spriteRender[PLAYER1]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
	m_spriteRender[PLAYER1]->SetPosition(PLAYER1_NAMEPOS);

	//Start�֐���return��
	return true;
}

TitleScene::~TitleScene()
{
	//�v���C���[�̐��������O�\���摜���폜
	for (int i = 0; i < m_totalPlayerNum; i++)
	{
		DeleteGO(m_spriteRender[i]);
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

				//�v���C���[�̃A�N�e�B�u��
				//�T���v���w�i�摜���������B
				m_spriteRender[m_totalPlayerNum] = NewGO<SpriteRender>(0);
				//2P�̃A�N�e�B�u��
				if (m_totalPlayerNum == PLAYER2)
				{
					m_spriteRender[PLAYER2]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_spriteRender[PLAYER2]->SetPosition(PLAYER2_NAMEPOS);
				}
				//3P�̃A�N�e�B�u��
				if (m_totalPlayerNum == PLAYER3)
				{
					m_spriteRender[PLAYER3]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_spriteRender[PLAYER3]->SetPosition(PLAYER3_NAMEPOS);
				}
				//4P�̃A�N�e�B�u��
				if (m_totalPlayerNum == PLAYER4)
				{
					m_spriteRender[PLAYER4]->Init("Assets/image/eheheNS.dds", 230.0f, 120.0f);
					//�摜�̃|�W�V�����w��
					m_spriteRender[PLAYER4]->SetPosition(PLAYER4_NAMEPOS);
				}
				//���̃v���C���[��...
				m_totalPlayerNum++;
			}
		}
		//1P�̃X�^�[�g�{�^���������ꂽ��Q�[���J�n
		if (g_pad[PLAYER1]->IsTrigger(enButtonStart))
		{
			//�Q�[����ʂɑJ��
			NewGO<GameScene>(0);
			//���̃N���X�̍폜
			//DeleteGO(this);

			//��x�̂݃Q�[���J�n�{�^����������悤�ɂ���
			isCanGameStartFlg = false;
		}
	}
}