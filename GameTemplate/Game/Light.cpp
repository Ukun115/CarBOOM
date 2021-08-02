///<<summary>
///ライト処理
///</summary>


#include "stdafx.h"


namespace nsCARBOOM
{
	namespace nsLight
	{
		//ディレクションライト
		const Vector3 DIRLIG_DIR = { nsStdafx::FLOAT_ZERO, -1.0f ,nsStdafx::FLOAT_ZERO };	//方向(真上から真下に落ちる)
		//スポットライト
		const Vector3 SPOLIG_POS = { nsStdafx::FLOAT_ZERO, 50.0f ,nsStdafx::FLOAT_ZERO };	//位置
		const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//方向
		const float	  SPOLIG_RAN = 100.0f;					//影響範囲
		const float	  SPOLIG_ANG = 75.0f;					//射出角度
		//半球ライト
		const Vector3 HEMISPHERELIG_GROUNDCOLOR = { 0.5f,0.3f,0.1f };	//地面色
		const Vector3 HEMISPHERELIG_SKYCOLOR = { 0.15f,0.3f,0.45f };		//天球色
		const Vector3 HEMISPHERELIG_GROUNDNORMAL = { 0.0f,1.0f,0.0f };	//地面の法線
	}


	bool Light::Start()
	{
		//視点の位置を設定する
		m_ligData.eyePos = g_camera3D->GetPosition();

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
		m_ligData.dirLigData.dirDirection = nsLight::DIRLIG_DIR;
		//ディレクションライトを正規化して大きさ1のベクトルにする
		m_ligData.dirLigData.dirDirection.Normalize();
		//ディレクションライトの色を設定
		m_ligData.dirLigData.dirColor = nsStdafx::GRAY;
	}


	//ポイントライトの座標,色,影響範囲を設定する関数
	void Light::SetPointLightData(const Vector3 position, const Vector3 color, const float range, const int lignum)
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
		m_ligData.spotLigData.spPosition = nsLight::SPOLIG_POS;
		//スポットライトの色を設定
		m_ligData.spotLigData.spColor = nsStdafx::WHITE;
		//スポットライトの方向を設定
		m_ligData.spotLigData.spDirection = nsLight::SPOLIG_DIR;
		//方向データだから大きさを1にするために正規化をする
		m_ligData.spotLigData.spDirection.Normalize();
		//スポットライトの射出範囲を設定
		m_ligData.spotLigData.spRange = nsLight::SPOLIG_RAN;
		//スポットライトの射出角度を設定
		//(デグリー単位(75度)からラジアン単位に変換した値を代入)
		m_ligData.spotLigData.spAngle = Math::DegToRad(nsLight::SPOLIG_ANG);
	}


	//半球ライトの地面色（照り返しのライト）,天球色,地面の法線を設定する関数
	void Light::SetHemiSphereLightData()
	{
		//地面色を設定
		m_ligData.hemiSphereLigData.hemiGroundColor = nsLight::HEMISPHERELIG_GROUNDCOLOR;
		//天球色を設定
		m_ligData.hemiSphereLigData.hemiSkyColor = nsLight::HEMISPHERELIG_SKYCOLOR;
		//地面の法線を設定
		m_ligData.hemiSphereLigData.hemiGroundNormal = nsLight::HEMISPHERELIG_GROUNDNORMAL;
	}
}