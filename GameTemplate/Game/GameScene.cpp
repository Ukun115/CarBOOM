#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"


namespace
{

}

bool GameScene::Start()
{
	//�v���C���[�N���X��ǉ�
	m_player = NewGO<Player>(0);

	//�X�e�[�W���f�������[�h
	m_normalStage = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	m_normalStage->Init("Assets/modelData/bg/stage_00.tkm");

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{
	//�X�e�[�W���폜�B
	DeleteGO(m_normalStage);
	//�v���C���[�N���X���폜�B
	DeleteGO(m_player);
}

void GameScene::Update()
{
	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}