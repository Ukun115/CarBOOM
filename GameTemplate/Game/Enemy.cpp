///<<summary>
///�GNPC�i�p�g�J�[�j�N���X
///</summary>


#include "stdafx.h"
#include "Stage.h"

#include<random>

#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//�L�����R�����g�����߂ɃC���N���[�h
		//��2�K�w��Ƀf�B���N�g�����ړ����Ă���t�H���_������Ă���B


//TODO: �e�𗎂Ƃ���悤�ɂ���


namespace
{
	const int RES_POS_NUM = 10;	//���X�|�[���ʒu�̑���
	//�G�̊e���X�|�[���ʒu
	const Vector3 ENE_RES_POS_1 = { -150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,150.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,150.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 0.0f,150.0f,0.0f };

	const float POILIG_RANGE = 50.0f;	//�|�C���g���C�g�̉e���͈�

	const int TIME0 = 0;

	const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };

	//const float PI = 3.141592;	//�~����
}


bool Enemy::Start()
{
	//�C���X�^���X��T���B
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_gameScene  = FindGO<GameScene>(GAMESCENE_NAME);
	m_player	 = FindGO<Player>(PLAYER_NAME);
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);
	m_light = FindGO<Light>(LIGHT_NAME);
	m_stage = FindGO<Stage>("stage");

	//�G�̃��X�|�[���ʒu�P�`�P�O
	m_ranEneResPos[ResPos1] = ENE_RES_POS_1;
	m_ranEneResPos[ResPos2] = ENE_RES_POS_2;
	m_ranEneResPos[ResPos3] = ENE_RES_POS_3;
	m_ranEneResPos[ResPos4] = ENE_RES_POS_4;
	m_ranEneResPos[ResPos5] = ENE_RES_POS_5;
	m_ranEneResPos[ResPos6] = ENE_RES_POS_6;
	m_ranEneResPos[ResPos7] = ENE_RES_POS_7;
	m_ranEneResPos[ResPos8] = ENE_RES_POS_8;
	m_ranEneResPos[ResPos9] = ENE_RES_POS_9;
	if (m_stageSelectScene->GetStageNum() == STAGE2)
	{
		m_ranEneResPos[ResPos10] = ENE_RES_POS_10;
	}

	//���X�|�[�����W���v���C���[1P�`4P�̍��W�Ɠ����ɂȂ�Ȃ��悤�ɂ��Ȃ��Ƃ����Ȃ��B
	//�y�v���C���[�̃��X�|�[���ʒu�z
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	m_randEneResAngle[0] = 1.0f;
	m_randEneResAngle[1] = 2.5f;
	m_randEneResAngle[2] = 3.7f;
	m_randEneResAngle[3] = 5.5f;
	m_randEneResAngle[4] = 0.5f;
	m_randEneResAngle[5] = 1.25f;
	m_randEneResAngle[6] = 1.85f;
	m_randEneResAngle[7] = 2.85f;

	//�G�̍ő吔�J��Ԃ�
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		//�G���f���I�u�W�F�N�g����
		m_enemy[eneNum] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//���f���̃t�@�C���p�X��ݒ�
		m_enemy[eneNum]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//�G���f��

		//�f�o�b�N�p�̓G�X�s�[�h�̖��\��
		//m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

		//�������W(���X�|�[�����W)�̐ݒ�B
		if (eneNum == Enemy1)
		{
			m_enePos[Enemy1] = m_ranEneResPos[0];		//�G�P�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		else if (eneNum == Enemy2)
		{
			m_enePos[Enemy2] = m_ranEneResPos[1];		//�G�Q�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		else if (eneNum == Enemy3)
		{
			m_enePos[Enemy3] = m_ranEneResPos[3];		//�G3�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		else if (eneNum == Enemy4)
		{
			m_enePos[Enemy4] = m_ranEneResPos[4];		//�G4�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		else if (eneNum == Enemy5)
		{
			m_enePos[Enemy5] = m_ranEneResPos[7];		//�G5�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		else if (eneNum == Enemy6)
		{
			m_enePos[Enemy6] = m_ranEneResPos[8];		//�G6�̏ꏊ

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//���
		}
		//�����蔻��̃C�j�V�����C�Y(������)
		m_charaCon[eneNum].Init(15.0f, 85.0f, m_enePos[eneNum]);
		//300�`600�͈̔͂̃����_���l�ŃX�^�[�g���̓G��DA��x�点��^�C�}�[�̒l�ɑ��
		m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120�`140�͈̔͂̃����_���l��DA���CT�^�C�}�[�̒l�ɑ��
		m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
		//�S�ŏ������B�S�͓��Ƀ^�[�Q�b�g�����B
		m_pushPlayer[eneNum] = 4;

		//���������Ƃ��̌��ăG�t�F�N�g�̏������B
		m_shootDownEffect[eneNum].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
		//�傫������
		m_shootDownEffect[eneNum].SetScale(SHOOTDOWNEFFECT_SCALE);
		//�ʏ킾�Ɖ�ʂ̏オ�G�t�F�N�g�̏�ɂȂ��Ă���̂ŁA�Q�[�����̃J������������ɂȂ�悤�ɒ���
		Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
		//���y���Ӂz�֐����ɓ����̂̓f�O���[�P�ʂł͂Ȃ����W�A���P�ʂł��B
		m_shootDownEffectRot.AddRotationX(-1.5708);	//X������_�ɁA-1.5708rad(-90��)��]
		m_shootDownEffect[eneNum].SetRotation(m_shootDownEffectRot);

		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8]; //�G�̌���
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//��]���X�V
	}

	//Start�֐���return��
	return true;
}


Enemy::~Enemy()
{
	//�S�Ă̓G���폜�B
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		DeleteGO(m_enemy[eneNum]);
	}
}


void Enemy::Update()
{
	m_poiLigNum = 0;

	//�S�G�����[�v
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		//�����鎞�ɗ�������点�鏈��
		SoundPlayBack(FallSound,eneNum);

		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_gameScene->GetNowTime() == TIME0)
		{
			continue;
		}
		//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
		if (!m_gameScene->GetCountDownFlg())
		{
			//�d�͂̉e����^����
			Gravity(eneNum);

			//�x�N�g��������������f�o�b�N�֐�
			//EneMooveSpeedDebug(eneNum);

			//�X�^�[�g�����u�ԂɓG���_�b�V�����Ă��܂��̂�������鏈��
			if (m_startDelayTimer < m_startDelay[eneNum])
			{
				//�X�^�[�g����DA��x�点��^�C�}�[�����Z
				m_startDelayTimer++;
			}
			else
			{
				//��]����
				EneTurn(eneNum);

				//���X�e�[�W�̎����̉e�����󂯂鏈��
				WindPower(eneNum);

				//�v���C���[���G�ƂԂ������Ƃ��G�ɉ�����鏈��
				PlaAndEneClash(eneNum);

				//DA�U������
				EneDA(eneNum);

				//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
				m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);

				//�v���C���[�̍��W�����X�|�[�����W�Ɉړ�
				EneResporn(eneNum);

				//�ԃ|�C���g���C�g��ݒ�
				m_enePoiLigPos = m_enePos[eneNum];
				m_enePoiLigPos.x -= 10.0f;
				m_enePoiLigPos.y += 10.0f;
				m_light->SetPointLightData(m_enePoiLigPos, RED, POILIG_RANGE, m_poiLigNum);
				m_poiLigNum++;
				//�|�C���g���C�g��ݒ�
				m_enePoiLigPos = m_enePos[eneNum];
				m_enePoiLigPos.x += 10.0f;
				m_enePoiLigPos.y += 10.0f;
				m_light->SetPointLightData(m_enePoiLigPos, BLUE, POILIG_RANGE, m_poiLigNum);
				m_poiLigNum++;

				m_enePos[eneNum] += m_moveSpeed[eneNum];
			}
		}
		else
		{
			//�x�N�g��������������f�o�b�N�֐�
			//EneMooveSpeedDebug(eneNum);

			//�d�͂̉e����^����
			Gravity(eneNum);
			//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
			m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);
		}
		//�G�̈ʒu�Ɖ�]�����X�V
		EneDataUpdate(eneNum);
	}
}


//�G�̈ʒu,��]�����X�V����֐�
void Enemy::EneDataUpdate(int eneNum)
{
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//��]���X�V
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);	//�ʒu���X�V
}


//�G����Ŋ��̃v���C���[����������֐�
void Enemy::Distance(int eneNum)
{
	//�o�^����Ă���v���C���[�̕�����������
	for (int plaNum = 0; plaNum < m_titleScene->GetTotalPlaNum(); plaNum++)
	{
		//�v���C���[�̈ʒu���擾
		m_plaPos[plaNum] = m_player->GetPlaPos(plaNum);
		//�v���C���[�̈ʒu�ƓG�̈ʒu�̋������擾
		m_mostShortKyori[plaNum] = m_plaPos[plaNum] - m_enePos[eneNum];
	}

	//��ԋ߂�����(m_mostShortKyori[0])�̂悤�ɕ��ёւ�(�\�[�g)
	for (int plaNum = 0; plaNum < m_titleScene->GetTotalPlaNum() - 1; plaNum++) {
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_titleScene->GetTotalPlaNum(); nextPlaNum++) {
			if (m_mostShortKyori[nextPlaNum].Length() < m_mostShortKyori[plaNum].Length()) {
				//����
				Vector3 tmp = m_mostShortKyori[nextPlaNum];
				m_mostShortKyori[nextPlaNum] = m_mostShortKyori[plaNum];
				m_mostShortKyori[plaNum] = tmp;
			}
		}
	}

	//��ԋ߂��v���C���[����G�̃x�N�g���𐳋K�����ĕ��������̏��ɂ���
	m_mostShortKyori[0].Normalize();
}


//�G��DA�����֐�
void Enemy::EneDA(int eneNum)
{
	if (!m_canCtCountFlg[eneNum]) {
		//�����ݒ�
		Distance(eneNum);

		if (m_charaCon[eneNum].IsOnGround()) {
			//����������m_mostShortKyori[0]��5.0f���|���đ��x�ɂ���
			m_moveSpeed[eneNum] = m_mostShortKyori[0] * 5.0f;
		}
		//�_�b�V���T�E���h
		SoundPlayBack(DashSound,eneNum);

		m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

		//CT���J�E���g����t���O�𗧂Ă�
		m_canCtCountFlg[eneNum] = true;
	}
	//CT�t���O�������Ă�Ƃ��A
	if (m_canCtCountFlg[eneNum]) {

		//CT���J�E���g����
		m_CTTime[eneNum]++;

		//���C�������Ă���
		EneFriction(eneNum);
	}
	//CT�̃J�E���g��120�b�`140�b�̂Ƃ��A
	if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

		//CT�t���O�����낷
		m_canCtCountFlg[eneNum] = false;

		//CT�̃J�E���g��0�ɂ���
		m_CTTime[eneNum] = 0;
	}
}


//�G�̉�]�����֐�
void Enemy::EneTurn(int eneNum)
{
	//fabsf()�͕��������_�̐�Βl��Ԃ��֐�
	if (fabsf(m_moveSpeed[eneNum].x) < 0.001f && fabsf(m_moveSpeed[eneNum].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[eneNum] = atan2(m_moveSpeed[eneNum].x, m_moveSpeed[eneNum].z);

	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);

	m_eneDir[eneNum] = m_moveSpeed[eneNum];
	m_eneDir[eneNum].Normalize();
}


//�G�̃��X�|�[�������֐�
void Enemy::EneResporn(int eneNum)
{
	if (m_enePos[eneNum].y < -1000.0f)
	{
		//���ăT�E���h
		SoundPlayBack(ShootDownSound,eneNum);

		//���ăG�t�F�N�g�Đ��J�n�B
		m_shootDownEffect[eneNum].Play();
		//���ăG�t�F�N�g�̈ʒu��G���������ʒu�ɐݒ�
		m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
		//�X�V
		m_shootDownEffect[eneNum].Update();

		//�����_���Ń��X�|�[���ʒu������
		m_enePos[eneNum] = m_ranEneResPos[rand() % RES_POS_NUM];
		if (m_stageSelectScene->GetStageNum() == STAGE2)
		{
			//�����_���֐���SEED�i��j��ݒ�
			//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
			srand((int)time(nullptr));
			//�����_���Ń��X�|�[���ʒu������
			m_enePos[eneNum] = m_ranEneResPos[rand() % 9];
		}
		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));
		//�����_���Ń��X�|�[����]������
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8];

		//�ʒu���Z�b�g
		m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);

		//��]�����Z�b�g����
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);

		//�L�����R���̍��W�Ƀv���C���[�̍��W�������
		m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

		//�X�s�[�h��0�ɂ���
		m_moveSpeed[eneNum] = { Vector3::Zero };

		//�L�����N�^�[�R���g���[���[���g�����ړ������ɕύX�B
		m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);

		//�������Ō�ɐG�ꂽ�G�Ƀ|�C���g��^����m_pushPlayer = �Ō�ɉ����Ă����v���C���[�̃i���o�[
		//y=5�ɂ��āA5�̎��͗��Ƃ��Ă����v���C���[�̃X�R�A��+10pt����悤�ɂ���B
		m_gameScene->GetPlayerAddScore(m_pushPlayer[eneNum], 5);
	}
}


