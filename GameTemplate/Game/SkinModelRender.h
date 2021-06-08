#pragma once
#include "DirectionLight.h"
#include "PointLight.h"
class Model;

//ライト全体のデータ構造体
struct ligData
{
	DirLigData dirLigData;		//ディレクションライトの構造体データ
	PoiLigData poiLigData;				//ポイントライトの構造体データ
};

class SkinModelRender : public IGameObject
{
public:
	bool Start();
	~SkinModelRender();
	void Update();

private:

	Vector3    m_pos = Vector3::Zero;					//位置
	Quaternion m_rot = Quaternion::Identity;			//回転
	Vector3    m_sca = Vector3::One;					//拡大率

	//モデルを初期化するための情報を設定
	ModelInitData m_modelInitData;
	//m_modelはモデルクラス
	Model m_model;

	ligData m_ligData;

	DirectionLight* m_directionLight = nullptr;
	PointLight* m_pointLight = nullptr;


public:
	//3Dモデルをロードするための情報を設定する関数
	void Init(const char* tkmFilePath);

	//位置を設定するセット関数
	void SetPosition(const Vector3 pos) { m_pos = pos; }

	Vector3 GetPosition() { return m_pos; }
	//回転を設定するセット関数
	void SetRotation(const Quaternion rot) { m_rot = rot; }
	//拡大率を設定するセット関数
	void SetScale(const Vector3 sca) { m_sca = sca; }

	//描画関数
	void Render(RenderContext& rc);

	////ディレクションライトクラスの構造体の中の情報をdirLigDataにセット
	//void SetDirLigData(const DirLigData ligData) { dirLigData = ligData; }

	////ポイントライトクラスの構造体の中の情報をpoiLigDataにセット
	//void SetPoiLigData(const PoiLigData ligData) { poiLigData = ligData; }
};