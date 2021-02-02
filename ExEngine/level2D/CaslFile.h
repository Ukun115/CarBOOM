#pragma once
#include <list>
#include <vector>
#include <cstdlib>
#include <memory>
#include <map>

struct Level2DObject
{
public:

	std::unique_ptr<char[]> name;	//名前。
	std::unique_ptr<char[]> fileName;	//ファイルのパス。
	Vector2 position = Vector2::Zero;
	int width = 0;
	int height = 0;
	int numberLayer = 0;
	Vector2 scale = Vector2::Zero;
};

class CaslFile
{
public:
	void Load(const char* filePath);
	Level2DObject* Find(const char* name);
	std::vector<Level2DObject*>& Finds(const char* name);
private:
	//1文字だけ読み込む、(,)を読み込むのに使う。
	void ReadOnlyOneCharacter(FILE* file);
	//整数を読み込む。
	int ReadInteger(FILE* file);
	//float型を読み込む。
	float ReadDecimal(FILE* file);

	std::vector<std::unique_ptr<Level2DObject>> m_levelObjectList;
	std::vector<Level2DObject*> m_specificlevelObjectList;
	int m_numLevel = 0;
};

