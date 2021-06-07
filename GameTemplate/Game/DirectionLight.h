#pragma once

//ディレクションライトの構造体の定義
struct DirLigData {
	Vector3 ligDirection;	//方向
	float pad1;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
	Vector3 ligColor; //= { 0.5f,0.5f,0.5f };		//色
	float pad2;

	Vector3 eyePos;			//視点の位置
};

class DirectionLight : public IGameObject
{
public:
	bool Start();
	~DirectionLight();
	void Update();

	/// <summary>
	/// ディレクションライトのデータを設定
	/// </summary>
	void SetDirectionData();

private:
	// ディレクションライトのデータを作成
	DirLigData directionLig;

public:
	DirLigData GetData()
	{
		return directionLig;
	}
};