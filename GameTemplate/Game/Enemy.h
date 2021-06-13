#pragma once
class PhysicsPlayer;

class Enemy : public IGameObject
{
private:
	SkinModelRender* m_enemy[6] = { nullptr };		//�G6��
	PhysicsPlayer* m_player;	//�v���C���[�B
	Vector3    m_plaPos[4];		//�v���C���[�̈ʒu
	Vector3    m_enePos[6];		//�G�l�~�[�̈ʒu
	Quaternion m_rot[6];		//�G�l�~�[�̉�]
	Vector3    m_kyori[6];   //�v���C���[�ƓG�̋���
	//Vector3    m_kyoriV[6];   //�v���C���[�ƓG�̋����x�N�g��
	//Vector3    m_kyoriL[6];   //�v���C���[�ƓG�̋����̑傫��

	Vector3 m_moveSpeed[6];				//�ړ����x
	Vector3 m_eneDir[6];					//����
	float m_rotAngle[6];				//��]�p�x
	Vector3 m_friction[6];				//���C
	Quaternion m_rot2[6];
	int m_cTime[6];				//�U����CT
	bool ctFlg[6] = { false };		//CT�̃t���O


public:
	bool Start();
	~Enemy();
	void Update();

	//�ړ�����
	void EneMove(int x);
	//��]����
	void EneTurn(int x);
	//�����ݒ�
	void Kyori(int x);

};