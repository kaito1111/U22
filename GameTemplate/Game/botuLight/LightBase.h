/// <summary>
/// ���C�g�̊��N���X
/// </summary>
/// <remarks>
/// ���C�g�����ꂽ�烊�X�g�ɒǉ�
/// ���C�g�������ꂽ�烊�X�g����폜
/// ����悤�Ƀ��C�g�}�l�[�W���Ɏw�����o��
/// </remarks>

#pragma once

namespace myEngine {
	class LightBase : public IGameObject
	{
	public:
		bool Start() override final;
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		LightBase::~LightBase();
	private:
		virtual bool StartSub() = 0;
	};
}

