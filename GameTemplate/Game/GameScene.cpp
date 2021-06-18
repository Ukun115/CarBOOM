#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "TitleScene.h"

namespace
{
	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//�������ԃt�H���g�̈ʒu
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//�������ԃt�H���g�̐F
	const float     TIMELIMIT_ROT = 0.0f;						//�������ԃt�H���g�̌X��
	const float     TIMELIMIT_SCA = 1.5f;						//�������ԃt�H���g�̊g�嗦
	const Vector2   TIMELIMIT_PIV = { 1.0f,1.0f };				//�������ԃt�H���g�̊�_

	const Vector2   PLA1SCORE_POS = { -520.0f, 255.0f };		//1P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA2SCORE_POS = { 450.0f, 255.0f };			//2P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA3SCORE_POS = { -520.0f,-205.0f };		//3P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA4SCORE_POS = { 450.0f,-205.0f };			//4P�X�R�A�t�H���g�̈ʒu

	const Vector4	PLAYER1SCORE_COL = { 1.0f,0.0f,0.0f,1.0f };
	const Vector4	PLAYER2SCORE_COL = { 0.0f,0.0f,1.0f,1.0f };
	const Vector4	PLAYER3SCORE_COL = { 1.0f,1.0f,0.0f,1.0f };
	const Vector4	PLAYER4SCORE_COL = { 0.0f,1.0f,0.0f,1.0f };
	const Vector4	PLAYERSCORE_GRAYCOL = { 0.7f,0.7f,0.7f,1.0f };

	const Vector2 PLAYER1_SCOREFONTPOS = { -420.0f,235.0f };	//�v���C���[1��SCROE�����\��
	const Vector2 PLAYER2_SCOREFONTPOS = { 550.0f,235.0f };		//�v���C���[2��SCROE�����\��
	const Vector2 PLAYER3_SCOREFONTPOS = { -420.0f,-230.0f };	//�v���C���[3��SCROE�����\��
	const Vector2 PLAYER4_SCOREFONTPOS = { 550.0f,-230.0f };	//�v���C���[4��SCROE�����\��
	const float SCORESCA = 0.85f;								//SCORE�����̑傫��

	const Vector3 PLAYER1_CROWNPOS = { -320.0f, 310.0f,0.0f };		//�v���C���[1�̉����\���ʒu
	const Vector3 PLAYER2_CROWNPOS = { 300.0f, 310.0f,0.0f };		//�v���C���[2�̉����\���ʒu
	const Vector3 PLAYER3_CROWNPOS = { -300.0f, -310.0f,0.0f };		//�v���C���[3�̉����\���ʒu
	const Vector3 PLAYER4_CROWNPOS = { 300.0f, -310.0f,0.0f };		//�v���C���[4�̉����\���ʒu
	const Vector3 CROWNSCA = { 0.2f, 0.2f,0.2f };					//�����摜�̑傫��

	const Vector3 CROWNMODELSCA = {0.5f,0.5f,0.5f};
}

