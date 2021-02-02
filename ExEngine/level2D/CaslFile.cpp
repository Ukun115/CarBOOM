#include "stdafx.h"
//#include "../../GameTemplate/Game/stdafx.h"
#include "CaslFile.h"
#include <string>

void CaslFile::Load(const char* filePath)
{
	auto fp = fopen(filePath, "rb");
	//ファイル読み込めなかったら。
	if (fp == nullptr) {
		return;
	}
	//画像の数を取得。
	m_numLevel = ReadInteger(fp);
	for (int i = 0; i < m_numLevel; i++)
	{

		auto levelObject = std::make_unique<Level2DObject>();
		//std::unique_ptr<Level2DObject> levelObject;
		//レベルファイルに保存してあるのは
		//以下全てchar型で保存してある、一つ一つに(,)で区切りがしてある。
		//名前の長さ(int)、名前(char)
		//ファイルパスの長さ(int)、ファイルパス(char)
		//座標x,y(float)
		//画像の大きさx,y(int)
		//レイヤー優先度x,y(int)
		//スケール倍率x,y(float)
		//画像の名前の長さを取得。
		int nameCount = ReadInteger(fp);
		//画像の名前を取得
		levelObject.get()->name = std::make_unique<char[]>(nameCount + 1);
		fread(levelObject.get()->name.get(), nameCount, 1, fp);
		ReadOnlyOneCharacter(fp);

		int fileNameCount = ReadInteger(fp);
		//画像の名前を取得
		levelObject.get()->fileName = std::make_unique<char[]>(fileNameCount + 1);
		fread(levelObject.get()->fileName.get(), fileNameCount, 1, fp);
		ReadOnlyOneCharacter(fp);

		//座標を取得。
		levelObject.get()->position.x = ReadDecimal(fp);
		levelObject.get()->position.y = ReadDecimal(fp);

		//幅と高さを取得。
		levelObject.get()->width = ReadInteger(fp);
		levelObject.get()->height = ReadInteger(fp);

		//レイヤー優先度を取得。
		levelObject.get()->numberLayer = ReadInteger(fp);

		//大きさの倍率を取得。
		levelObject.get()->scale.x = ReadDecimal(fp);
		levelObject.get()->scale.y = ReadDecimal(fp);

		m_levelObjectList.push_back(std::move(levelObject));
	}
	int a = 0;

}

void CaslFile::ReadOnlyOneCharacter(FILE* file)
{
	char a;
	fread(&a, 1, 1, file);
}

int CaslFile::ReadInteger(FILE* file)
{
	std::string number;
	while (true)
	{
		char c;
		fread(&c, 1, 1, file);
		if (c != ',' && c != '\n')
		{
			number += c;
		}
		else {
			break;
		}
	}
	//string型をint型に変換する。
	return atoi(number.c_str());
}

float CaslFile::ReadDecimal(FILE* file)
{
	std::string number;
	while (true)
	{
		char c;
		fread(&c, 1, 1, file);
		if (c != ',' && c != '\n')
		{
			number += c;
		}
		else {
			break;
		}
	}
	//string型をfloat型に変換する。
	return atof(number.c_str());
}

Level2DObject* CaslFile::Find(const char* name)
{
	int number = m_levelObjectList.size();
	for (int i = 0; i < number; i++)
	{
		if (strncmp(name, m_levelObjectList[i].get()->name.get(), strlen(m_levelObjectList[i].get()->name.get())) == 0)
		{
			return m_levelObjectList[i].get();
		}
	}
	return nullptr;
}

std::vector<Level2DObject*>& CaslFile::Finds(const char* name)
{
	int number = m_levelObjectList.size();
	m_specificlevelObjectList.clear();
	for (int i = 0; i < number; i++)
	{
		if (strncmp(name, m_levelObjectList[i].get()->name.get(), strlen(m_levelObjectList[i].get()->name.get())) == 0)
		{
			m_specificlevelObjectList.push_back(m_levelObjectList[i].get());
		}
	}
	return m_specificlevelObjectList;
}
