#include "stdafx.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "Enemy.h"
#include "Player.h"
#include "Stage.h"
#include "TitleScene.h"


namespace
{
<<<<<<< HEAD
	//�D��x
	const int PRIORITY_0 = 0;
	const int PRIORITY_1 = 1;
=======
	const int PRIORITY_0 = 0;	//�D��x0
	const int PRIORITY_1 = 1;	//�D��x1
>>>>>>> remotes/origin/master

	const Vector2   TIMELIMIT_POS = { -40.0f,300.0f };			//�������ԃt�H���g�̈ʒu
	const Vector4   TIMELIMIT_COL = { 1.0f,1.0f,1.0f,1.0f };	//�������ԃt�H���g�̐F

	const Vector2   PLA1SCORE_POS = { -520.0f, 255.0f };	//1P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA2SCORE_POS = { 450.0f, 255.0f };		//2P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA3SCORE_POS = { -520.0f,-205.0f };	//3P�X�R�A�t�H���g�̈ʒu
	const Vector2   PLA4SCORE_POS = { 450.0f,-205.0f };		//4P�X�R�A�t�H���g�̈ʒu

	const Vector4	PLAYER1_COL_RED = { 1.0f,0.0f,0.0f,1.0f };		//�v���C���[�P�̃X�R�A�̐F
	const Vector4	PLAYER2_COL_BLUE = { 0.0f,0.0f,1.0f,1.0f };		//�v���C���[�Q�̃X�R�A�̐F
	const Vector4	PLAYER3_COL_YELLOW = { 1.0f,1.0f,0.0f,1.0f };		//�v���C���[�R�̃X�R�A�̐F
	const Vector4	PLAYER4_COL_GREEN = { 0.0f,1.0f,0.0f,1.0f };		//�v���C���[�S�̃X�R�A�̐F
	const Vector4	PLAYER_COL_GRAY = { 0.7f,0.7f,0.7f,1.0f };		//�S�v���C���[�̔�A�N�e�B�u�̃X�R�A�̐F

	const float     FONT_ROT = 0.0f;			//�t�H���g�̌X��
	const Vector2   FONT_PIV = { 1.0f,1.0f };	//�t�H���g�̊�_
	const float     FONT_SCA = 1.5f;			//�t�H���g�̊g�嗦

	const Vector2 PLAYER1_PT_POS = { -420.0f,235.0f };	//�v���C���[1��pt�����\��
	const Vector2 PLAYER2_PT_POS = { 550.0f,235.0f };	//�v���C���[2��pt�����\��
	const Vector2 PLAYER3_PT_POS = { -420.0f,-230.0f };	//�v���C���[3��pt�����\��
	const Vector2 PLAYER4_PT_POS = { 550.0f,-230.0f };	//�v���C���[4��pt�����\��
	const float PT_SCA = 0.85f;		//pt�����̑傫��

	const Vector3 PLAYER1_CROWN_POS = { -320.0f, 310.0f,0.0f };		//�v���C���[1�̉����摜�\���ʒu
	const Vector3 PLAYER2_CROWN_POS = { 300.0f, 310.0f,0.0f };		//�v���C���[2�̉����摜�\���ʒu
	const Vector3 PLAYER3_CROWN_POS = { -300.0f, -310.0f,0.0f };	//�v���C���[3�̉����摜�\���ʒu
	const Vector3 PLAYER4_CROWN_POS = { 300.0f, -310.0f,0.0f };		//�v���C���[4�̉����摜�\���ʒu
	const Vector3 CROWN_SCA = { 0.2f, 0.2f,0.2f };					//�����摜�̊g�嗦

	const Vector3 CROWN_MODEL_SCA = {0.5f,0.5f,0.5f};	//�������f���̊g�嗦
	//�z��ԍ�
	const int ARRAY_NUM_0 = 0;
	const int ARRAY_NUM_1 = 1;
	const int ARRAY_NUM_2 = 2;
	const int ARRAY_NUM_3 = 3;
}


