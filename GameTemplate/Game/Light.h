#pragma once


//ディレクションライトの構造体の宣言
struct DirLigData {

	Vector3 ligDirection;	//方向
	float pad1;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
	Vector3 ligColor;		//色
	float pad2;				//パディング
};


//ポイントライトの構造体の宣言
struct PoiLigData {

	Vector3 ptPosition;		//位置
	float pad;				//パディング
	Vector3 ptColor;		//色
	float ptRange;			//影響範囲
};


//スポットライトの構造体の宣言
struct SpotLigData {

	Vector3 spPosition;		//位置
	float pad;				//パディング
	Vector3 spColor;		//色
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度
};


//ライト全体のデータ構造体の宣言
struct ligData {

	DirLigData  dirLigData;		//ディレクションライトの構造体データ
	PoiLigData  poiLigData;		//ポイントライトの構造体データ
	SpotLigData spotLigData;	//スポットライトの構造体データ

	Vector3 eyePos;				//視点の位置
};


class Light : public IGameObject
{
private:

	ligData m_ligData;		//ライト構造体のデータを作成

public:

	bool Start()override;
	~Light()override;
	void Update()override;


	/// <summary>
	/// セット関数
	/// </summary>
	//ディレクションライトの方向,色を設定する関数
	void SetDirectionLightData();
	//ポイントライトの座標,色,影響範囲を設定する関数
	void SetPointLightData(Vector3 x, Vector3 y, float z);
	//スポットライトの座標,色,方向,射出範囲,射出角度を設定する関数
	void SetSpotLightData();


	/// <summary>
	/// ゲット関数
	/// </summary>
	//ライトのデータを取得する関数
	ligData GetLight() {return m_ligData ; }
	//ライトのデータのアドレスを取得する関数
	ligData* GetLightAdoress() { return &m_ligData; }
};