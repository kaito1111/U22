#include "stdafx.h"
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
	int bufferSize = sizeof(SDirectionLight);
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//16�o�C�g�ɐ؂�グ
	bufferDesc.ByteWidth = Raundup(bufferSize);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);
}

void DirectionLight::InitDirectionLight()
{
	/*
	!!!!!	���C�g�̏ڍ׏������߂Ă�ꏊ�ł�								!!!!!
	!!!!!	Set�n�����ĂȂ��̂ŁA�����������ă��C�g�̏�񌈂߂Ă�������	!!!!!
	*/

	//���C�g�̕���
	//����܂肢����Ȃ��ق���������
	m_dirLight.direction[0] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_dirLight.direction[1] = { -1.0f, 0.0f, 0.0f,1.0f };
	m_dirLight.direction[2] = { 0.0f, 0.0f, 1.0f ,1.0f };
	m_dirLight.direction[3] = { 1.0f, 0.0f, -1.0f,1.0f };

	//���C�g�̃J���[
	m_dirLight.color[0] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_dirLight.color[1] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color[2] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_dirLight.color[3] = { 0.0f, 0.0f, 0.0f, 0.0f };

	//���C�g�̍i��
	m_dirLight.specPow[0] = 10.0f;
	m_dirLight.specPow[1] = 10.0f;
	m_dirLight.specPow[2] = 10.0f;
	m_dirLight.specPow[3] = 10.0f;

	//!!!!!���C�g���L����������!!!!!
	m_dirLight.active = true; 
}

void DirectionLight::Render()
{
	//�f�o�R���̎擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	//���_�̎擾
	m_dirLight.eyePos = g_camera3D.GetPosition();

	//���C�g�p�̒萔�o�b�t�@�̍X�V
	dc->UpdateSubresource(m_lightCb, 0, nullptr, &m_dirLight, 0, 0);

	//���C�g�p�̒萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�
	dc->PSSetConstantBuffers(0, 1, &m_lightCb);
}

void DirectionLight::Update()
{
	//CQuaternion qRot;
	//qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	//for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
	//	qRot.Multiply(m_dirLight.direction[i]);
	//}
	if (GetAsyncKeyState('B')) {
		for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
			m_dirLight.specPow[i] = max(0.0f, m_dirLight.specPow[i] - 0.5f);
		}
	}
	else if (GetAsyncKeyState('N')) {
		for (int i = 0; i < NUM_DIRECTION_LIG; i++) {
			m_dirLight.specPow[i] = min(0.0f, m_dirLight.specPow[i] + 0.5f);
		}
	}
}