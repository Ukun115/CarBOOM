#pragma once



//ディレクションライトの構造体の定義
struct DirLigData {
	Vector3 ligDirection;	//方向
	float pad1;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
	Vector3 ligColor;		//色
	float pad2;
};

//ポイントライトの構造体の定義
struct PoiLigData {
	Vector3 ptPosition;		//位置
	float pad;				//パディング
	Vector3 ptColor;		//カラー
	float ptRange;			//影響範囲
};

//スポットライトの構造体の定義
struct SpotLigData {
	Vector3 spPosition;		//位置
	float pad;				//パディング
	Vector3 spColor;		//カラー
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度
};


//ライト全体のデータ構造体
struct ligData {
	DirLigData  dirLigData;			//ディレクションライトの構造体データ
	PoiLigData  poiLigData;			//ポイントライトの構造体データ
	SpotLigData spotLigData;		//スポットライトの構造体データ

	Vector3 eyePos;			//視点の位置
};


class Light : public IGameObject
{
private:



public:
	bool Start()override;
	~Light()override;
	void Update()override;

	//ライトのデータを作成
	ligData m_ligdata;

	//ディレクションライトのデータを設定するセット関数
	void SetDirectionLightData();

	//ポイントライトのデータを設定するセット関数
	void SetPointLightData();

	//スポットライトのデータを設定するセット関数
	void SetSpotLightData();

	ligData GetLight() {return m_ligdata ; }
	ligData* GetLightAdoress() { return &m_ligdata; }
};

