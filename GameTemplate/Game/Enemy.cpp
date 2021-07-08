///<<summary>
///敵NPC（パトカー）クラス
///</summary>


#include "stdafx.h"
#include "Stage.h"

#include<random>

#include "Enemy.h"
#include "Player.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "../../ExEngine/physics/CharacterController.h"		//キャラコンを使うためにインクルード
		//↑2階層上にディレクトリを移動してからフォルダを潜っている。


//TODO: 影を落とせるようにする


namespace
{
	const int RES_POS_NUM = 10;	//リスポーン位置の総数
	//敵の各リスポーン位置
	const Vector3 ENE_RES_POS_1 = { -150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_2 = { 0.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_3 = { 100.0f,150.0f,100.0f };
	const Vector3 ENE_RES_POS_4 = { -100.0f,150.0f,00.0f };
	const Vector3 ENE_RES_POS_5 = { 150.0f,150.0f,150.0f };
	const Vector3 ENE_RES_POS_6 = { 100.0f,150.0f,0.0f };
	const Vector3 ENE_RES_POS_7 = { -100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_8 = { 0.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_9 = { 100.0f,150.0f,-100.0f };
	const Vector3 ENE_RES_POS_10 = { 0.0f,150.0f,0.0f };

	const float POILIG_RANGE = 50.0f;	//ポイントライトの影響範囲

	const int TIME0 = 0;

	const Vector3 SHOOTDOWNEFFECT_SCALE = { 40.0f,40.0f,40.0f };

	//const float PI = 3.141592;	//円周率
}


bool Enemy::Start()
{
	//インスタンスを探す。
	m_titleScene = FindGO<TitleScene>(TITLESCENE_NAME);
	m_gameScene  = FindGO<GameScene>(GAMESCENE_NAME);
	m_player	 = FindGO<Player>(PLAYER_NAME);
	m_stageSelectScene = FindGO<StageSelectScene>(STAGESELECT_NAME);
	m_light = FindGO<Light>(LIGHT_NAME);
	m_stage = FindGO<Stage>("stage");

	//敵のリスポーン位置１～１０
	m_ranEneResPos[ResPos1] = ENE_RES_POS_1;
	m_ranEneResPos[ResPos2] = ENE_RES_POS_2;
	m_ranEneResPos[ResPos3] = ENE_RES_POS_3;
	m_ranEneResPos[ResPos4] = ENE_RES_POS_4;
	m_ranEneResPos[ResPos5] = ENE_RES_POS_5;
	m_ranEneResPos[ResPos6] = ENE_RES_POS_6;
	m_ranEneResPos[ResPos7] = ENE_RES_POS_7;
	m_ranEneResPos[ResPos8] = ENE_RES_POS_8;
	m_ranEneResPos[ResPos9] = ENE_RES_POS_9;
	if (m_stageSelectScene->GetStageNum() == STAGE2)
	{
		m_ranEneResPos[ResPos10] = ENE_RES_POS_10;
	}

	//リスポーン座標がプレイヤー1P～4Pの座標と同じにならないようにしないといけない。
	//【プレイヤーのリスポーン位置】
	// { -100.0f,0.0f,100.0f }		//1P
	// {  100.0f,150.0f, 100.0f }	//2P
	//{ -100.0f,150.0f,-100.0f }	//3P
	//{  100.0f,150.0f,-100.0f }	//4P

	m_randEneResAngle[0] = 1.0f;
	m_randEneResAngle[1] = 2.5f;
	m_randEneResAngle[2] = 3.7f;
	m_randEneResAngle[3] = 5.5f;
	m_randEneResAngle[4] = 0.5f;
	m_randEneResAngle[5] = 1.25f;
	m_randEneResAngle[6] = 1.85f;
	m_randEneResAngle[7] = 2.85f;

	//敵の最大数繰り返す
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		//敵モデルオブジェクト生成
		m_enemy[eneNum] = NewGO<SkinModelRender>(PRIORITY_0,nullptr);
		//モデルのファイルパスを設定
		m_enemy[eneNum]->Init("Assets/modelData/LowPoly_PoliceCar.tkm");	//敵モデル

		//デバック用の敵スピードの矢印表示
		//m_skinModelRenderArrow[eneNum] = NewGO<SkinModelRender>(PRIORITY_0, nullptr);

		//初期座標(リスポーン座標)の設定。
		if (eneNum == Enemy1)
		{
			m_enePos[Enemy1] = m_ranEneResPos[0];		//敵１の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		else if (eneNum == Enemy2)
		{
			m_enePos[Enemy2] = m_ranEneResPos[1];		//敵２の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		else if (eneNum == Enemy3)
		{
			m_enePos[Enemy3] = m_ranEneResPos[3];		//敵3の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		else if (eneNum == Enemy4)
		{
			m_enePos[Enemy4] = m_ranEneResPos[4];		//敵4の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		else if (eneNum == Enemy5)
		{
			m_enePos[Enemy5] = m_ranEneResPos[7];		//敵5の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		else if (eneNum == Enemy6)
		{
			m_enePos[Enemy6] = m_ranEneResPos[8];		//敵6の場所

			//m_skinModelRenderArrow[eneNum]->Init("Assets/modelData/Arrow.tkm");	//矢印
		}
		//当たり判定のイニシャライズ(初期化)
		m_charaCon[eneNum].Init(15.0f, 85.0f, m_enePos[eneNum]);
		//300～600の範囲のランダム値でスタート時の敵のDAを遅らせるタイマーの値に代入
		m_startDelay[eneNum] = (300 + (int)(rand() * (600 - 300 + 1.0) / (1.0 + RAND_MAX)));
		//120～140の範囲のランダム値でDA後のCTタイマーの値に代入
		m_eneCTCount[eneNum] = (120 + (int)(rand() * (140 - 120 + 1.0) / (1.0 + RAND_MAX)));
		//４で初期化。４は特にターゲット無し。
		m_pushPlayer[eneNum] = 4;

		//落下したときの撃墜エフェクトの初期化。
		m_shootDownEffect[eneNum].Init(u"Assets/effect/efk/Enemy_ShootDown.efk");
		//大きさ調整
		m_shootDownEffect[eneNum].SetScale(SHOOTDOWNEFFECT_SCALE);
		//通常だと画面の上がエフェクトの上になっているので、ゲーム中のカメラ方向が上になるように調整
		Quaternion m_shootDownEffectRot = m_shootDownEffect[eneNum].GetRotation();
		//↓【注意】関数内に入れるのはデグリー単位ではなくラジアン単位です。
		m_shootDownEffectRot.AddRotationX(-1.5708);	//X軸を基点に、-1.5708rad(-90°)回転
		m_shootDownEffect[eneNum].SetRotation(m_shootDownEffectRot);

		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8]; //敵の向き
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//回転情報更新
	}

	//Start関数のreturn文
	return true;
}


Enemy::~Enemy()
{
	//全ての敵を削除。
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		DeleteGO(m_enemy[eneNum]);
	}
}


void Enemy::Update()
{
	m_poiLigNum = 0;

	//全敵分ループ
	for (int eneNum = Enemy1; eneNum < MaxEnemyNum; eneNum++)
	{
		//落ちる時に落下音を鳴らせる処理
		SoundPlayBack(FallSound,eneNum);

		//制限時間が０秒になったらプレイヤーの処理を全て止める
		if (m_gameScene->GetNowTime() == TIME0)
		{
			continue;
		}
		//ゲーム開始のカウントダウンが終わるまでプレイヤーの処理をすべて止める
		if (!m_gameScene->GetCountDownFlg())
		{
			//重力の影響を与える
			Gravity(eneNum);

			//ベクトルを可視化させるデバック関数
			//EneMooveSpeedDebug(eneNum);

			//スタートした瞬間に敵がダッシュしてしまうのを回避する処理
			if (m_startDelayTimer < m_startDelay[eneNum])
			{
				//スタート時にDAを遅らせるタイマーを加算
				m_startDelayTimer++;
			}
			else
			{
				//回転処理
				EneTurn(eneNum);

				//風ステージの時風の影響を受ける処理
				WindPower(eneNum);

				//プレイヤーが敵とぶつかったとき敵に押される処理
				PlaAndEneClash(eneNum);

				//DA攻撃処理
				EneDA(eneNum);

				//キャラクターコントローラーを使った移動処理に変更。
				m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);

				//プレイヤーの座標をリスポーン座標に移動
				EneResporn(eneNum);

				//赤ポイントライトを設定
				m_enePoiLigPos = m_enePos[eneNum];
				m_enePoiLigPos.x -= 10.0f;
				m_enePoiLigPos.y += 10.0f;
				m_light->SetPointLightData(m_enePoiLigPos, RED, POILIG_RANGE, m_poiLigNum);
				m_poiLigNum++;
				//青ポイントライトを設定
				m_enePoiLigPos = m_enePos[eneNum];
				m_enePoiLigPos.x += 10.0f;
				m_enePoiLigPos.y += 10.0f;
				m_light->SetPointLightData(m_enePoiLigPos, BLUE, POILIG_RANGE, m_poiLigNum);
				m_poiLigNum++;

				m_enePos[eneNum] += m_moveSpeed[eneNum];
			}
		}
		else
		{
			//ベクトルを可視化させるデバック関数
			//EneMooveSpeedDebug(eneNum);

			//重力の影響を与える
			Gravity(eneNum);
			//キャラクターコントローラーを使った移動処理に変更。
			m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);
		}
		//敵の位置と回転情報を更新
		EneDataUpdate(eneNum);
	}
}


//敵の位置,回転情報を更新する関数
void Enemy::EneDataUpdate(int eneNum)
{
	m_enemy[eneNum]->SetRotation(m_rot[eneNum]);		//回転情報更新
	m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);	//位置情報更新
}


//敵から最寄りのプレイヤーを検索する関数
void Enemy::Distance(int eneNum)
{
	//登録されているプレイヤーの分処理をする
	for (int plaNum = 0; plaNum < m_titleScene->GetTotalPlaNum(); plaNum++)
	{
		//プレイヤーの位置を取得
		m_plaPos[plaNum] = m_player->GetPlaPos(plaNum);
		//プレイヤーの位置と敵の位置の距離を取得
		m_mostShortKyori[plaNum] = m_plaPos[plaNum] - m_enePos[eneNum];
	}

	//一番近い距離(m_mostShortKyori[0])のように並び替え(ソート)
	for (int plaNum = 0; plaNum < m_titleScene->GetTotalPlaNum() - 1; plaNum++) {
		for (int nextPlaNum = plaNum + 1; nextPlaNum < m_titleScene->GetTotalPlaNum(); nextPlaNum++) {
			if (m_mostShortKyori[nextPlaNum].Length() < m_mostShortKyori[plaNum].Length()) {
				//交換
				Vector3 tmp = m_mostShortKyori[nextPlaNum];
				m_mostShortKyori[nextPlaNum] = m_mostShortKyori[plaNum];
				m_mostShortKyori[plaNum] = tmp;
			}
		}
	}

	//一番近いプレイヤーから敵のベクトルを正規化して方向だけの情報にする
	m_mostShortKyori[0].Normalize();
}


//敵のDA処理関数
void Enemy::EneDA(int eneNum)
{
	if (!m_canCtCountFlg[eneNum]) {
		//距離設定
		Distance(eneNum);

		if (m_charaCon[eneNum].IsOnGround()) {
			//方向だけのm_mostShortKyori[0]に5.0fを掛けて速度にする
			m_moveSpeed[eneNum] = m_mostShortKyori[0] * 5.0f;
		}
		//ダッシュサウンド
		SoundPlayBack(DashSound,eneNum);

		m_canPlaAndEneClashSoundPlayFlg[eneNum] = true;

		//CTをカウントするフラグを立てる
		m_canCtCountFlg[eneNum] = true;
	}
	//CTフラグが立ってるとき、
	if (m_canCtCountFlg[eneNum]) {

		//CTをカウントする
		m_CTTime[eneNum]++;

		//摩擦を加えていく
		EneFriction(eneNum);
	}
	//CTのカウントが120秒～140秒のとき、
	if (m_CTTime[eneNum] == m_eneCTCount[eneNum]) {

		//CTフラグを下ろす
		m_canCtCountFlg[eneNum] = false;

		//CTのカウントを0にする
		m_CTTime[eneNum] = 0;
	}
}


//敵の回転処理関数
void Enemy::EneTurn(int eneNum)
{
	//fabsf()は浮動小数点の絶対値を返す関数
	if (fabsf(m_moveSpeed[eneNum].x) < 0.001f && fabsf(m_moveSpeed[eneNum].z) < 0.001f) {
		return;
	}
	//回転角度
	m_rotAngle[eneNum] = atan2(m_moveSpeed[eneNum].x, m_moveSpeed[eneNum].z);

	m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);

	m_eneDir[eneNum] = m_moveSpeed[eneNum];
	m_eneDir[eneNum].Normalize();
}


//敵のリスポーン処理関数
void Enemy::EneResporn(int eneNum)
{
	if (m_enePos[eneNum].y < -1000.0f)
	{
		//撃墜サウンド
		SoundPlayBack(ShootDownSound,eneNum);

		//撃墜エフェクト再生開始。
		m_shootDownEffect[eneNum].Play();
		//撃墜エフェクトの位置を敵が落ちた位置に設定
		m_shootDownEffect[eneNum].SetPosition(m_enePos[eneNum]);
		//更新
		m_shootDownEffect[eneNum].Update();

		//ランダムでリスポーン位置を入れる
		m_enePos[eneNum] = m_ranEneResPos[rand() % RES_POS_NUM];
		if (m_stageSelectScene->GetStageNum() == STAGE2)
		{
			//ランダム関数のSEED（種）を設定
			//（これによりランダム値を本当の意味でランダムにしている）
			srand((int)time(nullptr));
			//ランダムでリスポーン位置を入れる
			m_enePos[eneNum] = m_ranEneResPos[rand() % 9];
		}
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		//ランダムでリスポーン回転を入れる
		m_rotAngle[eneNum] = m_randEneResAngle[rand() % 8];

		//位置をセット
		m_enemy[eneNum]->SetPosition(m_enePos[eneNum]);

		//回転情報をセットする
		m_rot[eneNum].SetRotation(Vector3::AxisY, m_rotAngle[eneNum]);
		m_enemy[eneNum]->SetRotation(m_rot[eneNum]);

		//キャラコンの座標にプレイヤーの座標をいれる
		m_charaCon[eneNum].SetPosition(m_enePos[eneNum]);

		//スピードを0にする
		m_moveSpeed[eneNum] = { Vector3::Zero };

		//キャラクターコントローラーを使った移動処理に変更。
		m_enePos[eneNum] = m_charaCon[eneNum].Execute(m_moveSpeed[eneNum], 1.0f);

		//落下時最後に触れた敵にポイントを与えるm_pushPlayer = 最後に押してきたプレイヤーのナンバー
		//y=5にして、5の時は落としてきたプレイヤーのスコアを+10ptするようにする。
		m_gameScene->GetPlayerAddScore(m_pushPlayer[eneNum], 5);
	}
}


//敵の摩擦処理関数
void Enemy::EneFriction(int eneNum)
{
	//摩擦力を設定する
	m_friction[eneNum] = m_moveSpeed[eneNum];
	m_friction[eneNum] *= -1.5f;

	///下のif文はステージの処理なのでステージクラスに移したい。
	//アイスステージが選択されているとき、
	if (m_stageSelectScene->GetStageNum() == STAGE3)
	{
		//摩擦を減らす
		m_friction[eneNum] /= 2.0f;
	}
	//摩擦力を加算する
	m_moveSpeed[eneNum].x += m_friction[eneNum].x * g_gameTime->GetFrameDeltaTime();
	m_moveSpeed[eneNum].z += m_friction[eneNum].z * g_gameTime->GetFrameDeltaTime();
}


//プレイヤーと敵がぶつかったときの処理関数
void Enemy::PlaAndEneClash(int eneNum)
{
	for (int plaNum = 0; plaNum < m_player->GetPlaNum(); plaNum++)
	{
		//プレイヤーと敵との距離を計算
		m_diff = m_player->GetPlaPos(plaNum) - m_enePos[eneNum];

		//距離の長さが40.0fより小さかったら、
		if (m_diff.Length() < 40.0f)
		{
			if (m_canPlaAndEneClashSoundPlayFlg[eneNum])
			{
				//衝突音4
				SoundPlayBack(PlaAndEneClashSound, eneNum);

				m_canPlaAndEneClashSoundPlayFlg[eneNum] = false;
			}

			if (m_player->GetPlaisTyazi1HanteiFlg(plaNum)) {
				m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
				m_samDir[eneNum].Normalize();
				m_moveSpeed[eneNum] = m_samDir[eneNum] * 20.0f;
			}
			if (m_player->GetPlaisTyazi2HanteiFlg(plaNum)) {

				m_samDir[eneNum] = m_eneDir[eneNum] * -1.0f + m_player->GetPlaDir(plaNum);
				m_samDir[eneNum].Normalize();
				m_moveSpeed[eneNum] = m_samDir[eneNum] * 30.0f;

			}
			//最後に押してきたプレイヤーを記録
			m_pushPlayer[eneNum] = plaNum;
		}
	}
}


//敵にかかる重力を設定する関数
void Enemy::Gravity(int eneNum)
{
	//重力の影響を与える
	m_moveSpeed[eneNum].y -= GRAVITY;
}


//ベクトルを可視化させるデバック関数
void Enemy::EneMooveSpeedDebug(int eneNum)
{
	Vector3 Dir = m_moveSpeed[eneNum];
	Dir.y = 0;
	Dir.Normalize();//大きさを位置にする
	float x = Dir.Dot(Vector3::AxisX);//X軸から何度ずれているかを入れる
	Dir.z *= -1;
	float angleX = acosf(x);//アークコサイン
	if (Dir.z < 0) {
		angleX *= -1;
	}
	//angleX -= 0.5 * PAI;
	m_arrowRot[eneNum].SetRotationY(angleX);//ｘ度だけY軸を回す
	m_skinModelRenderArrow[eneNum]->SetRotation(m_arrowRot[eneNum]);//角度を設定する
	m_arrowPos[eneNum] = m_enePos[eneNum];
	m_arrowPos[eneNum].y += 50.0f;
	m_skinModelRenderArrow[eneNum]->SetPosition(m_arrowPos[eneNum]);
	m_arrowSize.x = m_arrowSize.z = m_moveSpeed[eneNum].Length() / 10;
	m_skinModelRenderArrow[eneNum]->SetScale(m_arrowSize);
}

//サウンドを一括にまとめる関数
void Enemy::SoundPlayBack(int soundNum,int eneNum)
{
	switch (soundNum)
	{
	case ShootDownSound:
		//撃墜サウンドの初期化
		m_shootDownSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_shootDownSound[eneNum]->Init(L"Assets/sound/ShootDown.wav");
		m_shootDownSound[eneNum]->SetVolume(0.2f);
		m_shootDownSound[eneNum]->Play(false);	//偽でワンショット再生

		break;

	case FallSound:
		//高さが-10以下のとき再生
		if (m_enePos[eneNum].y < -10.0f && m_canFallSoundPlayFlg[eneNum])
		{
			//落下サウンドの初期化
			m_FallSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
			m_FallSound[eneNum]->Init(L"Assets/sound/Fall.wav");
			m_FallSound[eneNum]->SetVolume(0.1f);
			m_FallSound[eneNum]->Play(false);	//偽でワンショット再生

			m_canFallSoundPlayFlg[eneNum] = false;
		}
		//リスポーン位置に移動したときにフラグを復活させる
		if (m_enePos[eneNum].y == 150.0f)
		{
			m_canFallSoundPlayFlg[eneNum] = true;
		}

		break;

	case DashSound:
		//落下サウンドの初期化
		m_DashSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		//ランダム関数のSEED（種）を設定
		//（これによりランダム値を本当の意味でランダムにしている）
		srand((int)time(nullptr));
		m_randomDashSoundNum = rand() % 9;
		switch (m_randomDashSoundNum)
		{
		case 0:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash1.wav");
			break;
		case 1:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash2.wav");
			break;
		case 2:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash3.wav");
			break;
		case 3:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash4.wav");
			break;
		case 4:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash5.wav");
			break;
		case 5:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash6.wav");
			break;
		case 6:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash7.wav");
			break;
		case 7:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash8.wav");
			break;
		case 8:
			m_DashSound[eneNum]->Init(L"Assets/sound/EneDash9.wav");
			break;
		}
		m_DashSound[eneNum]->SetVolume(0.3f);
		m_DashSound[eneNum]->Play(false);	//偽でワンショット再生

		break;

	case PlaAndEneClashSound:
		//プレイヤーとプレイヤーがぶつかったときのサウンドの初期化
		m_PlaAndEneClashSound[eneNum] = NewGO<SoundSource>(PRIORITY_0, nullptr);
		m_PlaAndEneClashSound[eneNum]->Init(L"Assets/sound/Clash2.wav");
		m_PlaAndEneClashSound[eneNum]->SetVolume(0.5f);
		m_PlaAndEneClashSound[eneNum]->Play(false);	//偽でワンショット再生

		break;
	}
}


void Enemy::WindPower(int enenum)
{
	//風ステージが選択されている場合、風の影響を与える
	if (m_stageSelectScene->GetStageNum() == STAGE4)
	{


		//現在の風の向きに応じた処理
		switch (m_stage->GetWindDirection()) { //ここの()の中には、今どの向きの風なのかを保存している変数を入れる。
		case Up://下から上への風
			m_moveSpeed[enenum].z += 0.02f;
			break;
		case Down:
			m_moveSpeed[enenum].z -= 0.02f;
			break;
		case Left:
			m_moveSpeed[enenum].x -= 0.02f;
			break;
		case Right:
			m_moveSpeed[enenum].x += 0.02f;
			break;
		}

	}
}