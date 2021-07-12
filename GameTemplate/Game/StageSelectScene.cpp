///<<summary>
///ステージ選択画面クラス
///</summary>


#include "stdafx.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "TitleScene.h"


namespace
{
	const int PLAYER1 = 0;		//プレイヤー１

	const Vector3 STAGE_1_POS = { 0, 0, 90 };
	const Vector3 STAGE_2_POS = { 170, 0, 90 };
	const Vector3 STAGE_3_POS = { 0, 0, -90 };
	const Vector3 STAGE_4_POS = { 350, 0, 90 };
	const Vector3 STAGE_5_POS = { 170, 0, -90 };
	const Vector3 STAGE_RANDOM_POS = { 350, 0, -90 };

	const Vector3 STAGE_1_NAME_POS = { 0, 0, 0 };
	const Vector3 STAGE_2_NAME_POS = { 240, 0, 0 };
	const Vector3 STAGE_3_NAME_POS = { 0, -250, 0 };
	const Vector3 STAGE_4_NAME_POS = { 490, 0, 0 };
	const Vector3 STAGE_5_NAME_POS = { 240, -250, 0 };
	const Vector3 STAGE_RANDOM_NAME_POS = { 490, -250, 0 };

	const Vector3 BIG_STAGE_NAME = { 1.5f,1.5f,1.5f };	//拡大したときのサイズ
}


