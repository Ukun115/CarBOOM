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
	SpriteRender* m_plaNum[4] = {nullptr};			//�v���C���[4�l���p��
	SpriteRender* m_rankingSprite[4] = {nullptr};	//�v���C���[4�l���p��
	Player* m_player = nullptr;


	unsigned int m_plaScore[4];		//�v���C���[4�l���̃X�R�A������z��

public:

	bool Start()override;
	~ResultScene()override;
	void Update()override;


	//���ʂɂ���ă\�[�g���v���C���[���̉摜����ёւ���֐�
	void RankingSort();
};

