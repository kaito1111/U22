/// <summary>
/// �G�t�F�N�g�̊Ǘ���
/// �G�t�F�N�T�[���̊֐������b�v
/// </summary>

#pragma once
#include "Noncopyable.h"
#include "ResourceManager.h";

namespace myEngine {
	//�G�t�F�N�g�p�̃��\�[�X�}�l�[�W���[
	using CEffectResourceManager = TResourceManager<Effekseer::Effect>;
	class CEffectEngine : Noncopyable
	{
	public:
		CEffectEngine();
		~CEffectEngine();
		/// <summary>
		/// ���
		/// </summary>
		void Release();
		/// <summary>
		/// ������
		/// </summary>
		void Init();
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// �`��
		/// </summary>
		void Render();
		/// <summary>
		/// �G�t�F�N�g���쐬�Bwraper
		/// </summary>
		/// <param name="filepath">�G�t�F�N�g�̃t�@�C���p�X</param>
		/// <returns></returns>
		Effekseer::Effect* CreateEffect(const wchar_t* filepath);
		/// <summary>
		/// �G�t�F�N�g�̍Đ��Bwraper
		/// <para>Effect��Update�ō��W���̕ϊ��͂��邱�ƁB</para>
		/// </summary>
		/// <param name="effet">�Đ�����G�t�F�N�g</param>
		/// <returns>�G�t�F�N�g�̃n���h��</returns>
		Effekseer::Handle Play(Effekseer::Effect* effet);
		/// <summary>
		/// �G�t�F�N�g�̍Đ����~�B
		/// </summary>
		/// <param name="handle">�G�t�F�N�g�̃n���h��</param>
		void Stop(Effekseer::Handle handle);
		/// <summary>
		/// �G�t�F�N�T�[�̃}�l�[�W���[�擾�B
		/// </summary>
		/// <remarks>
		/// �A�h���X�ƃ|�C���^�ǂ������g���̂Ń_�u���|�C���^��
		/// </remarks>
		/// <returns></returns>
		Effekseer::Manager*& GetEffekseerManager() 
		{
			return *&m_manager;
		}
		/// <summary>
		/// �G�t�F�N�T�[�̃����_���[�擾�B
		/// </summary>
		/// <returns></returns>
		EffekseerRenderer::Renderer*& GetEffekseerRenderer() 
		{
			return *&m_effekseerRenderer;
		}
		/// <summary>
		/// �G�t�F�N�g���\�[�X�}�l�[�W���[�̎擾�B
		/// </summary>
		/// <returns></returns>
		CEffectResourceManager& GetEffectResourceManager()
		{
			return m_effectResourceManager;
		}
	private:
		EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;			//�G�t�F�N�T�[�����_�[
		Effekseer::Manager* m_manager = nullptr;							//�G�t�F�N�g�}�l�W���[
		CEffectResourceManager m_effectResourceManager;						//�G�t�F�N�g���\�[�X�}�l�W���[
	};
}

