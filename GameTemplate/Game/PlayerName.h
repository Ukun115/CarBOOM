///<<summary>
///��ʊp�ɕ\��������v���C���[���\������
///</summary>

#pragma once

namespace nsCARBOOM
{
	class GameScene;

	class PlayerName : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		/// <summary>
		/// �񋓌^�̐錾
		/// </summary>
		enum enPlayer
		{
			Player1,		//1P�̔z��ł̔ԍ�
			Player2,		//2P�̔z��ł̔ԍ�
			Player3,		//3P�̔z��ł̔ԍ�
			Player4,		//4P�̔z��ł̔ԍ�
			TotalPlaNum	//�v���C���[�̍ő吔
		};

		FontRender* m_PlaNameFont[TotalPlaNum] = { nullptr };
		GameScene* m_gameScene = nullptr;

		int m_totalPlaNum = 0;

		bool m_isAddPlayerFlg[TotalPlaNum] = { false };		//�e�v���C���[���o�^����Ă��邩�̔��ʃt���O

		bool Start()override final;
		~PlayerName()override final;
		void Update()override final;

	public:
		//�v���C���[��ǉ������Ƃ��ɃJ���[�`�F���W�i�A�N�e�B�u���j����֐�
		void ColorChange(const int totalPlaNum);

		//�^�C�g���V�[���ŉ��l�v���C���[���ǉ����ꂽ���������Ă���
		void SetTotalPlaNum(const int totalPlaNum) { m_totalPlaNum = totalPlaNum; }

		void AddPlayerFlgOn(const int totalPlaNum);
	};
}