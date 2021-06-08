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

	float4 worldPos : TEXCOORD1;
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

//ライトのデータを受け取るための定数バッファ
cbuffer LightCb : register(b1)
{
	//ディレクションライト

	float3 dirLigDirection;	//ライトの方向
	float3 dirLigColor;		//ライトの色
	//視点のデータにアクセルするための変数を定数バッファに追加する
	float3 eyePos;			//視点の位置

	//ポイントライト

	float3 ptLigPosition;	//ライトの位置
	float3 ptLigColor;		//ライトの色
	float  ptLigRange;		//ライトの影響範囲

	//スポットライト

	float3 spLigPosition;		//ライトの位置
	float3 spLigColor;			//ライトの色
	float  spLigRange;			//ライトの射出範囲
	float3 spLigDirection;		//ライトの射出方向
	float  spLigAngle;			//ライトの射出角度
};


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
	psIn.worldPos = psIn.pos;
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
	float t = dot(psIn.normal,dirLigDirection);
	//内積の結果に-1を乗算する
	t *= -1.0f;
	//内積の結果が0以下なら0にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - psIn.worldPos;
	//正規化して大きさ1のベクトルにする
	toEye = normalize(toEye);
	//ピクセルが受けている光を求める
	float3 dirDiffuseLig = dirLigColor * t;

	//ランバート拡散反射
	float PI = 3.141592;
	dirDiffuseLig /= PI;


	///ディレクションライトのフォン鏡面反射

	//反射ベクトルを求める
	float3 refVec = reflect(dirLigDirection, psIn.normal);
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
	float3 dirSpecularLig = dirLigColor * t;


	///ポイントライトのランバート拡散反射とフォン鏡面反射

	//このサーフェイスに入射しているポイントライトの光の向きを計算する
	float3 ptligDir = psIn.worldPos - ptLigPosition;
	//正規化して大きさ1のベクトルにする
	ptligDir = normalize(ptligDir);
	//減衰なしのランバート拡散反射光を計算する
	//ピクセルの法線とライトの方向の内積を計算する
	t = dot(psIn.normal, ptligDir) * -1.0f;
	//内積の値を0以上の値にする
	t = max(0.0f, t);
	//ランバート拡散反射(距離減衰なし)の光を求める
	float3 ptDiffuseLig = ptLigColor * t;

	//反射ベクトルを求める
	refVec = reflect(ptligDir, psIn.normal);
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	toEye = eyePos - psIn.worldPos;
	//正規化して大きさ1のベクトルにする
	toEye = normalize(toEye);
	//鏡面反射の強さを求める
	t = dot(refVec, toEye);
	//鏡面反射の強さを0以上の数値にする
	t = max(0.0f, t);
	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);
	//フォン鏡面反射(距離減衰なし)の光を求める
	float3 ptSpecularLig = ptLigColor * t;

	//ポイントライトの距離減衰の計算

	//ポイントライトとの距離を計算する
	float3 distance = length(psIn.worldPos - ptLigPosition);
	//影響率は距離に比例して小さくなっていく
	float affect = 1.0f - 1.0f / ptLigRange * distance;
	//影響力がマイナスにならないようにする補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}
	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);
	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	ptDiffuseLig *= affect;
	ptSpecularLig *= affect;


	//スポットライトのランバート拡散反射とフォン鏡面反射

	//このサーフェイスに入射しているスポットライトの光の向きを計算する
	//ピクセルの座標-スポットライトの座標を計算
	float3 spligDir = psIn.worldPos - spLigPosition;
	// 正規化して大きさ1のベクトルにする
	spligDir = normalize(spligDir);
	// ピクセルの法線とライトの方向の内積を計算する
	t = dot(psIn.normal, spligDir) * -1.0f;
	// 内積の値を0以上の値にする
	t = max(0.0f, t);
	//ランバート拡散反射(距離減衰なし)の光を求める
	float3 spDiffuseLig = spLigColor* t;

	//反射ベクトルを求める
	refVec = reflect(spligDir, psIn.normal);
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	toEye = eyePos - psIn.worldPos;
	//正規化して大きさ1のベクトルにする
	toEye = normalize(toEye);
	//鏡面反射の強さを求める
	t = dot(refVec, toEye);
	//鏡面反射の強さを0以上の数値にする
	t = max(0.0f, t);
	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);
	//フォン鏡面反射(距離減衰なし)の光を求める
	float3 spSpecularLig = spLigColor * t;

	//スポットライトの距離減衰の計算

	//スポットライトとの距離を計算する
	distance = length(psIn.worldPos - spLigPosition);
	//影響率は距離に比例して小さくなっていく
	affect = 1.0f - 1.0f / spLigRange * distance;
	//影響力がマイナスにならないようにする補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}
	//影響の仕方を指数関数的にする
	affect = pow(affect, 3.0f);
	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	spDiffuseLig *= affect;
	spSpecularLig *= affect;

	//入射光と射出方向の角度を求める
	//dot関数を利用して内積を求める
	float angle = dot(spligDir, spLigDirection);
	//dot関数で求めた値をacos関数に渡して角度を求める
	angle = acos(angle);
	//角度による影響率を求める
	//角度に比例して小さくなっていく影響率を計算する
	affect = 1.0f - 1.0f / spLigAngle * angle;
	//影響力がマイナスにならないように補正をかける
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}
	//影響の仕方を指数関数的にする
	affect = pow(affect, 0.5f);
	//角度による影響率を反射光に乗算して、影響を弱める
	spDiffuseLig *= affect;
	spSpecularLig *= affect;


	//ディレクションライトの拡散反射光と鏡面反射光を足し算して、最終的な光を求める
	float3 lig = dirDiffuseLig + dirSpecularLig;
	//ポイントライトの拡散反射光と鏡面反射光を追加で足し算して、最終的な光を求める
	lig += ptDiffuseLig + ptSpecularLig;
	//スポットライトの拡散反射光と鏡面反射光を追加で足し算して、最終的な光を求める
	lig += spDiffuseLig + spSpecularLig;


	//ライトのすべての要素を一律で底上げする。
	//ちょっと明るくしている（環境光(アンビエントライト)）
	lig.x += 0.3f;
	lig.y += 0.3f;
	lig.z += 0.3f;

	//モデルのテクスチャを参照
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//テクスチャカラーに求めた光を乗算して最終出力カラーに光を乗算
	albedoColor.xyz *= lig;


	//これで途中までの光の当たり具合を返す。デバック用
	//return float4(ptLigColor, 1.0f);


	//最終カラーを返す
	return albedoColor;
}