bool GameScene::Start()
{
	//�G�N���X
	enemy = NewGO<Enemy>(0,"enemy");
	//�v���C���[�N���X
	player = NewGO<Player>(0, "player");
	//�X�e�[�W�N���X
	physicsStage = NewGO<Stage>(0, nullptr);

	//�C���X�^���X���쐬
	m_titlescene = FindGO<TitleScene>("titlescene");

	//�����摜��������
	m_crownSprite = NewGO<SpriteRender>(1, nullptr);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });
	//�͂��߂͒N����ʂ���Ȃ��̂ŉB���Ă����B
	m_crownSprite->Deactivate();

	//�������f����������
	m_crownModel = NewGO<SkinModelRender>(1, nullptr);
	m_crownModel->Init("Assets/modelData/Crown.tkm");
	m_crownModel->SetScale({ Vector3::Zero });	//�͂��߂͒N���P�ʂ���Ȃ��̂ő傫����0�ɂ��ĉB���Ă���

	//�t�H���g�N���X�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(1);
	for (int i = 0; i < 4; i++) {
		m_ScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_ScoreFontRender[i]->Init
		(
			L"pt",
			GetScorePos(i),
			ScoreColor(i),	//�J���[
			TIMELIMIT_ROT,	//�X��
			SCORESCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
		);

		m_TextScoreFontRender[i] = NewGO<FontRender>(1, nullptr);
		m_TextScoreFontRender[i]->Init
		(
			L"",
			SetScoreTextPos(i),
			ScoreColor(i),	//�J���[
			TIMELIMIT_ROT,	//�X��
			TIMELIMIT_SCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
		);


		//�����̋��E���\��
		m_ScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
		//�����̋��E���\��
		m_TextScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
	//�o�^����Ă��Ȃ��v���C���[�̃X�R�A�̓O���[�\���ɂ���
	for (int i = m_titlescene->GetTotalPlaNum() ; i < 4; i++)
	{
		m_ScoreFontRender[i]->SetColor(PLAYERSCORE_GRAYCOL);
		m_TextScoreFontRender[i]->SetColor(PLAYERSCORE_GRAYCOL);
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
	DeleteGO(player);
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

	//���݂̃X�R�A�P�ʂ𔻒肵�A�����摜���ړ�
	NowCrown();

	//�������Ԃ�0�b�ɂȂ�����A
	if (counttime == 0)
	{
		m_resultsenniTimer++;
		if(m_resultsenniTimer > 120)
		{
			//���U���g��ʂɑJ��
			NewGO<ResultScene>(0, nullptr);
		}
	}
}

//�uScore�v�̕\���ʒu���ʊ֐�
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case PLAYER1:
		return PLAYER1_SCOREFONTPOS;
		break;
	case PLAYER2:
		return PLAYER2_SCOREFONTPOS;
		break;
	case PLAYER3:
		return PLAYER3_SCOREFONTPOS;
		break;
	case PLAYER4:
		return PLAYER4_SCOREFONTPOS;
		break;
	}
}

Vector2 GameScene::SetScoreTextPos(int t) {
	switch (t)
	{
	case PLAYER1:
		return PLA1SCORE_POS;
		break;
	case PLAYER2:
		return PLA2SCORE_POS;
		break;
	case PLAYER3:
		return PLA3SCORE_POS;
		break;
	case PLAYER4:
		return  PLA4SCORE_POS;
		break;
	}
}

Vector4 GameScene::ScoreColor(int c)
{
	switch (c)
	{
	case PLAYER1:
		return PLAYER1SCORE_COL;
		break;
	case PLAYER2:
		return PLAYER2SCORE_COL;
		break;
	case PLAYER3:
		return PLAYER3SCORE_COL;
		break;
	case PLAYER4:
		return PLAYER4SCORE_COL;
		break;
	}
}

//���͗��Ƃ����v���C���[�Ay�͎��ł����v���C���[
void GameScene::GetPlayerAddScore(int x,int y)
{
	//���ł����Ƃ��A
	if (x == 4)
	{
		//20pt����
		m_plscore[y] -= 20;
		//�_�����O�ȉ��ɂȂ�Ȃ��悤�ɕ␳
		if (m_plscore[y] < 0)
		{
			m_plscore[y] = 0;
		}
	}
	//���Ƃ����Ƃ��A
	else
	{
		//30pt����
		m_plscore[x] += 30;
		//�������Ƃ����G��1�ʂ�������A
		if (y == m_nowNumOnePla)
		{
			//���Ƃ��ꂽ�P�ʂ̓}�C�i�X60pt
			//��������邱�ƂłP�ʂ��_���₷���d�l�ɂ��Ă���B
			m_plscore[y] -= 60;
			//�_�����O�ȉ��ɂȂ�Ȃ��悤�ɕ␳
			if (m_plscore[y] < 0)
			{
				m_plscore[y] = 0;
			}
		}
	}
}

//�����摜�̈ʒu�X�V�֐�
void GameScene::NowCrown()
{
	for (int i = PLAYER1; i < m_titlescene->GetTotalPlaNum(); i++)
	{
		for (int u = PLAYER1; u < m_titlescene->GetTotalPlaNum(); u++)
		{
			//���̃v���C���[(i)�Ǝ��̃v���C���[(u)���r
			//���̃v���C���[�̂ق����X�R�A�������Ƃ��A
			if (m_plscore[i] < m_plscore[u])
			{
				//�����X�v���C�g��\��������
				m_crownSprite->Activate();
				//�������f����\��������
				m_crownModel->SetScale(CROWNMODELSCA);

				m_nowNumOnePla = u;
			}
		}
	}

	//�����̈ʒu�����̃v���C���[�̈ʒu�ɕύX
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = player->GetPlaPos(0);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWNPOS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = player->GetPlaPos(1);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWNPOS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = player->GetPlaPos(2);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWNPOS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = player->GetPlaPos(3);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
}