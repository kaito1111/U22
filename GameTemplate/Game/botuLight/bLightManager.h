/// <summary>
/// ���C�g�̊Ǘ���
/// </summary>

#pragma once

#include "bLight.h"
#include "GPUBuffer/StructuredBuffer.h"
#include "GPUBuffer/ConstantBuffer.h"

namespace myEngine {
	//�f�B���N�V�������C�g
	class DirectionLight;
	//���C�g�̊��N���X
	class LightBase;
	/// <summary>
	/// ���C�g�̊Ǘ���
	/// </summary>
	class LightManager
	{
	public:
		LightManager();
		~LightManager();
	public:
		/// <summary>
		/// ������
		/// </summary>
		void Init();
		/// <summary>
		/// ���C�g�����X�g�ɒǉ�
		/// </summary>
		/// <param name="light">�ǉ����郉�C�g</param>
		void AddLight(LightBase* light);
		/// <summary>
		/// ���C�g�����X�g���珜�O
		/// </summary>
		/// <param name="light">���O���郉�C�g</param>
		void RemoveLight(LightBase* light);
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		/// <summary>
		/// ���C�g�̃p�����[�^�[��GPU�ɑ��M�B
		/// </summary>
		void SendLightParamToGPU();
		/// <summary>
		/// �`��I��
		/// </summary>
		void EndRender();
	private:
		/// <summary>
		/// �f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@�[��������
		/// <para>LightManager���ł����g���ĂȂ��̂�private</para>
		/// </summary>
		void InitDirectionLightStructuredBuffer();
	private:
		static const int MAX_DIRECTION_LIGHT = 8;		//�f�B���N�V�������C�g�̍ő��
		/// <summary>
		/// ���C�g�̊�{���B
		/// �ς�����Shader�����ς��邱�ƁB
		/// </summary>
		struct SLightParam {
			CVector3 eyePos;			//���_�̈ʒu
			int numDirectionLight;		//�f�B���N�V�������C�g�̐�
		};
	private:
		SLightParam							m_lightParam;								//���C�g�̊�Ճp�����[�^�[	
		ConstantBuffer						m_lightParamCB;								//GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�萔�o�b�t�@
		//�f�B���N�V�������C�g//
		std::list<DirectionLight*>			m_directionLights;							//�f�B���N�V�������C�g�̃��X�g
		StructuredBuffer					m_directionLightSB;							//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@�[
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];	//�f�B���N�V�������C�g�̃p�����[�^�[

	};
}
