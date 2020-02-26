/// <summary>
/// �f�B���N�V�������C�g
/// </summary>

#pragma once
#include "GameObject/IGameObject.h"

namespace myEngine {

	const int NUM_DIRECTION_LIG = 4;	//���s���C�g�̐� �����̒l�ς�����InitDirectionLight�����₷����

	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	struct SDirectionLight
	{
		CVector4 direction[NUM_DIRECTION_LIG];	//���C�g�̕���
		CVector4 color[NUM_DIRECTION_LIG];		//���C�g�̃J���[
		int		 active[NUM_DIRECTION_LIG];		//0�Ȃ�False, 1�Ȃ�True
	};

	/// <summary>
	/// ���C�g�̐ݒ�ƃf�B���N�V�������C�g�̏�����
	/// </summary>
	class DirectionLight : public IGameObject
	{
	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// �������
		/// </summary>
		void Release();
		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		/// <summary>
		/// �`��ݒ�
		/// </summary>
		void Render();
		/// <summary>
		/// �萔�o�b�t�@�̍쐬
		/// </summary>
		void CreateLightCB();
		/// <summary>
		/// �f�B���N�V�������C�g�̏�����
		/// </summary>
		void InitDirectionLight();
	private:
		ID3D11Buffer*	m_lightCb = nullptr;	//���C�g�̒萔�o�b�t�@
		SDirectionLight	m_dirLight;				//�f�B���N�V�������C�g
	};


}
