#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_titleSprite = nullptr;
	SpriteRender* m_crownSprite = nullptr;
	SpriteRender* m_pushStartButtonSprite = nullptr;

	SpriteRender* m_plaDeactiveName[4] = {nullptr};		//�X�v���C�g�����_�[
	SpriteRender* m_plaActiveName[4] = {nullptr};		//�X�v���C�g�����_�[
	bool isAddPlayer[4] = { false };		//�v���C���[���o�^���ꂽ���̔��ʃt���O
	int m_totalPlayerNum = 1;			//�v���C���[�̍��v��
	bool isCanGameStartFlg = true;		//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������

	int m_buttonTimer = 0;
	bool m_buttonTimerFlg = true;

	enum PLAYER
	{
		PLAYER1,	//1P
		PLAYER2,	//2P
		PLAYER3,	//3P
		PLAYER4,	//4P
		MAXPLAYERNUM	//�ő�v���C�l��
	};

public:
	bool Start()override;
	~TitleScene()override;
	void Update()override;

	//�v���C���[���ǉ�����Ă��邩�̃t���O���擾����֐�
	bool GetPlaFlg(int x) { return isAddPlayer[x]; }

	int GetTotalPlaNum(){ return m_totalPlayerNum; }
};