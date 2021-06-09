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

