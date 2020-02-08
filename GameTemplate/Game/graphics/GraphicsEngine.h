#pragma once

/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */


class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/// <summary>
	/// �G�t�F�N�T�[�̏�����
	/// </summary>
	void InitEffekseer();
	/*!
	 *@brief	����B
	 */
	void Release();

	
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice() const
	{
		return m_pd3dDevice;
	}
	/// <summary>
	/// �����_�[�R���e�L�X�g�̎擾
	/// </summary>
	/// <returns></returns>
	//myEngine::RenderContext& GetRenderContext()
	//{
	//	return m_renderContext;
	//}
	/// <summary>
	/// D3D�����f�o�C�X�R���e�L�X�g�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D11DeviceContext* GetD3DImmediateDeviceContext() const
	{
		return m_pImmediateContext;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// �G�t�F�N�T�[�}�l�[�W���̎擾
	/// </summary>
	/// <returns></returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_manager;
	}
	/// <summary>
	/// �G�t�F�N�T�[�����_�[�̎擾
	/// </summary>
	/// <returns></returns>
	EffekseerRenderer::Renderer* GetEffekseerRenderer()
	{
		return m_effekseerRenderer;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;								//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;						//D3D11�f�o�C�X�B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;					//D3D11�f�o�C�X�R���e�L�X�g�B	
	ID3D11DeviceContext*	m_pImmediateContext = NULL;					//�����R���e�L�X�g
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B	
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�r���[�|�[�g
	IDXGISwapChain*			m_pSwapChain = NULL;						//�X���b�v�`�F�C���B
	ID3D11RenderTargetView* m_backBuffer = NULL;						//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;					//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;						//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;					//�f�v�X�X�e���V���r���[�B
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;			//�G�t�F�N�T�[�����_�[
	Effekseer::Manager* m_manager = nullptr;							//�G�t�F�N�g�}�l�W���[


};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��