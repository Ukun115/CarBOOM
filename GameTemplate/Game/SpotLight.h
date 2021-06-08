#pragma once

//スポットライトの構造体の定義
struct SpotLigData {
	Vector3 spPosition;		//位置
	float pad;				//パディング
	Vector3 spColor;		//カラー
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度
};

class SpotLight : public IGameObject
{
private:
	//Y軸周りの回転クォータニオン
	Quaternion qRotY;
	//X軸周りの回転クォータニオン
	Vector3 rotAxis;
	Quaternion qRotX;

	//スポットライトのデータを作成
	SpotLigData SpotLig;

public:
	bool Start();
	~SpotLight();
	void Update();


	void SetSpotLightData();

	SpotLigData& GetData()
	{
		return SpotLig;
	}
};

