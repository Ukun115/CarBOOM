#include "stdafx.h"

namespace
{
	const Vector3 DIRLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//ディレクションライトの初期方向
	const Vector3 DIRLIG_COL = { 1.0f, 1.0f ,1.0f };	//ディレクションライトの初期カラー

	const Vector3 SPOLIG_POS = { 0.0f, 0.0f ,0.0f };	//スポットライトの初期位置
	const Vector3 SPOLIG_COL = { 1.0f, 1.0f ,1.0f };	//スポットライトの初期カラー
	const Vector3 SPOLIG_DIR = { 1.0f, -1.0f ,-1.0f };	//スポットライトの初期方向
	const float	  SPOLIG_RAN = 100.0f;					//スポットライトの初期影響範囲
	const float	  SPOLIG_ANG = 75.0f;					//スポットライトの初期射出角度
}

bool Light::Start()
{
	//視点の位置を設定する
	m_ligdata.eyePos = g_camera3D->GetPosition();

	//ライトクラスの中のディレクションライトをセット
	//SetDirectionLightData();
	//ライトクラスの中のポイントライトをセット
	//SetPointLightData();
	//ライトクラスの中のスポットライトをセット
	//SetSpotLightData();

	//Start関数のreturn文
	return true;
}


Light::~Light()
{

}

void Light::Update()
{
	//スポットライトを動かしてみる処理(コメントアウト中)
	{
	//	//コントローラーでスポットライトを動かす。
	//	m_ligdata.spotLigData.spPosition.x -= g_pad[0]->GetLStickXF();
	//	m_ligdata.spotLigData.spPosition.z -= g_pad[0]->GetLStickYF();
	//	if (g_pad[0]->IsPress(enButtonB))//キーボード：K
	//	{
	//		m_ligdata.spotLigData.spPosition.y += 2.0f;
	//	}
	//	if (g_pad[0]->IsPress(enButtonX))//キーボード：L
	//	{
	//		m_ligdata.spotLigData.spPosition.y -= 2.0f;
	//	}
	//	//Y軸周りの回転クォータニオン
	//	static Quaternion qRotY;
	//	//Y軸周りの回転クォータニオンを計算する
	//	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
	//	//計算したクォータニオンでライトの方向を回す
	//	qRotY.Apply(m_ligdata.spotLigData.spDirection);
	//	//X軸周りの回転クォータニオン
	//	static Vector3 rotAxis;
	//	static Quaternion qRotX;
	//	//X軸周りの回転クォータニオンを計算する
	//	rotAxis.Cross(g_vec3AxisY, m_ligdata.spotLigData.spDirection);
	//	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
	//	//計算したクォータニオンでライトの方向を回す
	//	qRotX.Apply(m_ligdata.spotLigData.spDirection);
	}
}

void Light::SetDirectionLightData()
{
	//ディレクションライトの方向を設定
	m_ligdata.dirLigData.ligDirection = DIRLIG_DIR;
	//ディレクションライトを正規化して大きさ1のベクトルにする
	m_ligdata.dirLigData.ligDirection.Normalize();
	//ディレクションライトの色を設定
	m_ligdata.dirLigData.ligColor = DIRLIG_COL;
}

void Light::SetPointLightData(Vector3 x,Vector3 y,float z)
{
	//ポイントライトの座標を設定
	m_ligdata.poiLigData.ptPosition = x;
	//ポイントライトの色を設定
	m_ligdata.poiLigData.ptColor = y;
	//ポイントライトの影響範囲を設定
	m_ligdata.poiLigData.ptRange = z;
}

void Light::SetSpotLightData()
{
	//スポットライトの座標を設定
	m_ligdata.spotLigData.spPosition = SPOLIG_POS;
		//スポットライトの色を設定
	m_ligdata.spotLigData.spColor = SPOLIG_COL;
	//スポットライトの方向を設定
	m_ligdata.spotLigData.spDirection = SPOLIG_DIR;
	//方向データだから大きさを1にするために正規化をする
	m_ligdata.spotLigData.spDirection.Normalize();
	//スポットライトの射出範囲を設定
	m_ligdata.spotLigData.spRange = SPOLIG_RAN;
	//スポットライトの射出角度を設定
	//(デグリー単位(75度)からラジアン単位に変換した値を代入)
	m_ligdata.spotLigData.spAngle = Math::DegToRad(SPOLIG_ANG);
}