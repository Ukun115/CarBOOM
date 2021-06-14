#pragma once
class PhysicsPlayer;
class TitleScene;
class GameScene;

class Enemy : public IGameObject
{
private:
	BoxCollider m_boxCollider[6];		//�����蔻��
	RigidBody m_rigidBody[6];			//����

	Vector3 m_boxColliderSize[6];				//�c������
	RigidBodyInitData rbInitData[6];

	SkinModelRender* m_enemy[6] = { nullptr };		//�G6��
	PhysicsPlayer* m_player;	//�v���C���[�B
	Vector3    m_plaPos[4];		//�v���C���[�̈ʒu
	Vector3    m_enePos[6];		//�G�l�~�[�̈ʒu
	Quaternion m_rot[6];		//�G�l�~�[�̉�]
	Vector3    m_mostShortKyori[6];   //�v���C���[1�ƓG�̋���
	Vector3    m_newKyori[6];   //�v���C���[2�ƓG�̋���

	Vector3 m_moveSpeed[6];				//�ړ����x
	Vector3 m_eneDir[6];					//����
	float m_rotAngle[6];				//��]�p�x
	Vector3 m_friction[6];				//���C
	Quaternion m_rot2[6];
	int m_cTime[6];				//�U����CT
	bool ctFlg[6] = { false };		//CT�̃t���O

	TitleScene* m_titlescene = nullptr;
	GameScene* m_gamescene = nullptr;
	int m_startDelayTimer = 0;		//�X�^�[�g��x�点��ϐ�

	PhysicsPlayer* m_physicsPlayer = nullptr;

	Vector3 m_origin = { 0.0f,0.0f,0.0f };		//���_
	Vector3 m_diff;								//�p�g�J�[�ƃX�e�[�W�̒��S�i���_�j�Ƃ̋���

	bool m_respornFallFlg[6] = { false };	//������Ƀ��X�|�[�������̂ŁA����������t���O

public:
	bool Start()override;
	~Enemy()override;
	void Update()override;

	//�ړ�����
	void EneMove(int x);
	//��]����
	void EneTurn(int x);
	//�����ݒ�
	void Kyori(int x);

	//�p�g�J�[�������ʒu�ɖ߂��֐�
	void EneResporn(int x);
};