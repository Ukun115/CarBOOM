#include "stdafx.h"
#include "PointLight.h"

bool PointLight::Start()
{
	//ポイントライトの座標を設定
	PointLig.ptPosition.x = 0.0f;
	PointLig.ptPosition.y = 50.0f;
	PointLig.ptPosition.z = 50.0f;
	//ポイントライトの色を設定
	PointLig.ptColor.x = 15.0f;
	PointLig.ptColor.y = 0.0f;
	PointLig.ptColor.z = 0.0f;
	//ポイントライトの影響範囲を設定
	PointLig.ptRange = 100.0f;

	//Start関数のreturn文
	return true;
}

PointLight::~PointLight()
{

}

void PointLight::Update()
{
	//コントローラーでポイントライトを動かす。
	PointLig.ptPosition.x -= g_pad[0]->GetLStickXF();
	if (g_pad[0]->IsPress(enButtonB))
	{
		PointLig.ptPosition.y += g_pad[0]->GetLStickYF();
	}
	else
	{
		PointLig.ptPosition.z -= g_pad[0]->GetLStickYF();
	}
}