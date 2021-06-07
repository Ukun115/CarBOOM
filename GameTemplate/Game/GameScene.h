#pragma once
class DirectionLight;
class PointLight;

class GameScene:public IGameObject
{
public:
	bool Start();
	~GameScene();
	void Update();

private:
	DirectionLight* m_directionlight;		//�f�B���N�V�������C�g�N���X�^�̃|�C���^���쐬
	PointLight* m_pointlight;				//�|�C���g���C�g�N���X�^
	SkinModelRender* m_skinmodelrender;		//�X�L�����f�������_�[�N���X�^

	DirLigData directionLig;				// �f�B���N�V�������C�g�̃f�[�^���쐬

	Vector3 m_unityPos = Vector3::Zero;	//���j�e�B�[�����̈ʒu���

public:

};