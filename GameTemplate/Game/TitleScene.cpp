#include "stdafx.h"
#include "TitleScene.h"
#include "StageSelectScene.h"


/// <summary>
/// ���ӁI�Q�[���p�b�h�̓o�^���鏇�Ԃ́A�Q�[���p�b�h��PC�ɐڑ����ꂽ���ԁI�I
/// </summary>


namespace
{
	const Vector3 PLAYER1_NAME_POS = {-480.0f, 310.0f,0.0f};			//�v���C���[1�̖��O�\���ʒu
	const Vector3 PLAYER2_NAME_POS = { 480.0f, 310.0f,0.0f};			//�v���C���[2�̖��O�\���ʒu
	const Vector3 PLAYER3_NAME_POS = {-480.0f,-310.0f,0.0f};			//�v���C���[3�̖��O�\���ʒu
	const Vector3 PLAYER4_NAME_POS = { 480.0f,-310.0f,0.0f};			//�v���C���[4�̖��O�\���ʒu

	const Vector3 FlashingFont_POS = { 0.0f, -200.0f,0.0f };				//�_�ŕ����̕\���ʒu
	const Vector3 FlashingFont_SCA = { 1.2f, 1.2f,1.2f };					//�_�ŕ����̑傫��
}


bool TitleScene::Start()
{
	//�^�C�g�����W���O���T�E���h
	SoundPlayBack(TitleSceneGingle);

	//�^�C�g��BGM�T�E���h
	SoundPlayBack(TitleSceneBGM);

	//�^�C�g�����S�I�u�W�F�N�g����
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0,nullptr);
	m_titleSprite->Init("Assets/image/DDS/TitleRogo.dds", 1600.0f, 800.0f);

	//PUSH START BUTTON�I�u�W�F�N�g����
	m_pushStartButtonSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	m_pushStartButtonSprite->Init("Assets/image/DDS/PRESSSTARTBUTTON.dds", 400.0f, 200.0f);
	m_pushStartButtonSprite->SetPosition({ FlashingFont_POS });
	m_pushStartButtonSprite->SetScale({ FlashingFont_SCA });

	//PRESS A !! �����o���摜�I�u�W�F�N�g����
	for (int speechBalloonNum = 0; speechBalloonNum < 3; speechBalloonNum++)
	{
		m_pressASpeechBalloon[speechBalloonNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
		//PLAYER�R�̂ݐ����o���̍����ɂ���̂ő��Ƃ͈Ⴄ�����o�����g��
		if (speechBalloonNum == 1)
		{
			m_pressASpeechBalloon[speechBalloonNum]->Init("Assets/image/DDS/PRESS A !!_L.dds", 400.0f, 200.0f);
		}
		else
		{
			m_pressASpeechBalloon[speechBalloonNum]->Init("Assets/image/DDS/PRESS A !!_R.dds", 400.0f, 200.0f);
		}
		//PLAYER2�ȊO�͏����͔�A�N�e�B�u
		if (speechBalloonNum != 0)
		{
			m_pressASpeechBalloon[speechBalloonNum]->Deactivate();
		}
		//�ʒu�ݒ�
		switch (speechBalloonNum)
		{
		//2P�̍���
		case 0:
			//2P�̖��O�摜�̈ʒu����
			m_pressASpeechBalloonPos = PLAYER2_NAME_POS;
			//���ɂ��炷
			m_pressASpeechBalloonPos.x -= 250.0f;
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			break;
		//3P�̉E��
		case 1:
			//3P�̖��O�摜�̈ʒu����
			m_pressASpeechBalloonPos = PLAYER3_NAME_POS;
			//�E�ɂ��炷
			m_pressASpeechBalloonPos.x += 250.0f;
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			break;
		//4P�̍���
		case 2:
			//4P�̖��O�摜�̈ʒu����
			m_pressASpeechBalloonPos = PLAYER4_NAME_POS;
			//���ɂ��炷
			m_pressASpeechBalloonPos.x -= 250.0f;
			m_pressASpeechBalloon[speechBalloonNum]->SetPosition(m_pressASpeechBalloonPos);
			break;
		}
		//�傫������
		m_pressASpeechBalloon[speechBalloonNum]->SetScale({0.5f,0.5f,0.5f});
	}

	//1P�͔�A�N�e�B�u�Ƃ����Ȃ����߁A���߂���A�N�e�B�u�摜�I�u�W�F�N�g����
	m_plaActiveName[Player1] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
	m_plaActiveName[Player1]->Init("Assets/image/DDS/Player1_ActiveName.dds", 300.0f, 150.0f);
	m_plaActiveName[Player1]->SetPosition(PLAYER1_NAME_POS);

	//�PP�̒ǉ��t���O��^�ɁB
	m_isAddPlayerFlg[Player1] = true;

	for (int plaNum = Player1; plaNum < MaxPlayerNum; plaNum++) {
		//2P�`4P�̔�A�N�e�B�u�摜�I�u�W�F�N�g����
		m_plaDeactiveName[plaNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		//1P
		if (plaNum == Player1)
		{
			m_plaDeactiveName[plaNum]->Init("Assets/image/DDS/Player1_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER1_NAME_POS);
			//��A�N�e�B�u���͂Ȃ����߁A��\���ɂ��Ă����B
			m_plaDeactiveName[plaNum]->Deactivate();
		}
		//2P
		if (plaNum == Player2)
		{
			m_plaDeactiveName[plaNum]->Init("Assets/image/DDS/Player2_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER2_NAME_POS);
		}
		//3P
		if (plaNum == Player3)
		{
			m_plaDeactiveName[plaNum]->Init("Assets/image/DDS/Player3_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER3_NAME_POS);
		}
		//4P
		if (plaNum == Player4)
		{
			m_plaDeactiveName[plaNum]->Init("Assets/image/DDS/Player4_DeactiveName.dds", 300.0f, 150.0f);
			m_plaDeactiveName[plaNum]->SetPosition(PLAYER4_NAME_POS);
		}
	}

	//Start�֐���return��
	return true;
}


TitleScene::~TitleScene()
{
	//�o�^���ꂽ�v���C���[�̃A�N�e�B�u�摜���폜
	for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
	{
		DeleteGO(m_plaActiveName[plaNum]);
	}
	//�o�^����Ă��Ȃ��v���C���[�̔�A�N�e�B�u�摜���폜
	for (int plaNum = m_totalPlaNum; plaNum < (MaxPlayerNum+1); plaNum++)
	{
		//4P�܂œo�^����Ă�����m_plaDeactiveName[4]�ƁA
		//�Y�������I�[�o�[���Ă��܂��̂ł�����for���𔲂�������
		if (m_totalPlaNum == MaxPlayerNum)
		{
			break;
		}
		//�΂̔g���͑��v�ł�
		//DeleteGO(m_plaDeactiveName[i]);
	}
}


void TitleScene::Update()
{
	//�X�e�[�W�I����ʂɑJ�ڂ���Ɣ�����t���O
	if (m_isCanStageSelectSceneFlg == true) {

		m_titleCallDelayTimer++;
		if (m_titleCallDelayTimer == 150 && m_isTitleCallOneShotFlg)
		{
			//�^�C�g���R�[���T�E���h
			SoundPlayBack(TitleCallSound);

			m_isTitleCallOneShotFlg = false;
		}

		//�o�^���ꂽ�v���C���[�����ő吔4�l�ɂȂ�܂Œǉ��ł���
		if (m_totalPlaNum != MaxPlayerNum)
		{
			/*�o�^����Ă��Ȃ��R���g���[���[��A�{�^���������ꂽ��A
			�y���ӁzUSB�|�[�g�Ɍq���ꂽ������Ȃ��Ɠo�^����Ă����܂���B*/
			if (g_pad[m_totalPlaNum]->IsTrigger(enButtonA))
			{
				//�v���C���[��o�^����
				AddPlayer();
			}
		}

		//�o�^����Ă���N���̃X�^�[�g�{�^���������ꂽ��A
		for (int plaNum = Player1; plaNum < m_totalPlaNum; plaNum++)
		{
			if (g_pad[plaNum]->IsTrigger(enButtonStart))
			{
				//����T�E���h
				SoundPlayBack(DecideSound);

				//�X�e�[�W�I����ʂɑJ��
				StageSelectSceneTransition();
			}
		}
		//�uPRESS START BUTTON�v�����摜�̓_�ŏ���
		FlashingFont();
	}
}


//�v���C���[��ǉ�����֐�
void TitleScene::AddPlayer()
{
	//�G���W���T�E���h
	SoundPlayBack(EngineSound);

	//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
	m_isAddPlayerFlg[m_totalPlaNum] = true;

	//�v���C���[�̃A�N�e�B�u�摜�I�u�W�F�N�g�����i��ԏ�̃��C���[�ɒu�������̂Ńv���C�I���e�B�[�͍ō��l�j
	m_plaActiveName[m_totalPlaNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	//2P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == Player2)
	{
		m_plaActiveName[Player2]->Init("Assets/image/DDS/Player2_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[Player2]->SetPosition(PLAYER2_NAME_POS);

		//2P�̐����o�����\��
		m_pressASpeechBalloon[0]->Deactivate();
		//�����o����3P�̈ʒu�ɕ\��
		m_pressASpeechBalloon[1]->Activate();
	}
	//3P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == Player3)
	{
		m_plaActiveName[Player3]->Init("Assets/image/DDS/Player3_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[Player3]->SetPosition(PLAYER3_NAME_POS);

		//3P�̐����o�����\��
		m_pressASpeechBalloon[1]->Deactivate();
		//�����o����4P�̈ʒu�ɕ\��
		m_pressASpeechBalloon[2]->Activate();
	}
	//4P�̃A�N�e�B�u��+�A�N�e�B�u�摜�\��
	if (m_totalPlaNum == Player4)
	{
		m_plaActiveName[Player4]->Init("Assets/image/DDS/Player4_ActiveName.dds", 300.0f, 150.0f);
		//�摜�̈ʒu�w��
		m_plaActiveName[Player4]->SetPosition(PLAYER4_NAME_POS);

		//4P�̐����o�����\��
		m_pressASpeechBalloon[2]->Deactivate();
	}
	//��A�N�e�B�u�摜���폜�B
	DeleteGO(m_plaDeactiveName[m_totalPlaNum]);
	//���̃v���C���[��...
	m_totalPlaNum++;
}


//�X�e�[�W�I����ʂɑJ�ڂ���֐�
void TitleScene::StageSelectSceneTransition()
{
	//�X�e�[�W�I����ʂɑJ��
	m_stageSelectScene = NewGO<StageSelectScene>(PRIORITY_0, STAGESELECT_NAME);
	////���̃N���X�̍폜
	////DeleteGO(this);

	//�^�C�g�����S���폜�B
	DeleteGO(m_titleSprite);
	//PUSHSTARTBUTTON���폜�B
	DeleteGO(m_pushStartButtonSprite);
	//�����o�����폜�B
	for (int speechBalloonNum = 0; speechBalloonNum < 3; speechBalloonNum++)
	{
		DeleteGO(m_pressASpeechBalloon[speechBalloonNum]);
	}
	//�^�C�g��BGM���폜
	DeleteGO(m_titleBGM);
	//�G���W�������폜
	DeleteGO(m_addPlayer);
	//�^�C�g���R�[�����폜
	DeleteGO(m_titleCall);
	//�^�C�g���W���O�����폜
	DeleteGO(m_gameNameGingle);

	//�X�e�[�W�I����ʂɑJ�ڌ�A�{�^���ƃv���C���[�ǉ��{�^���������Ȃ�����t���O
	m_isCanStageSelectSceneFlg = false;
}


//�uPRESS START BUTTON�v�����摜�̓_�ŏ����֐�
void TitleScene::FlashingFont()
{
	if (m_isFlashingFontTimerActiveFlg)
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
		m_isFlashingFontTimerActiveFlg = false;
	}
	//�^�C�}�[��0��菬�����l�ɂȂ�ƁA
	if (m_flashingFontTimer < 10)
	{
		//�uPRESS START BUTTON�v��\������t���O
		m_isFlashingFontTimerActiveFlg = true;
	}
}


//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void TitleScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case TitleSceneGingle:
		//�^�C�g�����W���O���T�E���h�̏�����
		m_gameNameGingle = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_gameNameGingle->Init(L"Assets/sound/TitleSceneGingle.wav");
		m_gameNameGingle->SetVolume(0.5f);
		m_gameNameGingle->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case TitleSceneBGM:
		//�^�C�g��BGM�T�E���h�̏�����
		m_titleBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_titleBGM->Init(L"Assets/sound/TitleSceneBGM.wav");
		m_titleBGM->SetVolume(0.01f);
		m_titleBGM->Play(true);	//�^�Ń��[�v�Đ�

		break;

	case TitleCallSound:
		//�^�C�g���R�[���T�E���h�̏�����
		m_titleCall = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_titleCall->Init(L"Assets/sound/TitleCall.wav");
		m_titleCall->SetVolume(0.5f);
		m_titleCall->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case DecideSound:
		//����T�E���h
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case EngineSound:

		//�G���W���T�E���h
		m_addPlayer = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_addPlayer->Init(L"Assets/sound/AddPlayer.wav");
		m_addPlayer->SetVolume(0.5f);
		m_addPlayer->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}