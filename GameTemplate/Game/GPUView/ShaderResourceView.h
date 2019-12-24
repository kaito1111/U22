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
		/// <summary>
		/// StructuredBuffer�p��SRV���쐬
		/// </summary>
		/// <param name="structuredBuffer">�X�g���N�`���[�o�b�t�@</param>
		/// <returns>�N���G�C�g�ł��邩</returns>
		bool Create(StructuredBuffer& structuredBuffer);
		/// <summary>
		/// �e�N�X�`���p��SRV���쐬
		/// </summary>
		/// <param name="texture">�e�N�X�`��</param>
		/// <returns>�N���G�C�g�ł��邩</returns>
		bool Create(ID3D11Texture2D* texture);
		/// <summary>
		/// DDS�t�@�C������e�N�X�`����SRV���쐬
		/// </summary>
		/// <param name="fileName">�t�@�C����</param>
		/// <returns>�쐬�ł�����</returns>
		bool CreateFromDDSTextureFromFile(const wchar_t* fileName);
		/// <summary>
		/// �����I�ȊJ��
		/// </summary>
		/// <remarks>
		/// �����I�ɊJ������ꍇ�g�p
		/// </remarks>
		void Release();
	private:
		ID3D11ShaderResourceView*	m_srv = nullptr;		//SRV
		bool						m_isValid = false;		//�L���ȃf�[�^�H
	};
}


