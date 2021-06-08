#include "stdafx.h"
#include "SkinModelRender.h"



bool SkinModelRender::Start()
{


	//Start関数のreturn
	return true;
}

SkinModelRender::~SkinModelRender()
{

}

void SkinModelRender::Update()
{
	//ディレクションライトのデータを取得
	m_ligData.dirLigData = m_directionLight->GetData();
	//ポイントライトのデータを取得
	m_ligData.poiLigData = m_pointLight->GetData();
	//スポットライトのデータを取得
	m_ligData.spotLigData = m_spotLight->GetData();
	//モデルの位置、回転、拡大を更新
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
}

void SkinModelRender::Init(const char* tkmFilePath)
{

	m_directionLight = FindGO<DirectionLight>("directionlight");
	m_pointLight = FindGO<PointLight>("pointlight");
	m_spotLight = FindGO<SpotLight>("spotlight");

	//ディレクションライトクラスのオブジェクトが所持しているライトの構造体データを
	//このオブジェクトが所持している構造体データに渡す。
	m_ligData.dirLigData = m_directionLight->GetData();

	//ポイントライトクラスのオブジェクトが所持しているライトの構造体データを
	//このオブジェクトが所持している構造体データに渡す。
	m_ligData.poiLigData = m_pointLight->GetData();

	//スポットライトクラスのオブジェクトが所持しているライトの構造体データを
	//このオブジェクトが所持している構造体データに渡す。
	m_ligData.spotLigData = m_spotLight->GetData();

	//tkmファイルのファイルパスを設定する。
	m_modelInitData.m_tkmFilePath = tkmFilePath;
	//使用するシェーダーファイルパスを設定する。
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	//モデルの初期化情報を定数バッファとしてディスクリプタヒープに
	//登録するためにモデルの初期化情報として渡す。
	m_modelInitData.m_expandConstantBuffer = &m_ligData;
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_ligData);
	//初期化情報を使ってモデル表示処理を初期化する
	m_model.Init(m_modelInitData);
}

void SkinModelRender::Render(RenderContext& rc)
{
	//モデルのドローコールを実行し、表示する
	m_model.Draw(rc);
}