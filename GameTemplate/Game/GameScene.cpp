#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "SkinModelRender.h"

bool GameScene::Start()
{
	//�ԁi�j���f�������[�h
	m_skinmodelrender = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	m_skinmodelrender->Init("Assets/modelData/LowPoly_PlayerCar_Bule.tkm");
	//���f���̑傫����2�{
	m_skinmodelrender->SetScale({2,2,2});
	//���f����X���W�����_���炸�炵�ă|�C���g���C�g���킩��₷���悤�ɂ���
	m_unityPos.x = 50.0f;
	m_skinmodelrender->SetPosition(m_unityPos);

	//���A���f�������[�h
	m_bgModel = NewGO<SkinModelRender>(0);
	m_bgModel->Init("Assets/modelData/bg/bg.tkm");

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{

	DeleteGO(m_skinmodelrender);
}

void GameScene::Update()
{
	//�������ǂ����̃e�X�g/////////////////////////////
	if (g_pad[0]->IsPress(enButtonRight)) {
		m_unityPos.x += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_unityPos.x -= 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonUp)) {
		m_unityPos.z += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		m_unityPos.z -= 1.0f;
	}
	m_skinmodelrender->SetPosition(m_unityPos);	//�ʒu���X�V
	//////////////////////////////////////////////////////////////////////

	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}