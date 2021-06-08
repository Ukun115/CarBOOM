#pragma once

//ポイントライトの構造体の定義
struct PoiLigData {
	Vector3 ptPosition;		//位置
	float pad;				//パディング
	Vector3 ptColor;		//カラー
	float ptRange;			//影響範囲
};

class PointLight : public IGameObject
{
private:

	// ポイントライトのデータを作成
	PoiLigData PointLig;

public:
	bool Start();
	~PointLight();
	void Update();

	void SetPointLightData();

	PoiLigData& GetData()
	{
		return PointLig;
	}
};