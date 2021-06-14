#include "stdafx.h"
#include "PhysicsPlayer.h"
#include "TitleScene.h"
#include "GameScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = { 1.4f,1.4f,1.4f };			//�v���C���[�̏����T�C�Y
	const int PLAYER1 = 0;			//1P
	const int PLAYER2 = 1;			//2P
	const int PLAYER3 = 2;			//3P
	const int PLAYER4 = 3;			//4P
	const int MAXPLAYERNUM = 4;		//�v���C���[�̍ő�l��
	const Vector3 PLAYER1_RESPOS = { -100.0f,0.0f, 100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = {  100.0f,0.0f, 100.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -100.0f,0.0f,-100.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = {  100.0f,0.0f,-100.0f };		//���X�|�[�����W(�E��)
	const float PLANAME_WIDTHSIZE = 230.0f;			//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u���́v�傫��
	const float PLANAME_HEIGHTSIZE = 120.0f;		//�v���C���[�̉�ʊp�ɒu����Ă��閼�O�̉摜�́u�c�́v�傫��
}

bool PhysicsPlayer::Start()
{
	//�C���X�^���X��T���B
	m_nowTime = FindGO<GameScene>("gamescene");
	m_titlescene = FindGO<TitleScene>("titlescene");

	//�e�v���C���[�̂Q�i�K���ߍU���̉���
	for (int i = 0; i < 4; i++)
	{
		m_sprite1[i] = NewGO<SpriteRender>(3);
		m_sprite1[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite1[i]->Init("Assets/image/DDS/1.dds", 100.0f, 100.0f);
		m_sprite1[i]->Deactivate();


		m_sprite2[i] = NewGO<SpriteRender>(3);
		m_sprite2[i]->SetPosition({ -500.0f,0.0f,0.0f });
		m_sprite2[i]->Init("Assets/image/DDS/2.dds", 100.0f, 100.0f);
		m_sprite2[i]->Deactivate();
	}
	m_sprite1[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite1[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite1[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite1[3]->SetPosition({ 550.0f,-200.0f,0.0f });
	m_sprite2[0]->SetPosition({ -550.0f,200.0f,0.0f });
	m_sprite2[1]->SetPosition({ 550.0f,200.0f,0.0f });
	m_sprite2[2]->SetPosition({ -550.0f,-200.0f,0.0f });
	m_sprite2[3]->SetPosition({ 550.0f,-200.0f,0.0f });


	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�o�^����Ă�������s
		if (m_titlescene->GetPlaFlg(i) == true)
		{
			//�v���C���[�����[�h
			m_player[i] = NewGO<SkinModelRender>(0);

			////�����蔻��

			////�R���C�_�[���������B
			////�R���C�_�[�̑傫�����������B
			//m_boxColliderSize[i] = { 18.0f,10.0f,40.0f };
			//m_boxCollider[i].Create(m_boxColliderSize[i]);
			////���ʂ�ݒ肷��B
			//rbInitData[i].mass = 3.0f;
			//rbInitData[i].collider = &m_boxCollider[i];
			//if (i == PLAYER1)
			//rbInitData[i].pos = PLAYER1_RESPOS;
			//if (i == PLAYER2)
			//	rbInitData[i].pos = PLAYER2_RESPOS;
			//if (i == PLAYER3)
			//	rbInitData[i].pos = PLAYER3_RESPOS;
			//if (i == PLAYER4)
			//	rbInitData[i].pos = PLAYER4_RESPOS;
			////�͂��߂͂�����Əォ��
			//rbInitData[i].pos.y = 100.0f;
			//m_rigidBody[i].Init(rbInitData[i]);
			////���C�͂�ݒ肷��B0�`10
			//m_rigidBody[i].SetFriction(0.1f);
			////���`�ړ�����v�f��ݒ肷��B
			////0���w�肵�����͈ړ����Ȃ��B
			//m_rigidBody[i].SetLinearFactor(1.0f, 1.0f, 1.0f);

			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			//�ǉ����ꂽ�v���C���[�̖��O�摜�̕\���ƈʒu����
			//�PP
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
			}
			//2P
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��
			}
			//3P
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����
			}
			//4P
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�
			}
			//�傫�������B���̃��f�����������������߁A���f���̑傫����1.5�{�B
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
			//�v���C���[�������ʒu�Ɏ����Ă����B
			PlaResporn(i);

			//�v���C���[����+1
			m_plaNum++;
		}
	}

	//Start�֐���return��
	return true;
}

PhysicsPlayer::~PhysicsPlayer()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//�v���C���[���폜
		DeleteGO(m_player[i]);
	}
	//���ߍU���̍ۂ̒i�K�����\���̍폜�B
	for (int i = 0; i < 4; i++)
	{
		DeleteGO(m_sprite1[i]);
		DeleteGO(m_sprite2[i]);
	}
}

