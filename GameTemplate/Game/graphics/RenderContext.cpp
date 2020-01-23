#include "stdafx.h"
#include "RenderContext.h"


RenderContext::RenderContext()
{
	int i = 0;
}


RenderContext::~RenderContext()
{
}

void RenderContext::Init(ID3D11DeviceContext* pD3DDeviceContext, ID3D11DeviceContext* pD3DDeferredDeviceContext)
{
	m_pD3DImmidiateDeviceContext = pD3DDeviceContext;
	if (pD3DDeferredDeviceContext != nullptr) {
		//�f�B�t�@�[�h�R���e�L�X�g���w�肳��Ă���ꍇ�͂������B
		m_pD3DDeviceContext = pD3DDeferredDeviceContext;
	}
	else {
		m_pD3DDeviceContext = m_pD3DImmidiateDeviceContext;
	}
}
