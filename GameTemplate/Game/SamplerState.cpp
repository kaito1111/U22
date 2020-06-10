/// <summary>
/// サンプラーステート
/// </summary>

#include "stdafx.h"
#include "SamplerState.h"

namespace myEngine {
	bool SamplerState::Create(const D3D11_SAMPLER_DESC& desc)
	{
		//一応解放
		//Release();
		//hrで作れてるかの確認
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
		//失敗
		/*
			****throw****
		descの初期化を確認して下さい。
			****throw****
		*/
		if (FAILED(hr)) {
			throw;
		}

		return true;
	}
}