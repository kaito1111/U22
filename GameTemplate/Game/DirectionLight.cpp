#include "stdafx.h"
#include "DirectionLight.h"
#include "DirectionLight.h"

DirectionLight::DirectionLight()
{
	//ライト用の定数バッファ作成
	CreateLightCB();
	//平行ライトの向きと色の初期化
	InitDirectionLight();
}

DirectionLight::~DirectionLight()
{
	Release();
}

void DirectionLight::Release()
{
	//ライト用の定数バッファ解放
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
	//デバコンの取得
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	//ライト用の定数バッファの更新
	dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);

	//ライト用の定数バッファをシェーダースロットに設定
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