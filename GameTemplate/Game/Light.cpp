#include "stdafx.h"


namespace
{
	const Vector3 DIRLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//ディレクションライトの初期方向
	const Vector3 DIRLIG_COL = { 1.0f, 1.0f ,1.0f };	//ディレクションライトの初期色

	const Vector3 SPOLIG_POS = { 0.0f, 0.0f ,0.0f };	//スポットライトの初期位置
	const Vector3 SPOLIG_COL = { 1.0f, 1.0f ,1.0f };	//スポットライトの初期色
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//スポットライトの初期方向
	const float	  SPOLIG_RAN = 100.0f;					//スポットライトの初期影響範囲
	const float	  SPOLIG_ANG = 75.0f;					//スポットライトの初期射出角度
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
	m_ligData.dirLigData.ligDirection = DIRLIG_DIR;
	//ディレクションライトを正規化して大きさ1のベクトルにする
	m_ligData.dirLigData.ligDirection.Normalize();
	//ディレクションライトの色を設定
	m_ligData.dirLigData.ligColor = DIRLIG_COL;
}

//ポイントライトの座標,色,影響範囲を設定する関数
void Light::SetPointLightData(Vector3 x,Vector3 y,float z)
{
	//ポイントライトの座標を設定
	m_ligData.poiLigData.ptPosition = x;
	//ポイントライトの色を設定
	m_ligData.poiLigData.ptColor = y;
	//ポイントライトの影響範囲を設定
	m_ligData.poiLigData.ptRange = z;
}

//スポットライトの座標,色,方向,射出範囲,射出角度を設定する関数
void Light::SetSpotLightData()
{
	//スポットライトの座標を設定
	m_ligData.spotLigData.spPosition = SPOLIG_POS;
	//スポットライトの色を設定
	m_ligData.spotLigData.spColor = SPOLIG_COL;
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