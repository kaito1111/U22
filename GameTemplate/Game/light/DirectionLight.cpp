#include "stdafx.h"
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
	int bufferSize = sizeof(SDirectionLight);
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//16バイトに切り上げ
	bufferDesc.ByteWidth = Raundup(bufferSize);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	Engine().GetGraphicsEngine().GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}

void DirectionLight::InitDirectionLight()
{
	/*
	!!!!!	ライトの詳細情報を決めてる場所です								!!!!!
	!!!!!	Set系列作ってないので、ここいじってライトの情報決めてください	!!!!!
	*/

	/*
	ライトの方向
	ディレクションライトは位置情報は関係ないので向きのみになります。
	デフォルトでそれなりの位置においてます。
	*/
	m_dirLight.direction[0] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_dirLight.direction[1] = { -1.0f, 0.0f, 0.0f,1.0f };
	m_dirLight.direction[2] = { 0.0f, -1.0f, 0.0f ,1.0f };
	m_dirLight.direction[3] = { 0.0f, 0.0f, -1.0f,1.0f };

	//ライトのカラー
	m_dirLight.color[0] = { 1.1f, 1.1f, 1.1f, 1.0f };
	m_dirLight.color[1] = { 1.1f, 1.1f, 1.1f, 1.0f };
	m_dirLight.color[2] = { 1.1f, 1.1f, 1.1f, 1.0f };
	m_dirLight.color[3] = { 1.1f, 1.1f, 1.1f, 1.0f };
	//0.0f, 0.0f, 0.0f, 0.0f

	m_dirLight.eyePos = CVector3::Zero();
	
	/*
	ライトの絞り
	ここを1.0f未満にすると鏡面反射がOFFになります。
	※4本分あるけど0番目しか鏡面反射させれません※
	*/
	m_dirLight.specPow/*[0]*/ = 8.0f;
	//ここから↓のspecPowの値変えないで
	//m_dirLight.specPow[1] = 10.0f;
	//m_dirLight.specPow[2] = 10.0f;
	//m_dirLight.specPow[3] = 10.0f;

	/*
	ディレクションライトが有効か無効か
	trueにすると鏡面反射も付きます
	*/
	m_dirLight.active = true; 
}

void DirectionLight::sendLightParamToGPU()
{
	//デバコンの取得
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//視点の取得
	m_dirLight.eyePos = g_camera3D.GetPosition();
	//ライト用の定数バッファの更新
	dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);
	//ライト用の定数バッファをシェーダースロットに設定
	dc->PSSetConstantBuffers(1, 1, &m_lightCb);
}

void DirectionLight::Update()
{
	//CQuaternion qRot;
	//qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	//for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//	qRot.Multiply(m_dirLight.direction[i]);
	//}
	//if (GetAsyncKeyState('B')) {
	//	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//		m_dirLight.specPow[i] = max(0.0f, m_dirLight.specPow[i] - 0.5f);
	//	}
	//}
	//else if (GetAsyncKeyState('N')) {
	//	for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//		m_dirLight.specPow[i] = min(0.0f, m_dirLight.specPow[i] + 0.5f);
	//	}
	//}
}