void PhysicsPlayer::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < m_plaNum; i++)
	{
		//�������Ԃ��O�b�ɂȂ�����v���C���[�̏�����S�Ď~�߂�
		if (m_nowTime->GetNowTime() != 0) {
			//�Q�[���J�n�̃J�E���g�_�E�����I���܂Ńv���C���[�̏��������ׂĎ~�߂�
			if (m_nowTime->GetCountDownFlg() == false)
			{
				//�X�e�[�W�̒��S()���_�ƃv���C���[�Ƃ̋������v�Z
				m_diff = m_pos[i] - m_origin;
				//�X�e�[�W�ォ��O��Ă���Ƃ��A
				//(�x�N�g���̒������擾���A���ꂪ250.0f���傫���A500�ȉ��̒l��������A)
				if (m_diff.Length() > 250.0f && m_diff.Length() <= 500.0f)
				{
					//�v���C���[�����n���Ă���t���O��܂�
					m_isPlaLanding[i] = false;

					//����������
					m_pos[i].y -= 2.0f;
				}
				//�������班�����Ԃ��o�߂�����A
				//��{�̓X�e�[�^�X�̏������������ł��Ă��܂��B
				else if (m_diff.Length() > 500.0f)
				{
					//�v���C���[�������ʒu�Ɏ����Ă����B
					PlaResporn(i);
					//������Ə�Ƀv���C���[��߂��B
					m_pos[i].y += 50.0f;

					//�t���O�𗧂Ă�
					m_respornFallFlg[i] = true;
				}
				//�X�e�[�W��Ƀ��X�|�[�������Ƃ����t���O����������A
				else if (m_respornFallFlg[i])
				{
					//�X�e�[�W��ɗ��������鏈��
					if (m_pos[i].y != 0.0f)
					{
						m_pos[i].y -= 1.0f;
					}
					else
					{
						//�v���C���[�̒~�ς���Ă���X�s�[�h���������B
						m_moveSpeed[i] = { 0.0f,0.0f,0.0f };

						//���������̃^�C�}�[������
						m_pressTimer[i] = 0;
						//���������̃^�C�}�[������
						m_releaseTimer[i] = 0;
						isBPushFlg[i] = false;
						//���������������Ȃ��ƁA���n�����ۂɏ���Ƀ_�b�V���U������o�O���������܂��B


						//�t���O��܂�
						m_respornFallFlg[i] = false;
					}
				}
				//�X�e�[�W��ɂ���Ƃ����s�A
				else
				{
					m_isPlaLanding[i] = true;

					//��]����
					PlaTurn(i);

					//�����Ă���Ƃ��A
					if (g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == false)
					{
						//���������̃^�C�}�[�����Z
						m_pressTimer[i]++;

						//���������̃^�C�}�[������
						m_releaseTimer[i] = 0;

						isBPushFlg[i] = true;
					}
					//�������Ƃ��A
					if (!g_pad[i]->IsPress(enButtonB) && isBPushFlg[i] == true)
					{
						//���������̃^�C�}�[�����Z
						m_releaseTimer[i]++;

						//���������̃^�C�}�[������
						m_pressTimer[i] = 0;

						m_sprite1[i]->Deactivate();
						m_sprite2[i]->Deactivate();
					}

					//�v���C���[�̏��
					PlaNowSpeed(i);

					m_pos[i] += m_moveSpeed[i];

					////���̂̍��W�Ɖ�]��ݒ�B
					////m_rigidBody[i].SetPositionAndRotation(m_pos[i], m_rot[i]);
					////���̂̍��W�Ɖ�]���擾�B
					//m_rigidBody[i].GetPositionAndRotation(m_pos[i], m_rot[i]);
					////���̂̍��W�Ɖ�]�����f���ɔ��f�B
					//m_player[i]->GetModel().UpdateWorldMatrix(m_pos[i], m_rot[i], g_vec3One);
					////���̂ɗ͂�������B
					//m_rigidBody[i].AddForce(
					//	m_moveSpeed[i],		//��
					//	g_vec3Zero	//�͂������鍄�̂̑��Έʒu
					//);
				}
			}
			//�o�^����Ă���v���C���[�̏����X�V
			PlaDataUpdate(i);
		}
	}
}

