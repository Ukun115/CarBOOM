#pragma once

//ディレクションライトの構造体の定義
struct DirLigData {
	Vector3 ligDirection;	//方向
	float pad1;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
	Vector3 ligColor;		//色
	float pad2;

	Vector3 eyePos;			//視点の位置
	float pad3;
};

class DirectionLight : public IGameObject
{
private:
	// ディレクションライトのデータを作成
	DirLigData directionLig;

public:
	bool Start();
	~DirectionLight();
	void Update();

	// ディレクションライトのデータを設定
	void SetDirectionLightData();

	DirLigData& GetData()
	{
		return directionLig;
	}
};