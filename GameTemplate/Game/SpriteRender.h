#pragma once


class SpriteRender : public IGameObject		// コピー禁止ポリシーを継承する。
{
private:

	SpriteInitData m_spriteInitData;	//スプライトイニットデータ構造体のデータを作成
	Sprite m_sprite;					//スプライトクラスを作成


	Vector3    m_pos =  Vector3::Zero;			//位置(初期値:原点)
	Quaternion m_rot = Quaternion::Identity;	//回転(初期値:0,0,0,1)
	Vector3    m_sca = Vector3::One;			//拡大率(初期値:1倍)
	Vector4    m_mulColor = Vector4::White;		//乗算(Multiply)色(白)
							//↑詳しくはVectorクラスをみてね


	bool Start()override final;
	~SpriteRender()override final;
	void Update()override final;


public:

	//画像を初期化する関数
	void Init(const char* filepath, const float width, const float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans);
	//描画関数
	void Render(RenderContext& renderContext);


	/// <summary>
	/// セッター
	/// </summary>
	//画像の位置を設定する関数
	void SetPosition(const Vector3& pos) { m_pos = pos; }
	//画像の回転を設定する関数
	void SetRotation(const Quaternion& rot) { m_rot = rot; }
	//画像の拡大率を設定する関数
	void SetScale(const Vector3& sca) { m_sca = sca; }
	//画像の色を設定する関数
	void SetMulColor(const float& r, const float& g, const float& b, const float& a) { m_sprite.SetMulColor(r, g, b, a); }
};