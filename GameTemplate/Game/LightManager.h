/// <summary>
/// ���C�g�}�l�[�W���[
/// </summary>
/// <remarks>
/// �O���t�B�b�N�G���W�����烉�C�g�������Ď����Ă�������������
/// �Q�Ƃœn���Ɩ{�̂��ł���̂������āA�f�B���N�V�������C�g��D3D�n�ŃG���[�ł�A
/// �|�C���^�̓O���t�B�b�N�G���W����Create���Ă�킯����Ȃ��̂Ō����I����Ȃ�
/// �ȏ�𓥂܂��č쐬
/// </remarks>

#pragma once

#include "DirectionLight.h"

namespace myEngine
{
	class LightManager : public IGameObject
	{
	public:
		/// <summary>
		/// �f�B���N�V�������C�g�̎擾
		/// </summary>
		/// <returns></returns>
		myEngine::DirectionLight& GetDirLig()
		{
			return m_dirLig;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

	private:
		myEngine::DirectionLight m_dirLig;		//�f�B���N�V�������C�g
	};
}
