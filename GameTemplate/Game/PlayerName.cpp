///<<summary>
///画面角に表示させるプレイヤー名表示処理
///</summary>


#include "stdafx.h"
#include "PlayerName.h"
#include "GameScene.h"

namespace nsCARBOOM
{
	namespace nsPlayerName
	{
		const Vector2 PLANAME1POS = { -600.0f, 310.0f };			//プレイヤー1の名前表示位置
		const Vector2 PLANAME2POS = { 400.0f, 310.0f };				//プレイヤー2の名前表示位置
		const Vector2 PLANAME3POS = { -600.0f,-290.0f };			//プレイヤー3の名前表示位置
		const Vector2 PLANAME4POS = { 400.0f,-290.0f, };			//プレイヤー4の名前表示位置
		const float FONT_SCA = { 1.0f };					//拡大率
		const float     FONT_ROT = 0.0f;			//フォントの傾き
		const Vector2   FONT_PIV = { 1.0f,1.0f };	//フォントの基点
		const float TEXT_SHADOW_OFFSET = 3.0f;
	}

	bool PlayerName::Start()
	{
		m_gameScene = FindGO<GameScene>(nsStdafx::GAMESCENE_NAME);

		//１Pの追加フラグを真に。
		m_isAddPlayerFlg[Player1] = true;

		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
			//2P～4Pの非アクティブ画像オブジェクト生成
			m_PlaNameFont[plaNum] = NewGO<FontRender>(nsStdafx::PRIORITY_0, nullptr);		//1P
			switch (plaNum)
			{
			case Player1:
				m_PlaNameFont[Player1]->Init(
					L"PLAYER1",			//テキスト
					nsPlayerName::PLANAME1POS,		//位置
					nsStdafx::RED,		//色
					nsPlayerName::FONT_ROT,			//傾き
					nsPlayerName::FONT_SCA,		//拡大率
					nsPlayerName::FONT_PIV			//基点
				);
				break;
			case Player2:
				m_PlaNameFont[Player2]->Init(
					L"PLAYER2",			//テキスト
					nsPlayerName::PLANAME2POS,		//位置
					nsStdafx::GRAY,		//色
					nsPlayerName::FONT_ROT,			//傾き
					nsPlayerName::FONT_SCA,		//拡大率
					nsPlayerName::FONT_PIV			//基点
				);
				break;
			case Player3:
				m_PlaNameFont[Player3]->Init(
					L"PLAYER3",			//テキスト
					nsPlayerName::PLANAME3POS,		//位置
					nsStdafx::GRAY,		//色
					nsPlayerName::FONT_ROT,			//傾き
					nsPlayerName::FONT_SCA,		//拡大率
					nsPlayerName::FONT_PIV			//基点
				);
				break;
			case Player4:
				m_PlaNameFont[Player4]->Init(
					L"PLAYER4",			//テキスト
					nsPlayerName::PLANAME4POS,		//位置
					nsStdafx::GRAY,		//色
					nsPlayerName::FONT_ROT,			//傾き
					nsPlayerName::FONT_SCA,		//拡大率
					nsPlayerName::FONT_PIV			//基点
				);
				break;
			}
			//文字の境界線表示
			m_PlaNameFont[plaNum]->SetShadowParam(true, nsPlayerName::TEXT_SHADOW_OFFSET, Vector4::Black);

			if (m_totalPlaNum <= plaNum)
			{
				continue;
			}
			//アクティブなプレイヤーの名前をアクティブカラーに変更
			ColorChange(plaNum);
		}

		return true;
	}

	PlayerName::~PlayerName()
	{
		for (int plaNum = Player1; plaNum < TotalPlaNum; plaNum++) {
			DeleteGO(m_PlaNameFont[plaNum]);
		}
	}

	void PlayerName::Update()
	{

	}

	//プレイヤーを追加したときにカラーチェンジ（アクティブ化）する関数
	void PlayerName::ColorChange(const int totalPlaNum)
	{
		switch (totalPlaNum)
		{
		case Player1:
			m_PlaNameFont[Player1]->SetColor(nsStdafx::RED);
			break;
		case Player2:
			m_PlaNameFont[Player2]->SetColor(nsStdafx::BLUE);
			break;
		case Player3:
			m_PlaNameFont[Player3]->SetColor(nsStdafx::YELLOW);
			break;
		case Player4:
			m_PlaNameFont[Player4]->SetColor(nsStdafx::GREEN);
			break;
		}
	}

	void PlayerName::AddPlayerFlgOn(const int totalPlaNum)
	{
		//新規プレイヤーの追加フラグを真に。
		m_isAddPlayerFlg[totalPlaNum] = true;
	}
}