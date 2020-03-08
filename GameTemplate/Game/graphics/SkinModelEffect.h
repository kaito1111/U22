#pragma once

#include "graphics/Shader.h"

/*!
*@brief	モデルエフェクト。
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<マテリアル名。
	Shader* m_pVSShader = nullptr;
	Shader* m_pPSShader = nullptr;
	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSilhouette;			//シルエット用シェーダー
	bool m_renderMode = 0;			//レンダーモード
	bool isSkining;
	ID3D11ShaderResourceView*	m_albedoTex = nullptr;
	ID3D11DepthStencilState*	m_silhouettoDepthStencilState = nullptr;

public:
	ModelEffect()
	{
		//シェーダのロード
		m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
		m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
		//ポリモーフィズム？
		m_pPSShader = &m_psShader;
		//デプスの作成
		InitDepthStensliState();
	}
	virtual ~ModelEffect()
	{
		if (m_albedoTex) {
			m_albedoTex->Release();
		}

		if (m_silhouettoDepthStencilState != nullptr) {
			m_silhouettoDepthStencilState->Release();
		}
	}
	/// <summary>
	/// 深度ステンシルステートの作成
	/// </summary>
	void InitDepthStensliState()
	{
		//デバイス取得
		auto dv = g_graphicsEngine->GetD3DDevice();
		//深度ステンシルステートの定義を設定
		D3D11_DEPTH_STENCIL_DESC desc = { 0 };
		desc.DepthEnable = true;							//Zテスト有効
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;	//ZバッファにZ値を書き込まない
		desc.DepthFunc = D3D11_COMPARISON_GREATER;			//Z値が大きければフレームバッファに書き込み
		//作成
		dv->CreateDepthStencilState(&desc, &m_silhouettoDepthStencilState);
	}

	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTex = tex;
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	/// <summary>
	/// レンダーモードの設定
	/// </summary>
	/// <param name="renderMode"></param>
	void SetRenderMode(int renderMode)
	{
		m_renderMode = renderMode;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}
	
};
/*!
*@brief
*  スキンなしモデルエフェクト。
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		isSkining = false;
	}
};
/*!
*@brief
*  スキンモデルエフェクト。
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", Shader::EnType::VS);
		
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}
};

/*!
*@brief
*  エフェクトファクトリ。
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//スキニングあり。
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//スキニングなし。
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture)
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}
};
