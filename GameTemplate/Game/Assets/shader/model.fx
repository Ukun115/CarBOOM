/*!
 * @brief	シンプルなモデルシェーダー。
 */
 ///////////////////////////////////////////////
 //定数
 ///////////////////////////////////////////////
static const int ENEMY_POINT_LIGHT = 12;


////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos 	: TEXCOORD1;
	float3 normalInView : TEXCOORD2;	//カメラ空間の法線
};

//ディレクションライト
struct DirectionLight
{
	float3 direction;	//方向
	float3 color;		//色
};

//ポイントライト
struct PointLight
{
	float3 position;	//位置
	float3 color;		//色
	float Range;		//影響範囲
};

//スポットライト
struct SpotLight
{
	float3 position;	//位置
	float3 color;		//色
	float Range;		//射出範囲
	float3 direction;	//射出方向
	float angle;		//射出角度
};

//半球ライト
struct HemiSphereLight
{
	float3 groundColor;		//地面色（照り返しのライト）
	float3 skyColor;		//天球色
	float3 groundNormal;	//地面の法線
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

//全部のライト
cbuffer LightCb : register(b1)
{
	DirectionLight directionLight;				//ディレクションライト
	PointLight pointLight[ENEMY_POINT_LIGHT];	//ポイントライト
	SpotLight spotLight;						//スポットライト
	HemiSphereLight hemiSphereLight;			//半球ライト
	float3 eyePos;								//視点の位置
	//float3 ambientLight;						//環境光
};

////////////////////////////////////////////////
//関数宣言
////////////////////////////////////////////////
//拡散反射光の計算
float3 CalculateLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
//鏡面反射光の計算
float3 CalculatePhoneSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
//距離による影響率の計算
float CalculateImpactRate(float3 ligPos, float ligRange, float3 worldPos);
//リムライトの計算
float3 CalculateRimlight(float3 lightDirection, float3 lightColor, float3 normal, float normalInViewZ);

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
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
    for (int i1 = 0; i1 < 3; i1++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i1]] * skinVert.Weights[i1];
        w += skinVert.Weights[i1];
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

	psIn.normal = mul(mWorld, vsIn.normal); // 法線を回転させる。
	psIn.uv = vsIn.uv;

	psIn.normalInView = mul(mView,psIn.normal);	//カメラ空間の法線を求める

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
	//法線カラーを返すデバック。
	//return float4(psIn.normal,1.0f);


	//ディレクションライト用

	float3 diffDirection = CalculateLambertDiffuse(
		directionLight.direction,
		directionLight.color,
		psIn.normal
	);

	float3 specDirection = CalculatePhoneSpecular(
		directionLight.direction,
		directionLight.color,
		psIn.worldPos,
		psIn.normal
	);

	float3 finalDirectionLig = diffDirection+specDirection;


	//ポイントライト用
	float pAffect[ENEMY_POINT_LIGHT];
	float3 finalPointLig = { 0.0f,0.0f,0.0f };
	for (int ptLigNo = 0; ptLigNo < ENEMY_POINT_LIGHT; ptLigNo++)
	{
		//サーフェイスに入射するポイントライトの光の向きを計算する。
		float3 ligDir = psIn.worldPos - pointLight[ptLigNo].position;
		//正規化する。
		ligDir = normalize(ligDir);

		//減衰なしのランバート拡散反射光を計算する。
		float3 diffPoint = CalculateLambertDiffuse(
			ligDir,
			pointLight[ptLigNo].color,
			psIn.normal
		);

		//減衰なしのフォン鏡面反射光を計算する。
		float3 specPoint = CalculatePhoneSpecular(
			ligDir,
			pointLight[ptLigNo].color,
			psIn.worldPos,
			psIn.normal
		);

		//距離による影響率を計算する。
		pAffect[ptLigNo] = CalculateImpactRate(pointLight[ptLigNo].position, pointLight[ptLigNo].Range, psIn.worldPos);

		//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
		diffPoint *= pAffect[ptLigNo];
		specPoint *= pAffect[ptLigNo];

		finalPointLig += diffPoint + specPoint;
	}

	//ポイントライトカラーを返すデバック。
	//return float4(finalPointLig,1.0f);

	//スポットライト用

	float3 finalSpotLig = {0.0f,0.0f,0.0f};
	float aAffect;
	//サーフェイスに入射するポイントライトの光の向きを計算する。
	float3 sLigDir = psIn.worldPos - spotLight.position;
	//正規化する。
	sLigDir = normalize(sLigDir);

	//減衰なしのランバート拡散反射光を計算する。
	float3 diffSpot =  CalculateLambertDiffuse(
		sLigDir,
		spotLight.color,
		psIn.normal
	);

	//減衰なしのフォン鏡面反射光を計算する。
	float3 specSpot = CalculatePhoneSpecular(
		sLigDir,
		spotLight.color,
		psIn.worldPos,
		psIn.normal
	);

	//距離による影響率を計算する。
	float sAffect = CalculateImpactRate(spotLight.position,spotLight.Range,psIn.worldPos);

	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める。
	diffSpot *= sAffect;
	specSpot *= sAffect;


	//入射光と射出方向の角度を求める。
	//dot()を利用して内積を求める。
	float sAngle = dot(sLigDir,spotLight.direction);
	//dot()で求めた値をacosに渡して角度を求める。
	sAngle = acos(sAngle);

	//角度による影響率を求める。
	//角度に比例して小さくなっていく影響率を計算する。
	aAffect = 1.0f - 1.0f / spotLight.angle * sAngle;
	//影響力がマイナスにならないように補正をかける。
	aAffect = max(0.0f,aAffect);
	//影響の仕方を指数関数的にする。
	aAffect = pow(aAffect,3.0f);

	diffSpot *= aAffect;
	specSpot *= aAffect;

	finalSpotLig += diffSpot + specSpot;



	//拡散反射光・鏡面反射光・環境光を加算して最終的な光を求める。
	float3 lig = finalDirectionLig + finalPointLig + finalSpotLig;

	//リムライト

	float3 dirLim =  CalculateRimlight(
		directionLight.direction,
		directionLight.color,
		psIn.normal,
		psIn.normalInView.z
	);
	lig += dirLim;

		float3 spotLim = CalculateRimlight(
			spotLight.direction,
			spotLight.color,
			psIn.normal,
			psIn.normalInView.z
		);
		spotLim *= aAffect;
		lig += spotLim;



	//半球ライトを計算する。
	//サーフェイスの法線と地面の法線との内積を計算する。
	float hLigT = dot(psIn.normal,hemiSphereLight.groundNormal);

	//内積の結果を0~1の範囲に変換する。
	hLigT = (hLigT + 1.0f) / 2.0f;

	//地面色と天球色を補完率hLigTで線形補完する。
	float3 hemiLight = lerp(hemiSphereLight.groundColor,hemiSphereLight.skyColor,hLigT);

	//半球ライトを最終的な反射光に加算する。
	lig += hemiLight;

	//最終的なカラーを確定。
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//テクスチャカラーに求めた光を乗算して最終出力カラーを求める。
	albedoColor.xyz *= lig;

	return albedoColor;
}


