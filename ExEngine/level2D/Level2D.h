/*!
 *@brief	レベル。
 */


#pragma once

struct CaslData;
class MapChipRender2D;
/*!
* @brief	オブジェクト名。
*/
struct Level2DObjectData {
	Vector3 position = Vector3::Zero;		//<座標。
	Quaternion rotation = Quaternion::Identity;	//!<回転。
	Vector3 scale = Vector3::One;			//!<拡大率。
	int width = 0;		//!<横幅。
	int height = 0;		//!<縦幅。
	const char* name;	//!<名前。
	/*!
	* @brief	引数で渡したオブジェクト名のオブジェクトか調べる。
	*@param[in]	objName		調べる名前。
	*@return	名前が同じ場合にtrueを返します。
	*/
	bool EqualObjectName(const char* objName)
	{
		return strcmp(objName, name) == 0;
	}
	/*!
	* @brief	名前が前方一致するか調べる。
	*/
	bool ForwardMatchName(const char* n)
	{
		auto len = strlen(n);
		auto namelen = strlen(name);
		if (len > namelen) {
			//名前が長い。不一致。
			return false;
		}
		return strncmp(n, name, len) == 0;
	}
};
/*!
*@brief	レベル。
	*/
class Level2D {
public:
	~Level2D();
	/*!
	 * @brief	レベルを初期化。
	 *@param[in]	filePath		caslファイルのファイルパス。
	 *@param[in] hookFunc				オブジェクトを作成する時の処理をフックするための関数オブジェクト。
	 *   フックしないならnullptrを指定すればよい、
	 * この関数オブジェクトがfalseを返すと、オブジェクトの情報から、
	 * 静的オブジェクトのMapChip2Dクラスのインスタンスが生成されます。
	 * オブジェクトの名前などで、プレイヤーのHPバーなどの特殊なクラスのインスタンスを生成したときに、
	 * デフォルトで作成されるMapChipクラスのインスタンスが不要な場合はtrueを返してください。
	 * 例えば、フック関数の中で、渡されたオブジェクトデータの名前のスプライトを描画するクラスのインスタンスを
	 * 生成したときに、falseを返してしまうと、同じスプライトが二つ描画されることになります。
	 */
	void Init(const char* filePath, std::function<bool(Level2DObjectData & objData)> hookFunc);
private:
	/// <summary>
	/// マップチップレンダラー2Dを追加する。
	/// </summary>
	/// <param name="caslData">Caslデータ</param>
	void AddMapChipRender2D(CaslData* caslData);
private:
	std::vector<MapChipRender2D*> m_mapChipRender2DList;		//マップチップレンダラー。
};
