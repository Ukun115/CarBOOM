#pragma once


class Fade:public IGameObject	//TODO:�R�s�[�֎~�|���V�[���p������B
{
private:

	//�񋓌^
	enum enumState {
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};


	SpriteRender* m_fadeSprite = nullptr;


	//�摜�̃��l
	float m_alphaValue = FLOAT_ZERO;
	int m_nowState = 0;  //���݂̃X�e�[�g

	bool Start()override final;
	~Fade()override final;
	void Update()override final;

public:
	//���݂̃��l�𓾂�
	float GetAlphaValue()const { return m_alphaValue; }
	void SetAlphaValue(const float alphaValue) { m_alphaValue = alphaValue; }
	//���݂̏�Ԃ𓾂�
	int GetNowState()const { return m_nowState; }
	void SetState(const int newState) { m_nowState = newState; }
};