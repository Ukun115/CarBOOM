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
	DirectionLight* m_directionlight;		//ディレクションライトクラス型のポインタを作成
	PointLight* m_pointlight;				//ポイントライトクラス型
	SkinModelRender* m_skinmodelrender;		//スキンモデルレンダークラス型

	DirLigData directionLig;				// ディレクションライトのデータを作成

	Vector3 m_unityPos = Vector3::Zero;	//ユニティーちゃんの位置情報

public:

};