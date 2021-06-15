#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "PhysicsPlayer.h"
#include "Stage.h"

namespace
{
	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//�������ԃt�H���g�̈ʒu
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//�������ԃt�H���g�̐F
	const float     TIMELIMIT_ROT = 0.0f;						//�������ԃt�H���g�̌X��
	const float     TIMELIMIT_SCA = 1.5f;						//�������ԃt�H���g�̊g�嗦
	const Vector2   TIMELIMIT_PIV = { 0.0f,0.0f };				//�������ԃt�H���g�̊�_

	const Vector2   PLA1SCORE_POS = { -460.0f, 255.0f };			//1P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA2SCORE_POS = { 520.0f, 255.0f };			//2P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA3SCORE_POS = { -460.0f,-205.0f };			//3P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA4SCORE_POS = { 520.0f,-205.0f };			//4P�X�R�A�t�H���g�̈ʒu

	const Vector2 PLAYER1_SCOREFONTPOS = { -630.0f,260.0f };	//�v���C���[1��SCROE�����\��
	const Vector2 PLAYER2_SCOREFONTPOS = { 350.0f,260.0f };		//�v���C���[2��SCROE�����\��
	const Vector2 PLAYER3_SCOREFONTPOS = { -630.0f,-200.0f };	//�v���C���[3��SCROE�����\��
	const Vector2 PLAYER4_SCOREFONTPOS = { 350.0f,-200.0f };	//�v���C���[4��SCROE�����\��

	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int PLAYER3 = 2;
	const int PLAYER4 = 3;
	const int MAXPLAYERNUM = 4;		//�v���C���[�̍ő�l��

	const int SWITCH_PLA1 = 0;
	const int SWITCH_PLA2 = 1;
	const int SWITCH_PLA3 = 2;
	const int SWITCH_PLA4 = 3;
}

bool GameScene::Start()
{
	//�G�N���X
	enemy = NewGO<Enemy>(0,"enemy");
	//�v���C���[�N���X
	physicsPlayer = NewGO<PhysicsPlayer>(0, "physicsplayer");
	//�X�e�[�W�N���X
	physicsStage = NewGO<Stage>(0, nullptr);

	//�t�H���g�N���X�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(1);
	for (int i = 0; i < 4; i++) {
		m_ScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_ScoreFontRender[i]->Init
		(
			L"Score",
			GetScorePos(i),
			TIMELIMIT_COL,	//�J���[
			TIMELIMIT_ROT,	//�X��
			TIMELIMIT_SCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
		);

		m_TextScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_TextScoreFontRender[i]->Init
		(
			L"",
			SetScoreTextPos(i),
			TIMELIMIT_COL,	//�J���[
			TIMELIMIT_ROT,	//�X��
			TIMELIMIT_SCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
		);


		//�����̋��E���\��
		m_ScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
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
			m_sprite[0] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

			break;

		case 60:
			//�u3�v�폜�B
			DeleteGO(m_sprite[0]);

			//�u2�v�\��
			m_sprite[1] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);

			break;

		case 120:
			//�u2�v�폜�B
			DeleteGO(m_sprite[1]);

			//�u1�v�\��
			m_sprite[2] = NewGO<SpriteRender>(3, nullptr);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);

			break;

		case 180:
			//�u1�v�폜�B
			DeleteGO(m_sprite[2]);

			//�uGO!!�v�\��
			m_sprite[3] = NewGO<SpriteRender>(3, nullptr);
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

	//�c�莞�Ԃ̕`��
	wchar_t text1[64];
	swprintf_s(text1, L"%d", counttime);
	//��ʕ\��
	m_timeLimit->SetText(text1);

	wchar_t text2[64];
	swprintf_s(text2, L"%d", m_plscore);


	for (int i = 0; i < 4; i++) {
		//�v���C���[���Ƃ̃X�R�A�̕`��
		swprintf_s(text1, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text1);
	}

	//�������Ԃ�0�b�ɂȂ�����A
	if (counttime == 0)
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0, nullptr);
	}

	//1P�̃Z���N�g�{�^��(�L�[�{�[�h�F�X�y�[�X)�������ꂽ��A
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		//���U���g��ʂɑJ��
		NewGO<ResultScene>(0, nullptr);
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
		return PLAYER1_SCOREFONTPOS;
		break;
	case SWITCH_PLA2:
		return PLAYER2_SCOREFONTPOS;
		break;
	case SWITCH_PLA3:
		return PLAYER3_SCOREFONTPOS;
		break;
	case SWITCH_PLA4:
		return PLAYER4_SCOREFONTPOS;
		break;
	}
}

Vector2 GameScene::SetScoreTextPos(int t) {
	switch (t)
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
		return  PLA4SCORE_POS;
		break;
	}
}