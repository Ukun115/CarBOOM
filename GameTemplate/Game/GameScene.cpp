///<<summary>
///�Q�[����ʒ��̏������s���N���X
///</summary>


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
	const Vector4   TIMELIMIT_LAST_COL = { 1.0f,0.0f,0.0f,1.0f };	//�������ԃt�H���g�̎c��5�b�̐F

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
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);

	//�G�I�u�W�F�N�g����
	m_enemy = NewGO<Enemy>(PRIORITY_0, ENEMY_NAME);
	//�v���C���[�I�u�W�F�N�g����
	m_player = NewGO<Player>(PRIORITY_0, PLAYER_NAME);
	//�X�e�[�W�I�u�W�F�N�g����
	m_normalStage = NewGO<Stage>(PRIORITY_0, nullptr);

	//�����摜�I�u�W�F�N�g����
	m_crownSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//�����摜��������
	m_crownSprite->Init("Assets/image/DDS/crowngold.dds", 300.0f, 300.0f);	//�����摜
	m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });						//�ʒu��ݒ�
	m_crownSprite->SetScale({ CROWN_SCA });									//�g�嗦��ݒ�
	m_crownSprite->Deactivate();					//�͂��߂͒N����ʂ���Ȃ��̂ŉB���Ă����B

	//�������ԃt�H���g�I�u�W�F�N�g�����i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_timeLimit = NewGO<FontRender>(PRIORITY_1,nullptr);
	//�e�v���C���[�̃|�C���g�摜�̈ʒu��ݒ�
	m_plaScorePos[0] = { -520.0f, 255.0f };
	m_plaScorePos[1] = { 450.0f, 255.0f };
	m_plaScorePos[2] = { -520.0f,-205.0f };
	m_plaScorePos[3] = { 450.0f,-205.0f };

	for (int plaNum = 0; plaNum < 4; plaNum++) {
		//�v���C���[���Ƃ�pt�t�H���g�I�u�W�F�N�g����
		m_ScoreFontRender[plaNum] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//������
		m_ScoreFontRender[plaNum]->Init
		(
			L"pt",				//�e�L�X�g
			GetScorePos(plaNum),		//�ʒu
			ScoreColor(plaNum),		//�F
			FONT_ROT,			//�X��
			PT_SCA,				//�g�嗦
			FONT_PIV			//��_
		);
		//�v���C���[���Ƃ̃|�C���g�t�H���g�I�u�W�F�N�g����
		m_TextScoreFontRender[plaNum] = NewGO<FontRender>(PRIORITY_1, nullptr);
		//������
		m_TextScoreFontRender[plaNum]->Init
		(
			L"",					//�e�L�X�g
			m_plaScorePos[plaNum],		//�ʒu
			ScoreColor(plaNum),			//�F
			FONT_ROT,				//�X��
			FONT_SCA,				//�g�嗦
			FONT_PIV				//��_
		);


		//�����̋��E���\��
		m_ScoreFontRender[plaNum]->SetShadowParam(true, 1.0f, Vector4::Black);
		//�����̋��E���\��
		m_TextScoreFontRender[plaNum]->SetShadowParam(true, 1.0f, Vector4::Black);
	}
	//�o�^����Ă��Ȃ��v���C���[�̃X�R�A�̓O���[�\���ɂ���
	for (int plaNum = m_titleScene->GetTotalPlaNum() ; plaNum < 4; plaNum++)
	{
		m_ScoreFontRender[plaNum]->SetColor(GRAY);
		m_TextScoreFontRender[plaNum]->SetColor(GRAY);
	}
	//�������ԃt�H���g�̏�����
	m_timeLimit->Init
	(
		L"",			//�e�L�X�g
		TIMELIMIT_POS,	//�ʒu
		TIMELIMIT_COL,	//�F
		FONT_ROT,		//�X��
		FONT_SCA,		//�g�嗦
		FONT_PIV		//��_
	);
	//�����̋��E���\��
	m_timeLimit->SetShadowParam(true, 1.0f, Vector4::Black);

	m_syutyusen = NewGO<SpriteRender>(PRIORITY_0, nullptr);
	m_syutyusen->Init("Assets/image/DDS/BackScreenImage.dds", 1600.0f, 800.0f);

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
	//�������Ԃ̃J�E���g&�`�揈��
	TimeLimit();

	//�v���C���[�̃X�R�A�`��֐�
	PlaScoreDraw();

	//���݂̃X�R�A�P�ʂ𔻒肵�A�����摜���ړ�
	NowCrown();

	//�������Ԃ�0�b�ɂȂ�����A
	if (m_countTime == 0)
	{
		//���U���g��ʂɑJ�ڂ���
		ResultSceneTransition();
	}

	//�Q�[���V�[���ɑJ�ڂ�����A
	if (m_isFinishCountDownFlg)
	{
		//�J�E���g�_�E���������J�n
		CountDown();
	}
}


