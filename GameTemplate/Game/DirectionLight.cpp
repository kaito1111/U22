#include "stdafx.h"
#include "DirectionLight.h"
#include "DirectionLight.h"

DirectionLight::DirectionLight()
{
	//���C�g�p�̒萔�o�b�t�@�쐬
	CreateLightCB();
	//���s���C�g�̌����ƐF�̏�����
	InitDirectionLight();
}

DirectionLight::~DirectionLight()
{
	Release();
}

void DirectionLight::Release()
{
	//���C�g�p�̒萔�o�b�t�@���
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
}

void DirectionLight::CreateLightCB()
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(SDirectionLight);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}

void DirectionLight::InitDirectionLight()
{
	m_dirLight.direction[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color[0] = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_dirLight.direction[1] = { -1.0f, 0.0f, 0.0f, 0.0f };
	//m_dirLight.color[1] = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_dirLight.color[1] = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_dirLight.direction[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	//m_dirLight.color[2] = { 1.0f, 0.0f, 1.0f, 1.0f };
	m_dirLight.color[2] = { 0.0f, 0.0f, 0.0f, 1.0f };

	m_dirLight.direction[3] = { 1.0f, 0.0f, -1.0f, 0.0f };
	//m_dirLight.color[3] = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_dirLight.color[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void DirectionLight::Render()
{
	//�f�o�R���̎擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	//���C�g�p�̒萔�o�b�t�@�̍X�V
	dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);

	//���C�g�p�̒萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�
	dc->PSSetConstantBuffers(0, 1, &m_lightCb);
}

void DirectionLight::Update()
{
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
		qRot.Multiply(m_dirLight.direction[i]);
	}
}