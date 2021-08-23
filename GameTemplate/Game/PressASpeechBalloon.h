///<<summary>
///PressA!!�����o���摜�̃��[�u����
///</summary>

#pragma once

namespace nsCARBOOM
{
	class PressASpeechBalloon : public IGameObject		//TODO:�R�s�[�֎~�|���V�[���p������B
	{
	private:
		enum enNowState
		{
			Player3SidePos = 1,
			Player4SidePos,
			Delete
		};

		SpriteRender* m_pressASpeechBalloon = { nullptr };
		SpriteRender* m_pressASpeechBalloonArrow = { nullptr };

		Vector3 m_pressASpeechBalloonPos;		//�v���C���[�ǉ������o���̈ʒu
		Vector3 m_arrowSca;

		/// <summary>
		/// �^�C�}�[
		/// </summary>
		int m_sideMoveTimer = nsStdafx::INT_ZERO;

		bool Start()override final;
		~PressASpeechBalloon()override final;
		void Update()override final;

	public:
		void NextState(const int nowState);
	};
}