//�J�E���g�_�E�������֐�
void GameScene::CountDown()
{
	//�X�^�[�g�܂ł̃J�E���g�_�E�����J�n

	switch (m_countDownTimer) {
	//�J�E���g�_�E���^�C�}�[��0�̂Ƃ��A
	case 0:

		//�Q�[���X�^�[�g�W���O���T�E���h
		SoundPlayBack(GameStartGingle);

		break;

	case 300:
		//�J�E���g�_�E���T�E���h
		SoundPlayBack(CountDownSound);

		//�u�R�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_0]->SetPosition(Vector3::Zero);
		//������
		m_sprite[ARRAY_NUM_0]->Init("Assets/image/DDS/3.dds", 200.0f, 200.0f);

		break;

	//�J�E���g�_�E���^�C�}�[��60�̂Ƃ��A
	case 360:
		//�u3�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_0]);

		//�u�Q�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_1] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_1]->SetPosition(Vector3::Zero);
		//������
		m_sprite[ARRAY_NUM_1]->Init("Assets/image/DDS/2.dds", 200.0f, 200.0f);

		break;

	//�J�E���g�_�E���^�C�}�[��120�̂Ƃ��A
	case 420:
		//�u2�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_1]);

		//�u�P�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_2] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_2]->SetPosition(Vector3::Zero);
		//������
		m_sprite[ARRAY_NUM_2]->Init("Assets/image/DDS/1.dds", 200.0f, 200.0f);

		break;

		//�J�E���g�_�E���^�C�}�[��180�̂Ƃ��A
	case 480:
		//�u1�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_2]);

		//�uSTART�v�摜�I�u�W�F�N�g����
		m_sprite[ARRAY_NUM_3] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		m_sprite[ARRAY_NUM_3]->SetPosition(Vector3::Zero);
		//������
		m_sprite[ARRAY_NUM_3]->Init("Assets/image/DDS/START!!.dds", 400.0f, 200.0f);

		break;

		//�J�E���g�_�E���^�C�}�[��300�̂Ƃ��A
		//�uSTART�v�\���͓��ʏ�����������
	case 600:
		//�uSTART�v�폜�B
		DeleteGO(m_sprite[ARRAY_NUM_3]);

		//�Q�[������BGM�T�E���h
		SoundPlayBack(GameBGM);

		//�J�E���g�_�E���̏����𔲂���B
		m_isFinishCountDownFlg = false;

		break;
	}
	//�J�E���g�_�E���̃^�C�}�[�����Z
	m_countDownTimer++;
}


//�������ԏ����֐�
void GameScene::TimeLimit()
{
	//�J�E���g�_�E�����I����Ă��琧�����Ԃ�����ł����B
	if(!m_isFinishCountDownFlg)
	{
		//�������Ԃ��k�߂Ă����B
		m_timer--;
	}

	m_countTime = m_timer / 60;

	//�O�b�ɂȂ��Ă���̃J�E���g���}�C�i�X�ɍs���Ȃ��悤�ɕ␳
	m_countTime = max(0,m_countTime);

	//10�b�ȉ��̂Ƃ��A�������Ԃ�Ԃ��\��
	if(m_countTime <= 10)
	{
		m_timeLimit->SetColor(TIMELIMIT_LAST_COL);
	}

	//�������Ԃ̕`��
	swprintf_s(text1, L"%d", m_countTime);
	//��ʕ\��
	m_timeLimit->SetText(text1);
}


