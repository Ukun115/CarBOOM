#include "stdafx.h"


namespace
{

}


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
	//モデルの位置、回転、拡大を更新
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_sca);
}


//モデルを初期化する関数
void SkinModelRender::Init(const char* tkmFilePath)
{
	//インスタンスを探す
	m_light = FindGO<Light>(LIGHT_NAME);

	//tkmファイルのファイルパスを設定する
	m_modelInitData.m_tkmFilePath = tkmFilePath;
	//使用するシェーダーファイルパスを設定する
	m_modelInitData.m_fxFilePath = "Assets/shader/model.fx";
	/*モデルの初期化情報を定数バッファとしてディスクリプタヒープに
	  登録するためにモデルの初期化情報として渡す					*/
	m_modelInitData.m_expandConstantBuffer = m_light->GetLightAdoress();
	m_modelInitData.m_expandConstantBufferSize = sizeof(m_light->GetLight());
	//初期化情報を使ってモデル表示処理を初期化する
	m_model.Init(m_modelInitData);
}


//描画関数
void SkinModelRender::Render(RenderContext& rc)
{
	//モデルのドローコールを実行し、表示する
	m_model.Draw(rc);
}