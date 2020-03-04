#pragma once

class RenderTarget
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RenderTarget();

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̍쐬
	/// </summary>
	/// <param name="w">�e�N�X�`���̕�</param>
	/// <param name="h">�e�N�X�`���̍���</param>
	/// <param name="texFormat">�e�N�X�`���̃t�H�[�}�b�g</param>
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);

	/// <summary>
	/// �������
	/// </summary>
	void Release();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���̃N���A
	/// </summary>
	/// <param name="clearColor">�N���A�J���[</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���̎擾
	/// </summary>
	/// <returns>�����_�[�^�[�Q�b�g�r���[</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	/// <summary>
	/// �f�v�X�X�e���V���r���[�̎擾
	/// </summary>
	/// <returns>�f�v�X�X�e���V���r���[</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// �����_�����O�^�[�Q�b�g��SRV���擾
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}

private:
	ID3D11Texture2D*			m_renderTargetTex;		//�����_�[�^�[�Q�b�g�ƂȂ�e�N�X�`��
	ID3D11RenderTargetView*		m_renderTargetView;		//�����_�[�^�[�Q�b�g�r���[
	ID3D11RenderTargetView*		m_oldRenderTargetView;	//�o�b�N�A�b�v�p�̃����_�[�^�[�Q�b�g�r���[
	ID3D11ShaderResourceView*	m_renderTargetSRV;		//�����_�[�^�[�Q�b�g��SRV
	ID3D11Texture2D*			m_depthStencilTex;		//�f�v�X�X�e���V���ƂȂ�e�N�X�`��
	ID3D11DepthStencilView*		m_depthStencilView;		//�f�v�X�X�e���V���r���[
	ID3D11DepthStencilView*		m_oldDepthStencilView;	//�o�b�N�A�b�v�p�̃f�v�X�X�e���V���r���[
};

