#include "stdafx.h"
#include "DirectionLight.h"

bool DirectionLight::Start()
{

	//ディレクションライトの方向を設定
	directionLig.ligDirection.x = 1.0f;
	directionLig.ligDirection.y = -1.0f;
	directionLig.ligDirection.z = -1.0f;
	//ディレクションライトを正規化して大きさ1のベクトルにする
	directionLig.ligDirection.Normalize();
	//ディレクションライトの色を設定
	directionLig.ligColor.x = 0.5f;
	directionLig.ligColor.y = 0.5f;
	directionLig.ligColor.z = 0.5f;
	directionLig.ligColor.w = 1.0f;

	//視点の位置を設定する
	directionLig.eyePos = g_camera3D->GetPosition();

	//Start関数のreturn文
	return true;
}

DirectionLight::~DirectionLight()
{

}

void DirectionLight::Update()
{

}