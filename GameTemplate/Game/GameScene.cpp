#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "PhysicsEnemy.h"
#include "PhysicsPlayer.h"
#include "Stage.h"

namespace
{
	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//�������ԃt�H���g�̈ʒu
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//�������ԃt�H���g�̐F
	const float     TIMELIMIT_ROT =   0.0f;						//�������ԃt�H���g�̌X��
	const float     TIMELIMIT_SCA =   1.5f;						//�������ԃt�H���g�̊g�嗦
	const Vector2   TIMELIMIT_PIV = { 0.0f,0.0f };				//�������ԃt�H���g�̊�_

	const Vector2   PLA1SCORE_POS = { -570.0f, 300.0f };			//1P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA2SCORE_POS = {  570.0f, 300.0f };			//2P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA3SCORE_POS = { -570.0f,-300.0f };			//3P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA4SCORE_POS = {  570.0f,-300.0f };			//4P�X�R�A�t�H���g�̈ʒu

	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int PLAYER3 = 2;
	const int PLAYER4 = 3;
	const int MAXPLAYERNUM = 4;		//�v���C���[�̍ő�l��

	const int SWITCH_PLA1 = 1;
	const int SWITCH_PLA2 = 2;
	const int SWITCH_PLA3 = 3;
	const int SWITCH_PLA4 = 4;
}

bool GameScene::Start()
{
	//�v���C���[�N���X
	physicsPlayer = NewGO<PhysicsPlayer>(0,"physicsplayer");
	//�G�N���X
	//enemy = NewGO<Enemy>(0);
	//�X�e�[�W�N���X
	physicsStage = NewGO<Stage>(0);

	//�t�H���g�N���X�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(1);
	//�����ݒ�B
	m_timeLimit->Init
	(
		L"",
		TIMELIMIT_POS,	//�ʒu
		TIMELIMIT_COL,	//�J���[
		TIMELIMIT_ROT,	//�X��
		TIMELIMIT_SCA,	//�g�嗦
		TIMELIMIT_PIV	//��_
	);
	//�����̋��E���\��
	m_timeLimit->SetShadowParam(true, 1.0f, Vector4::Black);

	////�����_�ł̃X�R�A�\��
	//for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	//{
	//	m_plaScore[i] = NewGO<FontRender>(1);
	//	//�����ݒ�B
	//	m_plaScore[i]->Init
	//	(
	//		L"",
	//		GetScorePos(i),	//�ʒu
	//		TIMELIMIT_COL,	//�J���[
	//		TIMELIMIT_ROT,	//�X��
	//		TIMELIMIT_SCA,	//�g�嗦
	//		TIMELIMIT_PIV	//��_
	//	);
	//	//�����̋��E���\��
	//	m_plaScore[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	//}

	//Start�֐���return
	return true;
}

GameScene::~GameScene()
{
	//�X�e�[�W���폜�B
	DeleteGO(m_normalStage);
	//�v���C���[�N���X���폜�B
	DeleteGO(physicsPlayer);
	//�^�C�����폜
	DeleteGO(m_timeLimit);
}

void GameScene::Update()
{
	//�Q�[���V�[���ɑJ�ڂ�����A
	if (m_countTimeFlg)
	{
		//�X�^�[�g�܂ł̃J�E���g�_�E�����J�n

		switch (m_countDownTimer) {
			case 0:
			//�u3�v�\��
			m_sprite[0] = NewGO<SpriteRender>(3);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

			break;

			case 60:
			//�u3�v�폜�B
			DeleteGO(m_sprite[0]);

			//�u2�v�\��
			m_sprite[1] = NewGO<SpriteRender>(3);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);

			break;

			case 120:
			//�u2�v�폜�B
			DeleteGO(m_sprite[1]);

			//�u1�v�\��
			m_sprite[2] = NewGO<SpriteRender>(3);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);

			break;

			case 180:
			//�u1�v�폜�B
			DeleteGO(m_sprite[2]);

			//�uGO!!�v�\��
			m_sprite[3] = NewGO<SpriteRender>(3);
			m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);

			break;

			case 300:
			//�uGO!!�v�폜�B
			DeleteGO(m_sprite[3]);

			//�J�E���g�_�E���̏����𔲂���B
			m_countTimeFlg = false;

			break;
		}
		m_countDownTimer++;
	}
	//�J�E���g�_�E�����I����Ă��琧�����Ԃ�����ł����B
	else
	{
		//�������Ԃ��k�߂Ă����B
		m_timer--;
	}
	counttime = m_timer / 60;
	//�O�b�ɂȂ��Ă���̃J�E���g���}�C�i�X�ɍs���Ȃ��悤�ɕ␳
	if (counttime < 0)
	{
		counttime = 0;
	}
	wchar_t text1[64];
	swprintf_s(text1, L"%d", counttime);
	//��ʕ\��
	m_timeLimit->SetText(text1);

	//�������Ԃ�0�b�ɂȂ�����A
	if (counttime == 0)
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
	}

	//1P�̃Z���N�g�{�^��(�L�[�{�[�h�F�X�y�[�X)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0);
		//���̃N���X�̍폜
		DeleteGO(this);
	}
}

//�uScore : �v�̕\���ʒu���ʊ֐�
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case SWITCH_PLA1:
		return PLA1SCORE_POS;
		break;
	case SWITCH_PLA2:
		return PLA2SCORE_POS;
		break;
	case SWITCH_PLA3:
		return PLA3SCORE_POS;
		break;
	case SWITCH_PLA4:
		return PLA4SCORE_POS;
		break;
	}
}