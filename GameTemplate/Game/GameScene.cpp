///<<summary>
///�Q�[���V�[���̃��C������
///</summary>

#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Stage.h"
#include "Enemy.h"
#include "Player.h"
#include "Fade.h"
#include "PlayerName.h"
#include "Pause.h"

namespace nsCARBOOM
{
	namespace nsGameScene
	{
		const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//�v���C���[1�̖��O�\���ʒu
		const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//�v���C���[2�̖��O�\���ʒu
		const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//�v���C���[3�̖��O�\���ʒu
		const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//�v���C���[4�̖��O�\���ʒu
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
		//�z��ԍ�
		const int ARRAY_NUM_0 = 0;
		const int ARRAY_NUM_1 = 1;
		const int ARRAY_NUM_2 = 2;
		const int ARRAY_NUM_3 = 3;
	}

	bool GameScene::Start()
	{
		m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

		//���C�g�I�u�W�F�N�g����
		m_light = NewGO<Light>(nsStdafx::PRIORITY_0, nsStdafx::LIGHT_NAME);
		//�f�B���N�V�������C�g���Z�b�g
		m_light->SetDirectionLightData();
		//�������C�g���Z�b�g
		m_light->SetHemiSphereLightData();

		//�t�F�[�h�C��
		m_fade[FadeIn] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
		m_fade[FadeIn]->SetState(StateIn);
		m_fade[FadeIn]->SetAlphaValue(1.0f);

		//�|�[�Y�@�\
		m_pause = NewGO<Pause>(nsStdafx::PRIORITY_0, nsStdafx::PAUSE_NAME);

		//��ʋ��̃v���C���[���t�H���g
		m_playerName = NewGO<PlayerName>(nsStdafx::PRIORITY_0, nullptr);
		m_playerName->SetTotalPlaNum(m_totalPlaNum);

		//�G�I�u�W�F�N�g����
		m_enemy = NewGO<Enemy>(nsStdafx::PRIORITY_0, nsStdafx::ENEMY_NAME);
		m_enemy->SetTotalPlaNum(m_totalPlaNum);
		m_enemy->SetStageSelectNum(m_stageSelecttNum);

		//�v���C���[�I�u�W�F�N�g����
		m_player = NewGO<Player>(nsStdafx::PRIORITY_0, nsStdafx::PLAYER_NAME);
		m_player->SetTotalPlaNum(m_totalPlaNum);
		m_player->SetStageSelectNum(m_stageSelecttNum);

		//�X�e�[�W�I�u�W�F�N�g����
		m_stage = NewGO<Stage>(nsStdafx::PRIORITY_0, nsStdafx::STAGE_NAME);
		m_stage->SetSelectStageNum(m_stageSelecttNum);
		m_stage->SetTotalPlaNum(m_stageSelecttNum);

		//�����摜�I�u�W�F�N�g����
		m_crownSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
		//�����摜��������
		m_crownSprite->Init("crowngold", 300.0f, 300.0f);	//�����摜
		m_crownSprite->SetPosition({ nsGameScene::PLAYER1_CROWN_POS });						//�ʒu��ݒ�
		m_crownSprite->SetScale({ nsGameScene::CROWN_SCA });									//�g�嗦��ݒ�
		m_crownSprite->Deactivate();					//�͂��߂͒N����ʂ���Ȃ��̂ŉB���Ă����B

		m_gameBackScreen = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		m_gameBackScreen->Init("BackScreenImage", 1600.0f, 800.0f);

		//�������ԃt�H���g�̏��������܂Ƃ߂Ă���֐�
		InitTimeLimitFont();
		//�v���C���[�̃|�C���g�t�H���g�̏��������܂Ƃ߂Ă���֐�
		InitPlayerPtFont();

		return true;
	}

