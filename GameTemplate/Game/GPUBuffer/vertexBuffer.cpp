#include "stdafx.h"
#include "vertexBuffer.h"
#include "myEngine.h"

namespace myEngine {
	VertexBuffer::VertexBuffer()
	{
	}
	VertexBuffer::~VertexBuffer()
	{
		Release();
	}
	void VertexBuffer::Release()
	{
		if (m_vertexBuffer != nullptr) {
			m_vertexBuffer->Release();
			m_vertexBuffer = nullptr;
		}
	}
	bool VertexBuffer::Create(int numVertex, int stride, const void* pSrcVertexBuffer)
	{
		//4、5回かいたのでコメントなしでわかるのでコメントないよ
		//分からない人は、他のBufferクラスのとこはコメントしっかりしてるからそこから見てね
		Release();
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = stride * numVertex;
		//ここがVERTEXBUFFERなだけ
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = pSrcVertexBuffer;

		HRESULT hr = graphicsEngine().GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
		if (FAILED(hr)) {
			return false;
		}
		//配列の間隔
		m_stride = stride;
		return true;
	}

}
