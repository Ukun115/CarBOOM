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

	int m_plaNum = 0;	//�v���C���[�����J�E���g����ϐ�

	Vector3 m_moveSpeed[4];				//�ړ����x
	Vector3 m_plaDir[4];					//����
	float m_leftStick_x[4];				//���X�e�B�b�N��x���͗�
	float m_leftStick_y[4];				//���X�e�B�b�N��y���͗�
	int m_pressTimer[4];				//���������̃^�C�}�[
	int m_releaseTimer[4];				//���������̃^�C�}�[
	bool isBPushFlg[4] = { false };		//B�{�^���������ꂽ���̃t���O
	float m_rotAngle[4];				//��]�p�x
	Vector3 m_friction[4];				//���C
	Quaternion m_rot2[4];

public:
	bool Start();
	~Player();
	void Update();
	void PlaResporn(int x);		//�v���C���[�������ʒu�Ƀ��X�|�[��������֐�
	void PlaDataUpdate(int x);	//�v���C���[�̈ʒu��]�g�嗦�̏��X�V�֐�

	//�ړ�����
	void PlaMove(int x);
	//��]����
	void PlaTurn(int x);
	//�U����������
	void PlaAttackBefore(int x);
	//�U������
	void PlaAtack(int x);
	//�v���C���[�̏��
	void Joutai(int x);

	void PlaNowSpeed(int x);
};