	GameScene::~GameScene()
	{
		if (m_light != nullptr)
		{
			DeleteGO(m_light);
		}
		if (m_fade[FadeIn] != nullptr)
		{
			DeleteGO(m_fade[FadeIn]);
		}
		if (m_fade[FadeOut] != nullptr)
		{
			DeleteGO(m_fade[FadeOut]);
		}
		if (m_stage != nullptr)
		{
			//�X�e�[�W���폜�B
			DeleteGO(m_stage);
		}

		for (int i = Player1; i < TotalPlaNum; i++)
		{
			//�J�E���g�_�E���X�v���C�g���폜
			DeleteGO(m_sprite[i]);
			//pt�������폜
			DeleteGO(m_ScoreFontRender[i]);
			//
			DeleteGO(m_TextScoreFontRender[i]);
		}
		DeleteGO(m_playerName);
		//�v���C���[�N���X���폜�B
		DeleteGO(m_player);
		//�G�N���X���폜�B
		DeleteGO(m_enemy);
		//�^�C�����폜
		DeleteGO(m_timeLimit);
		//�����摜���폜
		DeleteGO(m_crownSprite);
		//�Q�[����ʔw�i���폜
		DeleteGO(m_gameBackScreen);

		DeleteGO(m_resultScene);
		if(m_pause != nullptr)
		DeleteGO(m_pause);
	}

	void GameScene::Update()
	{
		if (m_fade[FadeOut] == nullptr && m_isPauseFlg)
		{
			//�X�e�[�W�I����ʂɖ߂�
			for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
			{
				//�X�^�[�g�{�^���������ꂽ��A
				if (g_pad[plaNum]->IsTrigger(enButtonStart))
				{
					//����T�E���h
					m_soundPlayBack->GameSceneSoundPlayBack(DecideSound);
					//�t�F�[�h�A�E�g
					m_fade[FadeOut] = NewGO<Fade>(nsStdafx::PRIORITY_0, nullptr);
					m_fade[FadeOut]->SetState(StateOut);
					m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

				}
			}
		}
		if (m_fade[FadeOut] != nullptr && m_fade[FadeOut]->GetNowState() == StateWait)
		{
			//�X�e�[�W�I����ʂɖ߂�
			m_stageSelectScene = NewGO<StageSelectScene>(0, nullptr);
			m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);
			m_soundPlayBack->GameSceneDeleteGO();
			DeleteGO(this);
		}

		//�|�[�Y���̂Ƃ��́Areturn�ȍ~�̏��������Ȃ��B
		if (m_isPauseFlg)
		{
			return;
		}

		//�������Ԃ̃J�E���g&�`�揈��
		TimeLimit();
		m_stage->SetNowTime(m_countTime);

		//�v���C���[�̃X�R�A�`��֐�
		PlaScoreDraw();

		//���݂̃X�R�A�P�ʂ𔻒肵�A�����摜���ړ�
		NowCrown();

		//�������Ԃ�0�b�ɂȂ�����A
		if (m_countTime == nsStdafx::INT_ZERO)
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

