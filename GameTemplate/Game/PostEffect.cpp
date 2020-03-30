#include "stdafx.h"
#include "PostEffect.h"

namespace myEngine {
	PostEffect::PostEffect()
	{
		//�t���X�N���[���`��̂��߂̎l�p�`�v���~�e�B�u���������B
		InitFullScreenQuadPrimitive();
	}

	PostEffect::~PostEffect()
	{
		if (m_vertexBuffer != nullptr) {
			m_vertexBuffer->Release();
		}
	}

	void PostEffect::Update()
	{
		m_bloom.Update();
	}

	void PostEffect::Draw()
	{
		m_bloom.Draw(*this);
	}

	struct SVertex
	{
		float position[4];		//�e�N�X�`���𒣂�t���钸�_���W
		float uv[2];			//UV���W�B�e�N�X�`�����W
	};

	void PostEffect::InitFullScreenQuadPrimitive()
	{
		//���_�o�b�t�@��������
		SVertex vertex[4] = {
			//���_1(����
			{
				//���_���W
				-1.0f, -1.0f, 0.0f, 1.0f,
				//�e�N�X�`�����W
				0.0f, 1.0f
			},
			//���_2(�E��
			{
				//���_���W
				1.0f, -1.0f, 0.0f, 1.0f,
				//�e�N�X�`�����W
				1.0f, 1.0f
			},
			//���_3(����
			{
				//���_���W
				-1.0f, 1.0f, 0.0f, 1.0f,
				//�e�N�X�`�����W
				0.0f, 0.0f
			},
			//���_4(�E��
			{
				//���_���W
				1.0f, 1.0f, 0.0f, 1.0f,
				//�e�N�X�`�����W
				1.0f, 0.0f
			}
		};

		//�o�b�t�@�[�̐ݒ�
		D3D11_BUFFER_DESC bd;
		//0��������������
		ZeroMemory(&bd, sizeof(bd));
		//�o�b�t�@�[�̓ǂݍ��݁A�������ݐݒ�
		bd.Usage = D3D11_USAGE_DEFAULT;
		//���_�o�b�t�@�̃T�C�Y
		bd.ByteWidth = sizeof(vertex);
		//�Ȃ�̃o�b�t�@�Ƃ��ēo�^����񂶂�H�@���_�o�b�t�@����
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//�T�u���\�[�X�Ńf�[�^�̏�����
		//�Ȃ�ł��Ă�̂��킩��Ȃ��BSample�̕���NULL�n���Ă��G���[�͂ł񂩂����B
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertex;

		//���_�o�b�t�@�̍쐬
		g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	}

	void PostEffect::DrawFullScreenQuadPrimitive(Shader& vsShader, Shader& psShader)
	{
		auto dc = g_graphicsEngine->GetD3DDeviceContext();
		//�g�|���W�[(�ǂ�����ĕ`�悷�邩�I�ȁj���g���C�A���O���X�g���b�v�ɐݒ�
		dc->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//���_�T�C�Y
		unsigned int vertexSize = sizeof(SVertex);
		//�Ԋu
		unsigned int offset = 0;
		//�P�x���o�p�̃V�F�[�_�[�ݒ�
		dc->VSSetShader(
			(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
		);
		dc->PSSetShader(
			(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
		);
		//���C�A�E�g�ݒ�
		dc->IASetInputLayout(vsShader.GetInputLayout());
		//���_�o�b�t�@�̐ݒ�
		dc->IAGetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
		//�`��
		dc->Draw(4, 0);
	}
}