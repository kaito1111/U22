#pragma once
#include "Sprite.h"

namespace myEngine {
	class SpriteRender : public IGameObject
	{
	public:
		SpriteRender();
		~SpriteRender();
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="texFilePath">テクスチャのファイルパス</param>
		/// <param name="w">幅</param>
		/// <param name="h">高さ</param>
		void Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D);
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const CVector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns>座標</returns>
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rot">回転</param>
		void SetRotation(const CQuaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// 回転を取得
		/// </summary>
		/// <returns>回転</returns>
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="scale">スケール</param>
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// 拡大率の取得
		/// </summary>
		/// <returns>スケール</returns>
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/// <summary>
		/// ピボットの設定
		/// </summary>
		/// <param name="pivot">ピボット</param>
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
		void SetMulColor(const CVector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
	public:
		void Update() override final;
		void ForwardRender(RenderContext& rc);
		void PostRender(RenderContext& rc);
	private:
		bool m_isDraw3D = false;					//3D空間描画？
		//ID3D11ShaderResourceView m_texture;				//テクスチャ
		Sprite m_sprite;							//スプライト
		CVector3 m_position= CVector3::Zero();						//ポジション
		CQuaternion m_rotation = CQuaternion::Identity();						//回転
		CVector3 m_scale = CVector3::Zero();		//拡大率
		CVector2 m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット
	};
}


