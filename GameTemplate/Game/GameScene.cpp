#include "stdafx.h"
#include "GameScene.h"
#include "PointLight.h"
#include "ResultScene.h"
#include "SkinModelRender.h"

bool GameScene::Start()
{
	//���f�������[�h
	m_skinmodelrender = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	m_skinmodelrender->Init("Assets/modelData/unityChan.tkm");

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{
	DeleteGO(m_skinmodelrender);
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