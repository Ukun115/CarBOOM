/// <summary>
/// �^�C�g����ʃN���X
/// (���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I)
/// </summary>


#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "Fade.h"


namespace nsTitleScene
{
	const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//�v���C���[1�̖��O�\���ʒu
	const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//�v���C���[2�̖��O�\���ʒu
	const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//�v���C���[3�̖��O�\���ʒu
	const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//�v���C���[4�̖��O�\���ʒu

	const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//�_�ŕ����̕\���ʒu
	const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//�_�ŕ����̑傫��

	const Vector3 PressASpeechBalloonPos2 = { 300.0f,280.0f,0 };
	const Vector3 PressASpeechBalloonPos3 = { -270.0f,-315,0 };
	const Vector3 PressASpeechBalloonPos4 = { 300.0f,-315.0f,0 };

	const Vector4 PLANAME1COL = { 1.0f,0.0f,0.0f,1.0f };		//�v���C���[1�̕\���͏�ɂ���̂ŐԂČŒ�
	const Vector4 PLANAME234COL = { 0.7f,0.7f,0.7f,1.0f };	//�v���C���[2����̓A�N�e�B�u����O�͊D�F

	const float PLA1234_SCA = { 1.0f, };					//�g�嗦

	const Vector4 PLANAME2COL = { 0.0f,0.0f,1.0f,1.0f };			//�A�N�e�B�u���A��
	const Vector4 PLANAME3COL = { 1.0f,1.0f,0.0f,1.0f };			//�A�N�e�B�u���A���F
	const Vector4 PLANAME4COL = { 0.0f,1.0f,0.0f,1.0f };			//�A�N�e�B�u���A��


	const float     FONT_ROT = 0.0f;			//�t�H���g�̌X��
	const Vector2   FONT_PIV = { 1.0f,1.0f };	//�t�H���g�̊�_
	const float     FONT_SCA = 1.4f;			//�t�H���g�̊g�嗦
}


bool TitleScene::Start()
{
	//�t�F�[�h�C��
	m_fade[FadeIn] = NewGO<Fade>(0, nullptr);
	m_fade[FadeIn]->SetState(StateIn);
	m_fade[FadeIn]->SetAlphaValue(1.0f);

	m_soundPlayBack = FindGO<SoundPlayBack>(nsStdafx::SOUNDPLAYBACK_NAME);

	//�^�C�g�����W���O���T�E���h
	m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneGingle);

	//�^�C�g��BGM�T�E���h
	m_soundPlayBack->TitleSceneSoundPlayBack(TitleSceneBGM);

	//�^�C�g����ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
	InitTitleSceneImage();

	//PUSH START BUTTON�I�u�W�F�N�g����
	m_pushStartButtonSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("PRESSSTARTBUTTON", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ nsTitleScene::FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ nsTitleScene::FlashingFont_SCA });

	//PRESS A !! �����o���摜�I�u�W�F�N�g����
	m_pressASpeechBalloon = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
	m_pressASpeechBalloonArrow = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
	m_pressASpeechBalloon->Init("PRESS A !!", 400.0f, 200.0f);
	m_pressASpeechBalloonArrow->Init("PRESS A !!Arrow", 200.0f, 100.0f);
	//�����ʒu�ݒ�
	//2P�̍���
	m_pressASpeechBalloonPos = nsTitleScene::PressASpeechBalloonPos2;
	m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
	m_pressASpeechBalloonPos.x += 75.0f;
	m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
	//�傫������
	m_pressASpeechBalloon->SetScale({0.5f,0.5f,0.5f});

	//PLAYER�t�H���g�̏��������܂Ƃ߂Ă���֐�
	InitPlayerFont();

	return true;
}


TitleScene::~TitleScene()
{
	//�^�C�g�����S���폜�B
	DeleteGO(m_titleSprite);
	DeleteGO(m_titleNameSprite);
	for (int i = 0; i < 9; i++)
	{
		DeleteGO(m_titleBaraBaraSprite[i]);
	}
	//PUSHSTARTBUTTON���폜�B
	DeleteGO(m_pushStartButtonSprite);
	//�����o�����폜�B
	DeleteGO(m_pressASpeechBalloon);
	DeleteGO(m_pressASpeechBalloonArrow);

	for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
		DeleteGO(m_PlaNameFont[plaNum]);
	}

	for (int i = 0; i < 2; i++)
	{
		DeleteGO(m_fade[i]);
	}
}


