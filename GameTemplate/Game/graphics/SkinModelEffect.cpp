#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//�V�F�[�_�[�K�p
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	
	switch (m_renderMode)
	{
	case enRenderMode_Normal:
		//�ʏ�`��
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		break;
	case enRenderMode_CreateSilhouette:
		//�V���G�b�g�`��
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//�V���G�b�g�p �[�x�X�e���V���X�e�[�g
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStencilState, 0);
		break;
	case enRenderMode_CreateShadowMap:
		//�V���h�E�}�b�v����
		//deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}