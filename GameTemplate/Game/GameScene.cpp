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

	////�t�H���g�N���X
	//m_fontRender = NewGO<FontRender>(1);

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{
	//�X�e�[�W���폜�B
	DeleteGO(m_normalStage);
	//�v���C���[�N���X���폜�B
	DeleteGO(m_player);
	////�^�C�����폜
	//DeleteGO(m_fontRender);
}

void GameScene::Update()
{
	////�Q�[���c�莞�Ԃ��k�߂Ă����B
	//m_timer--;
	//int counttime = m_timer / 60;
	//wchar_t text1[64];
	//swprintf_s(text1, L"%d", counttime);
	//m_fontRender->SetText(text1);
	////0�b�ɂȂ�����A
	//if (counttime == 0)
	//{
	//	//���U���g��ʂɑJ��
	//	NewGO<ResultScene>(0);
	//}

	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}