bool GameScene::Start()
{
	//�C���X�^���X��T���B
	m_titleScene = FindGO<TitleScene>("titlescene");

<<<<<<< HEAD
	//�G�I�u�W�F�N�g����
	m_enemy = NewGO<Enemy>(PRIORITY_0,"enemy");
	//�v���C���[�I�u�W�F�N�g����
	m_player = NewGO<Player>(PRIORITY_0, "player");
	//�X�e�[�W�I�u�W�F�N�g����
	m_normalStage = NewGO<Stage>(PRIORITY_0, nullptr);

	//�����摜�I�u�W�F�N�g����
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//�����摜��������
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);	//�����摜
	m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });						//�ʒu��ݒ�
	m_crownSprite->SetScale({ CROWN_SCA });									//�g�嗦��ݒ�
	m_crownSprite->Deactivate();					//�͂��߂͒N����ʂ���Ȃ��̂ŉB���Ă����B
=======
	//�G�N���X
	m_enemy = NewGO<Enemy>(PRIORITY_0,"enemy");
	//�v���C���[�N���X
	m_player = NewGO<Player>(PRIORITY_0, "player");
	//�X�e�[�W�N���X
	m_normalStage = NewGO<Stage>(PRIORITY_0, nullptr);

	//�����摜��������
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);
	m_crownSprite->SetPosition({ PLAYER1_CROWNPOS });
	m_crownSprite->SetScale({ CROWNSCA });
	//�͂��߂͒N����ʂ���Ȃ��̂ŉB���Ă����B
	m_crownSprite->Deactivate();
>>>>>>> remotes/origin/master

	//�������f���I�u�W�F�N�g����
	m_crownModel = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
	//�������f����������
