#pragma once

class TitleScene : public IGameObject
{
private:
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	bool addPlayer[4] = { false };		//�v���C���[���o�^���ꂽ���̔��ʃt���O
	int m_totalPlayerNum = 1;			//�v���C���[�̍��v��

public:
	bool Start();
	~TitleScene();
	void Update();

	//�v���C���[���ǉ�����Ă��邩�̃t���O���擾����Q�b�g�֐�
	bool GetPlayerFlg(int x) { return addPlayer[x]; }
};