//�v���C���[�̃X�R�A�`��֐�
void GameScene::PlaScoreDraw()
{
	for (int plaNum = 0; plaNum < 4; plaNum++) {

		//�\���ʒu�X�V
		SetScoreTextPos(plaNum);

		//�v���C���[���Ƃ̃X�R�A�̕`��
		swprintf_s(text2, L"%d", m_plaScore[plaNum]);
		m_TextScoreFontRender[plaNum]->SetText(text2);
	}
}


//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
Vector2 GameScene::GetScorePos(int plaNum)
{
	switch (plaNum)
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


//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
void GameScene::SetScoreTextPos(int plaNum)
{
	//�X�R�A��1���̂Ƃ��A
	m_plaScorePos[0] = { -520.0f, 255.0f };
	m_plaScorePos[1] = { 450.0f, 255.0f };
	m_plaScorePos[2] = { -520.0f,-205.0f };
	m_plaScorePos[3] = { 450.0f,-205.0f };

	//�X�R�A��2���̂Ƃ��A
	if (10 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 100)
	{
		//������(x��-40)�ɂ��炵�ĕ\���ʒu�����킹��
		switch (plaNum)
		{
		case PLAYER1:
			m_plaScorePos[0].x = -560.0f;
			break;
		case PLAYER2:
			m_plaScorePos[1].x = 450.0f;
			break;
		case PLAYER3:
			m_plaScorePos[2].x = -560.0f;
			break;
		case PLAYER4:
			m_plaScorePos[3].x = 450.0f;
			break;
		}
	}
	//�X�R�A��3���̂Ƃ��A
	if (100 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 1000)
	{
		//������(x��-20)�ɂ��炵�ĕ\���ʒu�����킹��
		switch (plaNum)
		{
		case PLAYER1:
			m_plaScorePos[0].x = -580.0f;
			break;
		case PLAYER2:
			m_plaScorePos[1].x = 470.0f;
			break;
		case PLAYER3:
			m_plaScorePos[2].x = -580.0f;
			break;
		case PLAYER4:
			m_plaScorePos[3].x = 470.0f;
			break;
		}
	}
	//�X�R�A��4���̂Ƃ��A
	if (1000 <= m_plaScore[plaNum])
	{
		//������(x��-20)�ɂ��炵�ĕ\���ʒu�����킹��
		switch (plaNum)
		{
		case PLAYER1:
			m_plaScorePos[0].x = -600.0f;
			break;
		case PLAYER2:
			m_plaScorePos[1].x = 490.0f;
			break;
		case PLAYER3:
			m_plaScorePos[2].x = -600.0f;
			break;
		case PLAYER4:
			m_plaScorePos[3].x = 490.0f;
			break;
		}
	}

	//�ʒu���Z�b�g
	m_TextScoreFontRender[plaNum]->SetPosition(m_plaScorePos[plaNum]);
}


//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
Vector4 GameScene::ScoreColor(int plaNum)
{
	switch (plaNum)
	{
	case PLAYER1:
		return RED;
		break;
	case PLAYER2:
		return BLUE;
		break;
	case PLAYER3:
		return YELLOW;
		break;
	case PLAYER4:
		return GREEN;
		break;
	}
}


/*�v���C���[�̓��_�ϓ������֐�
  (plaNum1�͗��Ƃ����v���C���[�AplaNum2�͗��Ƃ��ꂽ�v���C���[)*/
void GameScene::GetPlayerAddScore(int plaNum1,int plaNum2)
{
	//4�̂Ƃ��������Ȃ�
	if (plaNum1 == 4)
	{
		return;
	}
	//���Ƃ����Ƃ��A
	//30pt����
	m_plaScore[plaNum1] += 30;
	//�������Ƃ����v���C���[��1�ʂ�������A
	if (plaNum2 == m_nowNumOnePla)
	{
		//���Ƃ��ꂽ�P�ʂ̓}�C�i�X20pt�B���Ƃ����v���C���[�̓v���X��20pt
		//��������邱�ƂłP�ʂ��_���₷���d�l�ɂ��Ă���B
		m_plaScore[plaNum2] -= 20;
		m_plaScore[plaNum1] += 20;
		//�_����0�ȉ��ɂȂ�Ȃ��悤�ɕ␳
		if (m_plaScore[plaNum2] < 0)
		{
			m_plaScore[plaNum2] = 0;
		}
	}
	//�G�𗎂Ƃ����Ƃ��A
	if (plaNum2 == 5)
	{
		//�G�𗎂Ƃ����Ƃ�pt��10pt�������悤�ɒ���
		//���ł�+30pt���Ă��邩��}�C�i�X20���Ă���B
		m_plaScore[plaNum1] -= 20;
	}
}


//�P�ʂɉ����摜�Ɖ������f����n���֐�
void GameScene::NowCrown()
{
	for (int plaNum = PLAYER1; plaNum < m_titleScene->GetTotalPlaNum(); plaNum++)
	{
		for (int nextPlaNum = PLAYER1; nextPlaNum < m_titleScene->GetTotalPlaNum(); nextPlaNum++)
		{
			//���̃v���C���[(i)�Ǝ��̃v���C���[(u)���r
			//���̃v���C���[�̂ق����X�R�A�������Ƃ��A
			if (m_plaScore[plaNum] < m_plaScore[nextPlaNum])
			{
				//�����X�v���C�g��\��������
				m_crownSprite->Activate();

				m_nowNumOnePla = nextPlaNum;
			}
		}
	}

	//�����̈ʒu�����̃v���C���[�̈ʒu�ɕύX
	if (m_nowNumOnePla == 0)
	{
		m_crownSprite->SetPosition({ PLAYER1_CROWN_POS });
	}
	if (m_nowNumOnePla == 1)
	{
		m_crownSprite->SetPosition({ PLAYER2_CROWN_POS });
	}
	if (m_nowNumOnePla == 2)
	{
		m_crownSprite->SetPosition({ PLAYER3_CROWN_POS });
	}
	if (m_nowNumOnePla == 3)
	{
		m_crownSprite->SetPosition({ PLAYER4_CROWN_POS });
	}
}


//���U���g��ʂɑJ�ڂ���֐�
void GameScene::ResultSceneTransition()
{
	//�^�C�}�[�����Z
	m_resultsenniTimer++;

	if (m_resultsenniTimer == 1)
	{
		//�z�C�b�X���T�E���h
		SoundPlayBack(WhistleSound);
	}
	//�^�C�}�[��120�𒴂��Ă��烊�U���g��ʂɑJ��
	if (m_resultsenniTimer == 180)
	{
		//���U���g��ʃI�u�W�F�N�g����
		NewGO<ResultScene>(PRIORITY_0, nullptr);
		//�Q�[��BGM�폜
		DeleteGO(m_gameBGM);
	}
}


//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void GameScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case GameStartGingle:
		//�Q�[���X�^�[�g�W���O���T�E���h�̏�����
		m_gameBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameBGM->Init(L"Assets/sound/GameStartGingle.wav");
		m_gameBGM->SetVolume(1.0f);
		m_gameBGM->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case CountDownSound:
		//�Q�[������BGM�T�E���h�̏�����
		m_countDown = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_countDown->Init(L"Assets/sound/CountDown.wav");
		m_countDown->SetVolume(1.0f);
		m_countDown->Play(false);	//�^�Ń����V���b�g�Đ�

		break;

	case GameBGM:
		//�Q�[������BGM�T�E���h�̏�����
		m_gameBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameBGM->Init(L"Assets/sound/GameBGM.wav");
		m_gameBGM->SetVolume(0.2f);
		m_gameBGM->Play(true);	//�^�Ń��[�v�Đ�

		break;

	case WhistleSound:
		//�z�C�b�X���T�E���h�̏�����
		m_whistleSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_whistleSound->Init(L"Assets/sound/Whistle.wav");
		m_whistleSound->SetVolume(0.1f);
		m_whistleSound->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}