#include "stdafx.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"


namespace
{
	const int PRIORITY_0 = 0;	//優先度0
	const int Stage1 = 0;		//プレイヤー１

	const Vector3 STAGE_1_POS = { -120, 0, 100 };
	const Vector3 STAGE_2_POS = { 120, 0, 100 };
	const Vector3 STAGE_3_POS = { -120, 0, -100 };
	const Vector3 STAGE_RANDOM_POS = { 120, 0, -100 };
}


bool StageSelectScene::Start()
{
	//インスタンスを作成
	m_titleScene = FindGO<TitleScene>("titlescene");

	for (int i = Stage1; i < TotalStageNum; i++)
	{
		//全ステージモデルオブジェクト生成
		m_stage[i] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);
		//大きさ調整
		m_stage[i]->SetScale({ 0.3,0.3,0.3 });
	}
	//どひょうステージをロード
	m_stage[Stage1]->Init("Assets/modelData/bg/stage_00.tkm");
	//左上
	m_stagePos[Stage1] = STAGE_1_POS;
	m_stage[Stage1]->SetPosition(m_stagePos[Stage1]);
	//ドーナツステージをロード
	m_stage[Stage2]->Init("Assets/modelData/bg/stage_00.tkm");
	//右上
	m_stagePos[Stage2] = STAGE_2_POS;
	m_stage[Stage2]->SetPosition(m_stagePos[Stage2]);
	//つるつるステージをロード
	m_stage[Stage3]->Init("Assets/modelData/bg/stage_00.tkm");
	//左下
	m_stagePos[Stage3] = STAGE_3_POS;
	m_stage[Stage3]->SetPosition(m_stagePos[Stage3]);
	//ランダムステージをロード
	m_stage[RandomStage]->Init("Assets/modelData/bg/stage_00.tkm");
	//右下
	m_stagePos[RandomStage] = STAGE_RANDOM_POS;
	m_stage[RandomStage]->SetPosition(m_stagePos[RandomStage]);

	//プレイヤーモデルオブジェクト生成
	m_pla = NewGO<SkinModelRender>(PRIORITY_0, nullptr);
	m_pla->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
	//初期位置設定
	m_pla->SetPosition({ 0.0f,0.0f,0.0f });
	//拡大
	m_pla->SetScale({1.5f,1.5f,1.5f});


	//Start関数のreturn文
	return true;
}


StageSelectScene::~StageSelectScene()
{

}


void StageSelectScene::Update()
{
	if (m_isCanGameStartFlg == true)
	{
		//プレイヤーの回転処理
		PlaTurn();
		//プレイヤーの通常移動処理
		PlaMove();
		//プレイヤーの移動速度に補正を入れる
		PlaSpeedCorrection();
		//プレイヤーが画面外に行かないようにする
		AvoidScreenOutSide();
		//プレイヤーの位置,回転の情報を更新する
		PlaDataUpdate();
		//ステージの上にいるときそのステージを選択できる関数
		TouchStage();
	}
}


//ゲーム画面遷移処理関数
void StageSelectScene::GameSceneTransition()
{
	//Aボタンが押されたら、
	if (g_pad[0]->IsPress(enButtonA))
	{
		//ランダムステージが選ばれていたら、
		if (m_stageNum == RandomStage)
		{
			//現在存在するステージの中からランダムで選ぶ
			m_stageNum = rand() % 3;
		}

		//ゲーム画面に遷移
		NewGO<GameScene>(PRIORITY_0, "gamescene");

		//表示されているステージモデルをすべて削除
		for (int i = 0; i < TotalStageNum; i++)
		{
			DeleteGO(m_stage[i]);
		}
		//プレイヤーを削除。
		DeleteGO(m_pla);

		m_isCanGameStartFlg == false;
	}
}


//プレイヤーの位置,回転の情報を更新する関数
void StageSelectScene::PlaDataUpdate()
{
	//位置をセット
	m_pla->SetPosition(m_pos);
	//回転をセット
	m_pla->SetRotation(m_rot);
}


//プレイヤーの通常移動処理関数
void StageSelectScene::PlaMove()
{
	//左スティックの入力量を加算する
	m_moveSpeed.x += m_leftStick_x * 10.0f * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed.z += m_leftStick_y * 10.0f * g_gameTime->GetFrameDeltaTime();

	//摩擦力を設定する
	m_friction = m_moveSpeed;
	m_friction *= -2.0f;

	//摩擦力を加算する
	m_moveSpeed.x += m_friction.x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed.z += m_friction.z * g_gameTime->GetFrameDeltaTime();

	m_pos += m_moveSpeed;
}


//プレイヤーの移動速度に補正を入れる関数
void StageSelectScene::PlaSpeedCorrection()
{
	//スピードの補正
	if (m_moveSpeed.x > 5.0f) {
		m_moveSpeed.x = 5.0f;	//右方向の最大速度
	}
	if (m_moveSpeed.x < -5.0f) {
		m_moveSpeed.x = -5.0f;	//左方向の最大速度
	}
	if (m_moveSpeed.z > 5.0f) {
		m_moveSpeed.z = 5.0f;	//上方向の最大速度
	}
	if (m_moveSpeed.z < -5.0f) {
		m_moveSpeed.z = -5.0f;	//下方向の最大速度
	}
}


//プレイヤーの回転処理関数
void StageSelectScene::PlaTurn()
{
	//左スティックの入力量を受け取る
	m_leftStick_x = g_pad[0]->GetLStickXF();
	m_leftStick_y = g_pad[0]->GetLStickYF();

	//移動してないときは回転しない
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//移動してないときは回転しない
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	m_rot.SetRotation(Vector3::AxisY, m_rotAngle);
}


//ステージの上にいるときそのステージを選択できる関数
void StageSelectScene::TouchStage()
{
	for (int i = Stage1; i < TotalStageNum; i++)
	{
		//プレイヤーと各ステージとの距離を求める
		m_diff = m_stagePos[i] - m_pos;
		//ステージの上に乗っていたら、
		if (m_diff.Length() < 50.0f)
		{
			//選択されているステージの判定を決定。
			m_stageNum = i;

			//ゲーム画面遷移処理
			GameSceneTransition();
		}
	}
}


//プレイヤーが画面外に行かないようにする関数
void StageSelectScene::AvoidScreenOutSide()
{
	//右側の補正
	if (m_pos.x > 420.0f)
	{
		m_pos.x = 420.0f;
	}
	//左側の補正
	if (m_pos.x < -420.0f)
	{
		m_pos.x = -420.0f;
	}
	//上側の補正
	if (m_pos.z > 230.0f )
	{
		m_pos.z = 230.0f;
	}
	//下側の補正
	if (m_pos.z < -230.0f)
	{
		m_pos.z = -230.0f;
	}
}