bool StageSelectScene::Start()
{
	//インスタンスを作成
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);

	//ステージ説明の背景画像オブジェクト生成
	m_stageDiscription[0] = NewGO<SpriteRender>(PRIORITY_1, nullptr);

	//ステージセレクト文字画像オブジェクト生成
	m_stageSelectSprite = NewGO<SpriteRender>(PRIORITY_1, nullptr);

	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
	{
		//操作説明の画像オブジェクト生成
		m_operatorDiscription[stageNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		m_operatorDiscription[stageNum]->Init("Assets/Image/DDS/OperationDiscription.dds", 550, 550);
		//説明文字の表示位置を指定
		m_operatorDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);

		//ステージ説明の背景画像オブジェクト生成
		m_stageDiscription[stageNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		//全ステージモデルオブジェクト生成
		m_stage[stageNum] = NewGO<SkinModelRender>(PRIORITY_1, nullptr);
		//全ステージスプライトオブジェクト生成
		m_stageName[stageNum] = NewGO<SpriteRender>(PRIORITY_1, nullptr);
	}

	m_stageSelectSprite->Init("Assets/Image/DDS/STAGESELECT.dds", 750, 375);
	Vector3 m_stageSelectSpritePos = {0.0f,310.0f,0.0f};
	m_stageSelectSprite->SetPosition(m_stageSelectSpritePos);

	//ステージ説明のバックスクリーン画像
	m_stageDiscription[0]->Init("Assets/Image/DDS/StageDescriptionBackScreen.dds", 500, 600);
	Vector3 m_stageDiscriptionPos = {-400.0f,-20.0f,0.0f};
	m_stageDiscription[0]->SetPosition(m_stageDiscriptionPos);
	//フラットステージ説明文字
	m_stageDiscription[Stage1]->Init("Assets/Image/DDS/FlatStageDiscription.dds", 550, 550);
	//ドーナツステージ説明文字
	m_stageDiscription[Stage2]->Init("Assets/Image/DDS/DonutStageDescription.dds", 550, 550);
	//アイスステージ説明文字
	m_stageDiscription[Stage3]->Init("Assets/Image/DDS/IceStageDiscription.dds", 550, 550);
	//ウィンドステージ説明文字
	m_stageDiscription[Stage4]->Init("Assets/Image/DDS/WindStageDiscription.dds", 550, 550);
	//ティルトステージ説明文字
	m_stageDiscription[Stage5]->Init("Assets/Image/DDS/TiltStageDiscription.dds", 550, 550);
	//ランダムステージ説明文字
	m_stageDiscription[RandomStage]->Init("Assets/Image/DDS/RandomStageDiscription.dds", 550, 550);

	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
	{
		//位置を指定
		m_stageDiscription[stageNum]->SetPosition(m_stageDiscriptionLetterPos);
		m_stageDiscription[stageNum]->Deactivate();
	}

	//どひょうステージ&名前画像をロード
	m_stage[Stage1]->Init("Assets/modelData/bg/stage_1_Select.tkm");
	m_stageName[Stage1]->Init("Assets/Image/DDS/FLAT STAGE.dds", 200, 100);
	//左上
	m_stagePos[Stage1] = STAGE_1_POS;
	m_stage[Stage1]->SetPosition(m_stagePos[Stage1]);
	m_stageName[Stage1]->SetPosition(STAGE_1_NAME_POS);

	//ドーナツステージ&名前画像をロード
	m_stage[Stage2]->Init("Assets/modelData/bg/stage_2_Select.tkm");
	m_stageName[Stage2]->Init("Assets/Image/DDS/DONUT STAGE.dds", 200, 100);
	//右上
	m_stagePos[Stage2] = STAGE_2_POS;
	m_stage[Stage2]->SetPosition(m_stagePos[Stage2]);
	m_stageName[Stage2]->SetPosition(STAGE_2_NAME_POS);

	//アイスステージ&名前画像をロード
	m_stage[Stage3]->Init("Assets/modelData/bg/stage_3_Select.tkm");
	m_stageName[Stage3]->Init("Assets/Image/DDS/ICE STAGE.dds", 200, 100);
	//左下
	m_stagePos[Stage3] = STAGE_3_POS;
	m_stage[Stage3]->SetPosition(m_stagePos[Stage3]);
	m_stageName[Stage3]->SetPosition(STAGE_3_NAME_POS);

	//ウィンドステージ&名前画像をロード
	m_stage[Stage4]->Init("Assets/modelData/bg/stage_4_Select.tkm");
	m_stageName[Stage4]->Init("Assets/Image/DDS/WIND STAGE.dds", 200, 100);
	//右下
	m_stagePos[Stage4] = STAGE_4_POS;
	m_stage[Stage4]->SetPosition(m_stagePos[Stage4]);
	m_stageName[Stage4]->SetPosition(STAGE_4_NAME_POS);

	//ティルトステージ&名前画像をロード
	m_stage[Stage5]->Init("Assets/modelData/bg/stage_5_Select.tkm");
	m_stageName[Stage5]->Init("Assets/Image/DDS/TILT STAGE.dds", 200, 100);
	//右真ん中
	m_stagePos[Stage5] = STAGE_5_POS;
	m_stage[Stage5]->SetPosition(m_stagePos[Stage5]);
	m_stageName[Stage5]->SetPosition(STAGE_5_NAME_POS);

	//ランダムステージ&名前画像をロード
	m_stage[RandomStage]->Init("Assets/modelData/bg/stage_random.tkm");
	m_stageName[RandomStage]->Init("Assets/Image/DDS/RANDOM.dds", 200, 100);
	//右下
	m_stagePos[RandomStage] = STAGE_RANDOM_POS;
	m_stage[RandomStage]->SetPosition(m_stagePos[RandomStage]);
	m_stageName[RandomStage]->SetPosition(STAGE_RANDOM_NAME_POS);

	//プレイヤーモデルオブジェクト生成
	//文字画像の上に乗るようにプライオリティーは１つ文字画像よりも高くする
	m_pla = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
	m_pla->Init("Assets/modelData/LowPoly_PlayerCar_Red.tkm");	//赤車
	//初期位置設定
	m_pla->SetPosition(Vector3::Zero);

	//デバック用のプレイヤースピードの矢印表示
	//m_skinModelRenderArrow = NewGO<SkinModelRender>(PRIORITY_2, nullptr);
	//m_skinModelRenderArrow->Init("Assets/modelData/Arrow.tkm");	//矢印


	m_AhukidasiPos[0] = { 0, 200, 0 };//フラット
	m_AhukidasiPos[1] = { 235, 200, 0 };//ドーナツ
	m_AhukidasiPos[2] = { 0, -50, 0 };//アイス
	m_AhukidasiPos[3] = { 490, 200, 0 };//ウィンド
	m_AhukidasiPos[4] = { 235, -50, 0 };//ティルト
	m_AhukidasiPos[5] = { 490, -50, 0 };//ランダム
	//プレイヤーの上に表示されるA吹き出し
	for (int stageNum = 0; stageNum < 6; stageNum++)
	{
		m_Ahukidasi[stageNum] = NewGO<SpriteRender>(PRIORITY_2, nullptr);
		m_Ahukidasi[stageNum]->Init("Assets/Image/DDS/Ahukidasi.dds", 100, 100);
		m_Ahukidasi[stageNum]->Deactivate();
		m_Ahukidasi[stageNum]->SetPosition(m_AhukidasiPos[stageNum]);
	}

	//オブジェクト生成(背景画像)
	m_titleSprite = NewGO<SpriteRender>(PRIORITY_0, nullptr);
	m_titleSprite->Init("Assets/image/DDS/BackScreenImage.dds", 1600.0f, 800.0f);

	//タイトルBGMサウンド
	SoundPlayBack(TitleSceneBGM);

	//Start関数のreturn文
	return true;
}


