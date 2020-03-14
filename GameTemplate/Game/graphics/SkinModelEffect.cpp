#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//シェーダー適用
	
	
	switch (m_renderMode)
	{
	//通常描画
	case enRenderMode_Normal:
		//頂点シェーダーの設定
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		//ピクセルシェーダーの設定
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		//テクスチャの設定
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		//ID3D11ShaderResourceView* srvArray[] = {
		//	m_albedoTex,
		//	g_graphicsEngine->GetShadowMap()->GetShadowMapSRV()
		//};
		//deviceContext->PSSetShaderResources(0,2,srvArray);
		break;
	//シルエット描画
	case enRenderMode_CreateSilhouette:
		//頂点シェーダーの設定
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		//ピクセルシェーダーの設定
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//シルエット用 深度ステンシルステート
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStencilState, 0);
		//シェーダーリソースのセット
		deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		break;
	case enRenderMode_CreateShadowMap:
		//シャドウマップ生成
		//シャドウマップ用の頂点シェーダーをセット
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		//シャドウマップ用のピクセルシェーダーをセット
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}