		//���U���g�V�[���N���X���폜���ꂽ�瓯�����Q�[���V�[�����폜����
		if (m_deleteFlg)
		{
			DeleteGO(this);
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
			m_soundPlayBack->GameSceneSoundPlayBack(GameStartGingle);

			break;

		case 300:
			//�J�E���g�_�E���T�E���h
			m_soundPlayBack->GameSceneSoundPlayBack(CountDownSound);

			//�u�R�v�摜�I�u�W�F�N�g����
			m_sprite[nsGameScene::ARRAY_NUM_0] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
			m_sprite[nsGameScene::ARRAY_NUM_0]->SetPosition(Vector3::Zero);
			//������
			m_sprite[nsGameScene::ARRAY_NUM_0]->Init("3", 200.0f, 200.0f);

			break;

			//�J�E���g�_�E���^�C�}�[��60�̂Ƃ��A
		case 360:
			//�u3�v�폜�B
			DeleteGO(m_sprite[nsGameScene::ARRAY_NUM_0]);

			//�u�Q�v�摜�I�u�W�F�N�g����
			m_sprite[nsGameScene::ARRAY_NUM_1] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
			m_sprite[nsGameScene::ARRAY_NUM_1]->SetPosition(Vector3::Zero);
			//������
			m_sprite[nsGameScene::ARRAY_NUM_1]->Init("2", 200.0f, 200.0f);

			break;

			//�J�E���g�_�E���^�C�}�[��120�̂Ƃ��A
		case 420:
			//�u2�v�폜�B
			DeleteGO(m_sprite[nsGameScene::ARRAY_NUM_1]);

			//�u�P�v�摜�I�u�W�F�N�g����
			m_sprite[nsGameScene::ARRAY_NUM_2] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
			m_sprite[nsGameScene::ARRAY_NUM_2]->SetPosition(Vector3::Zero);
			//������
			m_sprite[nsGameScene::ARRAY_NUM_2]->Init("1", 200.0f, 200.0f);

			break;

			//�J�E���g�_�E���^�C�}�[��180�̂Ƃ��A
		case 480:
			//�u1�v�폜�B
			DeleteGO(m_sprite[nsGameScene::ARRAY_NUM_2]);

			//�uSTART�v�摜�I�u�W�F�N�g����
			m_sprite[nsGameScene::ARRAY_NUM_3] = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
			m_sprite[nsGameScene::ARRAY_NUM_3]->SetPosition(Vector3::Zero);
			//������
			m_sprite[nsGameScene::ARRAY_NUM_3]->Init("START!!", 400.0f, 200.0f);

			break;

			//�J�E���g�_�E���^�C�}�[��300�̂Ƃ��A
			//�uSTART�v�\���͓��ʏ�����������
		case 600:
			//�uSTART�v�폜�B
			DeleteGO(m_sprite[nsGameScene::ARRAY_NUM_3]);

			//�Q�[������BGM�T�E���h
			m_soundPlayBack->GameSceneSoundPlayBack(GameBGM);

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
		if (!m_isFinishCountDownFlg)
		{
			//�������Ԃ��k�߂Ă����B
			m_timer--;
		}

		m_countTime = m_timer / 60;

		//�O�b�ɂȂ��Ă���̃J�E���g���}�C�i�X�ɍs���Ȃ��悤�ɕ␳
		m_countTime = max(0, m_countTime);

		//10�b�ȉ��̂Ƃ��A�������Ԃ�Ԃ��\��
		if (m_countTime <= 10)
		{
			m_timeLimit->SetColor(nsGameScene::TIMELIMIT_LAST_COL);
		}

		//�������Ԃ̕`��
		swprintf_s(text1, L"%d", m_countTime);
		//��ʕ\��
		m_timeLimit->SetText(text1);
	}

	//�v���C���[�̃X�R�A�`��֐�
	void GameScene::PlaScoreDraw()
	{
		for (int plaNum = nsStdafx::INT_ZERO; plaNum < TotalPlaNum; plaNum++) {

			//�\���ʒu�X�V
			SetScoreTextPos(plaNum);

			//�v���C���[���Ƃ̃X�R�A�̕`��
			swprintf_s(text2, L"%d", m_plaScore[plaNum]);
			m_TextScoreFontRender[plaNum]->SetText(text2);
		}
	}