StageSelectScene::~StageSelectScene()
{
	//表示されているステージモデルとステージ名画像をすべて削除
	for (int stageNum = 0; stageNum < TotalStageNum; stageNum++)
	{
		DeleteGO(m_stage[stageNum]);
		DeleteGO(m_stageName[stageNum]);
	}
	//プレイヤーを削除。
	DeleteGO(m_pla);
	//プレイヤーのスピード可視化矢印を削除。
	//DeleteGO(m_skinModelRenderArrow);
	//背景画像を削除
	DeleteGO(m_titleSprite);
	//A吹き出し画像を削除
	for (int plaNum = 0; plaNum < 6; plaNum++)
	{
		DeleteGO(m_Ahukidasi[plaNum]);
	}
	//タイトルBGMを削除
	DeleteGO(m_titleBGM);
	//ステージ選択文字画像
	DeleteGO(m_stageSelectSprite);

	for (int i = 0; i < 6; i++)
	{
		//ステージ説明の画像を削除
		DeleteGO(m_stageDiscription[i]);
		//操作説明がぞうを削除
		DeleteGO(m_operatorDiscription[i]);
	}
}


void StageSelectScene::Update()
{
	if (m_enableUpdateFlg == true)
	{
		//ベクトルを可視化させるデバック関数
		//PlaMooveSpeedDebug();
		//クラクションを鳴らす関数
		CarHorn();
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
	if (g_pad[PLAYER1]->IsPress(enButtonA))
	{
		//決定サウンド
		SoundPlayBack(DecideSound);

		//ランダムステージが選ばれていたら、
		if (m_stageNum == RandomStage)
		{
			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			//現在存在するステージの中からランダムで選ぶ
			m_stageNum = ((rand() % 5)+Stage1);
		}

		//ゲーム画面に遷移
		NewGO<GameScene>(PRIORITY_0, GAMESCENE_NAME);

		//表示されているステージモデルとステージ名画像をすべて削除
		for (int stageNum = 0; stageNum < TotalStageNum; stageNum++)
		{
			DeleteGO(m_stage[stageNum]);
			DeleteGO(m_stageName[stageNum]);
		}
		//プレイヤーを削除。
		DeleteGO(m_pla);
		//プレイヤーのスピード可視化矢印を削除。
		//DeleteGO(m_skinModelRenderArrow);
		//背景画像を削除
		DeleteGO(m_titleSprite);
		//A吹き出し画像を削除
		for (int plaNum = 0; plaNum < 6; plaNum++)
		{
			DeleteGO(m_Ahukidasi[plaNum]);
		}
		//タイトルBGMを削除
		DeleteGO(m_titleBGM);
		//ステージ選択文字画像
		DeleteGO(m_stageSelectSprite);

		for (int i = 0; i < 6; i++)
		{
			//ステージ説明の画像を削除
			DeleteGO(m_stageDiscription[i]);
			//操作説明がぞうを削除
			DeleteGO(m_operatorDiscription[i]);
		}

		//このクラスの処理をゲーム画面に移ったときに実行しなくなるフラグ
		m_enableUpdateFlg = false;
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
	m_moveSpeed.x = min(m_moveSpeed.x, 5.0f);//右方向の最大速度
	m_moveSpeed.x = max(m_moveSpeed.x, -5.0f);//左方向の最大速度

	m_moveSpeed.z = min(m_moveSpeed.z, 5.0f);//上方向の最大速度
	m_moveSpeed.z = max(m_moveSpeed.z, -5.0f);//下方向の最大速度
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
	//回転角度
	m_rotAngle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	m_rot.SetRotation(Vector3::AxisY, m_rotAngle);
}


//ステージの上にいるときそのステージを選択できる関数
void StageSelectScene::TouchStage()
{
	for (int stageNum = Stage1; stageNum < TotalStageNum; stageNum++)
	{
		//プレイヤーと各ステージとの距離を求める
		m_diff[stageNum] = m_stagePos[stageNum] - m_pos;

		//ステージの上に乗っていなかったら
		if (m_diff[stageNum].Length() >= 70.0f)
		{
			//全ての吹き出しを非表示
			m_Ahukidasi[stageNum-1]->Deactivate();
			//全てのステージ説明文字を非表示
			m_stageDiscription[stageNum]->Deactivate();


			if (m_isOperatorFlg[stageNum] == true)
			{
				//操作説明文表示
				m_operatorDiscription[stageNum]->Activate();
			}
			m_isOperatorFlg[stageNum] = false;

			//通常サイズ
			m_stageName[stageNum]->SetScale(Vector3::One);

			//音を鳴らせる！っていうフラグ復活！
			m_canOnStageSoundPlayFlg[stageNum] = true;
		}

		//ステージの上に乗っていたら
		if (m_diff[stageNum].Length() < 70.0f)
		{
			if (stageNum == 1)
			{
				//A吹き出しを表示
				m_Ahukidasi[0]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[Stage1]->Activate();
			}
			if (stageNum == 2)
			{
				//A吹き出しを表示
				m_Ahukidasi[1]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[Stage2]->Activate();
			}
			if (stageNum == 3)
			{
				//A吹き出しを表示
				m_Ahukidasi[2]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[Stage3]->Activate();
			}
			if (stageNum == 4)
			{
				//A吹き出しを表示
				m_Ahukidasi[3]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[Stage4]->Activate();
			}
			if (stageNum == 5)
			{
				//A吹き出しを表示
				m_Ahukidasi[4]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[Stage5]->Activate();
			}
			if (stageNum == 6)
			{
				//A吹き出しを表示
				m_Ahukidasi[5]->Activate();

				//ステージ説明文を表示
				m_stageDiscription[RandomStage]->Activate();
			}

			if (m_canOnStageSoundPlayFlg[stageNum])
			{
				//ステージを選択できるようになったら鳴らすサウンド
				SoundPlayBack(OnStageSound);

				m_canOnStageSoundPlayFlg[stageNum] = false;
			}

			for (int i = 1; i < 7; i++)
			{
				//操作説明文非表示
				m_operatorDiscription[i]->Deactivate();
			}

			//ステージ名画像を強調拡大
			m_stageName[stageNum]->SetScale(BIG_STAGE_NAME);

			m_isOperatorFlg[stageNum] = true;

			//選択されているステージの番号を決定。
			m_stageNum = stageNum;

			//ゲーム画面遷移処理関数
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


//ベクトルを可視化させるデバック関数
void StageSelectScene::PlaMooveSpeedDebug()
{
	Vector3 Dir = m_moveSpeed;
	Dir.y = 0;
	Dir.Normalize();//大きさを位置にする
	float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
	Dir.z *= -1;
	float angleX = acosf(x);//アークコサイン
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot.SetRotationY(angleX);//ｘ度だけY軸を回す
	m_skinModelRenderArrow->SetRotation(m_arrowRot);//角度を設定する
	m_arrowPos = m_pos;
	m_arrowPos.y += 30.0f;
	m_skinModelRenderArrow->SetPosition(m_arrowPos);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed.Length() / 5;
	m_skinModelRenderArrow->SetScale(m_arrowSize);
}


//クラクションを鳴らす関数
void StageSelectScene::CarHorn()
{
	//Xボタンが押されたとき再生
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		//クラクションサウンド
		SoundPlayBack(CarHornSound);
	}
}


//サウンドを一括にまとめる関数
void StageSelectScene::SoundPlayBack(int soundNum)
{
	switch (soundNum)
	{
	case TitleSceneBGM:
		//タイトルBGMサウンドの初期化
		m_titleBGM = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_titleBGM->Init(L"Assets/sound/TitleSceneBGM.wav");
		m_titleBGM->SetVolume(0.1f);
		m_titleBGM->Play(true);	//真でループ再生

		break;

	case DecideSound:
		//決定サウンド
		m_decideSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_decideSound->Init(L"Assets/sound/Decide.wav");
		m_decideSound->SetVolume(0.5f);
		m_decideSound->Play(false);	//偽でワンショット再生

		break;

	case OnStageSound:
		//ステージを選択できるようになったら鳴らすサウンドの初期化
		m_onStageSound = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_onStageSound->Init(L"Assets/sound/OnStage.wav");
		m_onStageSound->SetVolume(0.5f);
		m_onStageSound->Play(false);	//偽でワンショット再生

		break;

	case CarHornSound:
		//クラクションサウンドの初期化
		m_carHorn = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_carHorn->Init(L"Assets/sound/CarHorn.wav");
		m_carHorn->SetVolume(0.5f);
		m_carHorn->Play(false);	//偽でワンショット再生

		break;
	}
}