//�I�����ꂽ�v���C���[�����X�|�[���ʒu�܂Ŗ߂��֐�
void PhysicsPlayer::PlaResporn(int x)
{
	//1P
	if (x == PLAYER1)
	{
		m_pos[x] = PLAYER1_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[x] = 2.5f;
		//��]�����Z�b�g����
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//2P
	else if (x == PLAYER2)
	{
		m_pos[x] = PLAYER2_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[x] = 3.7f;
		//��]�����Z�b�g����
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//3P
	else if (x == PLAYER3)
	{
		m_pos[x] = PLAYER3_RESPOS;		//���X�|�[�����W(����)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[x] = 1.0f;
		//��]�����Z�b�g����
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
	//4P
	else if (x == PLAYER4)
	{
		m_pos[x] = PLAYER4_RESPOS;		//���X�|�[�����W(�E��)

		//�v���C���[�����X�|�[�������Ƃ��ɑS�v���C���[����ŃX�e�[�W�������������Ă������ق���
		//���X�|�[������a�����Ȃ��̂ŁA�X�e�[�W�������������Ă����B
		m_rotAngle[x] = 5.5f;
		//��]�����Z�b�g����
		m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);
	}
}

//�v���C���[�̏����X�V����֐�
void PhysicsPlayer::PlaDataUpdate(int x)
{
	//�ʒu���Z�b�g
	m_player[x]->SetPosition(m_pos[x]);
	//��]���Z�b�g
	m_player[x]->SetRotation(m_rot[x]);
}

void PhysicsPlayer::PlaNowSpeed(int x)
{
	if (m_pressTimer[x] == 0 && m_releaseTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;

	}
	if (m_pressTimer[x] > 0 && m_releaseTimer[x] == 0)
	{
		//�U����������
		PlaAttackBefore(x);

	}

	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack0Flg[x] == true)
	{
		//���������̃^�C�}�[������
		m_pressTimer[x] = 0;

		//���������̃^�C�}�[������
		m_releaseTimer[x] = 0;
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack1Flg[x] == true)
	{
		//�U������
		PlaAtack1(x);
	}
	if (m_releaseTimer[x] > 0 && m_pressTimer[x] == 0 && isAtack2Flg[x] == true)
	{
		//�U������2
		PlaAtack2(x);
	}

	if (m_releaseTimer[x] == 20 && m_pressTimer[x] == 0)
	{
		//�ړ�����
		PlaMove(x);
		isBPushFlg[x] = false;
		isAtack0Flg[x] = false;
		isAtack1Flg[x] = false;
		isAtack2Flg[x] = false;
		m_atackTime[x] = 0;
	}
}

//�ړ�����
void PhysicsPlayer::PlaMove(int x)
{
	//���X�e�B�b�N�̓��͗ʂ����Z����
	m_moveSpeed[x].x += m_leftStick_x[x] * 5.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_leftStick_y[x] * 5.0f * g_gameTime->GetFrameDeltaTime();

	//���C�͂�ݒ肷��
	m_friction[x] = m_moveSpeed[x];
	m_friction[x] *= -1.5f;

	//���C�͂����Z����
	m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
}

//��]����
void PhysicsPlayer::PlaTurn(int x)
{
	//���X�e�B�b�N�̓��͗ʂ��󂯎��
	m_leftStick_x[x] = g_pad[x]->GetLStickXF();
	m_leftStick_y[x] = g_pad[x]->GetLStickYF();

	//�ړ����ĂȂ����͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//�ړ����ĂȂ����͉�]���Ȃ�
	if (fabsf(m_moveSpeed[x].x) < 0.001f && fabsf(m_moveSpeed[x].z) < 0.001f) {
		return;
	}
	//��]�p�x
	m_rotAngle[x] = atan2(m_moveSpeed[x].x, m_moveSpeed[x].z);

	m_rot[x].SetRotation(Vector3::AxisY, m_rotAngle[x]);

	//������ݒ肷��
	m_plaDir[x] = m_moveSpeed[x];
	m_plaDir[x].Normalize();
}

//�U����������
void PhysicsPlayer::PlaAttackBefore(int x)
{
		m_moveSpeed[x].x += m_leftStick_x[x] * 1.5f * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_leftStick_y[x] * 1.5f * g_gameTime->GetFrameDeltaTime();

		//���C�͂�ݒ肷��
		m_friction[x] = m_moveSpeed[x];
		m_friction[x] *= -5.0f;

		//���C�͂����Z����
		m_moveSpeed[x].x += m_friction[x].x * g_gameTime->GetFrameDeltaTime();
		m_moveSpeed[x].z += m_friction[x].z * g_gameTime->GetFrameDeltaTime();
		m_atackTime[x]++;
		if (m_atackTime[x] > 0 && m_atackTime[x] < 30)
		{
			isAtack0Flg[x] = true;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = false;


		}
		if (m_atackTime[x] >= 30 && m_atackTime[x] < 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = true;
			isAtack2Flg[x] = false;
			//�u1�v�\��
			if (m_atackTime[x] == 30) {
				m_sprite2[x]->Deactivate();
				m_sprite1[x]->Activate();
			}
		}
		if (m_atackTime[x] > 90)
		{
			isAtack0Flg[x] = false;
			isAtack1Flg[x] = false;
			isAtack2Flg[x] = true;
			if (m_atackTime[x] == 91) {
				//�u2�v�\��
				m_sprite1[x]->Deactivate();
				m_sprite2[x]->Activate();

			}
		}
}

//�U������1
void PhysicsPlayer::PlaAtack1(int x)
{
	m_moveSpeed[x] = m_plaDir[x] * 4.0f;
}

//�U������2
void PhysicsPlayer::PlaAtack2(int x)
{
	m_moveSpeed[x] = m_plaDir[x] * 7.0f;
}