	//�v���C���[���Ƃ́upt�v�����̈ʒu���w�肷��֐�
	Vector2 GameScene::GetScorePos(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return nsGameScene::PLAYER1_PT_POS;
			break;
		case Player2:
			return nsGameScene::PLAYER2_PT_POS;
			break;
		case Player3:
			return nsGameScene::PLAYER3_PT_POS;
			break;
		case Player4:
			return nsGameScene::PLAYER4_PT_POS;
			break;
		}
	}

	//�v���C���[���Ƃ̃X�R�A�̈ʒu���w�肷��֐�
	void GameScene::SetScoreTextPos(const int plaNum)
	{
		//�X�R�A��1���̂Ƃ��A
		m_plaScorePos[Player1] = { -520.0f, 255.0f };
		m_plaScorePos[Player2] = { 450.0f, 255.0f };
		m_plaScorePos[Player3] = { -520.0f,-205.0f };
		m_plaScorePos[Player4] = { 450.0f,-205.0f };

		//�X�R�A��2���̂Ƃ��A
		if (10 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 100)
		{
			//������(x��-40)�ɂ��炵�ĕ\���ʒu�����킹��
			switch (plaNum)
			{
			case Player1:
				m_plaScorePos[Player1].x = -560.0f;
				break;
			case Player2:
				m_plaScorePos[Player2].x = 410.0f;
				break;
			case Player3:
				m_plaScorePos[Player3].x = -560.0f;
				break;
			case Player4:
				m_plaScorePos[Player4].x = 410.0f;
				break;
			}
		}
		//�X�R�A��3���̂Ƃ��A
		if (100 <= m_plaScore[plaNum] && m_plaScore[plaNum] < 1000)
		{
			//������(x��-20)�ɂ��炵�ĕ\���ʒu�����킹��
			switch (plaNum)
			{
			case Player1:
				m_plaScorePos[Player1].x = -580.0f;
				break;
			case Player2:
				m_plaScorePos[Player2].x = 390.0f;
				break;
			case Player3:
				m_plaScorePos[Player3].x = -580.0f;
				break;
			case Player4:
				m_plaScorePos[Player4].x = 390.0f;
				break;
			}
		}
		//�X�R�A��4���̂Ƃ��A
		if (1000 <= m_plaScore[plaNum])
		{
			//������(x��-20)�ɂ��炵�ĕ\���ʒu�����킹��
			switch (plaNum)
			{
			case Player1:
				m_plaScorePos[Player1].x = -600.0f;
				break;
			case Player2:
				m_plaScorePos[Player2].x = 370.0f;
				break;
			case Player3:
				m_plaScorePos[Player3].x = -600.0f;
				break;
			case Player4:
				m_plaScorePos[Player4].x = 370.0f;
				break;
			}
		}

		//�ʒu���Z�b�g
		m_TextScoreFontRender[plaNum]->SetPosition(m_plaScorePos[plaNum]);
	}

	//�v���C���[���Ƃ̃X�R�A�̐F���w�肷��֐�
	Vector4 GameScene::ScoreColor(const int plaNum)
	{
		switch (plaNum)
		{
		case Player1:
			return nsStdafx::RED;
			break;
		case Player2:
			return nsStdafx::BLUE;
			break;
		case Player3:
			return nsStdafx::YELLOW;
			break;
		case Player4:
			return nsStdafx::GREEN;
			break;
		}
	}

	/*�v���C���[�̓��_�ϓ������֐�
	  (plaNum1�͗��Ƃ����v���C���[�AplaNum2�͗��Ƃ��ꂽ�v���C���[)*/
	void GameScene::GetPlayerAddScore(const int plaNum1, const int plaNum2)
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
		}

		//�_����0�ȉ��ɂȂ�Ȃ��悤�ɕ␳
		m_plaScore[plaNum2] = max(m_plaScore[plaNum2], nsStdafx::INT_ZERO);
	}

	//�P�ʂɉ����摜�Ɖ������f����n���֐�
	void GameScene::NowCrown()
	{
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			for (int nextPlaNum = Player1; nextPlaNum < m_totalPlaNum; nextPlaNum++)
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
		switch (m_nowNumOnePla)
		{
		case Player1:
			m_crownSprite->SetPosition({ nsGameScene::PLAYER1_CROWN_POS });
			break;
		case Player2:
			m_crownSprite->SetPosition({ nsGameScene::PLAYER2_CROWN_POS });
			break;
		case Player3:
			m_crownSprite->SetPosition({ nsGameScene::PLAYER3_CROWN_POS });
			break;
		case Player4:
			m_crownSprite->SetPosition({ nsGameScene::PLAYER4_CROWN_POS });
			break;
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
			m_soundPlayBack->GameSceneSoundPlayBack(WhistleSound);
		}
		//�^�C�}�[��180�𒴂��Ă��烊�U���g��ʂɑJ��
		if (m_resultsenniTimer == 180)
		{
			m_soundPlayBack->GameSceneDeleteGO();
			//�|�[�Y�@�\���~
			DeleteGO(m_pause);
			//���U���g��ʃI�u�W�F�N�g����
			m_resultScene = NewGO<ResultScene>(nsStdafx::PRIORITY_1, nullptr);
			m_resultScene->SetTotalPlayerNum(m_totalPlaNum);
		}
	}

	//�v���C���[�̃|�C���g�t�H���g�̏��������܂Ƃ߂Ă���֐�
	void GameScene::InitPlayerPtFont()
	{
		//�e�v���C���[�̃|�C���g�摜�̈ʒu��ݒ�
		m_plaScorePos[0] = { -520.0f, 255.0f };
		m_plaScorePos[1] = { 450.0f, 255.0f };
		m_plaScorePos[2] = { -520.0f,-205.0f };
		m_plaScorePos[3] = { 450.0f,-205.0f };

		for (int plaNum = nsStdafx::INT_ZERO; plaNum < TotalPlaNum; plaNum++) {
			//�v���C���[���Ƃ�pt�t�H���g�I�u�W�F�N�g����
			m_ScoreFontRender[plaNum] = NewGO<FontRender>(nsStdafx::PRIORITY_1, nullptr);
			//������
			m_ScoreFontRender[plaNum]->Init
			(
				L"pt",				//�e�L�X�g
				GetScorePos(plaNum),		//�ʒu
				ScoreColor(plaNum),		//�F
				nsGameScene::FONT_ROT,			//�X��
				nsGameScene::PT_SCA,				//�g�嗦
				nsGameScene::FONT_PIV			//��_
			);
			//�v���C���[���Ƃ̃|�C���g�t�H���g�I�u�W�F�N�g����
			m_TextScoreFontRender[plaNum] = NewGO<FontRender>(nsStdafx::PRIORITY_1, nullptr);
			//������
			m_TextScoreFontRender[plaNum]->Init
			(
				L"",					//�e�L�X�g
				m_plaScorePos[plaNum],		//�ʒu
				ScoreColor(plaNum),			//�F
				nsGameScene::FONT_ROT,				//�X��
				nsGameScene::FONT_SCA,				//�g�嗦
				nsGameScene::FONT_PIV				//��_
			);


			//�����̋��E���\��
			m_ScoreFontRender[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
			//�����̋��E���\��
			m_TextScoreFontRender[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
		}
		//�o�^����Ă��Ȃ��v���C���[�̃X�R�A�̓O���[�\���ɂ���
		for (int plaNum = m_totalPlaNum; plaNum < TotalPlaNum; plaNum++)
		{
			m_ScoreFontRender[plaNum]->SetColor(nsStdafx::GRAY);
			m_TextScoreFontRender[plaNum]->SetColor(nsStdafx::GRAY);
		}
	}

	//�������ԃt�H���g�̏��������܂Ƃ߂Ă���֐�
	void GameScene::InitTimeLimitFont()
	{
		//�������ԃt�H���g�I�u�W�F�N�g�����i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
		m_timeLimit = NewGO<FontRender>(nsStdafx::PRIORITY_1, nullptr);

		//�������ԃt�H���g�̏�����
		m_timeLimit->Init
		(
			L"",			//�e�L�X�g
			nsGameScene::TIMELIMIT_POS,	//�ʒu
			nsGameScene::TIMELIMIT_COL,	//�F
			nsGameScene::FONT_ROT,		//�X��
			nsGameScene::FONT_SCA,		//�g�嗦
			nsGameScene::FONT_PIV		//��_
		);
		//�����̋��E���\��
		m_timeLimit->SetShadowParam(true, 3.0f, Vector4::Black);
	}
}