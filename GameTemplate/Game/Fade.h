#pragma once


class Fade:public IGameObject
{
private:
	SpriteRender* m_fadeSprite = nullptr;
	//�摜�̃��l
	float m_alphaValue = 0.0f;

	int m_nowState;  //���݂̃X�e�[�g

	bool Start()override;
	~Fade()override;
	void Update()override;

	//�񋓌^
	enum enumState {
		StateIn,	//�t�F�[�h�C��
		StateOut,	//�t�F�[�h�A�E�g
		StateWait,	//�ҋ@
	};

public:
	//���݂̃��l�𓾂�
	float GetAlphaValue() { return m_alphaValue; }
	void SetAlphaValue(float alphaValue) { m_alphaValue = alphaValue; }
	//���݂̏�Ԃ𓾂�
	int GetNowState() { return m_nowState; }
	void SetState(int newState) { m_nowState = newState; }
};