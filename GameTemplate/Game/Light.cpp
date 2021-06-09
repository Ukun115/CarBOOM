#include "stdafx.h"

bool Light::Start()
{


	//Start関数のreturn文
	return true;
}
Light::Light()
{
	//視点の位置を設定する
	m_ligdata.eyePos = g_camera3D->GetPosition();

	//ライトクラスの中のディレクションライトをセット
	SetDirectionLightData();
	//ライトクラスの中のポイントライトをセット
	SetPointLightData();
	//ライトクラスの中のスポットライトをセット
	SetSpotLightData();
}

Light::~Light()
{

}

void Light::Update()
{

	//スポットライトを動かしてみる処理
	{
		//コントローラーでスポットライトを動かす。
		m_ligdata.spotLigData.spPosition.x -= g_pad[0]->GetLStickXF();
		m_ligdata.spotLigData.spPosition.z -= g_pad[0]->GetLStickYF();
		if (g_pad[0]->IsPress(enButtonB))//キーボード：K
		{
			m_ligdata.spotLigData.spPosition.y += 2.0f;
		}
		if (g_pad[0]->IsPress(enButtonX))//キーボード：L
		{
			m_ligdata.spotLigData.spPosition.y -= 2.0f;
		}
		//Y軸周りの回転クォータニオンを計算する
		qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f);
		//計算したクォータニオンでライトの方向を回す
		qRotY.Apply(m_ligdata.spotLigData.spDirection);
		//X軸周りの回転クォータニオンを計算する
		rotAxis.Cross(g_vec3AxisY, m_ligdata.spotLigData.spDirection);
		qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.01f);
		//計算したクォータニオンでライトの方向を回す
		qRotX.Apply(m_ligdata.spotLigData.spDirection);
	}
}

void Light::SetDirectionLightData()
{
	//ディレクションライトの方向を設定
	m_ligdata.dirLigData.ligDirection.x = 1.0f;
	m_ligdata.dirLigData.ligDirection.y = -1.0f;
	m_ligdata.dirLigData.ligDirection.z = -1.0f;
	//ディレクションライトを正規化して大きさ1のベクトルにする
	m_ligdata.dirLigData.ligDirection.Normalize();
	//ディレクションライトの色を設定
	m_ligdata.dirLigData.ligColor.x = 1.0f;
	m_ligdata.dirLigData.ligColor.y = 1.0f;
	m_ligdata.dirLigData.ligColor.z = 1.0f;
}

void Light::SetPointLightData()
{
	//ポイントライトの座標を設定
	m_ligdata.poiLigData.ptPosition.x = 0.0f;
	m_ligdata.poiLigData.ptPosition.y = 0.0f;
	m_ligdata.poiLigData.ptPosition.z = 0.0f;
	//ポイントライトの色を設定
	m_ligdata.poiLigData.ptColor.x = 5.0f;
	m_ligdata.poiLigData.ptColor.y = 5.0f;
	m_ligdata.poiLigData.ptColor.z = 5.0f;
	//ポイントライトの影響範囲を設定
	m_ligdata.poiLigData.ptRange = 100;
}

void Light::SetSpotLightData()
{
	//スポットライトの座標を設定
	m_ligdata.spotLigData.spPosition.x = 0.0f;
	m_ligdata.spotLigData.spPosition.y = 0.0f;
	m_ligdata.spotLigData.spPosition.z = 50.0f;
	//スポットライトの色を設定
	m_ligdata.spotLigData.spColor.x = 10.0f;
	m_ligdata.spotLigData.spColor.y = 10.0f;
	m_ligdata.spotLigData.spColor.z = 10.0f;
	//スポットライトの方向を設定
	m_ligdata.spotLigData.spDirection.x = 1.0f;
	m_ligdata.spotLigData.spDirection.y = -1.0f;
	m_ligdata.spotLigData.spDirection.z = 1.0f;
	//方向データだから大きさを1にするために正規化をする
	m_ligdata.spotLigData.spDirection.Normalize();
	//スポットライトの射出範囲を設定
	m_ligdata.spotLigData.spRange = 300.0f;
	//スポットライトの射出角度を設定
	//(デグリー単位(75度)からラジアン単位に変換)
	m_ligdata.spotLigData.spAngle = Math::DegToRad(75.0f);
}