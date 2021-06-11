#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender[4] = {nullptr};		//�X�v���C�g�����_�[
	bool isAddPlayer[4] = { false };		//�v���C���[���o�^���ꂽ���̔��ʃt���O
	int m_totalPlayerNum = 1;			//�v���C���[�̍��v��
	bool isCanGameStartFlg = true;		//true�̂Ƃ��̓Q�[���X�^�[�g�{�^����������

public:
	bool Start();
	~TitleScene();
	void Update();

	//�v���C���[���ǉ�����Ă��邩�̃t���O���擾����Q�b�g�֐�
	bool GetPlaFlg(int x) { return isAddPlayer[x]; }
};