#pragma once
class PhysicsPlayer;
class TitleScene;
class GameScene;

#include "../../ExEngine/physics/CharacterController.h"

class Enemy : public IGameObject
{
private:

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
	Vector3 m_diff;								//�p�g�J�[�ƃv���C���[�Ƃ̋���
	Vector3 m_plaPushSpeed;

	bool m_respornFallFlg[6] = { false };	//������Ƀ��X�|�[�������̂ŁA����������t���O

	CharacterController m_charaCon[6];		//�L�����N�^�R���g���[���B

	float distance = 10000.0f;
	int a = 0;

	enum ENEMY
	{
		ENEMY1,		//�G�l�~�[�P
		ENEMY2,		//�G�l�~�[�Q
		ENEMY3,		//�G�l�~�[�R
		ENEMY4,		//�G�l�~�[�S
		ENEMY5,		//�G�l�~�[�T
		ENEMY6,		//�G�l�~�[�U
		ENEMYNUM	//�G�̑���
	};

	enum PLAYER
	{
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		MAXPLAYERNUM
	};

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

	Vector3 GetEnemySpeed(int x) { return m_moveSpeed[x]; }

	Vector3 GetEnemyPos(int x) { return m_enePos[x]; }
};