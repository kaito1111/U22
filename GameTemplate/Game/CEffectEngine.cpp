#include "stdafx.h"
#include "CEffectEngine.h"

namespace myEngine {

	CEffectEngine::CEffectEngine()
	{
	}

	CEffectEngine::~CEffectEngine()
	{
		//���
		Release();
	}

	void CEffectEngine::Release()
	{
		if (m_effekseerRenderer == nullptr) {
			//�C���X�^���X�j��
			m_effekseerRenderer->Destroy();
		}
		if (m_manager == nullptr) {
			//�C���X�^���X�j��
			m_manager->Destroy();
		}
	}

	void CEffectEngine::Init()
	{
		//�����_���[���������B
		m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
			g_graphicsEngine->GetD3DDevice(),					//D3D�f�o�C�X�B
			g_graphicsEngine->GetD3DDeviceContext(),			//D3D�f�o�C�X�R���e�L�X�g�B	
			2000												//�|���̍ő吔�B
		);
		//�G�t�F�N�g�}�l�[�W�����������B
		m_manager = Effekseer::Manager::Create(10000);

		// �`��p�C���X�^���X����`��@�\��ݒ�
		m_manager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
		m_manager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
		m_manager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
		m_manager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
		m_manager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

		// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
		// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
		m_manager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
		m_manager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
	}

	void CEffectEngine::Update()
	{
		//�G�t�F�N�T�[�̃J�����ݒ�
		m_effekseerRenderer->SetCameraMatrix(g_camera3D.GetViewMatrix());
		m_effekseerRenderer->SetProjectionMatrix(g_camera3D.GetViewMatrix());
		//�X�V
		m_manager->Update();
	}

	void CEffectEngine::Render()
	{
		//g_camera����J�����s��ƃv���W�F�N�V�����s����R�s�[
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);

		//�J�����s��ƃv���W�F�N�V�����s������_�ɐݒ�B
		//tkEngine���̓J�����̒����ɏo��悤�ɂȂ��Ă���K�X
		EffectEngineObj().GetEffekseerRenderer()->SetCameraMatrix(efCameraMat);
		EffectEngineObj().GetEffekseerRenderer()->SetProjectionMatrix(efProjMat);

		//Effekseer���X�V�B
		EffectEngineObj().GetEffekseerManager()->Update();

		//�G�t�F�N�g�`��p�̃����_�����O�ݒ�B
		m_effekseerRenderer->BeginRendering();
		//�G�t�F�N�g�̕`�揈��
		m_manager->Draw();
		//�����_�����O�ݒ�����Ƃɖ߂��B
		m_effekseerRenderer->EndRendering();
	}

	Effekseer::Effect* CEffectEngine::CreateEffect(const wchar_t* filepath)
	{
		//�쐬
		return Effekseer::Effect::Create(m_manager, (const EFK_CHAR*)filepath);
	}

	Effekseer::Handle CEffectEngine::Play(Effekseer::Effect* effect)
	{
		//Effect��Update�Ń��[���h���W�͌v�Z
		return m_manager->Play(effect, 0, 0, 0);
	}
}