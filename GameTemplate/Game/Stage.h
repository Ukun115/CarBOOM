#pragma once
class StageSelectScene;
class GameScene;
class StageSelectcene;
class Player;
class TitleScene;
class Enemy;


class Stage : public IGameObject		// �R�s�[�֎~�|���V�[���p������B
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	SkinModelRender* m_stage = nullptr;
	StageSelectScene* m_stageSelectScene= nullptr;
	GameScene* m_gameScene = nullptr;
	Player* m_player = nullptr;
	TitleScene* m_titleScene = nullptr;
	Enemy* m_enemy = nullptr;


	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g�N���X���쐬
	Effect m_fallSnowEffect[2];		//�A�C�X�X�e�[�W�̍~���Ă����G�t�F�N�g


	bool m_isPauseFlg = false;


	/// <summary>
	/// �^�C�}�[
	/// </summary>
	int m_fallSnowTimer = 0;
	int m_windDirection = 0;	//���݂̕�


	Vector3 m_plaPos[4];			//�v���C���[4�̕��̃v���C���[�̈ʒu
	Vector3 m_LengthFromStaPivToPla[4];	//�X�e�[�W�̊�_����v���C���[�܂ł̋���

	int m_stageSelectNum = 0;
	int m_nowTime = 0;
	int m_totalPlaNum = 0;

	/// <summary>
	/// �񋓌^�̐錾
	/// </summary>
	//�X�e�[�W�ԍ�
	enum StageNum
	{
		ehehe,	//Stage1���P�Ԃɂ��邽�߂�ehehe�����Ē���
		Stage1,
		Stage2,
		Stage3,
		Stage4,
		Stage5
	};


	bool Start() override;
	~Stage()override;
	void Update() override;


	//��G�t�F�N�g�����֐�
	void SnowFall();
	//���̉e����^���鏈��
	void WindStage();
	//�X�����鏈��
	void Tilt();

public:
	int GetWindDirection() { return m_windDirection; }

	void SetNowTime(int nowTime) { m_nowTime = nowTime ; }
	void SetSelectStageNum(int stageSelectNum) {m_stageSelectNum = stageSelectNum ; }
	void SetTotalPlaNum(int totalPlaNum) { m_totalPlaNum = totalPlaNum; }
	void SetPauseFlg(bool pauseFlg) { m_isPauseFlg = pauseFlg; }
};