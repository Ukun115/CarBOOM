#pragma once
class GameScene;
class Player;


class ResultScene : public IGameObject
{
private:

	/// <summary>
	/// �N���X�̃|�C���^
	/// </summary>
	GameScene* m_gameScene = nullptr;
	SpriteRender* m_resultSprite = nullptr;
<<<<<<< HEAD
	SpriteRender* m_plaNum[4] = {nullptr};			//�v���C���[4�l���p��
	SpriteRender* m_rankingSprite[4] = {nullptr};	//�v���C���[4�l���p��
	Player* m_player = nullptr;


	unsigned int m_plaScore[4];		//�v���C���[4�l���̃X�R�A������z��
=======
	SpriteRender* m_plaNum[4] = {nullptr};
	SpriteRender* m_rankingSprite[4] = {nullptr};
	Player* m_player = nullptr;


	int m_plaScore[4];		//�v���C���[�̃X�R�A������z��
>>>>>>> remotes/origin/master

public:

	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
	void RankingSort();
};

