#include "stdafx.h"
#include "ShadowMap.h"
#include "graphics/SkinModelShaderConst.h"

ShadowMap::ShadowMap()
{
	Init();
}

ShadowMap::~ShadowMap()
{
	Release();
}

void ShadowMap::Release()
{
	//���
	for (auto& rt : m_KshadowMapRT) {
		rt.Release();
	}
}

void ShadowMap::Init()
{
	//�ꉞ���
	Release();

	//�J�X�P�[�h�V���h�E�̃��C�g�J�����̈ʒu
	m_lightHieght = 2000.0f;

	//�J�X�P�[�h�V���h�E�}�b�v�͈̔�
	//���炭�������������獶�V�t�g
	//�����ŃV���h�E�̉𑜓x�����܂��I
	int wh[][2] = {
		//���̂܂܂͈̔�
		{shadowMapWidth, shadowMapHeight},
		//�c���E�V�t�g1�Ȃ̂ŏc�̒l��������
		{shadowMapWidth, shadowMapHeight >> 2},
		//�����E�V�t�g1�A�c���E�V�t�g1�Ȃ̂ŗ���������
		{shadowMapWidth >> 2, shadowMapHeight >> 2}
	};

	//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�������쐬
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		m_KshadowMapRT[i].Create(
			wh[i][0],
			wh[i][1],
			DXGI_FORMAT_R32_FLOAT
		);
		//pivot�I�ȓz�H
		//m_shadowCbEntity.texOffset[i].x = 1.0f / wh[i][0];
		//m_shadowCbEntity.texOffset[i].y = 1.0f / wh[i][1];
	}

	//�萔�o�b�t�@���쐬
	m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));

	//�V���h�E�}�b�v�p�T���v���[�쐬
	CD3D11_DEFAULT def;
	CD3D11_SAMPLER_DESC desc(def);

	//�e�N�X�`������`���
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//�͈͊O�͎w�肳�ꂽ�F��
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	//�͈͊O�̃J���[�ݒ�
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;

	//�T���v���[�X�e�[�g���쐬
	m_fetchShadowMapSampler.Create(desc);
	auto a = m_fetchShadowMapSampler.GetBody();
}

CVector3 ShadowMap::CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition)
{
	/*
	���̌v�Z�������Ȃ�ɐ}�ɂ������̂��J�X�P�[�h�V���h�E�̃t�@�C���̒��ɂ���̂�
	�R�[�h�̈Ӗ���������Ȃ��Ȃ����ꍇ�͂������Q�ƁB
	*/

	/*
	���C�g�̍��� = ������̒��S���W.y + ���C�g�̕��� * a
	�ꎟ�������Ȃ̂� a = �ɒ�����
	a = (���C�g�̍��� - ���_�̒��S���W.y) / ���C�g�̕���.y
	�ƂȂ�B
	*/
	auto alpha = (lightHeight - viewFrustomCenterPosition.y) / m_lightDirection.y;
	/*
	a���g���ă��C�g���W�����߂�B
	���C�g�̍��W = ������̒��S���W + ���C�g�̕��� * a
	*/
	auto lightPos = viewFrustomCenterPosition + m_lightDirection * alpha;
	//���C�g�̈ʒu
	return lightPos;
}

