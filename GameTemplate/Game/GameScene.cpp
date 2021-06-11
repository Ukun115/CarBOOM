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
	NewGO<Player>(0);

	//�X�e�[�W���f�������[�h
	bg_normal = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	bg_normal->Init("Assets/modelData/bg/stage_00.tkm");

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{

}

void GameScene::Update()
{


	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}