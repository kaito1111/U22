/// <summary>
/// ShaderResourceView
/// </summary>

#pragma once

namespace myEngine {
	class StructuredBuffer;
	/// <summary>
	/// ShaderResourceView
	/// </summary>
	/// <remarks>
	/// �e�N�X�`����X�g���N�`���[�o�b�t�@�Ȃǂ�
	/// �V�F�[�_�[�Ŏg�p���郊�\�[�X�Ŏg�p����r���[
	/// </remarks>
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();
		bool Create(StructuredBuffer& structuredBuffer);
	};
}


