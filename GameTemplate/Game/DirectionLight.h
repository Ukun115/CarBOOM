#pragma once

//ディレクションライトの構造体の定義
struct DirLigData {
	Vector3 ligDirection;	//方向
	float pad;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
	Vector4 ligColor;		//色

	//視点の位置
	Vector3 eyePos;
};

class DirectionLight
{
private:
	bool Start();
	~DirectionLight();
	void Update();

	// ディレクションライトのデータを作成
	DirLigData directionLig;
public:
};

