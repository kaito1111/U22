/// <summary>
/// �T���v���[�X�e�[�g
/// </summary>

#include "stdafx.h"
#include "SamplerState.h"

namespace myEngine {
	bool SamplerState::Create(const D3D11_SAMPLER_DESC& desc)
	{
		//�ꉞ���
		//Release();
		//hr�ō��Ă邩�̊m�F
		HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
		//���s
		/*
			****throw****
		desc�̏��������m�F���ĉ������B
			****throw****
		*/
		if (FAILED(hr)) {
			throw;
		}

		return true;
	}
}