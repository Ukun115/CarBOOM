#pragma once
class TitleScene;

class Player : public IGameObject
{
private:
	SkinModelRender* m_player[4] = { nullptr };		//�ő�v���C�l��4�l
	TitleScene* m_getAddPlayerFlg = { nullptr };

	Vector3    m_pos[4];		//�v���C���[�̈ʒu
	Quaternion m_rot[4];		//�v���C���[�̉�]
	Vector3    m_sca[4];		//�v���C���[�̊g�嗦

public:
	bool Start();
	~Player();
	void Update();
	void PlaDataUpdate();	//�v���C���[�̈ʒu��]�g�嗦�̏��X�V�֐�
};

