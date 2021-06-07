#pragma once
class DirectionLight;
class PointLight;

class GameScene:public IGameObject
{
private:
	bool Start();
	~GameScene();
	void Update();

	DirectionLight* m_directionlight;		//ディレクションライトクラス型のポインタを作成
	PointLight* m_pointlight;				//ポイントライトクラス型
	SkinModelRender* m_skinmodelrender;		//スキンモデルレンダークラス型

	DirLigData directionLig;				// ディレクションライトのデータを作成

public:

};