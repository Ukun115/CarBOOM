#include "stdafx.h"
#include "GameScene.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "ResultScene.h"

bool GameScene::Start()
{
	//�f�B���N�V�������C�g�����[�h
	m_directionlight = NewGO<DirectionLight>(0);

	//�|�C���g���C�g�����[�h
	m_pointlight = NewGO<PointLight>(0);

	//���f�������[�h
	m_skinmodelrender = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	m_skinmodelrender->Init("Assets/modelData/unityChan.tkm");
	//���f���Ƀf�B���N�V�������C�g�̐ݒ�
	m_skinmodelrender->SetDirLigData(directionLig);

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