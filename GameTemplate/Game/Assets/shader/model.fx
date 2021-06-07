/*!
 * @brief	シンプルなモデルシェーダー。
 */

 ////////////////////////////////////////////////
 // 構造体
 ////////////////////////////////////////////////
 //スキニング用の頂点データをひとまとめ。
struct SSkinVSIn {
	int4  Indices  	: BLENDINDICES0;
	float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn {
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ディレクションライトのデータを受け取るための定数バッファ
cbuffer DirectionLightCb : register(b1)
{
	float3 ligDirection;	//ライトの方向
	float4 ligColor;		//ライトの色

	//視点のデータにアクセルするための変数を定数バッファに追加する
	float3 eyePos;			//視点の位置
};

//ポイントライトのデータを受け取るための定数バッファ
cbuffer PointLightCb : register(b2)
{
	float3 ptPosition;		//ライトの位置
	float3 ptColor;			//ライトの色
	float ptRange;			//ライトの影響範囲
}


////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
//モデルテクスチャ
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal = mul(m, vsIn.normal);//法線を回転させる

	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn )
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	///ディレクションライトのランバート拡散反射

	//ピクセルの法線とライトの方向の内積を計算する
	float t = dot(psIn.normal,ligDirection);
	//内積の結果に-1を乗算する
	t *= -1.0f;
	//内積の結果が0以下なら0にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - psIn.pos;
	//正規化して大きさ1のベクトルにする
	toEye = normalize(toEye);
	//ピクセルが受けている光を求める
	float3 diffuseLig = ligColor * t;

	//ランバート拡散反射
	float PI = 3.141592;
	diffuseLig /= PI;


	///ディレクションライトのフォン鏡面反射

	//反射ベクトルを求める
	float3 refVec = reflect(ligDirection, psIn.normal);
	//鏡面反射の強さを求める
	//dot関数を利用しrefVecとtoEyeの内積を求める
	t = dot(refVec, toEye);
	//内積の結果に-1を乗算する
	t *= -1.0f;
	//内積の結果が0以下なら0にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);
	//鏡面反射の光を求める
	float3 specularLig = ligColor * t;

	//拡散反射光と鏡面反射光を足し算して、最終的な光を求める
	float3 lig = diffuseLig + specularLig;

	//ライトのすべての要素を一律で底上げする。
	//ちょっと明るくしている（環境光）
	lig.x += 0.3f;
	lig.y += 0.3f;
	lig.z += 0.3f;

	//モデルのテクスチャを参照
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//テクスチャカラーに求めた光を乗算して最終出力カラーに光を乗算
	albedoColor.xyz *= lig;


	//これで途中までの光の当たり具合を返す。デバック用
	//return float4(specularLig, 1.0f);


	//最終カラーを返す
	return albedoColor;
}