//�G�̖��C�����֐�
void Enemy::EneFriction(int eneNum)
{
	//���C�͂�ݒ肷��
	m_friction[eneNum] = m_moveSpeed[eneNum];
	m_friction[eneNum] *= -1.5f;

	///����if���̓X�e�[�W�̏����Ȃ̂ŃX�e�[�W�N���X�Ɉڂ������B
	//�A�C�X�X�e�[�W���I������Ă���Ƃ��A
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//���C�����炷
		m_friction[eneNum] /= 2.0f;
	}
	//���C�͂����Z����
	m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
}


//�v���C���[�ƓG���Ԃ������Ƃ��̏����֐�
void Enemy::PlaAndEneClash(int eneNum)
{
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//�v���C���[�ƓG�Ƃ̋������v�Z
		m_diff = m_player->GetPlaPos(plaNum) - m_enePos[eneNum];

		//�����̒�����40.0f��菬����������A
		if (m_diff.Length() < 40.0f)
		{
			if (m_canPlaAndEneClashSoundPlayFlg[eneNum])
			{
				//�Փˉ�4
				SoundPlayBack(PlaAndEneClashSound, eneNum);

				m_canPlaAndEneClashSoundPlayFlg[eneNum] = false;
			}

			if (m_player->GetPlaisTyazi1HanteiFlg(plaNum)) {
				m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
				m_samDir[eneNum].Normalize();
				m_moveSpeed[eneNum] = m_samDir[eneNum] * 20.0f;
			}
			if (m_player->GetPlaisTyazi2HanteiFlg(plaNum)) {

				m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
				m_samDir[eneNum].Normalize();
				m_moveSpeed[eneNum] = m_samDir[eneNum] * 30.0f;

			}
			//�Ō�ɉ����Ă����v���C���[���L�^
			m_pushPlayer[eneNum] = plaNum;
		}
	}
}


