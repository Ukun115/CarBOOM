#pragma once
#include <list>
#include <vector>

//2Dのレベルオブジェクト。
struct CaslData
{
public:

	std::unique_ptr<char[]> name;	//名前。
	std::unique_ptr<char[]> fileName;	//ファイルのパス。
	std::unique_ptr<char[]> ddsFileName;	//ddsファイルのパス。
	Vector2 position = Vector2::Zero;	//座標。
	int width = 0;		//横幅。
	int height = 0;		//縦幅。
	int numberLayer = 0;		//レイヤー優先度。
	Vector2 scale = Vector2::Zero;		//大きさ。
};

//Caslファイルを読み込む。
class CaslFile
{
public:
	/// <summary>
	/// caslファイルを読み込む。
	/// </summary>
	/// <param name="filePath">ファイルパス。</param>
	void Load(const char* filePath);
	int GetNumCaslData()
	{
		return m_caslDataList.size();
	}
	CaslData* GetCaslData(int number)
	{
		return m_caslDataList[number].get();
	}
private:
	//1文字だけ読み込む、(,)を読み込むのに使う。
	void ReadOnlyOneCharacter(FILE* file);
	//整数を読み込む。
	int ReadInteger(FILE* file);
	//float型を読み込む。
	float ReadDecimal(FILE* file);

	std::vector<std::unique_ptr<CaslData>> m_caslDataList;
	int m_numLevel = 0;
};

