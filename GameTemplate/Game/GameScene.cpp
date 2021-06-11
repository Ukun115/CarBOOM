#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Player.h"


namespace
{
	const Vector2 TIMEFONT_POS = {-40.0f,300.0f};			//�������ԃt�H���g�̈ʒu
	const Vector4 TIMEFONT_COL = {1.0f,1.0f,1.0f,1.0f};		//�������ԃt�H���g�̐F
	const float   TIMEFONT_ROT = 0.0f;						//�������ԃt�H���g�̌X��
	const float   TIMEFONT_SCA = 1.5f;						//�������ԃt�H���g�̊g�嗦
	const Vector2   TIMEFONT_PIV = { 0.0f,0.0f };			//�������ԃt�H���g�̊�_
}

bool GameScene::Start()
{
	//�v���C���[�N���X
	m_player = NewGO<Player>(0);

	//�X�e�[�W���f��
	m_normalStage = NewGO<SkinModelRender>(0);
	//���f���̃t�@�C���p�X��ݒ�B
	m_normalStage->Init("Assets/modelData/bg/stage_00.tkm");

	//�t�H���g�N���X�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_fontRender = NewGO<FontRender>(1);
	//�����ݒ�B
	m_fontRender->Init
	(
		L"",
		TIMEFONT_POS,	//�ʒu
		TIMEFONT_COL,	//�J���[
		TIMEFONT_ROT,	//�X��
		TIMEFONT_SCA,	//�g�嗦
		TIMEFONT_PIV	//��_
	);
	//�����̋��E���\��
	m_fontRender->SetShadowParam(true, 1.0f, Vector4::Black);

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{
	//�X�e�[�W���폜�B
	DeleteGO(m_normalStage);
	//�v���C���[�N���X���폜�B
	DeleteGO(m_player);
	//�^�C�����폜
	DeleteGO(m_fontRender);
}

void GameScene::Update()
{
	//�������Ԃ��k�߂Ă����B
	m_timer--;
	int counttime = m_timer / 60;
	wchar_t text1[64];
	swprintf_s(text1, L"%d", counttime);
	//��ʕ\��
	m_fontRender->SetText(text1);

	//�������Ԃ�0�b�ɂȂ�����A
	if (counttime == 0)
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
	}

	//A�{�^��(�L�[�{�[�h�FJ)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}