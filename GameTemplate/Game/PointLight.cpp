#include "stdafx.h"
#include "PointLight.h"

bool PointLight::Start()
{

	//Start関数のreturn文
	return true;
}

PointLight::~PointLight()
{

}

void PointLight::Update()
{
	////コントローラーでポイントライトを動かす。
	//PointLig.ptPosition.x -= g_pad[0]->GetLStickXF();
	//PointLig.ptPosition.z -= g_pad[0]->GetLStickYF();
	//if (g_pad[0]->IsPress(enButtonB))//キーボード：K
	//{
	//	PointLig.ptPosition.y += 2.0f;
	//}
	//if (g_pad[0]->IsPress(enButtonX))//キーボード：L
	//{
	//	PointLig.ptPosition.y -= 2.0f;
	//}
}

void PointLight::SetPointLightData()
{
	//ポイントライトの座標を設定
	PointLig.ptPosition.x = 0.0f;
	PointLig.ptPosition.y = 0.0f;
	PointLig.ptPosition.z = 0.0f;
	//ポイントライトの色を設定
	PointLig.ptColor.x = 1.0f;
	PointLig.ptColor.y = 1.0f;
	PointLig.ptColor.z = 1.0f;
	//ポイントライトの影響範囲を設定
	PointLig.ptRange = 100;
}