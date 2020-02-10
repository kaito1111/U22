/// <summary>
/// �G�t�F�N�g
/// DirectX�V���Q�l�ɍ쐬
/// </summary>

#include "stdafx.h"
#include "Effect.h"

namespace myEngine {
	Effect::Effect()
	{
		//�G�t�F�N�T�[�̏�����
		g_graphicsEngine->InitEffekseer();
	}
	Effect::~Effect()
	{
		//���
		Release();
	}
	
	void Effect::Release()
	{
		if (m_handle != -1) {
			g_graphicsEngine->GetEffekseerManager()->StopEffect(m_handle);
			m_handle = -1;
		}
	}

	void Effect::Play(const wchar_t* filePath)
	{
		//�n�b�V���̍쐬
		int nameKey = Util::MakeHash(filePath);
		m_effect = GetResource(nameKey);
		if (m_effect == nullptr) {
			//�G�t�F�N�g�̍쐬
			m_effect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)filePath );
			//���[�h���s�I�I
			//�H�H�t�@�C���p�X�ԈႦ�ĂȂ��H�H
			if (m_effect == nullptr) {
				throw;
			}
			//���ꂢ��H
			RegistResource(nameKey, m_effect);
		}
		m_handle = g_graphicsEngine->GetEffekseerManager()->Play(m_effect, 0, 0, 0);
	}

	void Effect::Update()
	{
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		g_graphicsEngine->GetEffekseerRenderer()->SetCameraMatrix(efCameraMat);
		g_graphicsEngine->GetEffekseerRenderer()->SetProjectionMatrix(efProjMat);
		
		//Effekseer���X�V�B
		g_graphicsEngine->GetEffekseerManager()->Update();

		//�e�s���`
		CMatrix mTrans, mRot, mScale, mBase;
		mTrans.MakeTranslation(m_position);
		mRot.MakeRotationFromQuaternion(m_rotation);
		mScale.MakeScaling(m_scale);
		//���[���h�s��ɕϊ�
		mBase = mScale * mRot;
		mBase = mBase * mTrans;
		
		//CMatrix�������ĕϊ��ł���悤�ɂ��Ă��
		g_graphicsEngine->GetEffekseerManager()->SetBaseMatrix(m_handle, mBase);

		if (IsPlay() == false) {
			//�Đ����I��������폜
			DeleteGO(this);
		}

	}

	void Effect::PostDraw()
	{
		//�`��
		g_graphicsEngine->GetEffekseerManager()->Draw();
	}
}