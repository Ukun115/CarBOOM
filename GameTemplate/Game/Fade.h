///<<summary>
///�t�F�[�h�C���t�F�[�h�A�E�g����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class Fade :public IGameObject	//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		//�񋓌^
		enum enState {
			StateIn,	//�t�F�[�h�C��
			StateOut,	//�t�F�[�h�A�E�g
			StateWait,	//�ҋ@
		};

		SpriteRender* m_fadeSprite = nullptr;

		//�摜�̃��l
		float m_alphaValue = nsStdafx::FLOAT_ZERO;
		int m_nowState = nsStdafx::INT_ZERO;  //���݂̃X�e�[�g

		bool Start()override final;
		~Fade()override final;
		void Update()override final;

	public:
		//�Q�b�^�[
		float GetAlphaValue()const { return m_alphaValue; }
		int GetNowState()const { return m_nowState; }
		//�Z�b�^�[
		void SetAlphaValue(const float alphaValue) { m_alphaValue = alphaValue; }
		void SetState(const int newState) { m_nowState = newState; }
	};
}