/// <summary>
/// �����_�����O�R���e�L�X�g
/// �`�揈���̂��߂̃f�[�^�̏W����
/// </summary>

#pragma once

/*
�������
DrawIndexed
Draw
UpdateSubresource
VSSetConstantBuffer
PSSetConstantBuffer
PSSetShaderResource
PSSetShader
VSSetShader
*/
#include "graphics/Shader.h"
#include "GPUBuffer/VertexBuffer.h"
#include "GPUBuffer/IndexBuffer.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "ConstantBuffer.h"
#include "GPUView/ShaderResourceView.h"
#include "GPUView/UnorderedAccessView.h"

namespace myEngine {
	class VertexBuffer;

	class RenderContext
	{
	public:
		RenderContext();
		~RenderContext();
		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="pD3DDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
		/// <param name="pD3DDeferredDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
		void Init(ID3D11DeviceContext* pD3DDeviceContext, ID3D11DeviceContext* pD3DDeferredDeviceContext);
		/// <summary>
		/// ���_�o�b�t�@�̐ݒ�
		/// </summary>
		/// <param name="vertexBuffer">���_�o�b�t�@</param>
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			//UINT = �l�̎���͈͂��{��int�^
			UINT offset = 0;
			//���_�o�b�t�@�̃X�g���C�h�̎擾
			UINT stride = vertexBuffer.GetStride();
		}
		/// <summary>
		/// �C���f�b�N�X�o�b�t�@
		/// </summary>
		/// <param name="indexBuffer">�C���f�b�N�X�o�b�t�@</param>
		void IASetIndexBuffer(IndexBuffer& indexBuffer)
		{
			//�C���f�b�N�X�̌^
			IndexBuffer::EnIndexType type = indexBuffer.GetIndexType();
			m_pD3DDeviceContext->IASetIndexBuffer(
				indexBuffer.GetBody(),
				//�������Z�q exp1 ? exp2:exp3	exp���^�Ȃ�exp2���A�U�Ȃ�exp3��
				//16�^����Ȃ��Ȃ�32�^���t�H�[�}�b�g(������
				type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
				0
			);
		}
		/// <summary>
		/// �v���~�e�B�u�̃g�|���W�[��ݒ�
		/// </summary>
		/// <param name="topology">�g�|���W�[</param>
		void IASetPrimitiveToporogy(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			m_pD3DDeviceContext->IASetPrimitiveTopology(topology);
		}
		/// <summary>
		/// VS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�
		/// </summary>
		/// <param name="slotNo">�X���b�g�ԍ�</param>
		/// <param name="cb">�萔�o�b�t�@</param>
		void VSSetConstantBuffer(
			UINT slotNo,
			ConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/// <summary>
		/// VS�X�e�[�W��SRV��ݒ�
		/// </summary>
		/// <param name="slotNo">�X���b�g�ԍ�</param>
		/// <param name="srv">SRV</param>
		void VSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			m_pD3DDeviceContext->VSGetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/// <summary>
		/// VS�X�e�[�W����SRV���O��
		/// </summary>
		/// <param name="slotNo">�X���b�g�ԍ�</param>
		void VSUnsetShaderResource(int slotNo)
		{
			ID3D11ShaderResourceView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->VSSetShaderResources(slotNo, 1, view);
		}
		/// <summary>
		/// PS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�
		/// </summary>
		/// <param name="slotNo">�X���b�g�ԍ�</param>
		/// <param name="cb">�萔�o�b�t�@</param>
		void PSSetConstantBuffer(
			UINT slotNo,
			ConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
	private:
		ID3D11DeviceContext*			m_pD3DDeviceContext = nullptr;
	};
}


