#include "stdafx.h"
#include "Player.h"
#include "TitleScene.h"

namespace
{
	const Vector3 PlAYER_NORMALSIZE = {1.5f,1.5f,1.5f};			//�v���C���[�̏����T�C�Y
	const int PLAYER1 = 0;
	const int PLAYER2 = 1;
	const int PLAYER3 = 2;
	const int PLAYER4 = 3;
	const int MAXPLAYERNUM = 4;			//�v���C���[�̍ő�l��
	const Vector3 PLAYER1_RESPOS = { -20.0f,0.0f,-20.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER2_RESPOS = { 20.0f,0.0f,-20.0f };		//���X�|�[�����W(�E��)
	const Vector3 PLAYER3_RESPOS = { -20.0f,0.0f,20.0f };		//���X�|�[�����W(����)
	const Vector3 PLAYER4_RESPOS = { 20.0f,0.0f,20.0f };		//���X�|�[�����W(�E��)
}

bool Player::Start()
{

	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{

		//�o�^���ꂽ�v���C���[�̎Ԃ����[�h
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//�v���C���[�̎Ԃ����[�h
			m_player[i] = NewGO<SkinModelRender>(0);
			//���f���̃t�@�C���p�X��ݒ聕�������W(���X�|�[�����W)�̐ݒ�B
			if (i == PLAYER1)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//�Ԏ�
				m_player[i]->SetPosition(PLAYER1_RESPOS);		//����
			}
			else if (i == PLAYER2)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Blue.tkm");	//��
				m_player[i]->SetPosition(PLAYER2_RESPOS);		//�E��
			}
			else if (i == PLAYER3)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Yellow.tkm");	//����
				m_player[i]->SetPosition(PLAYER3_RESPOS);		//����
			}
			else if (i == PLAYER4)
			{
				m_player[i]->Init("Assets/modelData/LowPoly_PlayerCar_Green.tkm");	//�Ύ�
				m_player[i]->SetPosition(PLAYER4_RESPOS);		//�E��
			}
			//�傫�������B���f���̑傫����1.5�{�B
			m_player[i]->SetScale(PlAYER_NORMALSIZE);
		}
	}


	//Start�֐���return��
	return true;
}

Player::~Player()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�ǉ�����Ă�����ǉ����ꂽ�v���C���[�̎Ԃ����[�h
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//�v���C���[���폜
			DeleteGO(m_player[i]);
		}
	}
}

void Player::Update()
{
	//�o�^����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		if (m_getAddPlayerFlg->GetPlayerFlg(i) == true)
		{
			//�R���g���[���[���X�e�B�b�N�Ńv���C���[�𓮂����B
			m_pos[i].x -= g_pad[i]->GetLStickXF() * 2.0f;
			m_pos[i].z -= g_pad[i]->GetLStickYF() * 2.0f;
		}
	}

	//�o�^����Ă���v���C���[�̏����X�V
	DataUpdate();
}

//�v���C���[�̏����X�V����֐�
void Player::DataUpdate()
{
	//�Q�����Ă���v���C���[�����[�v
	for (int i = PLAYER1; i < MAXPLAYERNUM; i++)
	{
		//�ʒu���Z�b�g
		m_player[i]->SetPosition(m_pos[i]);
		//��]���Z�b�g
		m_player[i]->SetRotation(m_rot[i]);
		//�g�嗦���Z�b�g
		m_player[i]->SetScale(m_sca[i]);
	}
}