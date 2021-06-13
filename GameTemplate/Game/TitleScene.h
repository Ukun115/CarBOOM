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

	bool isButtonFlg = true;	//true�ŕ\���Afalse�Ŕ�\��

	SpriteRender* m_sprite[4] = { nullptr };
	int m_countDownTimer = 0;	//�J�E���g�_�E���^�C�}�[
	bool m_countTimeFlg = true;

public:
	bool Start();
	~TitleScene();
	void Update();

	//�v���C���[���ǉ�����Ă��邩�̃t���O���擾����֐�
	bool GetPlaFlg(int x) { return isAddPlayer[x]; }

	bool GetCountDownFlg() { return m_countTimeFlg; }
};