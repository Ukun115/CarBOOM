///<<summary>
///ライトをまとめているクラス
///</summary>


#include "stdafx.h"


namespace
{
	//ディレクションライト
	const Vector3 DIRLIG_DIR = { 0.0f, -1.0f ,0.0f };	//方向(真上から真下に落ちる)
	//スポットライト
	const Vector3 SPOLIG_POS = { 0.0f, 50.0f ,0.0f };	//位置
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//方向
	const float	  SPOLIG_RAN = 100.0f;					//影響範囲
	const float	  SPOLIG_ANG = 75.0f;					//射出角度
	//半球ライト
	const Vector3 HEMISPHERELIG_GROUNDCOLOR = {0.5,0.3,0.1};	//地面色
	const Vector3 HEMISPHERELIG_SKYCOLOR = {0.15,0.3,0.45};		//天球色
	const Vector3 HEMISPHERELIG_GROUNDNORMAL = {0.0,1.0,0.0};	//地面の法線
}


bool Light::Start()
{
	//視点の位置を設定する
	m_ligData.eyePos = g_camera3D->GetPosition();

	//Start関数のreturn文
	return true;
}


Light::~Light()
{

}


void Light::Update()
{

}


//ディレクションライトの方向,色を設定する関数
void Light::SetDirectionLightData()
{
	//ディレクションライトの方向を設定
	m_ligData.dirLigData.dirDirection = DIRLIG_DIR;
	//ディレクションライトを正規化して大きさ1のベクトルにする
	m_ligData.dirLigData.dirDirection.Normalize();
	//ディレクションライトの色を設定
	m_ligData.dirLigData.dirColor = GRAY;
}


//ポイントライトの座標,色,影響範囲を設定する関数
void Light::SetPointLightData(Vector3 position,Vector3 color,float range,int lignum)
{
		//ポイントライトの座標を設定
		m_ligData.poiLigData[lignum].ptPosition = position;
		//ポイントライトの色を設定
		m_ligData.poiLigData[lignum].ptColor = color;
		//ポイントライトの影響範囲を設定
		m_ligData.poiLigData[lignum].ptRange = range;
}


//スポットライトの座標,色,方向,射出範囲,射出角度を設定する関数
void Light::SetSpotLightData()
{
	//スポットライトの座標を設定
	m_ligData.spotLigData.spPosition = SPOLIG_POS;
	//スポットライトの色を設定
	m_ligData.spotLigData.spColor = WHITE;
	//スポットライトの方向を設定
	m_ligData.spotLigData.spDirection = SPOLIG_DIR;
	//方向データだから大きさを1にするために正規化をする
	m_ligData.spotLigData.spDirection.Normalize();
	//スポットライトの射出範囲を設定
	m_ligData.spotLigData.spRange = SPOLIG_RAN;
	//スポットライトの射出角度を設定
	//(デグリー単位(75度)からラジアン単位に変換した値を代入)
	m_ligData.spotLigData.spAngle = Math::DegToRad(SPOLIG_ANG);
}


//半球ライトの地面色（照り返しのライト）,天球色,地面の法線を設定する関数
void Light::SetHemiSphereLightData()
{
	//地面色を設定
	m_ligData.hemiSphereLigData.hemiGroundColor = HEMISPHERELIG_GROUNDCOLOR;
	//天球色を設定
	m_ligData.hemiSphereLigData.hemiSkyColor = HEMISPHERELIG_SKYCOLOR;
	//地面の法線を設定
	m_ligData.hemiSphereLigData.hemiGroundNormal = HEMISPHERELIG_GROUNDNORMAL;
}