//関数

float3 CalculateLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	//ピクセルの法線とライトの方向の内積を計算する。
	float t = dot(normal,lightDirection);

	//内積の結果に-1を乗算する。
	t *= -1.0f;

	//内積の結果が0以下なら0にする。
	t = max(0.0f, t);

	//拡散反射光を求める。
	return lightColor * t;
}

float3 CalculatePhoneSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
//反射ベクトルを求める。
	float3 refVec = reflect(lightDirection,normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める。
	float3 toEye = eyePos - worldPos;
	//正規化する。
	toEye = normalize(toEye);

	//鏡面反射の強さを求める。
	//dot関数を利用してrefVecとtoEyeの内積を求める。
	float t = dot(refVec,toEye);
	//内積の結果はマイナスになるので、マイナスの場合は0にする。
	t = max(0.0f, t);

	//鏡面反射の強さを絞る。
	t = pow(t,3.0f);

	//鏡面反射光を求める。
	return directionLight.color * t;
}

float CalculateImpactRate(float3 ligPos, float ligRange, float3 worldPos)
{
	//距離による影響率を計算する。
	//ポイントライトとの距離を計算する。
	float3 lDistance = length(worldPos - ligPos);

	//影響率は距離に比例して小さくなっていく。
	float lAffect = 1.0f - 1.0f / ligRange * lDistance;

	//影響力がマイナスにならないように補正をかける。
	lAffect = max(0.0, lAffect);

	//影響を指数関数的にする。
	lAffect = pow(lAffect,1.0f);
	return lAffect;
}

float3 CalculateRimlight(float3 lightDirection, float3 lightColor, float3 normal, float normalInViewZ)
{
	//サーフェイスの法線と光の入射方向に依存するリムの強さを求める。
	float power1 = 1.0f - max(0.0f,dot(lightDirection,normal));

	//サーフェイスの法線と視線の方向に依存するリムの強さを求める。
	float power2 = 1.0f - max(0.0f,normalInViewZ * -1.0f);

	//最終的なリムの強さを求める。
	float limPower = power1* power2;

	//pow()を使用して、強さの変化を指数関数的にする。
	limPower = pow(limPower,0.5f);

	//最終的な反射光にリムライトの反射光を合算する。
	//まずはリムライトのカラーを計算する。
	float3 limColor = limPower * lightColor;

	return limColor;
}