void ShadowMap::Update()
{
	//�V�[���������_�����O���Ă���J�������g���āA���C�g�J�����̉�]���v�Z
	//�V�[���J�����̑O�����擾
	auto cameraDir = g_camera3D.GetForward();
	//fabs = ��Βl  FLT_EPSLION��float���L�̌덷���l�����Ȃ��B
	//x,z����0�ɋ߂��Ȃ�
	if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
		//�قڐ^��������Ă�
		return;
	}

	//���C�g�r���[�s��̉�]�������v�Z
	
	//���C�g�r���[�̑O���� ������
	CVector3 lightViewForward = m_lightDirection;
	//���C�g�r���[�̏����
	CVector3 lightViewUp;
	if (fabsf(lightViewForward.y) > 0.999f) {
		//�قڐ^��
		lightViewUp.Cross(lightViewForward, CVector3::Right());
	}
	else {
		lightViewUp.Cross(lightViewForward, CVector3::Up());
	}
	//���K��
	lightViewUp.Normalize();

	//���C�g�r���[�̉�����
	CVector3 lightViewRight;
	lightViewRight.Cross(lightViewUp, lightViewForward);
	lightViewRight.Normalize();

	//���C�g�r���[�ɉ�]��ݒ肵�Ă���
	CMatrix lightViewRot;
	//���C�g�r���[�̉���ݒ�
	lightViewRot.m[0][0] = lightViewRight.x;
	lightViewRot.m[0][1] = lightViewRight.y;
	lightViewRot.m[0][2] = lightViewRight.z;
	lightViewRot.m[0][3] = 0.0f;
	//���C�g�r���[�̏��ݒ�
	lightViewRot.m[1][0] = lightViewUp.x;
	lightViewRot.m[1][1] = lightViewUp.y;
	lightViewRot.m[1][2] = lightViewUp.z;
	lightViewRot.m[1][3] = 0.0f;
	//���C�g�r���[�̑O��ݒ肷��B
	lightViewRot.m[2][0] = lightViewForward.x;
	lightViewRot.m[2][1] = lightViewForward.y;
	lightViewRot.m[2][2] = lightViewForward.z;
	lightViewRot.m[2][3] = 0.0f;

	//������𕪊�����䗦
	float shadowAreaTbl[] = {
		2000 * 0.2f,
		2000 * 0.4f,
		2000 * 0.8f
	};

	//���C�g�r���[�̍������v�Z
	float lightHeight = g_camera3D.GetTarget().y + m_lightHieght;

	//�V���h�E�̍\����
	SShadowCb shadowCB;
	//�ߕ���
	float nearPlaneZ = 0.0f;
	//������
	float farPlaneZ;
	//���C���J�����̏����
	CVector3 cameraUp;
	//�O�ςŏ�������v�Z
	cameraUp.Cross(g_camera3D.GetRight(), g_camera3D.GetForward());
	//cameraUp = g_camera3D.GetUp();

	//������𕪊�����悤�Ƀ��C�g�r���[�v���W�F�N�V�����s����v�Z
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//�����ʂ��v�Z
		farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
		//���C�g�r���[
		CMatrix mLightView = CMatrix::Identity();
		//������̕Е�����(��A��)�v�Z���Ă����̂ŃA���O���͔���
		float halfViewAngle = g_camera3D.GetViewAngle() * 0.5f;
		//�������8���_�����C�g��Ԃɕϊ�����AABB(������̒��ɂ��钼����)�����߂āA���ˉe�̕��ƍ��������߂�B
		float w, h;
		float far_z = -1.0f;
		//8���_
		CVector3 v[8];
		{
			//�וԂ��ΕԂɑ΂��ĉ��{��
			float t = tan(halfViewAngle);
			//�ߕ��ʂƉ����ʂ̏�x�N�g��
			CVector3 toUpperNear, toUpperFar;
			//�Εӂ����߂�B�J�X�P�[�h�V���h�E��toUpper.png�Q�ƁB
			//nearPlaneZ���ו�
			toUpperNear = cameraUp * t * nearPlaneZ;
			toUpperFar = cameraUp * t * farPlaneZ;
			//�A�X�y�N�g�����Z
			//���܂܂ł͂܂������O�̎�����̐��̂݌v�Z�������̂�
			//��������͏c���̏�񂪂͂��邽�߁@�ڍׂ�aspect.png���Q�ƁB
			t *= g_camera3D.GetAspect();
			//�ߕ��ʂ̒������W���v�Z
			//����8vertex.png���Q�ƁB
			auto nearPlaneCenterPos = g_camera3D.GetPosition() + cameraDir * nearPlaneZ;

			//v[0] = ������̋ߕ��ʂŉE��ɂ���l�p�`�̒��_�B
			v[0] = nearPlaneCenterPos + g_camera3D.GetRight() * t * nearPlaneZ + toUpperNear;
			//v[1] = ������̋ߕ��ʂŉE���ɂ���l�p�`�̒��_
			v[1] = v[0] - toUpperNear * 2.0f;

			//v[2] = ������̋ߕ��ʂō���ɂ���l�p�`�̒��_
			v[2] = nearPlaneCenterPos + g_camera3D.GetRight() * -t * nearPlaneZ + toUpperNear;
			//v[3] = ������̋ߕ��ʂō����ɂ���l�p�`�̒��_
			v[3] = v[2] - toUpperNear * 2.0f;

			//�����ʂ̒������W���v�Z�B
			auto farPlaneCenterPos = g_camera3D.GetPosition() + cameraDir * farPlaneZ;

			//v[4] = ������̉����ʂŉE��ɂ���l�p�`�̒��_
			v[4] = farPlaneCenterPos + g_camera3D.GetRight() * t * farPlaneZ + toUpperFar;
			//v[5] = ������̉����ʂŉE���ɂ���l�p�`�̒��_
			v[5] = v[4] - toUpperFar * 2.0f;

			//v[6] = ������̉����ʂō���ɂ���l�p�`�̒��_
			v[6] = farPlaneCenterPos + g_camera3D.GetRight() * -t * farPlaneZ + toUpperFar;
			//v[7] = ������̉����ʂō����ɂ���l�p�`�̒��_
			v[7] = v[6] - toUpperFar * 2.0f;

			//���C�g�s����쐬
			//������̐^�񒆂��v�Z�B
			auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCenterPos) * 0.5f;
			//���C�g�̈ʒu���v�Z�B
			auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);
			//CVector3 lightPos = { 0,2000,1000 };

			//���C�g�̉�]
			mLightView = lightViewRot;

			//���C�g�̈ʒu,��]
			mLightView.m[3][0] = lightPos.x;
			mLightView.m[3][1] = lightPos.y;
			mLightView.m[3][2] = lightPos.z;
			mLightView.m[3][3] = 1.0f;

			//���C�g�r���[(���C�g���W���j����
			//�t�s�񂤂�ʂ񂩂ʂ�Y��Ă���ꍇ��GameProg�ɉ������B
			mLightView.Inverse(mLightView);

			//��������\������W���_�̌v�Z���ł����̂ŁA���C�g��Ԃɕϊ����āAAABB�����߂�B
			//�ő咸�_���W
			CVector3 vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
			//�ŏ����_���W
			CVector3 vMin = { FLT_MAX,FLT_MAX ,FLT_MAX };

			//8���_�����C�g�̍��W���ɕϊ�����B
			for (auto & vInLight : v) {
				mLightView.Mul(vInLight);
				vMax.Max(vInLight);
				vMin.Min(vInLight);
			}
			//�r���[�̕��ƍ��������߂�B
			w = vMax.x - vMin.x;
			h = vMax.y - vMin.y;
			far_z = vMax.z;
		}
		//�v���W�F�N�V�����s��
		CMatrix proj;
		//�쐬
		proj.MakeOrthoProjectionMatrix(
			w,
			h,
			far_z / 100.0f,
			far_z
		);
		m_lightViewMatrix[i] = mLightView;
		m_lightProjMatirx[i] = proj;
		//���C�g���W���ɕϊ�
		m_LVPMatrix[i] = mLightView * proj;
		//�G���e�B�e�B�ɐς�
		m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
		//�ǂ��܂ŉe�𗎂Ƃ���(���킫�킾�ƕςȋ��E����������̂ŏ������߂�B)
		m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ * 0.8f;
		//���̋ߕ��ʂ͍��̉����ʁB
		nearPlaneZ = farPlaneZ;
	}
}

