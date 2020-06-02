#pragma once

#include "Bloom/Bloom.h"

namespace myEngine {
	/// <summary>
	/// ポストエフェクト
	/// </summary>
	class PostEffect 
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		PostEffect();
		/// <summary>
		/// デストラクタ
		/// </summary>
		~PostEffect();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
		/// <summary>
		/// フルスクリーン描画
		/// <para>設定したいVS,PSをおくる</para>
		/// </summary>
		/// <param name="vs">頂点シェーダー</param>
		/// <param name="ps">ピクセルシェーダー</param>
		void DrawFullScreenQuadPrimitive(Shader& vsShader, Shader& psShader);
	private:
		/// <summary>
		/// フルスクリーン描画用四角形プリミティブ
		/// </summary>
		void InitFullScreenQuadPrimitive();
	private:
		Bloom  m_bloom;								//ブルーム
		ID3D11Buffer* m_vertexBuffer = nullptr;		//頂点バッファ
		ID3D11InputLayout* m_inputLayout = nullptr;	//入力レイアウト
	};

}

