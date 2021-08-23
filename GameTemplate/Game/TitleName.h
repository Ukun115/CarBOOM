///<<summary>
///�^�C�g�����̃��[�u����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class TitleName : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		enum enTitleSpriteNum
		{
			TitleSprite1,
			TotalTitleSpriteNum = 9
		};

		SpriteRender* m_titleBaraBaraSprite[TotalTitleSpriteNum] = { nullptr };

		char m_filePath[256];
		Vector3 m_titleBaraBaraSpritePos[TotalTitleSpriteNum];
		int m_waveTimer = 0;
		int m_verticalMoveTimer[TotalTitleSpriteNum] = { 0 };

		bool Start()override final;
		~TitleName()override final;
		void Update()override final;

		//�摜���c�ړ�����֐�
		void VerticalMove(const int width, const float speed, const int spriteNum);
		//�^�C�g�������E�F�[�u������֐�
		void TitleNameWave();

	public:

	};
}