//�G�ɂ�����d�͂�ݒ肷��֐�
void Enemy::Gravity(int eneNum)
{
	//�d�͂̉e����^����
	m_moveSpeed[eneNum].y -= GRAVITY;
}


//�x�N�g��������������f�o�b�N�֐�
void Enemy::EneMooveSpeedDebug(int eneNum)
{
	Vector3 Dir = m_moveSpeed[eneNum];
	Dir.y = 0;
	Dir.Normalize();//�傫�����ʒu�ɂ���
	float x = Dir.Dot(Vector3::AxisX);//X�����牽�x����Ă��邩������
	Dir.z *= -1;
	float angleX = acosf(x);//�A�[�N�R�T�C��
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[eneNum].SetRotationY(angleX);//���x����Y������
	m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//�p�x��ݒ肷��
	m_arrowPos[eneNum] = m_enePos[eneNum];
	m_arrowPos[eneNum].y += 50.0f;
	m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[eneNum].Length() / 10;
	m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize);
}

//�T�E���h���ꊇ�ɂ܂Ƃ߂�֐�
void Enemy::SoundPlayBack(int soundNum,int eneNum)
{
	switch (soundNum)
	{
	case ShootDownSound:
		//���ăT�E���h�̏�����
		m_shootDownSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_shootDownSound[eneNum]->Init(L"Assets/sound/ShootDown.wav");
		m_shootDownSound[eneNum]->SetVolume(0.2f);
		m_shootDownSound[eneNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case FallSound:
		//������-10�ȉ��̂Ƃ��Đ�
		if (m_enePos[eneNum].y < -10.0f && m_canFallSoundPlayFlg[eneNum])
		{
			//�����T�E���h�̏�����
			m_FallSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_FallSound[eneNum]->Init(L"Assets/sound/Fall.wav");
			m_FallSound[eneNum]->SetVolume(0.1f);
			m_FallSound[eneNum]->Play(false);	//�U�Ń����V���b�g�Đ�

			m_canFallSoundPlayFlg[eneNum] = false;
		}
		//���X�|�[���ʒu�Ɉړ������Ƃ��Ƀt���O�𕜊�������
		if (m_enePos[eneNum].y == 150.0f)
		{
			m_canFallSoundPlayFlg[eneNum] = true;
		}

		break;

	case DashSound:
		//�����T�E���h�̏�����
		m_DashSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		//�����_���֐���SEED�i��j��ݒ�
		//�i����ɂ�胉���_���l��{���̈Ӗ��Ń����_���ɂ��Ă���j
		srand((int)time(nullptr));
		m_randomDashSoundNum = rand() % 9;
		switch (m_randomDashSoundNum)
		{
		case 0:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash1.wav");
			break;
		case 1:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash2.wav");
			break;
		case 2:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash3.wav");
			break;
		case 3:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash4.wav");
			break;
		case 4:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash5.wav");
			break;
		case 5:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash6.wav");
			break;
		case 6:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash7.wav");
			break;
		case 7:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash8.wav");
			break;
		case 8:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash9.wav");
			break;
		}
		m_DashSound[eneNum]->SetVolume(0.3f);
		m_DashSound[eneNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;

	case PlaAndEneClashSound:
		//�v���C���[�ƃv���C���[���Ԃ������Ƃ��̃T�E���h�̏�����
		m_PlaAndEneClashSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_PlaAndEneClashSound[eneNum]->Init(L"Assets/sound/Clash2.wav");
		m_PlaAndEneClashSound[eneNum]->SetVolume(0.5f);
		m_PlaAndEneClashSound[eneNum]->Play(false);	//�U�Ń����V���b�g�Đ�

		break;
	}
}


void Enemy::WindPower(int enenum)
{
	//���X�e�[�W���I������Ă���ꍇ�A���̉e����^����
	if (m_stageSelectScene->GetStageNum() == STAGE4)
	{


		//���݂̕��̌����ɉ���������
		switch (m_stage->GetWindDirection()) { //������()�̒��ɂ́A���ǂ̌����̕��Ȃ̂���ۑ����Ă���ϐ�������B
		case Up://�������ւ̕�
			m_moveSpeed[enenum].z += 0.02f;
			break;
		case Down:
			m_moveSpeed[enenum].z -= 0.02f;
			break;
		case Left:
			m_moveSpeed[enenum].x -= 0.02f;
			break;
		case Right:
			m_moveSpeed[enenum].x += 0.02f;
			break;
		}

	}
}