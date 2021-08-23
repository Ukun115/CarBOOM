///<<summary>
///��ʊp�ɕ\��������v���C���[���\������
///</summary>


#include "stdafx.h"
#include "PlayerName.h"
#include "GameScene.h"

namespace nsCARBOOM
{
	namespace nsPlayerName
	{
		const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//�v���C���[1�̖��O�\���ʒu
		const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//�v���C���[2�̖��O�\���ʒu
		const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//�v���C���[3�̖��O�\���ʒu
		const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//�v���C���[4�̖��O�\���ʒu
		const float FONT_SCA = { 1.0f };					//�g�嗦
		const float     FONT_ROT = 0.0f;			//�t�H���g�̌X��
		const Vector2   FONT_PIV = { 1.0f,1.0f };	//�t�H���g�̊�_
		const float TEXT_SHADOW_OFFSET = 3.0f;
	}

	bool PlayerName::Start()
	{
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);

		//�PP�̒ǉ��t���O��^�ɁB
		m_isAddPlayerFlg[Player1] = true;

		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
			//2P�`4P�̔�A�N�e�B�u�摜�I�u�W�F�N�g����
			m_PlaNameFont[plaNum] = NewGO<FontRender>(nsStdafx::PRIORITY_0, nullptr);		//1P
			switch (plaNum)
			{
			case Player1:
				m_PlaNameFont[Player1]->Init(
					L"PLAYER1",			//�e�L�X�g
					nsPlayerName::PLANAME1POS,		//�ʒu
					nsStdafx::RED,		//�F
					nsPlayerName::FONT_ROT,			//�X��
					nsPlayerName::FONT_SCA,		//�g�嗦
					nsPlayerName::FONT_PIV			//��_
				);
				break;
			case Player2:
				m_PlaNameFont[Player2]->Init(
					L"PLAYER2",			//�e�L�X�g
					nsPlayerName::PLANAME2POS,		//�ʒu
					nsStdafx::GRAY,		//�F
					nsPlayerName::FONT_ROT,			//�X��
					nsPlayerName::FONT_SCA,		//�g�嗦
					nsPlayerName::FONT_PIV			//��_
				);
				break;
			case Player3:
				m_PlaNameFont[Player3]->Init(
					L"PLAYER3",			//�e�L�X�g
					nsPlayerName::PLANAME3POS,		//�ʒu
					nsStdafx::GRAY,		//�F
					nsPlayerName::FONT_ROT,			//�X��
					nsPlayerName::FONT_SCA,		//�g�嗦
					nsPlayerName::FONT_PIV			//��_
				);
				break;
			case Player4:
				m_PlaNameFont[Player4]->Init(
					L"PLAYER4",			//�e�L�X�g
					nsPlayerName::PLANAME4POS,		//�ʒu
					nsStdafx::GRAY,		//�F
					nsPlayerName::FONT_ROT,			//�X��
					nsPlayerName::FONT_SCA,		//�g�嗦
					nsPlayerName::FONT_PIV			//��_
				);
				break;
			}
			//�����̋��E���\��
			m_PlaNameFont[plaNum]->SetShadowParam(true, nsPlayerName::TEXT_SHADOW_OFFSET, Vector4::Black);

			if (m_totalPlaNum <= plaNum)
			{
				continue;
			}
			//�A�N�e�B�u�ȃv���C���[�̖��O���A�N�e�B�u�J���[�ɕύX
			ColorChange(plaNum);
		}

		return true;
	}

	PlayerName::~PlayerName()
	{
		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
			DeleteGO(m_PlaNameFont[plaNum]);
		}
	}

	void PlayerName::Update()
	{

	}

	//�v���C���[��ǉ������Ƃ��ɃJ���[�`�F���W�i�A�N�e�B�u���j����֐�
	void PlayerName::ColorChange(const int totalPlaNum)
	{
		switch (totalPlaNum)
		{
		case Player1:
			m_PlaNameFont[Player1]->SetColor(nsStdafx::RED);
			break;
		case Player2:
			m_PlaNameFont[Player2]->SetColor(nsStdafx::BLUE);
			break;
		case Player3:
			m_PlaNameFont[Player3]->SetColor(nsStdafx::YELLOW);
			break;
		case Player4:
			m_PlaNameFont[Player4]->SetColor(nsStdafx::GREEN);
			break;
		}
	}

	void PlayerName::AddPlayerFlgOn(const int totalPlaNum)
	{
		//�V�K�v���C���[�̒ǉ��t���O��^�ɁB
		m_isAddPlayerFlg[totalPlaNum] = true;
	}
}