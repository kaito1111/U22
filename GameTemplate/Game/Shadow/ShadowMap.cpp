#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	Init();
	////�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g���쐬
	////�𑜓x��2048*2048
	////�e�N�X�`���̃t�H�[�}�b�g��R�����̂�32bit���������_�^�B
	//m_shadowMapRT.Create(
	//	2048,
	//	2048,
	//	DXGI_FORMAT_R32_FLOAT
	//);

	//m_lightCameraPosition = { -358.0f, 2000.0, 0.0f };
	//m_lightCameraTarget = CVector3::Zero();
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
	//���炭�������������獶�V�t�g�Ƃ����Ă�񂾂낤�B
	int wh[][2] = {
		//���̂܂܂͈̔�
		{shadowMapWidth, shadowMapHeight},
		//�c�����V�t�g1�Ȃ̂ŏc�̒l��������
		{shadowMapWidth, shadowMapHeight >> 1},
		//�������V�t�g1�A�c�����V�t�g1�Ȃ̂ŗ���������
		{shadowMapWidth >> 1, shadowMapHeight >> 1}
	};

	//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�������쐬
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		m_KshadowMapRT[i].Create(
			wh[i][0],
			wh[i][1],
			DXGI_FORMAT_R32_FLOAT
		);
		//pivot�I�ȓz�H
		m_shadowCbEntity.texOffset[i].x = 1.0f / wh[i][0];
		m_shadowCbEntity.texOffset[i].y = 1.0f / wh[i][1];
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
		lightViewUp.Cross(lightViewUp, lightViewForward);
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
		2000 * 0.8f,
		2000 * 1.6f,
		2000 * 3.6f
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
		float halfViewAngle = g_camera3D.GetViewAngle() *0.5f;
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

			//�r���[�̉�]
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

		//���C�g���W���ɕϊ�
		m_LVPMatrix[i] = mLightView * proj;
		//�G���e�B�e�B�ɐς�
		m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
		//�ǂ��܂ŉe�𗎂Ƃ���(���킫�킾�ƕςȋ��E����������̂ŏ������߂�B)
		//m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ * 0.8f;
		//���̋ߕ��ʂ͍��̉����ʁB
		nearPlaneZ = farPlaneZ;
	}
}



//void ShadowMap::Update()
//{
//	//UpdateFromLightTarget(m_lightCameraPosition, m_lightCameraTarget);
//}

void ShadowMap::UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir)
{
	////���C�g�̕����ɂ���āA���C�g�̏���������߂�B
	//CVector3 lightCameraUpAxis;
	////fabsf()�͂�������Βl
	//if (fabsf(lightDir.y) > 0.99998f) {
	//	//�قڐ^��or�^���������Ă���̂ŁA{ 1,0,0 }��������ɂ���B
	//	lightCameraUpAxis = CVector3::AxisX();
	//}
	//else {
	//	//�^��or�^�������Ă��Ȃ��̂ŁA{ 0,1,0 }��������ɂ���B
	//	lightCameraUpAxis = CVector3::AxisY();
	//}
	////�J�����̏���������肵���̂ŁA���C�g�r���[�s����v�Z
	//m_lightViewMatrix.MakeLookAt(
	//	m_lightCameraPosition,
	//	m_lightCameraTarget,
	//	lightCameraUpAxis
	//);

	////���C�g�v���W�F�N�V�����s����쐬����B
	////���z������̉e�𗎂Ƃ������Ȃ�A���s���e�s����쐬����B
	////������w,h��������ƃV���h�E�}�b�v�͈̔͂��ς��I
	//m_lightProjMatirx.MakeOrthoProjectionMatrix(
	//	5000,
	//	5000,
	//	0.1f,
	//	5000.0f
	//);
}

void ShadowMap::UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	////���C�g�̕������v�Z
	//auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	//if (lightDir.Length() < 0.00001f) {
	//	//���_�ƒ����_�߂���
	//	//���炭�o�O�Ȃ̂ŃN���b�V��
	//	std::abort();
	//}
	////���K��
	//lightDir.Normalize();
	////�e�����Ƃ�����
	//UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::UpdateFromLightTarget()
{
	////���C�g�̕������v�Z
	//auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	//if (lightDir.Length() < 0.00001f) {
	//	//���_�ƒ����_�߂���
	//	//���炭�o�O�Ȃ̂ŃN���b�V��
	//	std::abort();
	//}
	////���K��
	//lightDir.Normalize();
	////�e�����Ƃ�����
	//UpdateFromLightDirection(m_lightCameraPosition, lightDir);
}

void ShadowMap::BiginRender()
{
	//�f�o�R���擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();
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

void ShadowMap::RenderToShadowMap()
{
	{
		//auto dc = g_graphicsEngine->GetD3DDeviceContext();
		////�����_�����O�^�[�Q�b�g��؂�ւ��B
		//ID3D11RenderTargetView* rts[] = {
		//	//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g
		//	m_shadowMapRT.GetRenderTargetView()
		//};
		//////�[�x�X�e���V���r���[�̐ݒ�
		//dc->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
		//////�r���[�|�[�g�̐ݒ�
		////dc->RSSetViewports(1, m_shadowMapRT.GetViewport());
		//////�V���h�E�}�b�v���N���A
		//////�P�ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ�
		////float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		////m_shadowMapRT.ClearRenderTarget(clearColor);

		//////�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O
		////for (auto& caster : m_shadowCasters) {
		////	//�o�^����Ă���V���h�E�L���X�^�[�̐�������
		////	//�V���h�E�}�b�v�`��
		////	caster->Draw(
		////		m_lightViewMatrix,
		////		m_lightProjMatirx,
		////		enRenderMode_CreateShadowMap
		////	);
		////}
		//////�L���X�^�[���N���A
		////m_shadowCasters.clear();
	}
	//�f�o�R���擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

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
			caster->Draw(m_LVPMatrix[i], CMatrix::Identity(), enRenderMode_CreateShadowMap);
		}
	}
	//�L���X�^�[���폜
	m_shadowCasters.clear();
}

void ShadowMap::EndRender()
{
	//�f�o�C�X�R���e�L�X�g�̎擾
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

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

