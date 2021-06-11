#include "stdafx.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{
	const int PLAYER1   = 0;
	const int MAXPLAYERNUM = 4;
}

bool TitleScene::Start()
{
	//1P�͖������Œǉ��t���O��^�ɁB
	addPlayer[PLAYER1] = true;

	//�T���v���w�i�摜���������B
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/image/eheheNS.dds", 1300.0f, 750.0f);
	m_spriteRender->SetPosition(Vector3::Zero);

	//Start�֐���return��
	return true;
}

TitleScene::~TitleScene()
{
	DeleteGO(m_spriteRender);
}

void TitleScene::Update()
{

	//�v���C���[��ǉ�����
	if(m_totalPlayerNum != MAXPLAYERNUM)
	{
		//�o�^����Ă��Ȃ��R���g���[���[�̃X�^�[�g�{�^���������ꂽ��A
		if (g_pad[m_totalPlayerNum]->IsTrigger(enButtonStart))
		{
			//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
			addPlayer[m_totalPlayerNum] = true;

			m_totalPlayerNum++;
		}
	}

	//1P�̃X�^�[�g�{�^��(�L�[�{�[�h�FJ)�������ꂽ��Q�[���J�n
	if (g_pad[PLAYER1]->IsTrigger(enButtonStart))
	{
		//�Q�[����ʂɑJ��
		NewGO<GameScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}

}