<<<<<<< HEAD
	m_crownModel->Init("Assets/modelData/Crown.tkm");
	m_crownModel->SetScale({ Vector3::Zero });	//�͂��߂͒N���P�ʂ���Ȃ��̂ő傫����0�ɂ��ĉB���Ă���

	//�������ԃt�H���g�I�u�W�F�N�g�����i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	for (int i = 0; i < 4; i++) {
		//�v���C���[���Ƃ�pt�t�H���g�I�u�W�F�N�g����
		m_ScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//������
		m_ScoreFontRender[i]->Init
		(
			L"pt",				//�e�L�X�g
			GetScorePos(i),		//�ʒu
			ScoreColor(i),		//�F
			FONT_ROT,			//�X��
			PT_SCA,				//�g�嗦
			FONT_PIV			//��_
		);
		//�v���C���[���Ƃ̃|�C���g�t�H���g�I�u�W�F�N�g����
		m_TextScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//������
		m_TextScoreFontRender[i]->Init
		(
			L"",					//�e�L�X�g
			SetScoreTextPos(i),		//�ʒu
			ScoreColor(i),			//�F
			FONT_ROT,				//�X��
			FONT_SCA,				//�g�嗦
			FONT_PIV				//��_
=======
	m_crownModel = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
	m_crownModel->Init("Assets/modelData/Crown.tkm");
	m_crownModel->SetScale({ Vector3::Zero });	//�͂��߂͒N���P�ʂ���Ȃ��̂ő傫����0�ɂ��ĉB���Ă���

	//�t�H���g�N���X�i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	for (int i = 0; i < 4; i++) {
		m_ScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		m_ScoreFontRender[i]->Init
		(
			L"pt",
			GetScorePos(i),
			ScoreColor(i),	//�F
			TIMELIMIT_ROT,	//�X��
			SCORESCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
		);

		m_TextScoreFontRender[i] = NewGO<FontRender>(PRIORITY_1, nullptr);
		m_TextScoreFontRender[i]->Init
		(
			L"",
			SetScoreTextPos(i),
			ScoreColor(i),	//�F
			TIMELIMIT_ROT,	//�X��
			TIMELIMIT_SCA,	//�g�嗦
			TIMELIMIT_PIV	//��_
>>>>>>> remotes/origin/master
		);


		//�����̋��E���\��
		m_ScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
		//�����̋��E���\��
		m_TextScoreFontRender[i]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
	//�o�^����Ă��Ȃ��v���C���[�̃X�R�A�̓O���[�\���ɂ���
	for (int i = m_titleScene->GetTotalPlaNum() ; i < 4; i++)
	{
		m_ScoreFontRender[i]->SetColor(PLAYER_COL_GRAY);
		m_TextScoreFontRender[i]->SetColor(PLAYER_COL_GRAY);
	}
	//�������ԃt�H���g�̏�����
	m_timeLimit->Init
	(
		L"",			//�e�L�X�g
		TIMELIMIT_POS,	//�ʒu
		TIMELIMIT_COL,	//�F
<<<<<<< HEAD
		FONT_ROT,		//�X��
		FONT_SCA,		//�g�嗦
		FONT_PIV		//��_
=======
		TIMELIMIT_ROT,	//�X��
		TIMELIMIT_SCA,	//�g�嗦
		TIMELIMIT_PIV	//��_
>>>>>>> remotes/origin/master
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
	DeleteGO(m_player);
	//�G�N���X���폜�B
	DeleteGO(m_enemy);
	//�^�C�����폜
	DeleteGO(m_timeLimit);
}


void GameScene::Update()
{
	//�Q�[���V�[���ɑJ�ڂ�����A
	if (m_isCountTimeFlg)
	{
		//�J�E���g�_�E���������J�n
		CountDown();
	}

<<<<<<< HEAD
	//�������Ԃ̃J�E���g&�`�揈��
	TimeLimit();
=======
		switch (m_countDownTimer) {
		case 0:
			//�u3�v�\��
			m_sprite[0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

	//�v���C���[�̃X�R�A�`��֐�
	PlaScoreDraw();

	//���݂̃X�R�A�P�ʂ𔻒肵�A�����摜���ړ�
	NowCrown();

<<<<<<< HEAD
	//�������Ԃ�0�b�ɂȂ�����A
	if (m_counttime == 0)
	{
		//���U���g��ʂɑJ�ڂ���
		ResultSceneTransition();
	}
}
=======
			//�u2�v�\��
			m_sprite[1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

//�J�E���g�_�E�������֐�
void GameScene::CountDown()
{
	//�X�^�[�g�܂ł̃J�E���g�_�E�����J�n

	switch (m_countDownTimer) {
	//�J�E���g�_�E���^�C�}�[��0�̂Ƃ��A
	case 0:
		//�u�R�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_0]->SetPosition({ 0.0f,0.0f,0.0f });
		//������
		m_sprite[ARRAY_NUM_0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

		break;

	//�J�E���g�_�E���^�C�}�[��60�̂Ƃ��A
	case 60:
		//�u3�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_0]);

<<<<<<< HEAD
		//�u�Q�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_1]->SetPosition({ 0.0f,0.0f,0.0f });
		//������
		m_sprite[ARRAY_NUM_1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);
=======
			//�u1�v�\��
			m_sprite[2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);
>>>>>>> remotes/origin/master

		break;

	//�J�E���g�_�E���^�C�}�[��120�̂Ƃ��A
	case 120:
		//�u2�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_1]);

<<<<<<< HEAD
		//�u�P�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_2]->SetPosition({ 0.0f,0.0f,0.0f });
		//������
		m_sprite[ARRAY_NUM_2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);
=======
			//�uGO!!�v�\��
			m_sprite[3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
			m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			m_sprite[3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);
>>>>>>> remotes/origin/master

		break;

		//�J�E���g�_�E���^�C�}�[��180�̂Ƃ��A
	case 180:
		//�u1�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_2]);

<<<<<<< HEAD
		//�uSTART�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_3]->SetPosition({ 0.0f,0.0f,0.0f });
		//������
		m_sprite[ARRAY_NUM_3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);
=======
			//�J�E���g�_�E���̏����𔲂���B
			m_isCountTimeFlg = false;
>>>>>>> remotes/origin/master

		break;

		//�J�E���g�_�E���^�C�}�[��300�̂Ƃ��A
		//�uSTART�v�\���͓��ʏ�����������
	case 300:
		//�uSTART�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_3]);

		//�J�E���g�_�E���̏����𔲂���B
		m_isCountTimeFlg = false;

		break;
	}
	//�J�E���g�_�E���̃^�C�}�[�����Z
	m_countDownTimer++;
}


//�������ԏ����֐�
void GameScene::TimeLimit()
{
	//�J�E���g�_�E�����I����Ă��琧�����Ԃ�����ł����B
	if(m_isCountTimeFlg == false)
	{
		//�������Ԃ��k�߂Ă����B
		m_timer--;
	}
<<<<<<< HEAD

	m_counttime = m_timer / 60;

=======
	m_counttime = m_timer / 60;
>>>>>>> remotes/origin/master
	//�O�b�ɂȂ��Ă���̃J�E���g���}�C�i�X�ɍs���Ȃ��悤�ɕ␳
	if (m_counttime < 0)
	{
		m_counttime = 0;
	}

<<<<<<< HEAD
	//�������Ԃ̕`��
=======
	//�c�莞�Ԃ̕`��
	wchar_t text1[64];
>>>>>>> remotes/origin/master
	swprintf_s(text1, L"%d", m_counttime);
	//��ʕ\��
	m_timeLimit->SetText(text1);
}


//�v���C���[�̃X�R�A�`��֐�
void GameScene::PlaScoreDraw()
{
	for (int i = 0; i < 4; i++) {
		//�v���C���[���Ƃ̃X�R�A�̕`��
<<<<<<< HEAD
		swprintf_s(text2, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text2);
=======
		swprintf_s(text1, L"%d", m_plscore[i]);
		m_TextScoreFontRender[i]->SetText(text1);
	}

	//���݂̃X�R�A�P�ʂ𔻒肵�A�����摜���ړ�
	NowCrown();

	//�������Ԃ�0�b�ɂȂ�����A
	if (m_counttime == 0)
	{
		m_resultsenniTimer++;
		if(m_resultsenniTimer > 120)
		{
			//���U���g��ʂɑJ��
			NewGO<ResultScene>(PRIORITY_0, nullptr);
		}
>>>>>>> remotes/origin/master
	}
}


//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
Vector2 GameScene::GetScorePos(int x)
{
	switch (x)
	{
	case PLAYER1:
		return PLAYER1_PT_POS;
		break;
	case PLAYER2:
		return PLAYER2_PT_POS;
		break;
	case PLAYER3:
		return PLAYER3_PT_POS;
		break;
	case PLAYER4:
		return PLAYER4_PT_POS;
		break;
	}
}

<<<<<<< HEAD

=======
>>>>>>> remotes/origin/master
//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
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

<<<<<<< HEAD

=======
>>>>>>> remotes/origin/master
//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
Vector4 GameScene::ScoreColor(int c)
{
	switch (c)
	{
	case PLAYER1:
		return PLAYER1_COL_RED;
		break;
	case PLAYER2:
		return PLAYER2_COL_BLUE;
		break;
	case PLAYER3:
		return PLAYER3_COL_YELLOW;
		break;
	case PLAYER4:
		return PLAYER4_COL_GREEN;
		break;
	}
}


/*�v���C���[�̓��_�ϓ������֐�
  (���͗��Ƃ����v���C���[�Ay�͎��ł����v���C���[)*/
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


//�P�ʂɉ����摜�Ɖ������f����n���֐�
void GameScene::NowCrown()
{
	for (int i = PLAYER1; i < m_titleScene->GetTotalPlaNum(); i++)
	{
		for (int u = PLAYER1; u < m_titleScene->GetTotalPlaNum(); u++)
		{
			//���̃v���C���[(i)�Ǝ��̃v���C���[(u)���r
			//���̃v���C���[�̂ق����X�R�A�������Ƃ��A
			if (m_plscore[i] < m_plscore[u])
			{
				//�����X�v���C�g��\��������
				m_crownSprite->Activate();
				//�������f����\��������
				m_crownModel->SetScale(CROWN_MODEL_SCA);

				m_nowNumOnePla = u;
			}
		}
	}

	//�����̈ʒu�����̃v���C���[�̈ʒu�ɕύX
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = m_player->GetPlaPos(0);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWN_POS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = m_player->GetPlaPos(1);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWN_POS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = m_player->GetPlaPos(2);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWN_POS });
		//�������f�������̃v���C���[�̓���ɒu��
		m_crownModelPos = m_player->GetPlaPos(3);
		m_crownModel->SetPosition({ m_crownModelPos.x,m_crownModelPos.y + 30.0f,m_crownModelPos.z });
	}
}


//���U���g��ʂɑJ�ڂ���֐�
void GameScene::ResultSceneTransition()
{

		//�^�C�}�[�����Z
		m_resultsenniTimer++;
		//�^�C�}�[��120�𒴂��Ă��烊�U���g��ʂɑJ��
		if (m_resultsenniTimer > 120)
		{
			//���U���g��ʃI�u�W�F�N�g����
			NewGO<ResultScene>(PRIORITY_0, nullptr);
		}
}