void TitleScene::Update()
{
	//�uPRESS START BUTTON�v�����摜�̓_�ŏ���
	FlashingFont();
	//�����o���̖��摜�����ړ�����֐�
	SideMove(60, 0.2f);

	//�^�C�g�����̓���
	if (m_titleNameSca.x != 1.0f)
	{
		//�^�C�g�������g�傷��֐�
		TitleNameScaUp();
	}
	else
	{
		//�^�C�g�������E�F�[�u������֐�
		TitleNameWave();
	}

	//�v���C���[��o�^����
	AddPlayer();

	if (m_fade[FadeOut] == nullptr)
	{
		//�o�^����Ă���N���̃X�^�[�g�{�^���������ꂽ��A
		for (unsigned int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
			PushStartButton(plaNum);
			//�{�^���������ꂽ�Ƃ��̏����֐�
			PushSelectButton(plaNum);
		}
	}
	else
	{
		//�I�����ꂽ���̃V�[���ɍs�������֐�
		NextScene();
	}
}


//�v���C���[��ǉ�����֐�
void TitleScene::AddPlayer()
{
	//�o�^���ꂽ�v���C���[�����ő吔4�l�ɂȂ�܂Œǉ��ł���
	if (m_totalPlaNum == TotalPlaNum)
	{
		return;
	}
	/*�o�^����Ă��Ȃ��R���g���[���[��A�{�^���������ꂽ��A
	�y���ӁzUSB�|�[�g�Ɍq���ꂽ������Ȃ��Ɠo�^����Ă����܂���B*/
	if (!g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
	{
		return;
	}
	//�G���W���T�E���h
	m_soundPlayBack->TitleSceneSoundPlayBack(EngineSound);

	//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	switch (m_totalPlaNum)
	{
	case Player2:
		m_PlaNameFont[1]->SetColor(nsTitleScene::PLANAME2COL);
		//3P�̉E��
		m_pressASpeechBalloonPos = nsTitleScene::PressASpeechBalloonPos3;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x -= 105.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
		//���]������
		m_arrowSca = { -1.0f,-1.0f,-1.0f };
		m_pressASpeechBalloonArrow->SetScale(m_arrowSca);
		break;

	case Player3:
		m_PlaNameFont[2]->SetColor(nsTitleScene::PLANAME3COL);
		//4P�̍���
		m_pressASpeechBalloonPos = nsTitleScene::PressASpeechBalloonPos4;
		m_pressASpeechBalloon->SetPosition(m_pressASpeechBalloonPos);
		m_pressASpeechBalloonPos.x += 80.0f;
		m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
		//���ɖ߂�
		m_pressASpeechBalloonArrow->SetScale(Vector3::One);
		break;

	case Player4:
		m_PlaNameFont[3]->SetColor(nsTitleScene::PLANAME4COL);
		//��\��
		m_pressASpeechBalloon->Deactivate();
		m_pressASpeechBalloonArrow->Deactivate();
		break;
	}
	//���̃v���C���[��
	m_totalPlaNum++;
}


//�X�e�[�W�I����ʂɑJ�ڂ���֐�
void TitleScene::StageSelectSceneTransition()
{
	//�X�e�[�W�I����ʂɑJ��
	m_stageSelectScene = NewGO<StageSelectScene>(nsStdafx::PRIORITY_0, nullptr);
	//�o�^���ꂽ�l���f�[�^�����̃N���X�ɓn��
	m_stageSelectScene->SetTotalPlaNum(m_totalPlaNum);
	//���̃N���X�̍폜
	DeleteGO(this);
	//�^�C�g���V�[���Ŏg����T�E���h��j��
	m_soundPlayBack->TitleSceneDeleteGO();
}


//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
void TitleScene::FlashingFont()
{
	if (m_isFlashingFontActiveFlg)
	{
		//�^�C�}�[���Z
		m_flashingFontTimer++;
		//�uPRESS START BUTTON�v�\��
		m_pushStartButtonSprite->Activate();
	}
	else
	{
		//�^�C�}�[���Z
		m_flashingFontTimer--;
		//�uPRESS START BUTTON�v��\��
		m_pushStartButtonSprite->Deactivate();
	}
	//�^�C�}�[��60���傫���l�ɂȂ�ƁA
	if (m_flashingFontTimer > 60)
	{
		//�uPRESS START BUTTON�v���\���ɂ���t���O
		m_isFlashingFontActiveFlg = false;
	}
	//�^�C�}�[��0��菬�����l�ɂȂ�ƁA
	if (m_flashingFontTimer < 10)
	{
		//�uPRESS START BUTTON�v��\������t���O
		m_isFlashingFontActiveFlg = true;
	}
}


//�摜�����ړ�����֐�
void TitleScene::SideMove(const int width, const float speed)
{
	if (m_sideMoveTimer < width)
	{
		m_pressASpeechBalloonPos.x += speed;
	}
	else if(m_sideMoveTimer < width*2)
	{
		m_pressASpeechBalloonPos.x -= speed;
	}
	else
	{
		//������
		m_sideMoveTimer = 0;
	}

	m_sideMoveTimer++;

	m_pressASpeechBalloonArrow->SetPosition(m_pressASpeechBalloonPos);
}


//�摜���c�ړ�����֐�
void TitleScene::VerticalMove(const int width, const float speed, const int spriteNum)
{
	if (m_verticalMoveTimer[spriteNum] < width)
	{
		m_titleBaraBaraSpritePos[spriteNum].y += speed;
	}
	else if (m_verticalMoveTimer[spriteNum] < (width * 2))
	{
		m_titleBaraBaraSpritePos[spriteNum].y -= speed;
	}
	else if(m_verticalMoveTimer[spriteNum] > (width * 2))
	{
		//������
		m_verticalMoveTimer[spriteNum] = 100;
		m_titleBaraBaraSprite[spriteNum]->SetPosition(Vector3::Zero);
	}

	m_verticalMoveTimer[spriteNum]++;

	m_titleBaraBaraSprite[spriteNum]->SetPosition(m_titleBaraBaraSpritePos[spriteNum]);
}


//�^�C�g�������g�傷��֐�
void TitleScene::TitleNameScaUp()
{
	if (m_titleNameSca.x >= 1.0f)
	{
		return;
	}
	m_scaUpValue += 0.001f;
	if (m_titleNameSca.x > 0.5f)
	{
		m_scaUpValue += 0.005f;
	}
	m_titleNameSca.x += m_scaUpValue;

	//1.0f�ŏI���悤�ɕ␳
	m_titleNameSca.x = min(m_titleNameSca.x, 1.0f);

	m_titleNameSprite->SetScale(m_titleNameSca);

	if (m_titleNameSca.x != 1.0f)
	{
		return;
	}
	//�^�C�g���g��p�̃^�C�g�����摜���폜�B
	DeleteGO(m_titleNameSprite);
}


//�^�C�g�������E�F�[�u������֐�
void TitleScene::TitleNameWave()
{
	for (int i = 0; i < 9; i++)
	{
		//�\��
		m_titleBaraBaraSprite[i]->Activate();
	}

	if (m_waveTimer < 30)
	{
		VerticalMove(10, 4.0f, 0);
	}
	if (5 < m_waveTimer && m_waveTimer < 35)
	{
		VerticalMove(10, 4.0f, 1);
	}
	if (15 < m_waveTimer && m_waveTimer < 45)
	{
		VerticalMove(10, 4.0f, 2);
	}
	if (25 < m_waveTimer && m_waveTimer < 55)
	{
		VerticalMove(10, 4.0f, 3);
	}
	if (35 < m_waveTimer && m_waveTimer < 65)
	{
		VerticalMove(10, 4.0f, 4);
	}
	if (45 < m_waveTimer && m_waveTimer < 75)
	{
		VerticalMove(10, 4.0f, 5);
	}
	if (55 < m_waveTimer && m_waveTimer < 85)
	{
		VerticalMove(10, 4.0f, 6);
	}
	if (65 < m_waveTimer && m_waveTimer < 95)
	{
		VerticalMove(10, 4.0f, 7);
	}
	if (75 < m_waveTimer && m_waveTimer < 105)
	{
		VerticalMove(10, 4.0f, 8);
	}

	//�^�C�}�[��������
	if (m_waveTimer > 170)
	{
		for (int spriteNum = 0; spriteNum < 9; spriteNum++)
		{
			//������
			m_verticalMoveTimer[spriteNum] = 0;
		}
		m_waveTimer = 0;
	}

	m_waveTimer++;
}


//�X�^�[�g�{�^���������ꂽ�Ƃ��̏����֐�
void TitleScene::PushStartButton(int plaNum)
{
	//�X�^�[�g�{�^���������ꂽ��A
	if (!g_pad[plaNum]->IsTrigger(enButtonStart))
	{
		return;
	}
	//����T�E���h
	m_soundPlayBack->TitleSceneSoundPlayBack(DecideSound);

	//�t�F�[�h�A�E�g
	m_fade[FadeOut] = NewGO<Fade>(0, nullptr);
	m_fade[FadeOut]->SetState(StateOut);
	m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

	m_nextScene = StateSelectScene;
}

//�{�^���������ꂽ�Ƃ��̏����֐�
void TitleScene::PushSelectButton(int plaNum)
{
	//�Z���N�g�{�^���������ꂽ��A�A
	if (!g_pad[plaNum]->IsTrigger(enButtonSelect))
	{
		return;
	}
	//�t�F�[�h�A�E�g
	m_fade[FadeOut] = NewGO<Fade>(0, nullptr);
	m_fade[FadeOut]->SetState(StateOut);
	m_fade[FadeOut]->SetAlphaValue(nsStdafx::FLOAT_ZERO);

	m_nextScene = GameEnd;
}

//�I�����ꂽ���̃V�[���ɍs�������֐�
void TitleScene::NextScene()
{
	//�^�����ɂȂ�����J��
	if (m_fade[FadeOut]->GetNowState() != StateWait)
	{
		return;
	}
	switch (m_nextScene)
	{
	case StateSelectScene:
		//�X�e�[�W�I����ʂɑJ��
		StageSelectSceneTransition();
		break;
	case GameEnd:
		//exe����ăQ�[���I��
		exit(EXIT_SUCCESS);
		//����//
		//exit(EXIT_FAILURE);�ُ͈�I��		EXIT_FAILURE = 1
		//exit(EXIT_SUCCESS);�͐���I��		EXIT_SUCCESS = 0
		break;
	}
}


//PLAYER�t�H���g�̏��������܂Ƃ߂Ă���֐�
void TitleScene::InitPlayerFont()
{
	//�PP�̒ǉ��t���O��^�ɁB
	m_isAddPlayerFlg[Player1] = true;

	for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
		//2P�`4P�̔�A�N�e�B�u�摜�I�u�W�F�N�g����
		m_PlaNameFont[plaNum] = NewGO<FontRender>(nsStdafx::PRIORITY_0,nullptr);		//1P
		switch (plaNum)
		{
		case Player1:
			m_PlaNameFont[Player1]->Init(
				L"PLAYER1",			//�e�L�X�g
				nsTitleScene::PLANAME1POS,		//�ʒu
				nsTitleScene::PLANAME1COL,		//�F
				nsTitleScene::FONT_ROT,			//�X��
				nsTitleScene::PLA1234_SCA,		//�g�嗦
				nsTitleScene::FONT_PIV			//��_
			);
			break;
		case Player2:
			m_PlaNameFont[Player2]->Init(
				L"PLAYER2",			//�e�L�X�g
				nsTitleScene::PLANAME2POS,		//�ʒu
				nsTitleScene::PLANAME234COL,		//�F
				nsTitleScene::FONT_ROT,			//�X��
				nsTitleScene::PLA1234_SCA,		//�g�嗦
				nsTitleScene::FONT_PIV			//��_
			);
			break;
		case Player3:
			m_PlaNameFont[Player3]->Init(
				L"PLAYER3",			//�e�L�X�g
				nsTitleScene::PLANAME3POS,		//�ʒu
				nsTitleScene::PLANAME234COL,		//�F
				nsTitleScene::FONT_ROT,			//�X��
				nsTitleScene::PLA1234_SCA,		//�g�嗦
				nsTitleScene::FONT_PIV			//��_
			);
			break;
		case Player4:
			m_PlaNameFont[Player4]->Init(
				L"PLAYER4",			//�e�L�X�g
				nsTitleScene::PLANAME4POS,		//�ʒu
				nsTitleScene::PLANAME234COL,		//�F
				nsTitleScene::FONT_ROT,			//�X��
				nsTitleScene::PLA1234_SCA,		//�g�嗦
				nsTitleScene::FONT_PIV			//��_
			);
			break;
		}
		//�����̋��E���\��
		m_PlaNameFont[plaNum]->SetShadowParam(true, 3.0f, Vector4::Black);
	}
}


//�^�C�g����ʂ̉摜�̏��������܂Ƃ߂Ă���֐�
void TitleScene::InitTitleSceneImage()
{
	//�^�C�g�����S�I�u�W�F�N�g����
	m_titleSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
	m_titleSprite->Init("TitleRogo", 1600.0f, 800.0f);
	//�^�C�g�����I�u�W�F�N�g����
	m_titleNameSprite = NewGO<SpriteRender>(nsStdafx::PRIORITY_1, nullptr);
	m_titleNameSprite->Init("TitleName", 1600.0f, 800.0f);
	m_titleNameSca.x = nsStdafx::FLOAT_ZERO;
	m_titleNameSprite->SetScale(m_titleNameSca);
	for (int i = 0; i < 9; i++)
	{
		m_titleBaraBaraSprite[i] = NewGO<SpriteRender>(nsStdafx::PRIORITY_0, nullptr);
		sprintf(m_filePath, "TitleName_%d", i);
		m_titleBaraBaraSprite[i]->Init(m_filePath, 1600.0f, 800.0f);
		//���߂͔�\��
		m_titleBaraBaraSprite[i]->Deactivate();
	}
}