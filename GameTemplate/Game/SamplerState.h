/// <summary>
/// サンプラーステート
/// </summary>

#pragma once

namespace myEngine {

	class SamplerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		SamplerState()
		{
		}
		/// <summary>
		/// デストラクタ
		/// </summary>
		~SamplerState()
		{
			Release();
		}
		/// <summary>
		/// 解放
		/// </summary>
		void Release()
		{
			//auto a = m_samplerState;
			if (m_samplerState != nullptr) {
				m_samplerState->Release();
				m_samplerState = nullptr;
			}
		}
		/// <summary>
		/// サンプラーステート作成
		/// </summary>
		/// <param name="desc">初期化データー</param>
		/// <returns></returns>
		bool Create(const D3D11_SAMPLER_DESC& desc);
		/// <summary>
		/// サンプラーステートを取得
		/// </summary>
		/// <returns></returns>
		ID3D11SamplerState*& GetBody()
		{
			return m_samplerState;
		}
	private:
		ID3D11SamplerState*		m_samplerState = nullptr;	//サンプラーステート

	};

}

