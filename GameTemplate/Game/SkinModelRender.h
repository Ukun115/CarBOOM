#pragma once
class Model;

class SkinModelRender : public IGameObject
{
private:

	bool Start();
	~SkinModelRender();
	void Update();

	Vector3    m_pos = Vector3::Zero;					//位置
	Quaternion m_rot = Quaternion::Identity;			//回転
	Vector3    m_sca = Vector3::One;					//拡大率

	//モデルを初期化するための情報を設定
	ModelInitData m_modelInitData;
	//m_modelはモデルクラス
	Model m_model;
	//ディレクションライトの構造体の中身を入れられる箱
	DirLigData* m_dirLigData = nullptr;

public:
	//3Dモデルをロードするための情報を設定する関数
	void Init(const char* tkmFilePath);

	//位置を設定するセット関数
	void SetPosition(Vector3 pos) { m_pos = pos; }
	//回転を設定するセット関数
	void SetRotation(Quaternion rot) { m_rot = rot; }
	//拡大率を設定するセット関数
	void SetScale(Vector3 sca) { m_sca = sca; }

	//描画関数
	void Render(RenderContext& rc);

	//ディレクションライトクラスの構造体の中の情報をm_dirLigDataにセット
	void SetDirLigData(DirLigData& ligData) { m_dirLigData = &ligData; }
};