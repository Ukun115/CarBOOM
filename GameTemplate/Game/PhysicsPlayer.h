#pragma once
class TitleScene;
class GameScene;

class PhysicsPlayer : public IGameObject
{
public:
	bool Start() override;
	~PhysicsPlayer() override;
	void Update() override;

	void PlaResporn(int x);		//�v���C���[�������ʒu�Ƀ��X�|�[��������֐�
	void PlaDataUpdate(int x);	//�v���C���[�̈ʒu��]�g�嗦�̏��X�V�֐�

	//�ړ�����
	void PlaMove(int x);
	//��]����
	void PlaTurn(int x);
	//�U����������
	void PlaAttackBefore(int x);
	//�U������1
	void PlaAtack1(int x);
	//�U������2
	void PlaAtack2(int x);

	void PlaNowSpeed(int x);

	//�v���C���[�|�W�V�������Q�b�g����֐�
	Vector3 GetPlaPos(int x) { return  m_pos[x]; }

	bool GetIsPlaLanding(int x) { return m_isPlaLanding[x]; }

private:
	BoxCollider m_boxCollider[4];		//�����蔻��
	RigidBody m_rigidBody[4];			//����

	Vector3 m_boxColliderSize[4];				//�c������
	RigidBodyInitData rbInitData[4];

	SkinModelRender* m_player[4] = { nullptr };		//�ő�v���C�l��4�l
	TitleScene* m_titlescene = nullptr;
	GameScene* m_nowTime = nullptr;

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

	Vector3 m_origin = {0.0f,0.0f,0.0f};		//���_
	Vector3 m_diff;								//�v���C���[�ƃX�e�[�W�̒��S�i���_�j�Ƃ̋���

	bool m_respornFallFlg[4] = {false};	//������Ƀ��X�|�[�������̂ŁA����������t���O

	bool m_isPlaLanding[4] = {false};	//�v���C���[�����n���Ă��邩���Ă��Ȃ����𔻕ʂ���t���O

	SpriteRender* m_sprite1[4] = { nullptr };
	SpriteRender* m_sprite2[4] = { nullptr };
	bool isAtack0Flg[4] = { false };		//B�{�^���������ꂽ���̃t���O
	bool isAtack1Flg[4] = { false };		//B�{�^���������ꂽ���̃t���O
	bool isAtack2Flg[4] = { false };		//B�{�^���������ꂽ���̃t���O
	int m_atackTime[4];				    //�U���̃^�C�}�[
};