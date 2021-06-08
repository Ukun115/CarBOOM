#include "stdafx.h"
#include "SpotLight.h"

bool SpotLight::Start()
{

	//Start関数のreturn文
	return true;
}

SpotLight::~SpotLight()
{

}

void SpotLight::Update()
{
	//コントローラーでスポットライトを動かす。
	SpotLig.spPosition.x -= g_pad[0]->GetLStickXF();
	SpotLig.spPosition.z -= g_pad[0]->GetLStickYF();
	if (g_pad[0]->IsPress(enButtonB))//キーボード：K
	{
		SpotLig.spPosition.y += 2.0f;
	}
	if (g_pad[0]->IsPress(enButtonX))//キーボード：L
	{
		SpotLig.spPosition.y -= 2.0f;
	}
	//Y軸周りの回転クォータニオンを計算する
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
	//計算したクォータニオンでライトの方向を回す
	qRotY.Apply(SpotLig.spDirection);
	//X軸周りの回転クォータニオンを計算する
	rotAxis.Cross(g_vec3AxisY, SpotLig.spDirection);
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
	//計算したクォータニオンでライトの方向を回す
	qRotX.Apply(SpotLig.spDirection);
}

void SpotLight::SetSpotLightData()
{
	//スポットライトの座標を設定
	SpotLig.spPosition.x = 0.0f;
	SpotLig.spPosition.y = 0.0f;
	SpotLig.spPosition.z = 50.0f;
	//スポットライトの色を設定
	SpotLig.spColor.x = 10.0f;
	SpotLig.spColor.y = 10.0f;
	SpotLig.spColor.z = 10.0f;
	//スポットライトの方向を設定
	SpotLig.spDirection.x = 1.0f;
	SpotLig.spDirection.y = -1.0f;
	SpotLig.spDirection.z = 1.0f;
	//方向データだから大きさを1にするために正規化をする
	SpotLig.spDirection.Normalize();
	//スポットライトの射出範囲を設定
	SpotLig.spRange = 300.0f;
	//スポットライトの射出角度を設定
	//(デグリー単位(25度)からラジアン単位(0.436332rad)に変換)
	SpotLig.spAngle = Math::DegToRad(25.0f);
}