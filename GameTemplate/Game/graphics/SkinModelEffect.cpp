#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//�V�F�[�_�[�K�p
	
	
	switch (m_renderMode)
	{
	//�ʏ�`��
	case enRenderMode_Normal:
		//���_�V�F�[�_�[�̐ݒ�
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		//�s�N�Z���V�F�[�_�[�̐ݒ�
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		//�e�N�X�`���̐ݒ�
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		//ID3D11ShaderResourceView* srvArray[] = {
		//	m_albedoTex,
		//	g_graphicsEngine->GetShadowMap()->GetShadowMapSRV()
		//};
		//deviceContext->PSSetShaderResources(0,2,srvArray);
		break;
	//�V���G�b�g�`��
	case enRenderMode_CreateSilhouette:
		//���_�V�F�[�_�[�̐ݒ�
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		//�s�N�Z���V�F�[�_�[�̐ݒ�
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//�V���G�b�g�p �[�x�X�e���V���X�e�[�g
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStencilState, 0);
		//�V�F�[�_�[���\�[�X�̃Z�b�g
		deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		break;
	case enRenderMode_CreateShadowMap:
		//�V���h�E�}�b�v����
		//�V���h�E�}�b�v�p�̒��_�V�F�[�_�[���Z�b�g
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		//�V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�[���Z�b�g
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}