void ShadowMap::BiginRender()
{
	//�f�o�R���擾
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//RTV��DSV�̃o�b�N�A�b�v
	dc->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	//�r���[�|�[�g
	viewport = 1;
	//�r���[�|�[�g�̃o�b�N�A�b�v
	dc->RSGetViewports(&viewport, &oldViewports);

}

void ShadowMap::SendShadowParam()
{
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();
	//���\�[�X�X�V
	dc->UpdateSubresource(m_shadowCb.GetBody(), 0, NULL, &m_shadowCbEntity, 0, 0);
	//�萔�o�b�t�@�̐ݒ�
	dc->PSSetConstantBuffers(enSkinModelCBReg_Shadow, 1, &m_shadowCb.GetBody());

	//���\�[�X�̃Z�b�g
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		dc->PSSetShaderResources(enSkinModelCBReg_Shadow1 + i, 1, &m_KshadowMapRT[i].GetRenderTargetSRV());
	}
}

void ShadowMap::RenderToShadowMap()
{

	//�f�o�R���擾
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//�r���[�̎擾
		ID3D11RenderTargetView* rtv[]{
			m_KshadowMapRT[i].GetRenderTargetView()
		};
		ID3D11DepthStencilView* dsv[]{
			m_KshadowMapRT[i].GetDepthStensilView()
		};
		//�r���[�|�[�g���擾
		D3D11_VIEWPORT* vp[]{
			m_KshadowMapRT[i].GetViewport()
		};
		//�r���[���Z�b�g
		dc->OMSetRenderTargets(1, rtv, *dsv);
		//�r���[�|�[�g���Z�b�g
		dc->RSSetViewports(1, *vp);

		//�����_�[�^�[�Q�b�g�𔒂œh��Ԃ��B
		float ClearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_KshadowMapRT[i].ClearRenderTarget(ClearColor);

		//�V���h�E�L���X�^�[�Ƃ��ēo�^����Ă����`��
		for (auto& caster : m_shadowCasters) {
			//�����J�������W���ɕϊ��ς݂Ȃ̂Ńv���W�F�N�V�����s��͂���Ȃ��H
			caster->Draw(m_lightViewMatrix[i], m_lightProjMatirx[i], enRenderMode_CreateShadowMap);
		}
	}
	//�L���X�^�[���폜
	m_shadowCasters.clear();
}

void ShadowMap::EndRender()
{
	//�f�o�C�X�R���e�L�X�g�̎擾
	auto dc = Engine().GetGraphicsEngine().GetD3DDeviceContext();

	//���Ƃɖ߂�
	dc->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);

	//�r���[�|�[�g�����Ƃɖ߂�
	dc->RSSetViewports(viewport, &oldViewports);

	//���
	oldDepthStencilView->Release();
	oldRenderTargetView->Release();
}

