///<<summary>
///PRESS START BUTTON �̃��[�u����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PressStartButton : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		SpriteRender* m_pressStartButtonSprite = { nullptr };

		/// <summary>
		/// �^�C�}�[
		/// </summary>
		unsigned int m_flashingFontTimer = { nsStdafx::INT_ZERO };		//�_�ŕ����̕\����\���̐؂�ւ��^�C�}�[

		bool m_isFlashingFontActiveFlg = { true };		//true�̂Ƃ��_�ŕ����̕\���^�C�~���O

		bool Start()override final;
		~PressStartButton()override final;
		void Update()override final;

	public:

	};
}