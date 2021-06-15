#pragma once
#include "Light.h"
class Model;
class Light;

class SkinModelRender : public IGameObject
{
public:
	bool Start()override;
	~SkinModelRender()override;
	void Update()override;

private:

	Vector3    m_pos = Vector3::Zero;					//位置
	Quaternion m_rot = Quaternion::Identity;			//回転
	Vector3    m_sca = Vector3::One;					//拡大率

	//モデルを初期化するための情報を設定
	ModelInitData m_modelInitData;
	//m_modelはモデルクラス
	Model m_model;

	Light* m_light;

public:
	//3Dモデルをロードするための情報を設定する関数
	void Init(const char* tkmFilePath);

	//位置を設定するセット関数
	void SetPosition(const Vector3 pos) { m_pos = pos; }
	//位置を取得するゲット関数
	Vector3 GetPosition() { return m_pos; }
	//回転を設定するセット関数
	void SetRotation(const Quaternion rot) { m_rot = rot; }
	//拡大率を設定するセット関数
	void SetScale(const Vector3 sca) { m_sca = sca; }

	Model* GetModel() { return &m_model ; }

	//描画関数
	void Render(RenderContext& rc);
};