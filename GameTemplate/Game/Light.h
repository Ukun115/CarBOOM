#pragma once


namespace nsCARBOOM
{
	//ディレクションライト構造体の宣言
	struct DirLigData {

		Vector3 dirDirection;	//方向
		float pad1 = 0.0f;				//HLSL側の定数バッファのfloat3型(12個分)の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておき、埋め合わせをしておく。
		Vector3 dirColor;		//色
		float pad2 = 0.0f;				//パディング
	};


	//ポイントライト構造体の宣言
	struct PoiLigData {

		Vector3 ptPosition;		//位置
		float pad = 0.0f;				//パディング
		Vector3 ptColor;		//色
		float ptRange = 0.0f;			//影響範囲
	};


	//スポットライト構造体の宣言
	struct SpotLigData {

		Vector3 spPosition;		//位置
		float pad = 0.0f;				//パディング
		Vector3 spColor;		//色
		float spRange = 0.0f;			//影響範囲
		Vector3 spDirection;	//射出方向
		float spAngle = 0.0f;			//射出角度
	};


	//半球ライト構造体の宣言
	struct HemiSphereLight
	{
		Vector3 hemiGroundColor;	//地面色（照り返しのライト）
		float pad1 = 0.0f;				//パディング
		Vector3 hemiSkyColor;		//天球色
		float pad2 = 0.0f;				//パディング
		Vector3 hemiGroundNormal;	//地面の法線
		float pad3 = 0.0f;				//パディング
	};


	//ライト全体のデータ構造体の宣言
	struct ligData {

		DirLigData  dirLigData;					//ディレクションライト構造体データ
		PoiLigData  poiLigData[12];				//ポイントライト構造体データ
		SpotLigData spotLigData;				//スポットライト構造体データ
		HemiSphereLight hemiSphereLigData;		//半球ライト構造体データ

		Vector3 eyePos;				//視点の位置
		//Vector3 ambientLight;		//環境光
	};


	class Light : public IGameObject		//TODO:コピー禁止ポリシーを継承する。
	{
	private:

		ligData m_ligData;		//ライト構造体のデータを作成


		bool Start()override final;
		~Light()override final;
		void Update()override final;


	public:

		/// <summary>
		/// セッター
		/// </summary>
		//ディレクションライトの方向,色を設定する関数
		void SetDirectionLightData();
		//ポイントライトの座標,色,影響範囲を設定する関数
		void SetPointLightData(const Vector3 position, const Vector3 color, const float range, const int lignum);
		//スポットライトの座標,色,方向,射出範囲,射出角度を設定する関数
		void SetSpotLightData();
		//半球ライトの地面色（照り返しのライト）,天球色,地面の法線を設定する関数
		void SetHemiSphereLightData();


		/// <summary>
		/// ゲッター
		/// </summary>
		//ライトのデータを取得する関数
		ligData GetLight()const { return m_ligData; }
		//ライトのデータのアドレスを取得する関数
		ligData* GetLightAdoress() { return &m_ligData; }
	};
}