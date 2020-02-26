/// <summary>
/// ���C�g�̊Ǘ���
/// </summary>

#pragma once

#include "Light.h"
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
	/// <remarks>
	/// 1.���C�g�̃o�b�t�@�[�̏�����
	/// 2.���C�g�̃��X�g�Ǘ�
	/// </remarks>
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
		/// �`��ݒ�
		/// </summary>
		void Render();
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
		struct SLightParam {
			CVector3 eyePos;			//���_�̈ʒu
			int numDirectionLight;		//�f�B���N�V�������C�g�̐�
			CVector4	screenParam;	//�X�N���[���p�����[�^�[
		};
	public:
		SLightParam							m_lightParam;		//���C�g�̏��		
		ConstantBuffer						m_lightParamCB;		//GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�萔�o�b�t�@
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];	//�f�B���N�V�������C�g�̐��f�[�^
		std::list<DirectionLight*>			m_directionLights;	//�f�B���N�V�������C�g�̃��X�g
		StructuredBuffer					m_directionLightSB;	//�f�B���N�V�������C�g�̃X�g���N�`���[�o�b�t�@�[
	};
}
